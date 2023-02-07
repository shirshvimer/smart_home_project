
#ifndef SM_EXCEPTION_HPP
#define SM_EXCEPTION_HPP

#include <string>
#include <exception>

namespace exception {

class Exception : public std::exception {
public:
    Exception(const char* a_functionName, const char* a_what);

    virtual ~Exception() = default;

    virtual const char* what() const throw(); 

protected:
    std::string m_func;
    std::string m_what;
};

}//exception

#include "inl/exception.hxx"

#endif /* SM_EXCEPTION_HPP */