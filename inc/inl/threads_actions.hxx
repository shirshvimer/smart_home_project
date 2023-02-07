#ifndef THREADS_ACTIONS_HXX 
#define THREADS_ACTIONS_HXX

#include "threads_actions.hpp"

namespace threads {

template <typename F>
FuncObjectAdaptor<F>::FuncObjectAdaptor(F a_func)
: m_func(std::move(a_func))
{
}

template <typename F>
void FuncObjectAdaptor<F>::Act()
{
    m_func();
}


inline void ShutDownTask::Act() 
{ 
    throw ShutDownException{}; 
}

}//threads

#endif /* THREADS_ACTIONS_HXX */