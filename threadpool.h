#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <pthread.h>
#include <list>
#include <locker.h>

// 定义成模板类是为了代码的复用，参数T表示任务类
template<typename T>
class threadpool {
private:
    // 线程的数量
    int m_thread_number;
    // 线程池的数组
    pthread_t * m_threads;
    // 队列大小
    int m_max_requests;
    // 队列实例
    std::list<T*> m_workqueue;
    // 互斥锁
    locker m_queuelocker;
    // 信号量,判断是否有任务需要处理
    sem m_queuestat;
    // 是否结束线程 
    bool m_stop;
public:
    thread_pool(int thread_num = 8, int m_max_requests = 1000);
    ~threadpool();
    bool append(T * request);
};


template<typename T>


#endif