#pragma once
#ifndef SYSTEM_RAM_HPP_H_
#define SYSTEM_RAM_HPP_H_

#include <list>
#include <unordered_map>

using namespace std;


struct SCDate
{
	int key;
	bool used;
};

class SysRam
{
public:
	SysRam();
	virtual ~SysRam();

	/*内存LRU置换算法实现----------------------*/
	//淘汰页面
	void eliminate_page_lru()
	{
		mem_pages_lru.pop_back();
	}

	//访问页面
	int access_page_lru(int key)
	{
		if (hash_pages_lru.count(key) > 0)
		{
			auto p = hash_pages_lru.at(key);
			int value = *p;
			mem_pages_lru.push_front(*p);
			mem_pages_lru.erase(p);
			hash_pages_lru.at(key) = mem_pages_lru.begin();

			return value;
		}
		else
		{
			return -1;
		}
	}

	//插入页面
	void insert_page_lru(int key)
	{
		if (mem_pages_lru.size() > maxCount)
		{
			eliminate_page_lru();
		}

		mem_pages_lru.push_front(key);
		hash_pages_lru.insert(make_pair(key, mem_pages_lru.begin()));

		return;
	}

	/*-----------------------------------------*/

	//内存第二次机会 + 时钟算法
	//淘汰页面
	list<SCDate>::iterator eliminate_page_second_clock()
	{
		auto clock_tmp = clock_p;

		//往后找
		while (clock_tmp != mem_pages_sc.end())
		{
			if (clock_tmp->used == true)
			{
				clock_tmp->used = false;
			}
			else
			{
				return clock_tmp;
			}
		}

		clock_tmp = mem_pages_sc.begin();

		//从头开始，直到回到原位
		while (clock_p != clock_p)
		{
			if (clock_tmp->used == true)
			{
				clock_tmp->used = false;
			}
			else
			{
				return clock_tmp;
			}
		}

		return clock_p;
	}

	//插入页面
	void insert_sc(int key)
	{
		SCDate sc;
		sc.key = key;
		sc.used = false;

		if (mem_pages_sc.size() == maxCount)
		{
			auto c_p = eliminate_page_second_clock();
			c_p->key = key;
			c_p->used = true; // 更新true

			// 时针往后移，如果到尾就回到头(仿循环链表)
			clock_p = ++c_p;
			if (clock_p == mem_pages_sc.end())
			{
				clock_p = mem_pages_sc.begin();
			}
		}
		else
		{	
			mem_pages_sc.push_back(std::move(sc));
			if (mem_pages_sc.size() == 1)
			{			
				clock_p = clock_p = mem_pages_sc.begin();
			}
		
			hash_pages_sc.insert(make_pair(cur_index++, --mem_pages_sc.end()));
		}
	}

	//访问页面
	int access_page_sc(int index)
	{
		return hash_pages_sc.at(index)->key;
	}

private:
	int maxCount = 1000;
	list<int> mem_pages_lru;
	unordered_map<int, list<int>::iterator> hash_pages_lru;

	int cur_index = 0;
	list<SCDate>::iterator clock_p;
	list<SCDate> mem_pages_sc;
	unordered_map<int, list<SCDate>::iterator> hash_pages_sc;
};

SysRam::SysRam()
{
}

SysRam::~SysRam()
{
}


#endif // !SYSTEM_RAM_HPP_H_
