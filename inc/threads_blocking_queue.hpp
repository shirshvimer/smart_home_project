#ifndef THREADS_BLOCKING_QUEUE_HPP
#define THREADS_BLOCKING_QUEUE_HPP

#include <mutex>
#include <queue>

#include "exception.hpp"
#include "threads_semaphore.hpp"

namespace threads {

class BlockingQueueException: public exception::Exception  {
public:
    BlockingQueueException(const char* fn, const char* w) : Exception(fn, w) {}
};


template <typename T>
class BlockingQueue {
public:
    explicit BlockingQueue(size_t a_capacity = 0);
    ~BlockingQueue() = default;
    BlockingQueue(BlockingQueue const& a_other) = delete;
    BlockingQueue& operator=(BlockingQueue const& a_other) = delete;

    void EnQueue(T const& a_item);
    void EnQueue(T && a_item);
    void DeQueue(T& a_buff);
    size_t Size() const;
    bool IsEmpty() const;

private:
    bool m_isLimited;
    std::queue<T> m_queue;
    size_t m_capacity;
    mutable Semaphore m_mutex;
    Semaphore m_full;
    Semaphore m_empty;

#ifdef DEBUG_TIMESTAMP
private:
    size_t pushCount;
    size_t popCount;
#endif
};

}//threads

#include "inl/threads_blocking_queue.hxx"

#endif /* THREADS_BLOCKING_QUEUE_HPP */