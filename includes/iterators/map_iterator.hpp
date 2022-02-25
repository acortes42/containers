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

            Node (Node	*parent, Node	*left, Node	*right)
			:
				pair(),
				left(left),
				right(right),
				parent(parent)
			{}

			Node (const T& t, Node	*parent = u_nullptr, Node	*left = u_nullptr, Node	*right = u_nullptr)
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

			MapIterator(const MapIterator& it)
			:
				_node(it._node),
				_last_node(it._last_node),
				_comp()
			{}

			virtual ~MapIterator() { }

			MapIterator &operator=(const MapIterator& it)
			{
				if (*this == it)
					return (*this);
				this->_node = it._node;
				this->_last_node = it._last_node;
				this->_comp = it._comp;
				return (*this);
			}

			bool operator==(const MapIterator& it)
			{ return (this->_node == it._node); }

			bool operator!=(const MapIterator& it)
			{ return (this->_node != it._node); }

			reference operator*() const
			{ return (this->_node->pair); }

			pointer operator->() const
			{ return (&this->_node->pair); }

			MapIterator& operator++(void)
			{
				T* new_node = _node;

				if (_node->right == _last_node)
				{
					new_node = _node->parent;
					while (new_node != _last_node
						&& _comp(new_node->pair.first, _node->pair.first))
						new_node = new_node->parent;
					_node = new_node;
				}
				else if (new_node == _last_node)
					_node = _last_node->right;
				else
				{
					new_node = _node->right;
					if (new_node == _last_node->parent
						&& new_node->right == _last_node)
						_node = new_node;
					else
					{
						while (new_node->left != _last_node)
							new_node = new_node->left;
					}
					_node = new_node;
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
				T* new_node = _node;

				if (_node->left == _last_node)
				{
					new_node = _node->parent;
					while (new_node != _last_node
						&& !_comp(new_node->pair.first, _node->pair.first))
						new_node = new_node->parent;
					_node = new_node;
				}
				else if (new_node == _last_node)
					_node = _last_node->right;
				else
				{
					new_node = _node->left;
					if (new_node == _last_node->parent
						&& new_node->left == _last_node)
						_node = new_node;
					else
					{
						while (new_node->right != _last_node)
							new_node = new_node->right;
					}
					_node = new_node;
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

	template <typename T, class Compare >
		class ReverseMapIterator : ft::iterator<ft::bidirectional_iterator_tag, T>
		{
			public :

				typedef typename T::value_type    value_type;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category iterator_category;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type   difference_type;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer   pointer;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference reference;

				ReverseMapIterator(const Compare& comp = Compare())
				:
					_node(),
					_last_node(),
					_comp(comp)
				{}

				ReverseMapIterator(T * node_p, T * last_node,
							const Compare& comp = Compare())
				:
					_node(node_p),
					_last_node(last_node),
					_comp(comp)
				{}

				ReverseMapIterator(const ReverseMapIterator& it)
				:
					_node(it._node),
					_last_node(it._last_node),
					_comp()
				{}

				virtual ~ReverseMapIterator() { }

				ReverseMapIterator &operator=(const ReverseMapIterator& it)
				{
					if (*this == it)
						return (*this);
					this->_node = it._node;
					this->_last_node = it._last_node;
					this->_comp = it._comp;
					return (*this);
				}

				bool operator==(const ReverseMapIterator& it)
				{ return (this->_node == it._node); }

				bool operator!=(const ReverseMapIterator& it)
				{ return (this->_node != it._node); }

				reference operator*() const
				{ return (this->_node->pair); }

				pointer operator->() const
				{ return (&this->_node->pair); }

				ReverseMapIterator& operator--(void)
				{
					T* new_node = _node;

					if (_node->right == _last_node)
					{
						new_node = _node->parent;
						while (new_node != _last_node
							&& _comp(new_node->pair.first, _node->pair.first))
							new_node = new_node->parent;
						_node = new_node;
					}
					else if (new_node == _last_node)
						_node = _last_node->right;
					else
					{
						new_node = _node->right;
						if (new_node == _last_node->parent
							&& new_node->right == _last_node)
							_node = new_node;
						else
						{
							while (new_node->left != _last_node)
								new_node = new_node->left;
						}
						_node = new_node;
					}
					return (*this);
				}

				ReverseMapIterator operator--(int)
				{
					ReverseMapIterator tmp(*this);
					operator--();
					return (tmp);
				}

				ReverseMapIterator& operator++(void)
				{
					T* new_node = _node;

					if (_node->left == _last_node)
					{
						new_node = _node->parent;
						while (new_node != _last_node
							&& !_comp(new_node->pair.first, _node->pair.first))
							new_node = new_node->parent;
						_node = new_node;
					}
					else if (new_node == _last_node)
						_node = _last_node->right;
					else
					{
						new_node = _node->left;
						if (new_node == _last_node->parent
							&& new_node->left == _last_node)
							_node = new_node;
						else
						{
							while (new_node->right != _last_node)
								new_node = new_node->right;
						}
						_node = new_node;
					}
					return (*this);
				}

				ReverseMapIterator operator++(int)
				{
					ReverseMapIterator tmp(*this);
					operator++();
					return (tmp);
				}            

				T *			_node;
				T *			_last_node;
				Compare     _comp;
		};
}
#endif
