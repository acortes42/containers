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
			:
				alloc(alloc2),
				firts_elem(u_nullptr),
				last_elem(u_nullptr),
				allocated_size(u_nullptr)
			{}

			explicit vector (size_type n, const value_type& val = value_type(),
            	const allocator_type& alloc2 = allocator_type())
			:
				alloc(alloc2),
				firts_elem(u_nullptr),
				last_elem(u_nullptr),
				allocated_size(u_nullptr)
			{
				firts_elem = alloc.allocate(n);
				allocated_size = firts_elem + n;
				last_elem = firts_elem;
				while(n--)
				{
					alloc.construct(last_elem, val);
					last_elem++;
				}
			}

         	vector (iterator first, iterator last, const allocator_type& alloc2 = allocator_type())
			:
			 	alloc(alloc2),
				firts_elem(u_nullptr),
				last_elem(u_nullptr),
				allocated_size(u_nullptr)

			{
				size_type i = 0;
				size_type n = this->distance(first, last);
				firts_elem = alloc.allocate(n);
				allocated_size = firts_elem + n;
				last_elem = firts_elem;
				while( i < n)
				{
					alloc.construct(last_elem, *first);
					last_elem++;
					*first++;
					i++;
				}
			}
			
			vector (const vector& x)
			:
				alloc(x.alloc),
				firts_elem(u_nullptr),
				last_elem(u_nullptr),
				allocated_size(u_nullptr)
			{
				size_type n;

				n = x.size();
				for(size_type i = 0; i < n; i++)
					this->push_back(x[i]);
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

			iterator end() 
			{
				if(this->empty())
					return(firts_elem);
				return(last_elem);
			}

			const_iterator end() const
			{
				if(this->empty())
					return(firts_elem);
				return(last_elem);
			}

			reverse_iterator rbegin(){return(reverse_iterator(this->last_elem));}
			const_reverse_iterator rbegin() const{return(const_reverse_iterator(this->end));}
			
			reverse_iterator rend() {return(reverse_iterator(firts_elem));}
			const_reverse_iterator rend() const {return(const_reverse_iterator(firts_elem));}

			//Capacity

			size_type size(void) const
			{
				return (this->last_elem - this->firts_elem);
			}

			size_type distance (iterator first, iterator last)
			{
				size_type n;

				n = 0;
				while (first != last)
				{
					first++;
					n++;
				}
				return (n);
			}

			size_type max_size() const{ return ((size_t)(-1) / sizeof(this)); }

			void resize (size_type n, value_type val = value_type())
			{
				if(n > this->size())
				{
					size_type i =  n - this->size();
					while(i--)
						this->push_back(val);
				}
				else
				{
					size_type i = this->size() - n;
					while(i--)
						this->pop_back();
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
			
			vector &operator=(const vector& x)
			{
				size_type n;

				n = x.size();
				if (this == &x)
					return(*this);
				this->clear();
				for(size_type i = 0; i < n; i++)
					this->push_back(x[i]);
				return(*this);
			}

			bool operator==(const vector& x)
			{
				if (this->size() != x.size())
					return(false);
				const_iterator new_other_begin = x.begin();
				const_iterator new_other_end = x.end();
				iterator new_this_begin = this->begin();
				while(new_this_begin != this->end())
				{
					if (*new_other_begin == new_other_end || *new_this_begin != *new_other_begin)
						return(false);
					*new_other_begin++;
					*new_this_begin++;
				}
				return (true);
			}

			reference operator[] (size_type n) { return (at(n)); }

			const_reference operator[] (size_type n) const { return (at(n)); }
			
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
			reference back() { return (firts_elem[this->size() - 1]);}
			const_reference back() const { return (*last_elem); }

			//Modifiers

			// Problema al hacer el overload en assign

			void assign (size_type n, const value_type& val)
			{
				this->clear();

				this->firts_elem = alloc.allocate(n);
				this->allocated_size = this->firts_elem + n;
				this->last_elem = this->firts_elem;
				while(n--)
				{
					alloc.construct(last_elem, val);
					this->last_elem++;
				}
			}

  			void assign (iterator first, iterator last)
			{
				this->clear();
				size_type i = 0;
				size_type n = this->distance(first, last);
				firts_elem = alloc.allocate(n);
				allocated_size = firts_elem + n;
				last_elem = firts_elem;
				while( i < n)
				{
					alloc.construct(last_elem, *first);
					last_elem++;
					*first++;
					i++;
				}
			};

			void push_back(T value)
			{
				if (last_elem == allocated_size)
				{
					int next_capacity = (this->size() > 0) ? (int)(this->size() * 2) : 1;
					this->reserve(next_capacity);
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
	
				size_type next_capacity = 0;
				if (size_type(allocated_size - last_elem) <= 1)
				{
					for(size_type i = 0; i < pos_len; i++)
						alloc.construct(last_elem - i, *(last_elem - i - 1));
					last_elem++;
					alloc.construct(last_elem - pos_len, val);
				}
				else
				{
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
				}
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
				
				if (size_type(allocated_size - last_elem + n) >= 1)
				{
					for (size_type i = 0; i < this->size() - pos_len; i++)
						alloc.construct(last_elem - i + (n - 1), *(last_elem - i - 1));
					last_elem += n;
					while (n)
					{
						alloc.construct(&(*position) + (n - 1), val);
						n--;
					}
				}
				next_capacity = (capacity * 2 > 0) ? capacity * 2 : 1; 
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

    		void insert (iterator position, iterator first, iterator last)
			{
				size_type pos_len = &(*position) - firts_elem;
				pointer newfirts_elem = pointer();
				pointer newlast_elem = pointer();
				pointer newcapacity = pointer();
				size_type capacity;
				size_type next_capacity;
				size_type n;


				capacity = this->capacity();
				next_capacity = 0;
				n = this->distance(first, last);
				if (size_type(allocated_size - last_elem + n) >= 1)
				{
					for (size_type i = 0; i < this->size() - pos_len; i++)
						alloc.construct(last_elem - i + (n - 1), *(last_elem - i - 1));
					last_elem += n;
					while (first != last)
					{
						alloc.construct(&(*position), *first);
						first++;
						position++;
					}
				}
				next_capacity = (capacity * 2 > 0) ? capacity * 2 : 1;
				newfirts_elem = alloc.allocate( next_capacity );
				newlast_elem = newfirts_elem + this->size() + n;
				newcapacity = newfirts_elem + next_capacity;
				for (size_type i = 0; i < pos_len; i++)
					alloc.construct(newfirts_elem + i, *(firts_elem + i));
				for (size_type i = 0; i < n; i++)
				{
					alloc.construct(newfirts_elem + pos_len + i, *first);
					first++;
				}
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