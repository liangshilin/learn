#pragma once

#ifndef SYSTEM_THREAD_POOL_HPP_
#define SYSTEM_THREAD_POOL_HPP_

#include <deque>
#include <mutex>
#include <list>
#include <thread>
#include <condition_variable>

#define MIN_THREAD_COUNT 10
#define MAX_THREAD_COUNT 100

using namespace std;

class TaskBase
{
public:
    virtual void Run() = 0;

};

class SysThread
{
public:
	SysThread(list<SysThread*>* pool) :idel_(true), u_lock(mutex_), pool_(pool)
	{
	};

	~SysThread();

	void start(TaskBase* task)
	{
		idel_ = false;
		task_ = task;
		start_cd.notify_one();
	}

	void run()
	{
		while (true)
		{
			start_cd.wait(u_lock);
			if (stop_)
			{
				return;
			}

			task_->Run();
			delete task_;
			task_ = nullptr;
			idel_ = true;
		}
	}

	bool isIdle()
	{
		return idel_;
	}

	void stop()
	{
		stop_ = true;
		start_cd.notify_one();
	}

private:
	bool stop_;
	bool idel_;
	thread thread_;
	mutex mutex_;
	unique_lock<mutex> u_lock;
	TaskBase* task_;
	condition_variable start_cd;
	list<SysThread*>* pool_;
};

class SysThreadPool
{
public:
	SysThreadPool() :count_(MIN_THREAD_COUNT) 
	{
		first_start();
	}

	SysThreadPool(int count) :count_(count)
	{
		first_start();
	}

	~SysThreadPool()
	{
		for (auto thread : threads)
		{
			thread->stop();
		}
	}

	void push_back(TaskBase* task)
	{
		if (nullptr == task)
		{
			return;
		}

		{
			lock_guard<mutex> lock_(tasks_mutex);			
			tasks.push_back(task);
		}
		task_cd.notify_one();
	}

	void push_front(TaskBase* task)
	{
		if (nullptr == task)
		{
			return;
		}

		{
			lock_guard<mutex> lock_(tasks_mutex);
			tasks.push_front(task);
		}
	}

private:
	void first_start()
	{
		for (int i = 0; i < MIN_THREAD_COUNT; i++)
		{
			threads.push_back(new SysThread(&threads));
		}
	}

	void start()
	{
		while (true)
		{
			unique_lock<mutex> lock_(tasks_mutex);
			task_cd.wait(lock_, tasks.size() > 0);

			for (auto& thread : threads)
			{
				if (thread->isIdle())
				{
					thread->start(tasks.front());
					tasks.pop_front();
				}
				break;
			}
		}
	}

private:
	int count_;
	deque<TaskBase*> tasks;
	mutex tasks_mutex;
	list<SysThread*> threads;
	condition_variable task_cd;
};



#endif // !SYSTEM_THREAD_POOL_HPP_
