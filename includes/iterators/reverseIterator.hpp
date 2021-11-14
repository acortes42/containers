#ifndef REVERSEITERATOR_HPP
#define REVERSEITERATOR_HPP

#include "iterator.hpp"

namespace ft
{
template<typename T>
class ReverseIterator : public Iterator<T>
{
	public:

    ReverseIterator(T* ptr = nullptr):Iterator<T>(ptr){}
    ReverseIterator(const Iterator<T>& rawIterator){this->m_ptr = rawIterator.getPtr();}
    ReverseIterator(const ReverseIterator<T>& rawReverseIterator);
    ~ReverseIterator(){}

    ReverseIterator<T>&           operator=(const ReverseIterator<T>& rawReverseIterator);
    ReverseIterator<T>&           operator=(const Iterator<T>& rawIterator){this->m_ptr = rawIterator.getPtr();return (*this);}
    ReverseIterator<T>&           operator=(T* ptr){this->setPtr(ptr);return (*this);}

    ReverseIterator<T>&           operator+=(const std::ptrdiff_t& movement){this->m_ptr -= movement;return (*this);}
    ReverseIterator<T>&           operator-=(const std::ptrdiff_t& movement){this->m_ptr += movement;return (*this);}
    ReverseIterator<T>&           operator++(){--this->m_ptr;return (*this);}
    ReverseIterator<T>&           operator--(){++this->m_ptr;return (*this);}
    ReverseIterator<T>            operator++(int){T temp(*this);--this->m_ptr;return temp;}
    ReverseIterator<T>            operator--(int){T temp(*this);++this->m_ptr;return temp;}
    ReverseIterator<T>            operator+(const int& movement){T oldPtr = this->m_ptr;this->m_ptr-=movement;T temp(*this);this->m_ptr = oldPtr;return temp;}
    ReverseIterator<T>            operator-(const int& movement){T oldPtr = this->m_ptr;this->m_ptr+=movement;T temp(*this);this->m_ptr = oldPtr;return temp;}

    std::ptrdiff_t                             operator-(const ReverseIterator<T>& rawReverseIterator){return std::distance(this->getPtr(),rawReverseIterator.getPtr());}

    Iterator<T>                   base(){Iterator<T> forwardIterator(this->m_ptr); ++forwardIterator; return forwardIterator;}
};
}
#endif