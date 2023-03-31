#include <iostream>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
bool ready = false;

void *thread1(void *arg)
{
    std::cout << "Thread 1: Waiting for signal" << std::endl;
    pthread_mutex_lock(&mutex);
    while (!ready)
    {
        pthread_cond_wait(&cond, &mutex);
        //pthread_cond_wait()函数返回时，它会自动获取互斥锁mutex，因此我们不需要手动调用pthread_mutex_lock()函数来获取互斥锁。
    }
// 在这个代码中，将pthread_cond_wait()放在while循环内是为了避免虚假唤醒（spurious wakeup）的问题。
// 虚假唤醒是指线程在没有被显式唤醒的情况下，从pthread_cond_wait()中返回的情况。这种情况可能发生在多个线程等待同一个条件变量的情况下，当另一个线程发出信号时，所有等待线程都会被唤醒，但只有其中一个线程实际上需要处理该信号。如果没有while循环来重新检查条件，线程可能会因为没有满足条件就被错误地唤醒而导致程序不正确的行为。
// 因此，将pthread_cond_wait()放在while循环内部，可以确保线程只在条件满足时才会继续执行，从而避免虚假唤醒的问题。
    std::cout << "Thread 1: Received signal" << std::endl;
    pthread_mutex_unlock(&mutex);
    return nullptr;
}

void *thread2(void *arg)
{
    std::cout << "Thread 2: Sending signal" << std::endl;
    pthread_mutex_lock(&mutex);
    ready = true;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
    return nullptr;
}

int main()
{
    pthread_t t1, t2;
    pthread_create(&t1, nullptr, thread1, nullptr);
    pthread_create(&t2, nullptr, thread2, nullptr);
    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);
    return 0;
}
// Thread 1: Waiting for signal
// Thread 2: Sending signal
// Thread 1: Received signal