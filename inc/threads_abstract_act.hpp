#ifndef THREADS_WQ_HPP 
#define THREADS_WQ_HPP

namespace threads {

class AbstractAct {
public:
    virtual ~AbstractAct() = default;
    virtual void Act() = 0;

protected:
    AbstractAct() = default;
    AbstractAct(AbstractAct const& a_other) = default;
    AbstractAct& operator=(AbstractAct const& a_other) = default;
}; 

}//threads

#endif /* THREADS_WQ_HPP */