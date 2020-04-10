#pragma once
#ifndef CONCURRENT_QUEUE_H_
#define CONCURRENT_QUEUE_H_

#include <queue>
#include <mutex>
#include <condition_variable>
using namespace std;

template <typename T>
class DTConcurrentQueue
{
public:
	DTConcurrentQueue()  = default;
	~DTConcurrentQueue() = default;

	T dequeue()
	{
		unique_lock<mutex> mutex_tmp(mutex_);
		if (pop_cv.wait(mutex_, !queue_.empty()))
		{
			auto tmp = queue_.front();
			queue_.pop();
			push_cv.notify_one();
			return tmp;
		}
	}

	void enqueue(T&& element);
	{
		unique_lock<mutex> mutex_tmp(mutex_);
	}

	bool enqueue_nowait(T&& element)
	{
		return true;
	}

private:
	queue<T> queue_;
	mutex mutex_;
	condition_variable push_cv;
	condition_variable pop_cv;
};



#endif // !CONCURRENT_QUEUE_H_

