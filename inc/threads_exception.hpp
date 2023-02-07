
#ifndef SM_THREADS_EXCEPTION_HPP
#define SM_THREADS_EXCEPTION_HPP

#include <string>
#include <exception>

namespace threads {

class ThreadsException : public std::exception {
public:
    ThreadsException(const char* a_what, int a_errno);
    virtual ~ThreadsException() = default;

    virtual const char* what() const throw(); 
    int getErrno() const;

protected:
    std::string m_what;
    int m_errno;
};

}//threads

#include "inl/threads_exception.hxx"

#endif /* SM_THREADS_EXCEPTION_HPP */