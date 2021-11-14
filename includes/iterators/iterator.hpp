#ifndef ITERATOR_HPP
#define ITERATOR_HPP


namespace ft
{
template<typename T>
class Iterator
{

public:

    Iterator(T* ptr = nullptr){m_ptr = ptr;}
    Iterator(const Iterator<T>& rawIterator);
    ~Iterator(){}

    Iterator<T>&                  operator=(const Iterator<T>& rawIterator);
    Iterator<T>&                  operator=(T* ptr){m_ptr = ptr;return (*this);}

    operator                                    bool()const
    {
        if(m_ptr)
            return true;
        else
            return false;
    }

    bool                                        operator==(const Iterator<T>& rawIterator)const{return (m_ptr == rawIterator.getConstPtr());}
    bool                                        operator!=(const Iterator<T>& rawIterator)const{return (m_ptr != rawIterator.getConstPtr());}

    Iterator<T>&                  operator+=(const std::ptrdiff_t& movement){m_ptr += movement;return (*this);}
    Iterator<T>&                  operator-=(const std::ptrdiff_t& movement){m_ptr -= movement;return (*this);}
    Iterator<T>&                  operator++(){++m_ptr;return (*this);}
    Iterator<T>&                  operator--(){--m_ptr;return (*this);}
    Iterator<T>                   operator++(int){T temp(*this);++m_ptr;return temp;}
    Iterator<T>                   operator--(int){T temp(*this);--m_ptr;return temp;}
    Iterator<T>                   operator+(const std::ptrdiff_t& movement){T oldPtr = m_ptr;m_ptr+=movement;T temp(*this);m_ptr = oldPtr;return temp;}
    Iterator<T>                   operator-(const std::ptrdiff_t& movement){T oldPtr = m_ptr;m_ptr-=movement;T temp(*this);m_ptr = oldPtr;return temp;}

    std::ptrdiff_t                             operator-(const Iterator<T>& rawIterator){return std::distance(rawIterator.getPtr(),this->getPtr());}

    T&                                 operator*(){return *m_ptr;}
    const T&                           operator*()const{return *m_ptr;}
    T*                                 operator->(){return m_ptr;}

    T*                                 getPtr()const{return m_ptr;}
    const T*                           getConstPtr()const{return m_ptr;}

protected:

    T*                                 m_ptr;
};
}
#endif
