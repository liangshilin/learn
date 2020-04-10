
#include "ThreadPool.h"
#include <thread>
#include <cstdio>

bool CThreadPool::setThreadNum(int num)
{
	if (num < 0 || num > std::thread::hardware_concurrency() / 2)
	{
		num = 100;
		fprintf(stderr, "setThreadNum too large, set to default 100\n");
		pool_num_ = num;
		return true;
	}

	pool_num_ = num;
	return true;
}

