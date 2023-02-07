#ifndef THREADS_SEMAPHORE_HPP 
#define THREADS_SEMAPHORE_HPP

#include <semaphore.h>
#include "threads_exception.hpp"

namespace threads {

class SemaphoreException: public ThreadsException {
public:
    using ThreadsException::ThreadsException;
};

class Semaphore
{
public:
    Semaphore(unsigned int a_value);
    ~Semaphore();
    Semaphore(Semaphore const& a_other) = delete;
    Semaphore& operator=(Semaphore const& a_other) = delete;

    void Down() noexcept;
    void Up();
    
private:
    sem_t m_sem;
};

}//threads

#endif /* THREADS_SEMAPHORE_HPP */