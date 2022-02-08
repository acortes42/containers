#ifndef STACK_HPP
#define STACK_HPP

#include "containers.hpp"

namespace ft
{
	template < class T, class Container = std::deque<T> >
	class stack
	{
		public:

			typedef T value_type;
			typedef Container  container_type;
			typedef size_t size_type;

			explicit stack (const container_type& ctnr = container_type()){(void)ctnr;};
			bool empty() const{return (ctnr.empty());}
			size_type size() const{ return(ctnr.size());}
			value_type& top(){ return(ctnr.back());}
			const value_type& top() const{ return(ctnr.back());}
			void push (const value_type& val){ctnr.push_back(val);}
			void pop(){ctnr.pop_back() ;}

		private:
			container_type	ctnr;
	};
	
	template <class T, class Container>
  	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return(lhs.ctnr == rhs.ctnr);
	};

	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return(lhs.ctnr != rhs.ctnr);	
	}

	template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return(lhs.ctnr < rhs.ctnr);	
	}

	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return(lhs.ctnr <= rhs.ctnr);
	}

	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return(lhs.ctnr > rhs.ctnr);
	}

	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return(lhs.ctnr >= rhs.ctnr);
	}
}
#endif

