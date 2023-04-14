#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <semaphore.h>

using namespace std;

sem_t sem[5]; // 5个信号量，用于控制线程的执行顺序

void thread_func(int id)
{
    // 等待前一个线程释放信号量
    sem_wait(&sem[id]);
    cout << "Thread " << id << " is running" << endl;
    // 释放下一个线程的信号量
    if (id != 4)
        sem_post(&sem[id + 1]);
        else sem_post(&sem[0]);
}

int main()
{
    // 初始化信号量，第一个线程可以直接运行
    sem_init(&sem[0], 0, 0);
    sem_init(&sem[1], 0, 1);//让1先运行
    for (int i = 2; i < 5; i++)
    {
        sem_init(&sem[i], 0, 0);
    }

    // 创建 5 个线程
    thread threads[5];
    for (int i = 0; i < 5; i++)
    {
        threads[i] = thread(thread_func, i);
    }

    // 等待所有线程运行结束
    for (int i = 0; i < 5; i++)
    {
        threads[i].join();
    }

    // 销毁信号量
    for (int i = 0; i < 5; i++)
    {
        sem_destroy(&sem[i]);
    }

    return 0;
}