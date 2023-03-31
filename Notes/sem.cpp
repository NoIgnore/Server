#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 5

int shared_resource = 0;
pthread_mutex_t mutex;
sem_t semaphore;

void *thread_function(void *arg)
{
    int thread_num = *(int *)arg;

    // 使用互斥量保护共享资源
    pthread_mutex_lock(&mutex);
    shared_resource++;
    printf("Thread %d: shared_resource = %d\n", thread_num, shared_resource);
    pthread_mutex_unlock(&mutex);

    // 使用信号量协调线程执行顺序
    sem_wait(&semaphore);//semaphore--
    printf("Thread %d: semaphore\n", thread_num);
    sem_post(&semaphore);//semaphore++

    return NULL;
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int thread_nums[NUM_THREADS];

    // 初始化互斥量和信号量
    pthread_mutex_init(&mutex, NULL);
    sem_init(&semaphore, 0, 1);

    // 创建线程
    for (int i = 0; i < NUM_THREADS; i++)
    {
        thread_nums[i] = i;
        pthread_create(&threads[i], NULL, thread_function, &thread_nums[i]);
    }

    // 等待线程结束
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // 销毁互斥量和信号量
    pthread_mutex_destroy(&mutex);
    sem_destroy(&semaphore);

    return 0;
}
// Thread 0: shared_resource = 1
// Thread 0: semaphore
// Thread 1: shared_resource = 2
// Thread 1: semaphore
// Thread 2: shared_resource = 3
// Thread 2: semaphore
// Thread 3: shared_resource = 4
// Thread 3: semaphore
// Thread 4: shared_resource = 5
// Thread 4: semaphore
//信号量为1，确保线程的执行顺序