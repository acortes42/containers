#ifndef ITERATOR_HPP
#define ITERATOR_HPP

namespace ft
{
    static class nullptr_t
    {
        public:

            template<class T>
            operator T*() const
            {
                return (0);
            }

            template<class C, class T>
            operator T C::*() const
            {
                return (0);
            }

        private:
            
            void operator&() const;

    } u_nullptr = {};

    template <class Category, class T, class Distance = ptrdiff_t,
          class Pointer = T*, class Reference = T&>
    struct iterator 
    {
        typedef T         value_type;
        typedef Distance  difference_type;
        typedef Pointer   pointer;
        typedef Reference reference;
        typedef Category  iterator_category;
    };

    // input_iterator_tag

    struct input_iterator_tag { };

    // output_iterator_tag

    struct output_iterator_tag { };

    // forward_iterator_tag

    struct forward_iterator_tag : public input_iterator_tag { };

    // bidirectional_iterator_tag

    struct bidirectional_iterator_tag : public forward_iterator_tag { };

    // random_access_iterator_tag
    
    struct random_access_iterator_tag : public bidirectional_iterator_tag { };

    //iteration_traits

    template <class T>
    class bidirectional_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
    {  
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category     iterator_category;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type            value_type;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type       difference_type;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer               pointer;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference             reference;
        
        private:
            pointer _elem;
    };

    template <class Iterator> 
    struct iterator_traits
    {
        typedef typename Iterator::iterator_category iterator_category;
        typedef typename Iterator::difference_type difference_type;
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::pointer pointer;
        typedef typename Iterator::reference reference;
    };

    template< class T >
    struct iterator_traits<T*>
    {
        typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;
        typedef random_access_iterator_tag iterator_category;
    };

    template< class T >
    struct iterator_traits<const T*>
    {
        typedef ptrdiff_t difference_type;
        typedef const T value_type;
        typedef const T* pointer;
        typedef const T& reference;
        typedef random_access_iterator_tag iterator_category;
    };

    template <typename T>
        class random_access_iterator : ft::iterator<ft::random_access_iterator_tag, T>
        {
            public:
                
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category     iterator_category;
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type            value_type;
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type       difference_type;
            typedef T*               pointer;
            typedef T&             reference;

            random_access_iterator(void)
            {
                _iter = u_nullptr;
            }
            
            random_access_iterator(pointer elem)  
            {
                _iter = elem;
            }

            random_access_iterator(const random_access_iterator& op)                
            {
                _iter = op._iter;
            }

            random_access_iterator &operator=(const random_access_iterator& op)
            {
                if (this == &op)
                    return (*this);
                this->_iter = op._iter;
                return (*this);
            }

            virtual ~random_access_iterator() {}

            pointer base() const
            {
                return (this->_iter);
            }

            reference operator*(void) const 
            { 
                return (*_iter); 
            }

            pointer operator->(void)
            {
                return (this->operator*()); 
            }

            random_access_iterator& operator++(void)
            {
                _iter++;
                return (*this);
            }

            random_access_iterator operator++(int)
            {
                random_access_iterator rtn(*this);
                operator++();
                return (rtn);
            }

            random_access_iterator& operator--(void)
            {
                _iter--;
                return (*this);
            }

            random_access_iterator operator--(int)
            {
                random_access_iterator rtn(*this);
                operator--();
                return (rtn);
            }

            random_access_iterator operator+(difference_type n) const
            {
                return (_iter + n);
            }

            random_access_iterator operator-(difference_type n) const
            {
                return (_iter - n);
            }

            random_access_iterator& operator+=(difference_type n)
            {
                _iter += n;
                return (*this);
            }

            random_access_iterator& operator-=(difference_type n)
            {
                _iter -= n;
                return (*this);
            }

            reference operator[](difference_type n) { return (*(operator+(n))); }

            operator random_access_iterator<const T> () const
            { return (random_access_iterator<const T>(this->_iter)); }

            private:
                pointer _iter;
        };
    
    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator!=(const ft::random_access_iterator<T> lhs,
              const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() != rhs.base());
    }

    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator==(const ft::random_access_iterator<T> lhs,
              const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() == rhs.base());
    }

    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator>(const ft::random_access_iterator<T> lhs,
              const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() > rhs.base());
    }

    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator<(const ft::random_access_iterator<T> lhs,
              const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() < rhs.base());
    }

    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator<=(const ft::random_access_iterator<T> lhs,
              const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator>=(const ft::random_access_iterator<T> lhs,
              const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() >= rhs.base());
    }
}

#endif
