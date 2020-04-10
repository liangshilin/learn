#pragma once
#ifndef CMESSAGEQUEUE_H_
#define CMESSAGEQUEUE_H_

#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <cstdio>
#include <unistd.h>
#include <string>
#include <cstdlib>
#include <cstring>
#include <atomic>

using namespace std;


template <typename T>
class CMsgQueue
{
public:
	CMsgQueue()
	{
		key_ = -1;
		msg_id_ = -1;
		msg_size_ = sizeof(T) - sizeof(long);
		msg_alive_ = ATOMIC_FLAG_INIT; //初始化为false
	}

	CMsgQueue(int msg_key)
	{
		if (msg_key <= 0) 
		{
			printf("message key shou be more than 0\n");
			return;
		}

		// 开始新建队列，已存在则获取已存在队列id
		int id_tmp = msgget(msg_key, IPC_CREAT|IPC_EXCL);
		if (-1 == key_tmp && errno == EEXIST)
		{
			id_tmp = msgget(msg_key, IPC_CREAT);
			msg_id_ = id_tmp;
			key_ = msg_key;
		}

		msg_alive_.test_and_set(memory_order_acquire);
	}

	virtual ~CMsgQueue()
	{
	}

	bool Create(const int& msg_key)
	{
		if (msg_key == key_)
		{
			return true;
		}

		auto id_tmp = msgget(msg_key, IPC_CREAT);
		if (-1 == id_tmp)
		{
			printf("");
			return false;
		}

		key_ = msg_key;
		msg_id_ = id_tmp;
		msg_alive_.test_and_set(memory_order_acquire);
		return true;
	}

	bool GetMessage(T& message)
	{
		if (msg_id_ <= 0 || !msg_alive_.test_and_set(memory_order_acquire))
		{
			return false;
		}

		auto ret = msgrcv(msg_id_, static_cast<void*>(&message), msg_size_, 0, IPC_NOWAIT);

		if (-1 == ret)
		{
			return false;
		}

		return true;
	}

	bool SaveMessage(const T* message)
	{
		if (msg_id_ <= 0 || !msg_alive_.test_and_set(memory_order_acquire))
		{
			return false;
		}

		auto ret = msgsnd(msgid_, static_cast<void*>(message), msg_size_, IPC_NOWAIT);

		if (-1 == ret)
		{
			return false;
		}

		return true;

	}

	bool SwapQueueId(const int& msg_queue_id)
	{
		msg_alive_.clear(memory_order_release);
		msg_id_ = msg_queue_id;
		key_ = -1;
		msg_alive_.test_and_set(memory_order_acquire);
		return true;
	}

	bool SwapMessageKey(const int& key)
	{

		auto id_tmp = msgget(key, IPC_CREAT);
		if (-1 == id_tmp)
		{
			return false;
		}

		key_ = key;
		msg_id_ = id_tmp;

		return true;
	}

	bool RemoveMessageQueue()
	{
		if (msg_id_ <= 0)
		{
			return true;
		}

		msqid_ds ds_tmp;
		memset(&ds_tmp, 0, sizeof(msqid_ds));
		if (-1 == msgctl(msg_id_, IPC_RMID, &ds_tmp))
		{
			return false;
		}

		return true;
	}

	int GetMsgCount(int& count)
	{
		msqid_ds ds_tmp;
		memset(&ds_tmp, 0, sizeof(msqid_ds));
		if (-1 == msgctl(msg_id_, IPC_STAT, ds_tmp))
		{
			return -1;
		}

		return ds_tmp.msg_qnum;
	}

private:
	size_t msg_size_;
	key_t key_;
	int msg_id_;
	atomic_flag msg_alive_; //队列存活标志
};


#endif // !CMESSAGEQUEUE_H_

