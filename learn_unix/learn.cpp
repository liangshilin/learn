// learn.cpp: 定义应用程序的入口点。

#include "algorithm/sort.hpp"
#include "algorithm/list.hpp"
#include "algorithm/str.hpp"
#include "datastruct/binary_tree.hpp"
#include "algorithm/interesting.hpp"
#include "stl/containers.hpp"
#include "algorithm/array.hpp"
#include "system/ipc.hpp"
#include <random>
#include <iostream>
#include <thread>
#include <ext/pool_allocator.h>

using namespace std;


void test(char value[100])
{
    int size = sizeof(value);
    printf("    %d   ", sizeof(value));
}

int main()
{
    char value[50];
    printf("   %d   ", sizeof(value));
    test(value);
    getchar();
    SysIPC::consumer(nullptr);
    exit(0);

    SysIPC tmpIPC;
    tmpIPC.fork_test(10);
    exit(0);

    vector<int> yes;
    int vector_size = sizeof(vector<int>);
    int map_size = sizeof(map<int, int>);
    int list_size = sizeof(list<int>);
    int forward_list_size = sizeof(forward_list<int>);

    string str("abcdaefgdhijk");
    ALGStr tmpStr;
    tmpStr.maxSubStringLength(str);
    // 以随机值播种，若可能
    std::random_device rd;

    // 选择 -1000 与 1000 间的随机数
    std::default_random_engine re(rd());
    std::uniform_int_distribution<int> uniform_dist(1, 100);

    // 生成100个随机数据
    vector<int> test_data;
    for (int i = 0; i < 100; i++)
    {
        test_data.push_back(uniform_dist(re));
    }

    ALGSort<int> sortTest(test_data);
    sortTest.mergeSort2(false);

    ALGArray testArray;
    const auto result1 = testArray.maxSubProduct(test_data);
    cout << "The max product in subArrays is " << result1 << endl;

    const int specialNum = uniform_dist(re);
    const auto result2 = testArray.specialSub(test_data, specialNum);
    printf("The subArray sum = %d is [%d, %d]\n", specialNum, result2.first, result2.second);

    const auto result3 = testArray.maxSubNum(test_data);
    printf("The max subArray sum is %d", result3);

	cout << "Hello World." << endl;
	return 0;
}
