#ifndef UTILITYFUNCTIONS
#define UTILITYFUNCTIONS

#include "iterator.hpp"
#include "reverseIterator.hpp"

namespace ft
{
	template<bool Cond, class T = void> struct enable_if {};
    template<class T> struct enable_if<true, T> { typedef T type; };

    // std::is_integral

    template <class T> struct is_integral
    {
         return (std::floor(val) == val);
    };
            
	template <class InputIterator1, class InputIterator2> bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, 
        InputIterator2 first2, InputIterator2 last2)
    {
        while (first1 != last1)
        {
            if (first2 == last2 || *first2 < *first1) return false;
            else if (*first1 < *first2) return true;
            ++first1;
            ++first2;
        }
        return (first2 != last2);
    };

    template <class InputIterator1, class InputIterator2, class Compare> bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
        InputIterator2 first2, InputIterator2 last2, Compare comp)
    {
        while (first1 != last1)
        {
            if (first2 == last2 || comp(*first2, *first1))
				return false;
            else if (comp(*first1, *first2))
				return true;
            ++first1;
            ++first2;
        }
        return (first2 != last2);
    }

    template <class T1, class T2> struct pair
    {
        typedef T1 first_type;
        typedef T2 second_type;

         private:

            first_type first;
            second_type second;

        public:

        	pair()
            {
                first();
				second();
            };

            template<class U, class V> pair (const pair<U,V>& pr)
            {
                this->first = pr.first;
                this->second = pr.second;
            };

            pair (const first_type& a, const second_type& b)
            {
                first(a);
                second(b);
            }

            pair& operator= (const pair& pr)
            {
                if (*this == pr)
                    return(*this);
                this->first = pr.first;
                this->second = pr.second;
                return(*this);
            }
	};
	
	template <class T1, class T2> pair<T1,T2> make_pair (T1 x, T2 y)
    {
        return ( pair<T1,T2>(x,y) );
    };
}
#endif