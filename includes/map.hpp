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
			
			//nodes

			typedef Node<Key, T>	node;
			typedef node			*node_pointer;
			// Falta aplicar iterator 

			typedef typename ft::MapIterator<node, key_type, mapped_type>		iterator;
			typedef typename ft::MapIterator<node, key_type, mapped_type>		const_iterator;

			typedef std::reverse_iterator<iterator> reverse_iterator;	
			typedef std::reverse_iterator<const iterator> const_reverse_iterator;


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
				while (all_right->HasRightChild())
					all_right = all_right->right;
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
				iterator x = find_this(k).first;

				std::cout << "x->pair.first : " << x._iter->pair.first << std::endl;
				std::cout << "x->pair.secont : " << x._iter->pair.second << std::endl;

				return(x);
			}

			const_iterator find (const key_type& k) const
			{
				if(!root->Exist())
					return(this->end());
				std::pair<iterator, int> tmp = find_this(k);
				if(tmp.second == 0)
					return (tmp.first);
				return(this->end());
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

/*
			std::pair<iterator, int>	find_this(node root, const key_type& firstValue)
			{
				std::cout << "root.pair.first : " << root.pair.first << " ,firstValue: " << firstValue << std::endl;
				if (!root.pair.first)
					return(std::make_pair(iterator(), 0));
				if (root.pair.first == firstValue)
				{
					std::cout << "equal value"<< std::endl;
					return(std::make_pair(iterator(), 0));
				}
				if (firstValue < root.pair.first && root.left)
				{
					node tmp_node = *root.left;
					std::cout << "root.left tmp_node.pair.first of : " <<  tmp_node.pair.first << std::endl;
					find_this(tmp_node, firstValue);
				}
				else if (firstValue > root.pair.first && root.right )
				{
					node tmp_node = *root.right;
					std::cout << "----> rightValue: : " <<  tmp_node.pair.first << std::endl;
					find_this(tmp_node, firstValue);
				}
				std::cout << "escape with root.pair.first of : " <<  root.pair.first << std::endl;
				node_pointer tmp_node = &root;
				return(std::make_pair(iterator(tmp_node), 1));
			}	
*/
			std::pair<iterator, int> find_this(const key_type& firstValue)
			{	
				int ret_int;
				node tmp_node;

				tmp_node = *this->root;
				ret_int = 1;
				while(true)
				{
					if (tmp_node.pair.first == firstValue)
					{
						std::cout << "equal value"<< std::endl;
						ret_int = 0;
						break;
					}
					if (firstValue < tmp_node.pair.first && tmp_node.left)
					{
						tmp_node = *tmp_node.left;
						std::cout << "tmp_node.left tmp_node.pair.first of : " <<  tmp_node.pair.first << std::endl;
						continue;
					}
					else if (firstValue > tmp_node.pair.first && tmp_node.right )
					{
						tmp_node = *tmp_node.right;
						std::cout << "----> rightValue: : " <<  tmp_node.pair.first << std::endl;
						continue;
					}
					break;
				}
				
				std::cout << "escape with tmp_node.pair.first of : " <<  tmp_node.pair.first << std::endl;
				node_pointer tmp_node_pointer = &tmp_node;
				return(std::make_pair(iterator(tmp_node_pointer), ret_int));
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
				if (!root->left && !root->right && !root->pair.first)
				{
						std::cout << "root of roots" << std::endl;
						root->pair.first = val.first;
						root->pair.second = val.second;	
						return(root);
				}
				if(val.first < root->pair.first)
				{
					if (!root->left)
					{
						root->left = newNode(val.first, val.second, root);
						return(root->left);
					}
					this->insertNode(root->left, val);
				}
				else if(val.first > root->pair.first)
				{
					if (!root->right)
					{
						root->right = newNode(val.first, val.second, root);
						return(root->right);
					}
					this->insertNode(root->right, val);
				}
				return(root);
			}

			std::pair<iterator,bool> insertPair(node_pointer root, const value_type& val)
			{
				//iterator tmp = this->find(val.first);
				std::pair<iterator, int> tmp = find_this(val.first);
				/*if (tmp->first)
						std::cout << "no exploto" << std::endl;	*/
				if (tmp.second == 0)
				{
					std::cout << "encontrado" << std::endl;
					return (tmp);
				}
				map_size++;
				return (std::make_pair(iterator(insertNode(root, val)), true));
			}
	};

}

#endif