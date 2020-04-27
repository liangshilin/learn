#ifndef IPC_HPP_
#define IPC_HPP_

#include <cstdio>
#include <errno.h>
#include <string.h>
#include <csignal>
#include <vector>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>  
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/stat.h>

//SYSTEM V
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>
//POSIX
#include <sys/mman.h>
#include <mqueue.h>
#include <semaphore.h>


using namespace std;

class SysIPC
{
public:
	SysIPC() {}

	~SysIPC() = default;

	static void signal_func(int signal)
	{
		char tmp[256] = { 0 };
		sprintf(tmp, "echo \"child finish\" >> ./main.txt");
		system(tmp);
	}

	static void signal_term(int signal)
	{
		char tmp[256] = { 0 };
		sprintf(tmp, "echo \"child passive finish \" >> ./child.txt");
		system(tmp);
	}

	//fork 测试
	void fork_test(int num)
	{
		system("echo \"main\" > ./main.txt");
		char tmp[256] = { 0 };
		vector<pid_t> pids;

		sharemem_test1();
		
		for (auto i = 0; i < num; i++)
		{
			pid_t pid_tmp;
			pid_tmp = fork();
			if (pid_tmp == 0)
			{
				sprintf(tmp, "echo \"child_%d\" > ./child_%d.txt", i, i);
				system(tmp);
				signal(SIGTERM, signal_term);
				sharemem_test2(i);
				sleep(10); // 10 second

				exit(0);
			}
			else
			{
				pids.push_back(pid_tmp);
			}
			
			
			sprintf(tmp, "echo \"main fork child_%d\" >> ./main.txt", i);
			system(tmp);
		}

		signal(SIGINT, SysIPC::signal_func);
		
		sleep(5); // 5 second
		usleep(3000000); // microsecond

		for (auto pid : pids)
		{
			kill(pid, SIGTERM);
		}

		while (wait(nullptr) > 0); // wait all subprocess

		if (errno != ECHILD)
		{
			exit(-1);
		}

		exit(0);
	}

	//共享内存测试
	static void sharemem_test1()
	{
		int fd = shm_open("\mem_test", O_RDWR | O_CREAT, 0666);
		ftruncate(fd, sizeof(int) * 100);

		int* mem_array = (int*)mmap(nullptr, sizeof(int) * 100, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
		
		close(fd);

		for (auto i = 0; i < 100; i++)
		{
			mem_array[i] = i*i;
		}
	}

	static void sharemem_test2(int index)
	{
		int fd = shm_open("\mem_test", O_RDWR, 0);
		int* memarry = (int*)mmap(nullptr, sizeof(int) * 100, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
		close(fd);

		char tmp[256] = { 0 };
		sprintf(tmp, "echo \"child share_mem %d\" >> ./child_%d.txt", memarry[index], index);
		system(tmp);
	}

	struct msg_date
	{
		long type;
		char name[128];
		int age;
		char gender; // man：m women：w
	};

	//生产者
	static int queue_producer1()
	{
		auto msg_id = msgget(0x12345678, IPC_CREAT | IPC_EXCL);

		if (msg_id < 0)
		{
			// 队列存在则删除重建
			if (errno == EEXIST || errno == EINTR)
			{
				msg_id = msgget(0x12345678, IPC_EXCL);
				if (msgctl(msg_id, IPC_RMID, nullptr) < 0)
				{
					//
					return -1;
				}

				msg_id = msgget(0x12345678, IPC_CREAT | IPC_EXCL);
			}
			else
			{
				return -1;
			}
		}

		//share memory----------------------------------------------
		char random_msg111[512];
		auto shm_id = shmget(0x12345678, sizeof(random_msg111), IPC_CREAT | IPC_EXCL);

		if (shm_id < 0)
		{
			// 队列存在则删除重建
			if (errno == EEXIST || errno == EINTR)
			{
				shm_id = shmget(0x12345678, sizeof(random_msg111), IPC_CREAT);
				if (msgctl(shm_id, IPC_RMID, nullptr) < 0)
				{
					//
					return -1;
				}

				shm_id = shmget(0x12345678, sizeof(random_msg111), IPC_CREAT);
			}
		}

		auto random_msg = shmat(shm_id, nullptr, 0);

		//----------------------------------------------------

		//semaphore--------------------------------------------

		auto sem_id = sem_open("\shilin_sem", O_CREAT, 0, 1);
		if(sem_id == SEM_FAILED)
		{
			if (errno == EINVAL)
			{
				sem_id = sem_open("\shilin_sem", O_CREAT, 0, 1);
			}
			else
			{
				return -1;
			}
		}

		//------------------------------------------------------

		int size = sizeof(msg_date) - sizeof(long);
		for (auto i = 0; i < 10; i++)
		{
			msg_date message;
			message.type = i % 3 + 1;
			sprintf(message.name, "shilin_%d", i);
			message.age = 28 + i;
			message.gender = 'm';

			// 在共享内存丢随机消息，信号量读写互斥
			sem_wait(sem_id);
			sprintf((char*)random_msg, "producer share memory random value: %d", random() % 100);
			sem_post(sem_id);
			
			if (msgsnd(msg_id, (void*)&message, size, IPC_NOWAIT) < 0)
			{
				if (errno ==  EAGAIN || errno == EINTR)
				{
					i--;
					continue;
				}
				else
				{
					//e.g EIDRM 消息队列已不存在
					auto err_ = strerror(errno);
					return -1;
				}
			}

			printf("send message: [%d][%s][%d][%c]\n", message.type, message.name, message.age, message.gender);
		}


		// 清除消息队列和共享内存
		bool msg_flag = false;
		bool shm_flag = false;

		while (!msg_flag || !shm_flag)
		{
			// 消息队列的消息是否消耗完
			msqid_ds mds;
			if (!msg_flag && msgctl(msg_id, IPC_STAT, &mds) < 0)
			{
				if (errno == EINTR)
				{
					msgctl(msg_id, IPC_STAT, &mds);
				}
			}

			if (mds.msg_qnum == 0)
			{
				msgctl(msg_id, IPC_RMID, nullptr);
				msg_flag = true;
			}
			else
			{
				continue;
			}

			//查看共享内存的跟踪者数量
			shmid_ds shm_ds;
			if (shmctl(shm_id, IPC_STAT, &shm_ds) < 0)
			{
				if (errno == EINTR)
				{
					shmctl(shm_id, IPC_STAT, &shm_ds);
				}
			}

			if (shm_ds.shm_nattch == 1)
			{
				shmdt(random_msg);
				shmctl(shm_id, IPC_RMID, nullptr);
				shm_flag = true;
			}

			printf("message queue count is %d\n", mds.msg_qnum);
			printf("share memory attaches number is %d\n", shm_ds.shm_nattch);
			sleep(1);
		}

		//销毁信号量
		sem_close(sem_id);
		sem_unlink("\shilin_sem");
		return 0;
	}

	//消费者
	static int queue_consumer1()
	{
		auto msg_id = msgget(0x12345678, IPC_EXCL);

		if (msg_id < 0)
		{
			if (errno == EINTR)
			{
				msg_id = msgget(0x12345678, IPC_EXCL);
			}
			else
			{
				return -1;
			}
		}

		// share memory----------------------------
		auto shm_id = shmget(0x12345678, 512, IPC_EXCL);
		if (shm_id < 0)
		{
			if (errno == EINTR)
			{
				shm_id = shmget(0x12345678, 512, IPC_EXCL);
			}
			else
			{
				return -1;
			}
		}

		auto random_msg = shmat(shm_id, 0, 0);
		// ----------------------------------------

		// semaphore--------------------------------------------
		auto sem_id = sem_open("\shilin_sem", O_EXCL);
		if (sem_id == SEM_FAILED)
		{
			if (errno == EINVAL)
			{
				sem_id = sem_open("\shilin_sem", O_EXCL);
			}
			else
			{
				return -1;
			}
		}
		// ------------------------------------------------------

		while (true)
		{
			int size = sizeof(msg_date) - sizeof(long);
			msg_date message;
			if (msgrcv(msg_id, (void*)&message, size, 0, IPC_NOWAIT) < 0)
			{
				if (errno == EAGAIN || errno == EINTR)
				{
					continue;
				}

				if (errno == EIDRM || errno == ENOMSG)
				{
				
					auto err_msg = strerror(errno);
					printf("%s\n", err_msg);
					break;
				}
				auto err_msg = strerror(errno);
				printf("%s\n", err_msg);
			}

			//读取共享内存的random msg
			sem_wait(sem_id);
			printf("consumer random message: %s\n", (char*)random_msg);
			sem_post(sem_id);

			printf("consumer message: [%d][%s][%d][%c]\n", message.type, message.name, message.age, message.gender);
		}

		shmdt(random_msg);
		sem_close(sem_id);

		return 0;
	}

	static void producer(void*)
	{
		queue_producer1();
	}

	static void consumer(void*)
	{
		queue_consumer1();
	}

private:
};


#endif // !IPC_HPP_
