#ifndef THREADS_BLOCKING_QUEUE_HXX
#define THREADS_BLOCKING_QUEUE_HXX

#include "threads_blocking_queue.hpp"

namespace threads {

template <typename T>
BlockingQueue<T>::BlockingQueue(size_t a_capacity)
: m_isLimited(a_capacity != 0)
, m_queue()
, m_capacity(a_capacity)
, m_mutex(1)
, m_full(0)
, m_empty(a_capacity == 0 ? 0 : a_capacity)
#ifdef DEBUG_TIMESTAMP
, pushCount(1)
, popCount(1)
#endif
{
}

template <typename T>
void BlockingQueue<T>::EnQueue(T const& a_item)
{
    if(m_isLimited) {
        m_empty.Down();
    }
    m_mutex.Down();

    try {
        #ifdef DEBUG_TIMESTAMP
            a_item.m_pushCounter = pushCount;
            ++pushCount;
        #endif
        m_queue.push(a_item); // copy
    }
    catch(...) {
        m_mutex.Up();

        if(m_isLimited) {
            m_empty.Up();
        }

        throw BlockingQueueException("push", "push failed");
    }

    m_mutex.Up();
    m_full.Up();

}

template <typename T>
void BlockingQueue<T>::EnQueue(T && a_item)
{
    if(m_isLimited) {
        m_empty.Down();
    }
    m_mutex.Down();

    try {
        #ifdef DEBUG_TIMESTAMP
            a_item.m_pushCounter = pushCount;
            ++pushCount;
        #endif
        m_queue.push(std::move(a_item)); // move
    }
    catch(...) {
        m_mutex.Up();

        if(m_isLimited) {
            m_empty.Up();
        }

        throw BlockingQueueException("push", "push failed");
    }

    m_mutex.Up();
    m_full.Up();

}

template <typename T>
void BlockingQueue<T>::DeQueue(T& a_buff)
{
    m_full.Down();
    m_mutex.Down();

    try {
        a_buff = std::move(m_queue.front()); //assignment operator- can fail if not exist
        m_queue.pop();

        #ifdef DEBUG_TIMESTAMP
            a_buff.m_popCounter = popCount;
            ++popCount;
        #endif
    }
    catch(...) {
        m_mutex.Up();
        m_full.Up();
        throw BlockingQueueException("pop", "pop failed");
    }

    m_mutex.Up();

    if(m_isLimited) {
        m_empty.Up();
    }
}

template <typename T>
size_t BlockingQueue<T>::Size() const
{
    m_mutex.Down();
    size_t size = m_queue.size();
    m_mutex.Up();

    return size;
}

template <typename T>
bool BlockingQueue<T>::IsEmpty() const
{
    m_mutex.Down();
    bool result = m_queue.empty();
    m_mutex.Up();

    return result;
}

}//threads

#endif /* THREADS_BLOCKING_QUEUE_HXX */