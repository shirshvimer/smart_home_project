#include <cassert>
#include "threads_semaphore.hpp"

namespace threads {
Semaphore::Semaphore(unsigned int a_value)
{
    if(sem_init(&m_sem, 0, a_value) != 0) {
        switch (errno)
        {
        case ENOSYS:
            assert(!"sem init failed");
            break;
        
        default:
            throw SemaphoreException("sem init failed", errno);
            break;
        }
    }
}

Semaphore::~Semaphore()
{
    if(sem_destroy(&m_sem) != 0) {
        assert(!"destroy failed: invalid semaphore");
    }
}

void Semaphore::Down() noexcept
{
    bool isContinue = true;

    while(isContinue) {
        isContinue = false;
        if(sem_wait(&m_sem) != 0) {
            switch (errno)
            {
                case EINVAL:
                    assert(!"wait failed: invalid semaphore");
                    break;
                case EINTR:
                    isContinue = true;
                    break;
            }
        }
    }
    
}

void Semaphore::Up()
{
    if(sem_post(&m_sem) != 0) {
        switch (errno)
        {
            case EINVAL:
                assert(!"post failed: invalid semaphore");
                break;
                
            default:
                throw SemaphoreException("sem post failed", errno);
                break;
        }
    }
}


}//threads