#include <cstdio>

#include<thread>
#include<cstring>
#include<string>
#include <mutex>
#include <condition_variable>

#include <unistd.h>

using namespace std;

mutex g_mutex1;
mutex g_mutex2;
condition_variable g_cond1;
condition_variable g_cond2;
bool g_flag1 = false;
bool g_flag2 = false;

void task_one(void* args)
{
    //int* pi = new int[4];

    //pi[4] = 5;

    //int a = pi[4];

    //delete[] pi;

    //a = pi[0];

    //pi[0] = 5;

    //delete[] pi;

    int i = 10;
    while (i--)
    {
        {
            //unique_lock<mutex> unique_1(g_mutex1);
            sleep(random() % 2);

            {
                char* pstr = new  char[204800];
                //unique_lock<mutex> unique_2(g_mutex2);
                sleep(random() % 2);
            }

            //system("echo 111111 >> ./tmp");
        }
    }
    g_flag1 = true;
    g_cond1.notify_one();
}

void task_two(void* args)
{
    //int* pi = new int[4];

    //pi[4] = 5;

    //int a = pi[4];

    //delete[] pi;

    //a = pi[0];

    //pi[0] = 5;

    //delete[] pi;

    int i = 10;
    while (i--)
    {
        {
            //unique_lock<mutex> unique_1(g_mutex1);
            sleep(random() % 2);

            {
                char* pstr = new  char[102400];
                //unique_lock<mutex> unique_2(g_mutex2);
                sleep(random() % 2);
            }

            //system("echo 22222 >> ./tmp");
        }

    }

    g_flag2 = true;
    g_cond2.notify_one();
}

class test1
{
public:
    test1() {}
    ~test1() {}

    void one()
    {
        printf("one");
    }

private:
    int a;
    double b;
    char c;
};

class test2
{
public:
    test2() {}
    virtual ~test2() {}
    virtual void one()
    {
        printf("one");
    }
private:
    int a;
    double b;
    char c;
};


int main()
{
    char* pc = new char[10240000];
    srandom(getpid());

    thread tr1(task_one, nullptr);
    thread tr2(task_two, nullptr);

    tr1.detach();
    tr2.detach();

    {
        unique_lock<mutex> un_mutex1(g_mutex1);
        g_cond1.wait(un_mutex1, [] {return g_flag1; });
    }

    {
        unique_lock<mutex> un_mutex2(g_mutex2);
        g_cond2.wait(un_mutex2, [] {return g_flag2; });
    }
    
    printf("main....");

    return 0;
}