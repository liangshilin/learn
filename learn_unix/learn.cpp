// learn.cpp: 定义应用程序的入口点。

#include "algorithm/sort.hpp"
#include "algorithm/list.hpp"
#include "algorithm/str.hpp"
#include "datastruct/binary_tree.hpp"
#include "algorithm/interesting.hpp"
#include "stl/containers.hpp"
#include "algorithm/array.hpp"
#include "system/ipc.hpp"
#include "net/udp_test.hpp"
#include "other/heap_stack_obj.hpp"
#include "net/socket_test.hpp"
#include "other/utility.hpp"
#include <random>
#include <iostream>
#include <thread>
#include <ext/pool_allocator.h>

using namespace std;

int main(int argc, char** argv)
{

    utility::run();
    exit(0);

    NetSocket_::run1(true);
    exit(0);

    // 只堆和只栈对象测试
    //OnlyHeap stack_oh;
    OnlyHeap* heap_oh = OnlyHeap::Create();
    heap_oh->Destory();

    OnlyStack stack_os;
    //OnlyStack* heap_os = new OnlyStack[10];
    //auto tmp = *heap_os;
    //delete [] heap_os;

    exit(0); //清理完调用_exit()



    // 查看stl容器的大小
    vector<int> yes;
    int vector_size = sizeof(vector<int>);
    int map_size = sizeof(map<int, int>);
    int list_size = sizeof(list<int>);
    int forward_list_size = sizeof(forward_list<int>);


    // 算法测试
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
