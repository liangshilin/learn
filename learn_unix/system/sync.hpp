#pragma once
#ifndef SYSTEM_SYNC_HPP_
#define SYSTEM_SYNC_HPP_

#include <mutex>

using namespace std;

class SysSync
{
public:
	SysSync();
	virtual ~SysSync();

	void reader1()
	{
		door_mutex.lock();
		r_mutex.lock();
		r_count++;

		if (r_count == 1)
		{
			resource_mutex.lock();
		}
		r_mutex.unlock();
		door_mutex.unlock();

		//reading

		r_mutex.lock();
		r_count--;
		if (r_count == 0)
		{
			resource_mutex.unlock();
		}
		r_mutex.unlock();
	}

	void writer1()
	{
		door_mutex.lock();
		resource_mutex.lock();

		//writer...

		resource_mutex.unlock();
		door_mutex.unlock();
	}

	void reader2()
	{
		door_mutex.lock();
		r_mutex.lock();
		if (r_count == 0)
		{
			resource_mutex.lock();
		}

		r_count++;
		r_mutex.unlock();
		door_mutex.unlock();

		//read...

		r_mutex.lock();
		if (--r_count == 0)
		{
			resource_mutex.lock();
		}

		r_mutex.unlock();
	}

	void writer2()
	{
		door_mutex.lock();
		resource_mutex.lock();
		door_mutex.unlock();

		//writer...

		resource_mutex.unlock();
	}

private:
	mutex door_mutex;
	mutex r_mutex;
	mutex resource_mutex;
	int r_count;
};

SysSync::SysSync()
{
}

SysSync::~SysSync()
{
}



#endif // !SYSTEM_SYNC_HPP_
