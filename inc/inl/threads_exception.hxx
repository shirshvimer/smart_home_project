#include "threads_exception.hpp"
#include <iostream>

namespace threads {

inline ThreadsException::ThreadsException(const char* a_what, int a_errno) 
: m_what(a_what) 
, m_errno(a_errno)
{
}

inline const char* ThreadsException::what() const throw() 
{ 
    std::cout << "errno: " << m_errno;
    return m_what.c_str(); 
}

inline int ThreadsException::getErrno() const
{ 
    return m_errno;
}


}//threads
