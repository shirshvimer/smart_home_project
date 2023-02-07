#ifndef THREADS_THREAD_POOL_HXX
#define THREADS_THREAD_POOL_HXX

#include <iostream>
#include "threads_thread_pool.hpp"
#include "threads_actions.hpp"

namespace threads {

template<typename F>
void ThreadPool::AddTask(F a_task)
{
    AddTask(std::unique_ptr<AbstractAct>{new FuncObjectAdaptor<F>(a_task)});
}

}//threads


#endif /* THREADS_THREAD_POOL_HXX */

