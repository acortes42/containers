#ifndef MAP_HPP
#define MAP_HPP

#include "iterators/map_iterator.hpp"
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
			typedef typename ft::MapIterator<Key, T>		iterator;
			typedef typename ft::MapIterator<Key, T>		const_iterator;

			typedef std::reverse_iterator<iterator> reverse_iterator;	
			typedef std::reverse_iterator<const iterator> const_reverse_iterator;	
			typedef Node<Key, T>	node;
			typedef node			*node_pointer;
			//constructors

			explicit map (const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type())
			:
				comparation(comp), 
				allocated(alloc),
				map_size(0)
			{
				std::cout << "check	" << std::endl;
				root = newNode(key_type(), mapped_type(), nullptr);
			}

			template <class InputIterator>  map (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			:
				comparation(comp), 
				allocated(alloc),
				map_size(0)
			{
				while(first != last)
				{
					root->insert(std::make_pair(first.first, first.second));
					this->map_size++;
					first++;
				}
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
				node_pointer all_left = this->root;
				if (!(all_left->left) && !(all_left->right))
					return(this->end());
				if (!(all_left->left && all_left->right))
					all_left = all_left->right;
				while (all_left->left)
					all_left = all_left->left;
				return(iterator(all_left));
			}

			const_iterator const_begin() const
			{
				node_pointer all_left = this->root;
				if (!(all_left->left) && !(all_left->right))
					return(this->end());
				if (!(all_left->left && all_left->right))
					all_left = all_left->right;
				while (all_left->left)
					all_left = all_left->left;
				return(const_iterator(all_left));
			}

			iterator end()
			{
				node_pointer all_right = this->root;
				std::cout << "end	" << std::endl;
				while (all_right->HasRightChild())
					all_right = all_right->right;
				std::cout << "end 2	" << std::endl;

				return(iterator(all_right));
			}

			const_iterator const_end() const
			{
				node_pointer all_right = this->root;
				while (all_right->right)
					all_right = all_right->right;
				return(const_iterator(all_right));
			}

			// capacity

			bool empty() const
			{
				return(root->exist());
			}

			size_type size() const
			{
				return(map_size);
			}

			size_type	max_size() const
			{ 
				return (std::numeric_limits<size_type>::max() / (sizeof(Node<key_type, mapped_type>)));
			}

			// Element access

			mapped_type& operator[] (const key_type& k)
			{
				iterator new_iter = this->find(k);
				
				if (new_iter != this->end())
					return(new_iter._ptr->pair.second );
				return(this->insert(std::make_pair(new_iter._ptr->pair.first, new_iter._ptr->pair.second)).first._ptr->pair.second );
			}

			//modifiers
			
			std::pair<iterator,bool> insert (const value_type& val)
			{
				return((this->insertPair(root, std::make_pair(val.first, val.second))));
			};
			
			iterator insert (iterator position, const value_type& val)
			{
				(void)position;
				return(this->insertPair(root, std::make_pair(val.first, val.second)).first);
			}

			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				while(first != last)
				{
					root->insert(std::make_pair(first._ptr->pair.first, first._ptr->pair.second));
					this->map_size++;
					first++;
				}
			}

			/*
			void erase (iterator position)
			{
				
			}
			
			size_type erase (const key_type& k)
			{

			}

     		void erase (iterator first, iterator last)
			 {

			 }
			*/

			//operations

			iterator find (const key_type& k)
			{
				if(!root->Exist())
					return(this->end());
				std::cout << "find from find" << std::endl;
				return (iterator(find_this(root, k)));
			}

			const_iterator find (const key_type& k) const
			{
				if(!root->Exist())
					return(this->end());
				return (iterator(find_this(root, k)));
			}

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

			Compare			comparation;
			allocator_type	allocated;
			node_pointer	root;
			size_type		map_size;

			const node_pointer	find_this(node_pointer root, const key_type& firstValue)
			{
				std::cout << "find this" << std::endl;
				if (root->left == nullptr && root->right == nullptr)
				{
					std::cout << "find no childs" << std::endl;
					return(nullptr);
				}
				std::cout << "find firstValue: "  << firstValue << " , find root->pair.first: " << root->pair.first << std::endl;		
				if (firstValue < root->pair.first && root->left != nullptr)
				{
					std::cout << "find a lesser" << std::endl;
					find_this(root->left, firstValue);
				}
				else if (firstValue > root->pair.first && root->right != nullptr )
				{
					std::cout << "find a bigger" << std::endl;
					find_this(root->right, firstValue);
					
				}
				if (firstValue == root->pair.first)
						return(root->parent);
				std::cout << "find this 2" << std::endl;
				return(nullptr);
			}	

			node_pointer	newNode(key_type first, mapped_type second, node_pointer parent)
			{

				node_pointer new_node =	new Node<key_type, mapped_type>();
															
				new_node->pair = std::make_pair(first, second);
				new_node->left = nullptr;
				new_node->right = nullptr;
				new_node->parent = parent;
				
				return(new_node);
			}

			node_pointer insertNode(node_pointer root, const value_type& val)
			{
				if (!root->HasLeftChild() && !root->HasRightChild() && !root->pair.first)
				{
						std::cout << "root of roots" << std::endl;
						root->pair.first = val.first;
						root->pair.second = val.second;	
						return(root);
				}
				std::cout << "val.first: "  << val.first << " , root->pair.first: " << root->pair.first << std::endl;
				if(val.first < root->pair.first)
				{
					std::cout << "root->left insert node" << std::endl;

					if (!root->left)
					{
						root->left = newNode(val.first, val.second, root);
						std::cout << "root->left more left" << std::endl;
						return(root->left);
					}
					std::cout << "root->left insert node out" << std::endl;

					this->insertNode(root->left, val);
				}
				else if(val.first > root->pair.first)
				{
					std::cout << "root->right insert node" << std::endl;

					if (!root->right)
					{
						std::cout << "root->right insert node without right" << std::endl;

						root->right = newNode(val.first, val.second, root);
						return(root->right);
					}
					this->insertNode(root->right, val);
				}
				std::cout << "return root" << std::endl;
				return(root);
			}

			std::pair<iterator,bool> insertPair(node_pointer root, const value_type& val)
			{
				if (this->find_this(root, val.first) != nullptr)
				{
					std::cout << "encontrado" << std::endl;
					return (std::make_pair(iterator(this->find_this(root, val.first)), true));
				}
				map_size++;
				return (std::make_pair(iterator(insertNode(root, val)), true));
			}
	};

}

#endif