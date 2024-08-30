#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <pthread.h>
#include <list>
#include <locker.h>
#include <exception>
#include <cstdio>

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
threadpool<T>::thread_pool(int thread_number, int max_requests) :
    m_thread_number(thread_number), m_max_request(max_requests),
    m_stop(false), m_thread(NULL) {
        if (thread_number <= 0 || max_requests <= 0) {
            throw std::exception();
        }
        m_threads = new pthread_t[m_thread_number];

        if (! m_threads) {
            throw std::exception();
        }

        for (int i = 0; i < thread_number, i ++) {
            printf("create the %dth thread", i);
            if (pthread_create(m_threads + i, NULL, worker, NULL) != 0) {
                delete [] m_threads;
                throw std::exception();
            }

            if (pthread_detach(m_thread[i])) {
                delete[] m_threads;
                throw std::exception();
            }
        }

    }


#endif