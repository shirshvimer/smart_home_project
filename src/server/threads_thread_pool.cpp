#include "threads_thread_pool.hpp"

namespace threads {

void ThreadPool::ExecuteFromQueue()
{
    while(!m_isTerminatedNow) {
        std::shared_ptr<AbstractAct> task;

        ++m_NumOfThreadsInLoop;
        m_wq.DeQueue(task);
        --m_NumOfThreadsInLoop;
        
        try {
            if(task){
                task->Act();
            }
        }
        catch(ShutDownException const& e) {
            break;
        }
        catch(...) {
            std::cerr << "task didn't execute- exception was thrown\n";
        }
    }
}

ThreadPool::ThreadPool(size_t a_numOfThreads)
: m_wq()
, m_threads()
, m_isTerminate(false)
, m_isTerminatedNow(false)
, m_NumOfThreadsInLoop(0)
{
    m_threads.reserve(a_numOfThreads);
    AddThreads(a_numOfThreads);
}

ThreadPool::~ThreadPool()
{
    for(auto &it : m_threads) {
        it.join();
    }
}

void ThreadPool::AddTask(std::shared_ptr<AbstractAct> a_task)
{
    if(!m_isTerminate) {
        InternalAddTask(a_task);
    }
    else {
        std::cerr << "not allowed adding more tasks\n";
    }
}

void ThreadPool::AddTask(std::unique_ptr<AbstractAct> a_task)
{
    if(!m_isTerminate) {
        InternalAddTask(std::move(a_task));
    }
    else {
        std::cerr << "not allowed adding more tasks\n";
    }
}

void ThreadPool::InternalAddTask(std::shared_ptr<AbstractAct> a_task)
{
    m_wq.EnQueue(a_task);
}

void ThreadPool::InternalAddTask(std::unique_ptr<AbstractAct> a_task)
{
    m_wq.EnQueue(std::move(a_task));
}

void ThreadPool::ShutDown()
{
    m_isTerminate = true;
    size_t numOfThreads = m_threads.size();

    for(size_t i = 0; i < numOfThreads; ++i) {
        InternalAddTask(std::unique_ptr<AbstractAct>{new ShutDownTask});
    }
}

void ThreadPool::ShutDownNow()
{
    m_isTerminatedNow = true;
    
    size_t num = m_NumOfThreadsInLoop;
    size_t numOfApple = num - m_wq.Size();
    
    if(m_wq.Size() <= num) {
        for(size_t i = 0; i < numOfApple; ++i) {
            InternalAddTask(std::unique_ptr<AbstractAct>{new ShutDownTask});
        }
    }
} 

void ThreadPool::AddThreads(size_t a_numOfThreads)
{
    for(size_t i = 0; i < a_numOfThreads; ++i) {
        m_threads.push_back(std::thread{&ThreadPool::ExecuteFromQueue, this});
    }
}

void ThreadPool::RemoveThreads(size_t a_numOfThreads)
{
    for(size_t i = 0; i < a_numOfThreads; ++i) {
        m_threads.back().join();
        m_threads.pop_back();
    }
}

}//threads
