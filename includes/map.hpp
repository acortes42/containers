#ifndef MAP_HPP
#define MAP_HPP

#include "iterators/binary_tree_search.hpp"
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
			typedef std::size_t	size_type;
			typedef	std::ptrdiff_t	difference_type;
			typedef	Compare	key_compare;
			typedef Allocator allocator_type;
			typedef	value_type&	reference;
			typedef const value_type&	const_reference;
			typedef typename Allocator::pointer pointer;
			typedef typename Allocator::const_pointer const_pointer;
			
			// Falta aplicar iterator 
			typedef typename ft::Binary_search_tree<value_type> ::iterator			iterator;
			typedef typename ft::Binary_search_tree<const value_type>::iterator	const_iterator;

			typedef std::reverse_iterator<iterator> reverse_iterator;	
			typedef std::reverse_iterator<const iterator> const_reverse_iterator;	

			//constructors

			explicit map (const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type())
			:
				tree(),
				compare(comp), 
				allocated(alloc)
			{}

			/*
			template <class InputIterator>
  			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
       		const allocator_type& alloc = allocator_type())
			   :
					compare(comp),
					allocated(alloc),
					tree()
			{
				//insert here "insert"
			}
			*/
			map (const map& x)
			{
				this->tree = x.tree;
				this->next = x.next;
			}

			// DESTRUCTOR a revisar

			~map(){};
			
			std::pair<iterator,bool> get(ft::BST_Node<T>* k)
			{
				return(iterator(tree.searchByKey(ft::make_pair(k, mapped_type())), tree.last_node));
			}

			mapped_type& operator[] (const key_type& k)
			{
				iterator value = tree.get(k);
	
				return (value.second());
			}

			// Equal operator

			/*map& operator= (const map& x)
			{
				this->tree = x.tree;
				this->next = x.next;
				return(*this);
			};*/

			// Iterators

			iterator begin()
			{
				return(tree.minimum());
			}

			const_iterator begin() const
			{
				return(tree.minimum());
			}

			iterator end()
			{
				return(tree.maximum());
			}

			const_iterator end() const
			{
				return(tree.maximum());
			}

			//insert

			void printMap()
			{
				tree.printTree();
			}
	
			std::pair<iterator,bool> insert (const value_type& val)
			{
				std::pair<iterator,bool> x = tree.insertPair(val);
				return(x);
			};
			

			//utils

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

			map& operator= (const map& x)
			{
				if (*this == x)
					return *this;

				this->tree = x.tree;
				this->comp = x.comp;
				this->alloc = x.alloc;
			}

		private:

			BinaryTree<T> tree;
			Compare compare;
			allocator_type allocated;

	};

}

#endif