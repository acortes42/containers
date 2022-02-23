#ifndef MAP_HPP
#define MAP_HPP

#include "iterators/binary_tree.hpp"
#include "containers.hpp"

namespace ft
{
	template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> > > 
	class map
	{
		public:

			typedef	Key	key_type;	
			typedef	T	mapped_type;
			typedef std::pair<Key, T>	value_type;
			typedef size_t	size_type;
			typedef	std::ptrdiff_t	difference_type;
			typedef	Compare	key_compare;
			typedef Allocator allocator_type;
			typedef	value_type&	reference;
			typedef const value_type&	const_reference;
			typedef typename Allocator::pointer pointer;
			typedef typename Allocator::const_pointer const_pointer;
			typedef Binary_tree<value_type, Compare>	BTree;
			
			typedef Node<value_type>	node;
			typedef node			*node_pointer;

			typedef typename ft::MapIterator<node, Compare>			iterator;
			typedef typename ft::MapIterator<node, Compare>			const_iterator;
			typedef typename ft::ReverseMapIterator<node, Compare>	reverse_iterator;	
			typedef typename ft::ReverseMapIterator<node, Compare>	const_reverse_iterator;

			class value_compare
			{   
				protected:

					Compare comp;
					
					
				public:

				value_compare (Compare c) : comp(c) {}

				typedef bool result_type;
				typedef value_type first_argument_type;
				typedef value_type second_argument_type;

				bool operator() (const value_type& x, const value_type& y) const
				{
					return comp(x.first, y.first);
				};
			};

			//constructors

			explicit map (const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type())
			:
				comparation(comp), 
				allocated(alloc),
				tree()
			{}

			template <class InputIterator>  map (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			:
				tree(),
				comparation(comp), 
				allocated(alloc)
			{
				tree->insert(std::make_pair(iterator(first, last), true));
			}

			map (const map& x)
			{
				this->root = x.root;
				this->allocated = x.allocated;
				this->comparation = x.comparation;
			}

			// DESTRUCTOR a revisar

			~map()
			{
				this->clear();
			};

			map& operator= (const map& x)
			{
				if (*this == x)
					return (*this);

				this->root = x.root;
				this->allocated = x.allocated;
				this->comparation = x.comparation;
			}
			
			// Right to the left, or right and right to the left...right?

			iterator begin()
			{
				return(iterator(this->tree._last_node->left, this->tree._last_node));
			}

			const_iterator const_begin() const
			{
				return(const_iterator(this->tree._last_node->left, this->tree._last_node));
			}

			reverse_iterator rbegin()
			{
				return(reverse_iterator(this->tree._last_node->right, this->tree._last_node));
			}

			const_reverse_iterator const_rbegin()
			{
				return(const_reverse_iterator(this->tree._last_node->right, this->tree._last_node));
			}

			iterator end()
			{
				return(iterator(this->tree._last_node, this->tree._last_node));
			}

			const_iterator const_end() const
			{
				return(const_iterator(this->tree._last_node, this->tree._last_node));
			}

			reverse_iterator rend()
			{
				return(reverse_iterator(this->tree._last_node, this->tree._last_node->left));
			}

			const_reverse_iterator const_rend() const
			{
				return(const_reverse_iterator(this->tree._last_node, this->tree._last_node->left));
			}

			// capacity

			bool empty() const
			{
				if (this->tree->left == this->tree->right)
					return(0);
				return(1);
			}

			size_type size() const
			{
				return(this->tree._last_node->pair.first);
			}

			size_type	max_size() const
			{ 
				return (std::numeric_limits<size_type>::max() / (sizeof(Node<value_type>)));
			}

			// Element access

			mapped_type& operator[] (const key_type& k)
			{
				const_iterator new_iter = this->find(k);

				if (new_iter == this->const_end())
					this->insert(std::make_pair(k, mapped_type()));
				return((*new_iter).second);
			}

			//modifiers
			
			std::pair<iterator,bool> insert (const value_type& val)
			{
				return(this->tree.insertPair(val));
			};
			
			iterator insert (iterator position, const value_type& val)
			{
				(void)position;
				return(this->tree.insertPair(val).first);
			}

			void insert (iterator first, iterator last)
			{
				while(first != last)
				{
					tree->insert(*first);
					first++;
				}
			}

			void erase (iterator position)
			{
				this->erase((*(position)).first);
			}
			
			size_type erase (const key_type& k)
			{
				iterator new_iter = this->find(k);

				if (new_iter == this->end())
					return(0);
				this->tree.removeByKey(std::make_pair(k, mapped_type()));
				return(1);
			}

     		void erase (iterator first, iterator last)
			 {
				while(last != first)
				{
					this->erase((*(last)).first);
					*last--;
				}
			 }

			void swap (map& x)
			{
				map tmp(*this);
				*this = x;
				x = tmp;
			}

			void clear()
			{
				this->erase(this->begin(), this->end());
			}

			//	Observers

			key_compare key_comp() const
			{
				return(key_compare());
			}

			value_compare value_comp() const
			{
				return(value_compare(key_comp()));
			}

			//	Operations

			iterator find (const key_type& k)
			{
				return(iterator(this->tree.searchByKey(std::make_pair(k, mapped_type())), this->tree._last_node));
			}

			const_iterator find (const key_type& k) const
			{
				return(const_iterator(this->tree.searchByKey(std::make_pair(k, mapped_type())), this->tree._last_node));
			}

			size_type count (const key_type& k) const
			{
				const_iterator new_iter = this->find(k);
				
				if (new_iter == this->const_end())
					return (0);
				return(1);
			}

			iterator lower_bound (const key_type& k)
			{
				iterator start = this->begin();
				iterator end = this->end();

				while(start != end)
				{
					if (comparation((*start).first, k) == false)
						break;
					start++;
				}
				return(start);
			}
			const_iterator lower_bound (const key_type& k) const
			{
				return(const_iterator(this->lower_bound(k)));
			}


			iterator upper_bound (const key_type& k)
			{
				iterator start = this->begin();
				iterator end = this->end();

				while(start != end)
				{
					if (comparation(k, (*start).first))
						break;
					start++;
				}
				return(start);
			}
			const_iterator upper_bound (const key_type& k) const
			{
				return(const_iterator(this->upper_bound(k)));
			}

			std::pair<const_iterator,const_iterator> equal_range (const key_type& k) const
			{
				return(std::make_pair(const_iterator(lower_bound(k)), const_iterator(upper_bound(k))));
			}
			
			std::pair<iterator,iterator> equal_range (const key_type& k)
			{
				return(std::make_pair(iterator(lower_bound(k)), iterator(upper_bound(k))));
			}

			// Allocator

			allocator_type get_allocator() const
			{
				return(this->allocated);
			}


			// overloads

			bool operator ==(const map& e1)
			{
				return (*this == e1);
			}

			bool operator <(const map& e1)
			{
				return (*this < e1);
			}

			bool operator >(const map& e1)
			{
				return (*this > e1);
			}

		private:

			// Of all this values, tree is the only one that is used properly. 

			Compare			comparation;
			allocator_type	allocated;
			BTree			tree;
	};

}

#endif