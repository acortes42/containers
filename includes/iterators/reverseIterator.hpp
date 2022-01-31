#ifndef REVERSEITERATOR_HPP
#define REVERSEITERATOR_HPP

#include "iterator.hpp"

namespace ft
{
    template <class Iterator> 
    class reverse_iterator
    {
        public:

            typedef Iterator iterator_type;
            typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
            typedef typename iterator_traits<Iterator>::value_type value_type;
            typedef typename iterator_traits<Iterator>::difference_type difference_type;
            typedef typename iterator_traits<Iterator>::pointer pointer;
            typedef typename iterator_traits<Iterator>::reference reference;

            reverse_iterator()
            { 
                _iter();
            };

            explicit reverse_iterator( iterator_type x )
            {
                _iter(x);
            };

            template< class U >reverse_iterator( const reverse_iterator<U>& other ) 
            {
                _iter(other.base());
            };

            iterator_type base() const
            {
                return(_iter);
            };

            reference operator*() const
            {
                iterator_type x= _iter.base();
                return (*(--x)); 
            };

            reverse_iterator operator+ (difference_type n) const
            {
                return (reverse_iterator(_iter.base() - n));
            };

            reverse_iterator& operator++()
            {
                *this--;
                return(*this);
            };
                        
            reverse_iterator& operator++(int)
            {
                reverse_iterator tmp = *this;
                --(*this);
                return (*tmp);
            };
            
            reverse_iterator& operator+= (difference_type n)
            {
                _iter -= n;
                return(*this);
            }

            reverse_iterator operator- (difference_type n) const
            {
                return (reverse_iterator(_iter.base() + n));
            };

            reverse_iterator& operator--()
            {
                *this++;
                return(*this);
            };

            reverse_iterator& operator--(int)
            {
                reverse_iterator tmp = *this;
                ++(*this);
                return (*tmp);
            };

            reverse_iterator& operator-= (difference_type n)
            {
                _iter += n;
                return(*this);
            }

            pointer operator->() const
            {
                return &(operator*());
            }
            
            reference operator[] (difference_type n) const
            {
                return(this->base()[-n-1]);
            }

            // relational operators (reverse_iterator)

        private:

            iterator_type _iter;
    };
}
#endif