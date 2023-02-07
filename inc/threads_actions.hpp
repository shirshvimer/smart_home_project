#ifndef THREADS_ACTIONS_HPP 
#define THREADS_ACTIONS_HPP

#include "threads_abstract_act.hpp"

namespace threads {

class IsPrime : public AbstractAct{
public:
    IsPrime(unsigned int a_num);

    virtual void Act() override;

private:
    bool IsPrimeFunc();

private:
    unsigned int m_num;
};


template <typename F>
class FuncObjectAdaptor : public AbstractAct {
public:
    FuncObjectAdaptor(F a_func);

    virtual void Act() override;

private:
    F m_func;
};

class ShutDownException : public std::runtime_error { 
public: 
    ShutDownException() : std::runtime_error("end thread") {}; 
};

class ShutDownTask : public AbstractAct 
{ 
    virtual void Act() override; 
}; 

}//threads

#include "inl/threads_actions.hxx"

#endif /* THREADS_ACTIONS_HPP */