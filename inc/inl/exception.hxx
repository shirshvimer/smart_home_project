#include "exception.hpp"

namespace exception {

inline Exception::Exception(const char* a_functionName, const char* a_what) 
: m_func(a_functionName)
, m_what(a_what) 
{
}

inline const char* Exception::what() const throw() 
{ 
    return m_what.c_str(); 
}

}//exception
