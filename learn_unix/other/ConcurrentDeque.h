#pragma once
#ifndef CONCURRENTDEQUE_H_
#define CONCURRENTDEQUE_H_

#include <iostream>
#include <mutex>
#include <deque>

using namespace std;

template <class T>
class ConCurrentDeque: public deque<T>
{
public:
	ConCurrentDeque() = default;
	~ConCurrentDeque() = default;

	//线程安全insert元素
	void safe_insert(const T& value)
	{
		lock_guard<mutex> guard(mutex_);
		deque<T>::push_front(value);
	}

	//线程安全取出并删除最老的元素
	bool safe_get(T& value)
	{
		{
			lock_guard<mutex> guard(mutex_);
			if (!deque<T>::empty())
			{
				value = deque<T>::back();
				deque<T>::pop_back();
				return true;
			}
		}

		cout << "deque no data" << endl;
		return false;		
	}

private:
	mutex mutex_;
};


#endif // !CONCURRENTLIST_H_

