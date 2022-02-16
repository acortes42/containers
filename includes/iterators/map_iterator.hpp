#ifndef MAPITERATOR_HPP
#define MAPITERATOR_HPP

namespace ft
{
	template <class Key, class T>
	class Node
	{
		public:

			std::pair<Key, T> pair;
			Node<Key, T> *left;
			Node<Key, T> *right;
			Node<Key, T> *parent;

			Node()
			:
				pair(),
				left(nullptr),
				right(nullptr),
				parent(nullptr)
			{}

			Node (const T& t)
			:
				pair(t),
				parent(nullptr),
				left(nullptr),
				right(nullptr)
			{}

            Node (Node	*parent, Node	*left, Node	*right)
			:
				pair(),
				parent(parent),
				left(left),
				right(right)
			{}

			Node (const T& t, Node	*parent, Node	*left, Node	*right)
			:
				pair(t),
				parent(parent),
				left(left),
				right(right)
			{}

			Node &operator=(const Node &x)
			{
				this->pair = x.value;
				this->left = x.left;
				this->right = x.right;
				this->parent = x.parent;
			}

			bool operator ==(const Node &x)
			{
				return (this == x);
			}

			bool operator !=(const Node &x)
			{
				return (this->pair != x.pair);
			}

			bool Exist()
			{
				if (this->pair.first)
					return (1);
				return (0);
			}
		
			bool HasParent()
			{
				if (this != nullptr && this->parent != nullptr)
					return 1;
				return 0;
			}

			bool HasLeftChild()
			{
					if (this != nullptr && this->left != nullptr)
						return 1;
					return 0;
			}

			bool HasRightChild()
			{
				if (this != nullptr && this->right != nullptr)
					return 1;
				return 0;
			}

			bool IsLeftChild()
			{
				if (this != nullptr && this->parent != nullptr && this == this->parent->left)
					return 1;
				return 0;
			}

			bool IsRightChild()
			{
				if (this != nullptr && this->parent != nullptr && this == this->parent->right)
					return 1;
				return 0;
			}

			T&	Retrieve()
			{
				return (this->pair);
			}
	};

	template <typename K, typename T>
	class MapIterator
	{
		public:

			typedef std::pair<K, T> 				value_type;
			typedef std::pair<K, T> 				*value_pointer;
			typedef std::pair<K, T> 				&value_reference;
			typedef ft::Node<K, T>*					node_pointer;
			typedef ft::Node<K, T>&					node_reference;
			typedef MapIterator<K, T>				curr_class;
			typedef MapIterator<K, T>       		iterator;
			typedef size_t							size_type;

			node_pointer _ptr;

			MapIterator(void): _ptr(0) {}
			MapIterator(const node_pointer ptr): _ptr(ptr) {}
			MapIterator(const iterator &other) { *this = other;}
			
			MapIterator &operator=(const iterator &other)
			{
				_ptr = other._ptr;
				return (*this);
			};
			
			node_pointer node(void) { return (_ptr);}
			
			node_pointer operator*(void) { return (_ptr);}
			
			value_pointer operator->()  
			{ 
				std::cout << "Esto es un mensaje personal para decir que segfault va\n";
				return (&this->_ptr->pair );
			}
			
			bool operator==(const curr_class &other) { return (_ptr == other._ptr);}
			bool operator!=(const curr_class &other) { return (!(*this == other));}
			
			MapIterator &operator++(void)
			{
				_ptr = this->ptr_next(_ptr);
				return (*this);
			}

			MapIterator &operator--(void)
			{
				_ptr = this->ptr_prev(_ptr);
				return (*this);
			}

			MapIterator operator++(int)
			{
				MapIterator tmp(*this);
				this->operator++();
				return (tmp);
			}

			MapIterator operator--(int)
			{
				MapIterator tmp(*this);
				this->operator--();
				return (tmp);
			}
			value_pointer operator[] (size_type n) 
			{ 
				(void)n;
				
				return (&this->_ptr->pair); 
			}


		private:

			/*
				Successor alghoritm

				First rule: The first node in the tree is the leftmost node in the tree.

				Next rule: The successor of a node is:

				Next-R rule: If it has a right subtree, the leftmost node in the right subtree.

				Next-U rule: Otherwise, traverse up the tree
				If you make a right turn (i.e. this node was a left child), then that parent node is the successor
				If you make a left turn (i.e. this node was a right child), continue going up.
				If you can't go up anymore, then there's no successor
			*/

			node_pointer ptr_next(node_pointer ptr)
			{
				//falla en varios sitios
				
				node_pointer next;
				if (!ptr->right)
				{
					next = ptr;
					while (next->parent && next == next->parent->right)
						next = next->parent;
					next = next->parent;
				}
				else
				{
					next = ptr->right;
					while (next->left)
						next = next->left;
				}
				std::cout << "errrorr asdfasdf\n";

				return (next);
			};

			node_pointer ptr_prev(node_pointer ptr)
			{
				node_pointer next;

				if (!ptr->left)
				{
					next = ptr;
					while (next->parent && next == next->parent->left)
						next = next->parent;
					next = next->parent;
				}
				else
				{
					next = ptr->left;
					while (next->right)
						next = next->right;
				}
				return (next);
			};
	};
}

#endif
