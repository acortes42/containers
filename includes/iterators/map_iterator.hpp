#ifndef MAPITERATOR_HPP
#define MAPITERATOR_HPP

namespace ft
{
	template <class T>
	class Node
	{
		public:

			typedef T value_type;

			value_type	pair;
			Node		*left;
			Node		*right;
			Node		*parent;

			Node()
			:
				pair(),
				left(u_nullptr),
				right(u_nullptr),
				parent(u_nullptr)
			{}

			Node (const T& t)
			:
				pair(t),
				parent(u_nullptr),
				left(u_nullptr),
				right(u_nullptr)
			{}

            Node (Node	*parent, Node	*left, Node	*right)
			:
				pair(),
				left(left),
				right(right),
				parent(parent)
			{}

			Node (const T& t, Node	*parent, Node	*left, Node	*right)
			:
				pair(t),
				left(left),
				right(right),
				parent(parent)
			{}

			Node &operator=(const Node &x)
			{
				this->pair = x.pair;
				this->left = x.left;
				this->right = x.right;
				this->parent = x.parent;

				return(*this);
			}

			bool operator ==(const Node &x)
			{
				return (this == x);
			}

			bool operator !=(const Node &x)
			{
				return (this->pair != x.pair);
			}

			value_type	get_pair()	
			{
				return(pair);
			}

			bool Exist()
			{
				if (this->pair.first)
					return (1);
				return (0);
			}
		
			bool HasParent()
			{
				if (this != u_nullptr && this->parent != u_nullptr)
					return 1;
				return 0;
			}

			bool HasLeftChild()
			{
					if (this != u_nullptr && this->left != u_nullptr)
						return 1;
					return 0;
			}

			bool HasRightChild()
			{
				if (this != u_nullptr && this->right != u_nullptr)
					return 1;
				return 0;
			}

			bool IsLeftChild()
			{
				if (this != u_nullptr && this->parent != u_nullptr && this == this->parent->left)
					return 1;
				return 0;
			}

			bool IsRightChild()
			{
				if (this != u_nullptr && this->parent != u_nullptr && this == this->parent->right)
					return 1;
				return 0;
			}

			T&	Retrieve()
			{
				return (this->pair);
			}
	};

	template <typename T, class Compare >
	class MapIterator : ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		public :

			typedef typename T::value_type    value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category iterator_category;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type   difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer   pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference reference;

			MapIterator(const Compare& comp = Compare())
			:
				_node(),
				_last_node(),
				_comp(comp)
			{}

			MapIterator(T * node_p, T * last_node,
						const Compare& comp = Compare())
			:
				_node(node_p),
				_last_node(last_node),
				_comp(comp)
			{}

			MapIterator(const MapIterator& bst_it)
			:
				_node(bst_it._node),
				_last_node(bst_it._last_node),
				_comp()
			{}

			virtual ~MapIterator() { }

			MapIterator &operator=(const MapIterator& bst_it)
			{
				if (*this == bst_it)
					return (*this);
				this->_node = bst_it._node;
				this->_last_node = bst_it._last_node;
				this->_comp = bst_it._comp;
				return (*this);
			}

			bool operator==(const MapIterator& bst_it)
			{ return (this->_node == bst_it._node); }

			bool operator!=(const MapIterator& bst_it)
			{ return (this->_node != bst_it._node); }

			reference operator*() const
			{ return (this->_node->pair); }

			pointer operator->() const
			{ return (&this->_node->pair); }

			MapIterator& operator++(void)
			{
				T* cursor = _node;

				if (_node->right == _last_node)
				{
					cursor = _node->parent;
					while (cursor != _last_node
						&& _comp(cursor->pair.first, _node->pair.first))
						cursor = cursor->parent;
					_node = cursor;
				}
				else if (cursor == _last_node)
					_node = _last_node->right;
				else
				{
					cursor = _node->right;
					if (cursor == _last_node->parent
						&& cursor->right == _last_node)
						_node = cursor;
					else
					{
						while (cursor->left != _last_node)
							cursor = cursor->left;
					}
					_node = cursor;
				}
				return (*this);
			}

			MapIterator operator++(int)
			{
				MapIterator tmp(*this);
				operator++();
				return (tmp);
			}

			MapIterator& operator--(void)
			{
				T* cursor = _node;

				if (_node->left == _last_node)
				{
					cursor = _node->parent;
					while (cursor != _last_node
						&& !_comp(cursor->pair.first, _node->pair.first))
						cursor = cursor->parent;
					_node = cursor;
				}
				else if (cursor == _last_node)
					_node = _last_node->right;
				else
				{
					cursor = _node->left;
					if (cursor == _last_node->parent
						&& cursor->left == _last_node)
						_node = cursor;
					else
					{
						while (cursor->right != _last_node)
							cursor = cursor->right;
					}
					_node = cursor;
				}
				return (*this);
			}

			MapIterator operator--(int)
			{
				MapIterator tmp(*this);
				operator--();
				return (tmp);
			}            

			T *			_node;
			T *			_last_node;
			Compare     _comp;
	};
};	

#endif
