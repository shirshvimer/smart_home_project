#ifndef THREADS_THREAD_POOL_HPP
#define THREADS_THREAD_POOL_HPP

#include <vector>
#include <thread>
#include <memory>
#include <functional>
#include <atomic>

#include "threads_blocking_queue.hpp"
#include "threads_abstract_act.hpp"

namespace threads {

class ThreadPool {
public:
    explicit ThreadPool(size_t a_numOfThreads = 1);
    ~ThreadPool();

    void AddTask(std::shared_ptr<AbstractAct> a_task);
    void AddTask(std::unique_ptr<AbstractAct> a_task);

    template<typename F>
    void AddTask(F a_task);

    void ShutDown();
    void ShutDownNow();
    void AddThreads(size_t a_numOfThreads);
    void RemoveThreads(size_t a_numOfThreads);

private:
    void ExecuteFromQueue();
    void InternalAddTask(std::shared_ptr<AbstractAct> a_task);
    void InternalAddTask(std::unique_ptr<AbstractAct> a_task);

private:
    BlockingQueue<std::shared_ptr<AbstractAct>> m_wq;
    std::vector<std::thread> m_threads;
    std::atomic<bool> m_isTerminate;
    std::atomic<bool> m_isTerminatedNow;
    std::atomic<size_t> m_NumOfThreadsInLoop;
};

}//threads

#include "inl/threads_thread_pool.hxx"

#endif /* THREADS_THREAD_POOL_HPP */