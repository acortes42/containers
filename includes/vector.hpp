#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "containers.hpp"

namespace ft
{
	template<class InputIterator> typename ft::iterator_traits<InputIterator>::difference_type
    distance (InputIterator first, InputIterator last)
    {
        typename ft::iterator_traits<InputIterator>::difference_type rtn = 0;
        while (first != last)
        {
            first++;
            rtn++;
        }
        return (rtn);
    }

	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:

			typedef T                                           value_type;
			typedef Alloc                                       allocator_type;
			typedef typename allocator_type::reference          reference;
			typedef typename allocator_type::const_reference    const_reference;
			typedef typename allocator_type::pointer            pointer;
			typedef typename allocator_type::const_pointer      const_pointer;
			typedef ft::random_access_iterator<value_type>      iterator;
			typedef ft::random_access_iterator<const value_type>  const_iterator;
			typedef ft::reverse_iterator<iterator>             reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>       const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type    difference_type; 
			typedef typename allocator_type::size_type          size_type;
			
			explicit vector (const allocator_type& alloc2 = allocator_type())
			{
				alloc = alloc2;
				firts_elem = u_nullptr;
				last_elem = u_nullptr;
				allocated_size = u_nullptr;
			}

			explicit vector (size_type n, const value_type& val = value_type(),
            	const allocator_type& alloc2 = allocator_type())
			{
				alloc = alloc2;
				firts_elem = u_nullptr;
				last_elem = u_nullptr;

				firts_elem = alloc.allocate(n);
				last_elem = firts_elem;
				allocated_size = firts_elem + n;
				while(n > 0)
				{
					alloc.construct(last_elem, val); 
					last_elem++;
				}
			}

			template<class InputIterator>
         	vector (InputIterator first, InputIterator last, const allocator_type& alloc2 = allocator_type())
			{
				alloc = alloc2;
				firts_elem = u_nullptr;
				last_elem = u_nullptr;
				allocated_size = u_nullptr;
				difference_type distance = ft::distance(first, last);

				firts_elem = alloc.allocate(distance);
				last_elem = firts_elem;
				allocated_size = firts_elem + distance;
				while(first != last)
				{
					alloc.construct(last_elem, first); 
					last_elem++;
					first++;
				}
			}
			
			vector (const vector& x)
			{
				int distance;

				alloc = x.alloc;
				firts_elem = u_nullptr;
				last_elem = u_nullptr;
				allocated_size = u_nullptr;

				distance = distance(x.begin(), x.end());
				pointer start = x.begin();
				firts_elem = alloc.allocate(distance);
				last_elem = firts_elem;
				allocated_size = firts_elem + distance;
				while(distance > 0)
				{
					alloc.construct(last_elem, start); 
					last_elem++;
					start++;
					distance--;
				}
			}

			// Destructor

			~vector<T>()
			{
        		alloc.deallocate(this->firts_elem, this->capacity());
			};

			// Iterators

			iterator begin(){return(firts_elem);}
			
			const_iterator begin() const{return(firts_elem);}
			
			iterator end(){return(last_elem);}

			const_iterator end() const{return(last_elem);}

			reverse_iterator rbegin(){return(reverse_iterator(this->last_elem));}
			const_reverse_iterator rbegin() const{return(const_reverse_iterator(this->end));}
			
			reverse_iterator rend() {return(reverse_iterator(this->firts_elem));}
			const_reverse_iterator rend() const {return(const_reverse_iterator(this->firts_elem));}

			//Capacity

			size_type size(void) const
			{
				return (this->last_elem - this->firts_elem);
			}

			size_type max_size() const{ return ((size_t)(-1) / sizeof(this)); }

			void resize (size_type n, value_type val = value_type())
			{
				try
				{
					while (n > size())
					{
						this->push_back(val);
					}
				}
				catch(...)
				{
					std::cerr << "Error in resize" << '\n';
				}
			}

			size_type capacity(void) const
			{
				return (this->allocated_size - this->firts_elem);
			}

			bool empty() const
			{
				return size() == 0?true:false;
			}

			void	reserve(size_type n)
			{
				size_type x;

				x = 0;
				pointer old_last = last_elem;
				pointer old_first = firts_elem;
				size_type old_size = size();
				size_type old_allocated_size = capacity();

				firts_elem = alloc.allocate(n);
				last_elem = firts_elem;
				allocated_size = firts_elem + n;
				while(old_first != old_last)
				{
					alloc.construct(last_elem, *old_first); 
					old_first++;
					last_elem++;
				}
				alloc.deallocate(old_first - old_size, old_allocated_size);
			}

			// Element access

			reference operator[] (size_type n) { return (*(firts_elem + n)); }

			const_reference operator[] (size_type n) const { return (*(firts_elem + n)); }
			
			reference at(size_type n)
			{
				if (n >= this->size())
					throw std::out_of_range("Out of range");
				return (*(this->firts_elem + n));
			}

			const_reference at (size_type n) const
			{
				if (n >= this->size())
					throw std::out_of_range("Out of range");
				return (*(this->firts_elem + n));
			}

			reference front() { return (*v_data);}
			const_reference front() const { *v_data; }
			reference back() { return (*(v_data + (size() - 1)));}
			const_reference back() const { return (*(v_data + (size() - 1))); }

			//Modifiers

			template <class InputIterator>
			void assign (InputIterator first, InputIterator last)
			{
				
			}
			
			void push_back(T value)
			{
				size_type n;
				if(last_elem == allocated_size)
				{
					if(capacity() > 0)
						n = size() * 2;
					else
						n = 1;
					reserve(n);
				}
				alloc.construct(last_elem, value); 
				last_elem++;
				
			}
		/*
			

			

			T* data()
			{
				return (v_data);
			}

			void assign (unsigned int n, const T& val)
			{
				unsigned int x;

				x = 0;
				while (x++ < n)
					this->push_back(val);
			}

			void assign (iterator first, iterator last)
			{
				for(iterator it = first.begin(); it != last.end(); ++it)
					this->push_back(it);
			}
			
			void pop_back()
			{
				T	*v_data_tmp;
				unsigned int	x;

				x = 0;
				if (last_elem > 0)
				{
					v_data_tmp = this->alloc.allocate(this->allocated_size);
					while (x < last_elem)
					{
						v_data_tmp[x] = this->v_data[x];
						x++;
					}
					delete(v_data);
					last_elem--;
					this->v_data = this->alloc.allocate(allocated_size);
					this->v_data = v_data_tmp;
				}
			}
			
			iterator insert (iterator position, const T& val)
			{
				T				*v_data_tmp;
				unsigned int	x;

				x = 0;
				if (this->last_elem >= this->allocated_size)
				{
					this->allocated_size *= 2;
					v_data_tmp = this->alloc.allocate(this->allocated_size);
					for (unsigned int i = 0 ; i < this->last_elem ; i++)
						v_data_tmp[i] = this->v_data[i];
					this->v_data = this->alloc.allocate(allocated_size);
					this->v_data = v_data_tmp;
				}
				for(iterator it = v_data.begin(); it != first.end(); ++it)
					this->v_data[this->last_elem++] = val;
			}
			*/

		private:

		allocator_type	alloc;
		pointer 		firts_elem;
		pointer			last_elem;
		pointer			allocated_size;
	};
	
}

#endif