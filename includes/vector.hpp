#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "containers.hpp"

namespace ft
{
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
				difference_type distance = distance(first, last);

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
				this->clear();
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

			size_type distance (iterator first, iterator last)
			{
				size_type rtn = 0;
				while (first != last)
				{
					first++;
					rtn++;
				}
				return (rtn);
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
				size_type oldallocated_size = capacity();

				firts_elem = alloc.allocate(n);
				last_elem = firts_elem;
				allocated_size = firts_elem + n;
				while(old_first != old_last)
				{
					alloc.construct(last_elem, *old_first); 
					old_first++;
					last_elem++;
				}
				alloc.deallocate(old_first - old_size, oldallocated_size);
			}

			// Element access
			
			//vector &operator=(const vector& x){}

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

			reference front() { return (*firts_elem);}
			const_reference front() const {return (*firts_elem);}
			reference back() { return (*last_elem);}
			const_reference back() const { return (*last_elem); }

			//Modifiers

			// Problema al hacer el overload en assign

			template <class InputIterator>
  			void assign (InputIterator first, InputIterator last)
			{
				this->clear();
				while(first != last)
				{
					alloc.construct(last_elem, first); 
					last_elem++;
					first++;
				}
			};
			
			void assign (size_type n, const value_type& val)
			{
				size_type i = 0;
				this->clear();
				while (i++ < n)
					push_back(val);
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

			void pop_back()
			{
				alloc.destroy(&this->back());
				last_elem--;
				
			}

			iterator insert (iterator position, const value_type& val)
			{
				size_type pos_len = &(*position) - firts_elem;
				pointer newfirts_elem = pointer();
				pointer newlast_elem = pointer();
				pointer newcapacity = pointer();

				int next_capacity = 0;
				if (size_type(allocated_size - last_elem) >= 1)
					next_capacity = this->capacity();
				else
					next_capacity = (this->capacity() * 2 > 0) ? this->capacity() * 2 : 1; 
				newfirts_elem = alloc.allocate( next_capacity );
				newlast_elem = newfirts_elem + this->size() + 1;
				newcapacity = newfirts_elem + next_capacity;
				for (size_type i = 0; i < pos_len; i++)
					alloc.construct(newfirts_elem + i, *(firts_elem + i));
				alloc.construct(newfirts_elem + pos_len, val);
				for (size_type j = 0; j < this->size() - pos_len; j++)
					alloc.construct(newlast_elem - j - 1, *(last_elem - j - 1));

				for (size_type l = 0; l < this->size(); l++)
					alloc.destroy(firts_elem + l);
				if (firts_elem)
					alloc.deallocate(firts_elem, this->capacity());
				firts_elem = newfirts_elem;
				last_elem = newlast_elem;
				allocated_size = newcapacity;
				return (iterator(firts_elem + pos_len));
			}
	
			// Por ahora, insert no entra aqui cuando deberia. Se va al de abajo. De momento, cambie el de abajo a iterator. Revisar

			void insert (iterator position, size_type n, const value_type& val)
			{
				size_type pos_len = &(*position) - firts_elem;
				pointer newfirts_elem = pointer();
				pointer newlast_elem = pointer();
				pointer newcapacity = pointer();
				size_type capacity = this->capacity();

				size_type next_capacity = 0;
				while(next_capacity < (capacity + n))
				{
					if (size_type(allocated_size - last_elem) >= n)
						next_capacity = capacity;
					else
						next_capacity = (capacity * 2 > 0) ? capacity * 2 : 1; 
				}
				
				newfirts_elem = alloc.allocate( next_capacity );
				newlast_elem = newfirts_elem + this->size() + n;
				newcapacity = newfirts_elem + next_capacity;
				for (size_type i = 0; i < pos_len; i++)
					alloc.construct(newfirts_elem + i, *(firts_elem + i));
				for (size_type i = 0; i < n; i++)
					alloc.construct(newfirts_elem + pos_len + i, val);
				for (size_type j = 0; j < this->size() - pos_len; j++)
					alloc.construct(newlast_elem - j - 1, *(last_elem - j - 1));

				for (size_type l = 0; l < this->size(); l++)
					alloc.destroy(firts_elem + l);
				if (firts_elem)
					alloc.deallocate(firts_elem, capacity);
				firts_elem = newfirts_elem;
				last_elem = newlast_elem;
				allocated_size = newcapacity;
			}

			/*
			template <class InputIterator>
    		void insert (iterator position, InputIterator first, InputIterator last)
			{
				size_type pos_len = &(*position) - firts_elem;
				pointer newfirts_elem = pointer();
				pointer newlast_elem = pointer();
				pointer newcapacity = pointer();
				size_type capacity = this->capacity();

				size_type next_capacity = 0;
				size_type n = distance(first, last);

				while(next_capacity < (capacity + n))
				{
					std::cout << "capacty: " << capacity << std::endl;
					std::cout << "next capacty: " << next_capacity << std::endl;
					std::cout << "n: " << n << std::endl;
				
					if (size_type(allocated_size - last_elem) >= n)
						next_capacity = capacity;
					else
						next_capacity = (capacity * 2 > 0) ? capacity * 2 : 1; 
				}
				newfirts_elem = alloc.allocate( next_capacity );
				newlast_elem = newfirts_elem + this->size() + n;
				newcapacity = newfirts_elem + next_capacity;
				for (size_type i = 0; i < pos_len; i++)
					alloc.construct(newfirts_elem + i, *(firts_elem + i));
				for (size_type i = 0; i < n; i++)
					alloc.construct(newfirts_elem + pos_len + i, first++);
				for (size_type j = 0; j < this->size() - pos_len; j++)
					alloc.construct(newlast_elem - j - 1, *(last_elem - j - 1));

				for (size_type l = 0; l < this->size(); l++)
					alloc.destroy(firts_elem + l);
				if (firts_elem)
					alloc.deallocate(firts_elem, capacity);
				firts_elem = newfirts_elem;
				last_elem = newlast_elem;
				allocated_size = newcapacity;
			}
			*/
			iterator erase (iterator position)
			{
				pointer p_pos = &(*position);
				alloc.destroy(&(*position));
				if (&(*position) + 1 == last_elem)
					alloc.destroy(&(*position));
				else
				{
					for (int i = 0; i < last_elem - &(*position) - 1; i++)
					{
						alloc.construct(&(*position) + i, *(&(*position) + i + 1));
						alloc.destroy(&(*position) + i + 1);
					}
				}
				last_elem -= 1;
				return (iterator(p_pos));
			}

			iterator erase (iterator first, iterator last)
			{
				pointer p_first = &(*first);
				for (; &(*first) != &(*last); first++)
					alloc.destroy(&(*first));
				for (int i = 0; i < last_elem - &(*last); i++)
				{
					alloc.construct(p_first + i, *(&(*last) + i));
					alloc.destroy(&(*last) + i);
				}
				last_elem -= (&(*last) - p_first);
				return (iterator(p_first));
			}

			void swap(vector& x)
			{	
				pointer save_start = x.firts_elem;
				pointer save_end = x.last_elem;
				pointer save_end_capacity = x.allocated_size;
				allocator_type save_alloc = x.alloc;

				x.firts_elem = this->firts_elem;
				x.last_elem = this->last_elem;
				x.allocated_size = this->allocated_size;
				x.alloc = this->alloc;

				this->firts_elem = save_start;
				this->last_elem = save_end;
				this->allocated_size = save_end_capacity;
				this->alloc = save_alloc;	
			}

			void clear()
			{
				size_type size = this->size();
				for (size_type i = 0; i < size; i++)
				{
					last_elem--;
					alloc.destroy(last_elem);
				}
			}
		private:

			allocator_type	alloc;
			pointer 		firts_elem;
			pointer			last_elem;
			pointer			allocated_size;
	};
	
}

#endif