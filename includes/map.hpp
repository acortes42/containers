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


			//constructors

			explicit map (const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type())
			:
				comparation(comp), 
				allocated(alloc),
				tree(),
				map_size(0)
			{}

			template <class InputIterator>  map (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			:
				tree(),
				comparation(comp), 
				allocated(alloc),
				map_size(0)
			{
				tree->insert(std::make_pair(iterator(first, last), true));
			}

			map (const map& x)
			{
				this->root = x.root;
				this->allocated = x.allocated;
				this->comparation = x.comparation;
				this->map_size = x.map_size;
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
				this->map_size = x.map_size;
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
				return(reverse_iterator(this->tree._last_node, this->tree._last_node));
			}

			const_reverse_iterator const_rbegin()
			{
				return(const_reverse_iterator(this->tree._last_node, this->tree._last_node));
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
				return(reverse_iterator(this->tree._last_node->left, this->tree._last_node));
			}

			const_reverse_iterator const_rend() const
			{
				return(const_reverse_iterator(this->tree._last_node->left, this->tree._last_node));
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
				return(map_size);
			}

			size_type	max_size() const
			{ 
				return (std::numeric_limits<size_type>::max() / (sizeof(Node<value_type>)));
			}

			// Element access

			mapped_type& operator[] (const key_type& k)
			{
				iterator new_iter = this->find(k);

				if (new_iter == this->end())
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
					this->map_size++;
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
			//operations

			iterator find (const key_type& k)
			{
				return(iterator(this->tree.searchByKey(std::make_pair(k, mapped_type())), this->tree._last_node));
			}

			const_iterator find (const key_type& k) const
			{
				return(const_iterator(this->tree.searchByKey(std::make_pair(k, mapped_type())), this->tree._last_node));

			}
			void clear()
			{
				this->erase(this->begin(), this->end());
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
			size_type		map_size;
	};

}

#endif