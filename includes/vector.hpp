#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "iterators/reverseIterator.hpp"

namespace ft
{
	template< typename T > 
	class vector
	{
		private:

			T					*v_data;
			std::allocator<T>	alloc;
			unsigned int		last_elem;
			unsigned int		allocated_size;

		public:

			typedef typename std::allocator<T>::reference		reference;
		    typedef typename std::allocator<T>::const_reference	const_reference;

			typedef Iterator<T>              iterator;
    		typedef Iterator<const T>        const_iterator;

    		typedef ReverseIterator<T>       reverse_iterator;
    		typedef ReverseIterator<const T> const_reverse_iterator;

			iterator                                       begin(){return iterator(&v_data[0]);}
    		iterator                                       end(){return iterator(&v_data[last_elem]);}
    		
			const_iterator                                 cbegin(){return const_iterator(&v_data[0]);}
    		const_iterator                                 cend(){return const_iterator(&v_data[last_elem]);}

    		reverse_iterator                               rbegin(){return reverse_iterator(&v_data[last_elem - 1]);}
    		reverse_iterator                               rend(){return reverse_iterator(&v_data[-1]);}

    		const_reverse_iterator                         crbegin(){return const_reverse_iterator(&v_data[last_elem - 1]);}
    		const_reverse_iterator                         crend(){return const_reverse_iterator(&v_data[-1]);}
			
			vector<T>()
			{
				this->v_data = this->alloc.allocate(1);
				this->allocated_size = 1;
				this->last_elem = 0;
			}

			vector<T>(unsigned int x, unsigned int y)
			{
				this->v_data = this->alloc.allocate(1);
				this->allocated_size = 1;
				this->last_elem = 0;
				for (unsigned int i = 0; i < x; i++)
					push_back(y);
			}

	//		vector<T>(vector::iterator begin, vector::iterator end){}   ***Falta implementar***

			vector<T>(vector &other)
			{
				alloc.deallocate(this->v_data, this->allocated_size);
				this->v_data = other.v_data;
				this->allocated_size = other.allocated_size;
				this->last_elem = other.last_elem;
			}
			~vector<T>()
			{
        		alloc.deallocate(this->v_data, this->allocated_size);
			};

			vector &operator =(vector& other)
			{
				if (this == &other)
					return (*this);
				alloc.deallocate(this->v_data, this->allocated_size);
				this->allocated_size = other.allocated_size;
				this->last_elem = 0;
				this->v_data = this->alloc.allocate(this->allocated_size);
				for (unsigned int i = 0; i < other.last_elem; i++)
					push_back(other[i]);
				return (*this);
			}

			T& operator[](unsigned int x)
			{
				if (x >= this->last_elem)
					throw std::out_of_range("Out of range");
				return (this->v_data[x]);
			}

			void push_back(T value)
			{
				T	*v_data_tmp;
				if (this->last_elem >= this->allocated_size)
				{
					this->allocated_size *= 2;
					v_data_tmp = this->alloc.allocate(this->allocated_size);
					for (unsigned int i = 0 ; i < this->last_elem ; i++)
						v_data_tmp[i] = this->v_data[i];
					this->v_data = this->alloc.allocate(allocated_size);
					this->v_data = v_data_tmp;
				}
				this->v_data[this->last_elem++] = value;
			}

			unsigned int size() { return (last_elem); }
			unsigned long max_size(){ return ((size_t)(-1) / sizeof(this)); }
			unsigned int capacity() { return (allocated_size); }
			bool empty() {return (last_elem ? true : false) ;}

			void	resize(unsigned int x)
			{
				try
				{
					while (x > last_elem)
						this->push_back("");
				}
				catch(...)
				{
					std::cerr << "Error in resize" << '\n';
				}
			}

			void	resize(unsigned int x, T y)
			{
				while (x > last_elem)
					this->push_back(y);
			}

			void reserve(unsigned int x)
			{
				try 
				{
					if (x > allocated_size)
						allocated_size = x;
  				}
				catch (const std::length_error& le)
				{
		  			std::cerr << "Length error: " << le.what() << '\n';
				}
				return ;
			}
			
			reference at(unsigned int x)
			{
				if (x >= this->last_elem)
					throw std::out_of_range("Out of range");
				return (*(v_data + x));
			}

			reference front() { return (*v_data);}
			const_reference front() const { *v_data; }
			reference back() { return (*(v_data + (last_elem - 1)));}
			const_reference back() const { return (*(v_data + (last_elem - 1))); }

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

	};
}

#endif