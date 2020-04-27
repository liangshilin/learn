
// Copyright(c) 2015-present, Gabi Melman & spdlog contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

// multi producer-multi consumer blocking queue.
// enqueue(..) - will block until room found to put the new message.
// enqueue_nowait(..) - will return immediately with false if no room left in
// the queue.
// dequeue_for(..) - will block until the queue is not empty or timeout have
// passed.

#include <condition_variable>
#include <mutex>
#include <cstddef>
#include <vector>
#include <utility>
#include <assert.h>
#include <atomic>
#include <chrono>
#include <initializer_list>
#include <memory>
#include <exception>
#include <string>
#include <type_traits>
#include <functional>

#define size_t int

template<typename T>
class circular_q
{
	int max_items_ = 0;
	typename std::vector<T>::size_type head_ = 0;
	typename std::vector<T>::size_type tail_ = 0;
	int overrun_counter_ = 0;
	std::vector<T> v_;

public:
	using value_type = T;

	// empty ctor - create a disabled queue with no elements allocated at all
	circular_q() = default;

	explicit circular_q(int max_items)
		: max_items_(max_items + 1) // one item is reserved as marker for full q
		, v_(max_items_)
	{}

	circular_q(const circular_q &) = default;
	circular_q &operator=(const circular_q &) = default;

	// move cannot be default,
	// since we need to reset head_, tail_, etc to zero in the moved object
	circular_q(circular_q&& other) noexcept
	{
		copy_moveable(std::move(other));
	}

	circular_q &operator=(circular_q &&other) noexcept
	{
		copy_moveable(std::move(other));
		return *this;
	}

	// push back, overrun (oldest) item if no room left
	void push_back(T &&item)
	{
		if (max_items_ > 0)
		{
			v_[tail_] = std::move(item);
			tail_ = (tail_ + 1) % max_items_;

			if (tail_ == head_) // overrun last item if full
			{
				head_ = (head_ + 1) % max_items_;
				++overrun_counter_;
			}
		}
	}

	// Return reference to the front item.
	// If there are no elements in the container, the behavior is undefined.
	const T &front() const
	{
		return v_[head_];
	}

	T &front()
	{
		return v_[head_];
	}

	// Return number of elements actually stored
	int size() const
	{
		if (tail_ >= head_)
		{
			return tail_ - head_;
		}
		else
		{
			return max_items_ - (head_ - tail_);
		}
	}

	// Return const reference to item by index.
	// If index is out of range 0¡­size()-1, the behavior is undefined.
	const T &at(int i) const
	{
		assert(i < size());
		return v_[(head_ + i) % max_items_];
	}

	// Pop item from front.
	// If there are no elements in the container, the behavior is undefined.
	void pop_front()
	{
		head_ = (head_ + 1) % max_items_;
	}

	bool empty() const
	{
		return tail_ == head_;
	}

	bool full() const
	{
		// head is ahead of the tail by 1
		if (max_items_ > 0)
		{
			return ((tail_ + 1) % max_items_) == head_;
		}
		return false;
	}

	int overrun_counter() const
	{
		return overrun_counter_;
	}

	private:
	// copy from other&& and reset it to disabled state
	void copy_moveable(circular_q &&other) noexcept
	{
		max_items_ = other.max_items_;
		head_ = other.head_;
		tail_ = other.tail_;
		overrun_counter_ = other.overrun_counter_;
		v_ = std::move(other.v_);

		// put &&other in disabled, but valid state
		other.max_items_ = 0;
		other.head_ = other.tail_ = 0;
		other.overrun_counter_ = 0;
	}
};


template<typename T>
class mpmc_blocking_queue
{
public:
	using item_type = T;
	explicit mpmc_blocking_queue(size_t max_items)
		: q_(max_items)
	{}

#ifndef __MINGW32__
	// try to enqueue and block if no room left
	void enqueue(T&& item)
	{
		{
			std::unique_lock<std::mutex> lock(queue_mutex_);
			pop_cv_.wait(lock, [this] { return !this->q_.full(); });
			q_.push_back(std::move(item));
		}
		push_cv_.notify_one();
	}

	bool enqueue_noblock(T&& item)
	{
		bool flag = true;
		{
			std::unique_lock<std::mutex> lock(queue_mutex_);
			if (q_.full())
				flag = false;
			else
				q_.push_back(std::move(item));
		}
		push_cv_.notify_one();

		return flag;
	}

	// enqueue immediately. overrun oldest message in the queue if no room left.
	void enqueue_nowait(T&& item)
	{
		{
			std::unique_lock<std::mutex> lock(queue_mutex_);
			q_.push_back(std::move(item));
		}
		push_cv_.notify_one();
	}

	// try to dequeue item. if no item found. wait upto timeout and try again
	// Return true, if succeeded dequeue item, false otherwise
	bool dequeue_for(T& popped_item, std::chrono::milliseconds wait_duration)
	{
		{
			std::unique_lock<std::mutex> lock(queue_mutex_);
			if (!push_cv_.wait_for(lock, wait_duration, [this] { return !this->q_.empty(); }))
			{
				return false;
			}
			popped_item = std::move(q_.front());
			q_.pop_front();
		}
		pop_cv_.notify_one();
		return true;
	}

#else
	// apparently mingw deadlocks if the mutex is released before cv.notify_one(),
	// so release the mutex at the very end each function.

	// try to enqueue and block if no room left
	void enqueue(T&& item)
	{
		std::unique_lock<std::mutex> lock(queue_mutex_);
		pop_cv_.wait(lock, [this] { return !this->q_.full(); });
		q_.push_back(std::move(item));
		push_cv_.notify_one();
	}

	// enqueue immediately. overrun oldest message in the queue if no room left.
	void enqueue_nowait(T&& item)
	{
		std::unique_lock<std::mutex> lock(queue_mutex_);
		q_.push_back(std::move(item));
		push_cv_.notify_one();
	}

	// try to dequeue item. if no item found. wait upto timeout and try again
	// Return true, if succeeded dequeue item, false otherwise
	bool dequeue_for(T& popped_item, std::chrono::milliseconds wait_duration)
	{
		std::unique_lock<std::mutex> lock(queue_mutex_);
		if (!push_cv_.wait_for(lock, wait_duration, [this] { return !this->q_.empty(); }))
		{
			return false;
		}
		popped_item = std::move(q_.front());
		q_.pop_front();
		pop_cv_.notify_one();
		return true;
	}

#endif

	size_t overrun_counter()
	{
		std::unique_lock<std::mutex> lock(queue_mutex_);
		return q_.overrun_counter();
	}

private:
	std::mutex queue_mutex_;
	std::condition_variable push_cv_;
	std::condition_variable pop_cv_;
	circular_q<T> q_;
};


