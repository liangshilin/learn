#pragma once
#ifndef THREADPOOL_H__
#define THREADPOOL_H__

#include <functional>
#include <memory>
#include "blocking_q.h"

typedef void (*thread_func)(void*);

using namespace std;

class CThreadPool 
{

private:
	CThreadPool():pool_num_(100),thread_queue_(10000){};
public:
	CThreadPool(const CThreadPool&) = delete;
	CThreadPool& operator = (const CThreadPool&) = delete;
	CThreadPool(CThreadPool&&) = delete;
	CThreadPool& operator = (CThreadPool&&) = delete;

public:
	/*------------ 单例模式获取实例 -------------*/
	static CThreadPool& getInstace()
	{
		static CThreadPool instance;
		return instance;
	}

	bool setThreadNum(int num);

	bool submit(void*);

	void shutdown();

	void Start();


private:
	int pool_num_;
	mpmc_blocking_queue<unique_ptr<void*>> thread_queue_;

};





#endif // !THREADPOOL_H__

