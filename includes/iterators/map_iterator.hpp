#ifndef MAPITERATOR_HPP
#define MAPITERATOR_HPP

namespace ft
{
	template <class Key, class T>
	struct Node
	{
			std::pair<Key, T> pair;
			Node<Key, T> *left;
			Node<Key, T> *right;
			Node<Key, T> *parent;
	};

	template <typename T, typename Key, typename Value>
	class MapIterator: ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		public:

			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category     iterator_category;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type            value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type       difference_type;
			typedef MapIterator<T, Key, Value>		this_class;
			typedef T								iterator;
			typedef T								*pointer;
			typedef T								&reference;
			typedef std::pair<Key, Value>			pair_value;
			typedef std::pair<Key, Value>			&pair_reference;
			typedef std::pair<Key, Value>			*pair_pointer;


			pointer _iter;

			MapIterator()
			: 
				_iter(u_nullptr)
			{}

			MapIterator(const pointer iter)
			: 
				_iter(iter)
			{}

			MapIterator(const iterator &other) {*this = other;}
			
			MapIterator &operator=(const MapIterator &other)
			{
				_iter = other._iter;
				return (*this);
			};

			virtual ~MapIterator(){}

			MapIterator & operator++(void)
            {
                _iter(_iter->right);
                return (*this);
            }

			MapIterator operator++(int)
            {
                iter_next(_iter);
                return (*this);
            }

			pair_reference operator*(void) const 
            { 
                return (*_iter->pair); 
            }

            pair_pointer operator->(void)
            {
                return (&_iter->pair); 
            }
			
			bool Retrieve()
			{
				return(*_iter->pair.Retrieve());
			}
			bool operator==(const this_class &other) { return (_iter == other._iter);}
			bool operator!=(const this_class &other) { return (!(*this == other));}




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

			pointer iter_next(pointer iter)
			{
				//falla en varios sitios
				
				pointer next;

				if (!iter->right)
				{
					std::cout << "errrorr asdfasdf\n";
					pointer next(iter);
					std::cout << "errrorr asdfasdf\n";
					while (next->parent && next == next->parent->right)
						next = next->parent;
					next = next->parent;
				}
				else
				{
					next = iter->right;
					while (next->left)
						next = next->left;
				}
				std::cout << "errrorr asdfasdf\n";

				return (next);
			};

			pointer iter_prev(pointer iter)
			{
				pointer next;

				if (!iter->left)
				{
					next = iter;
					while (next->parent && next == next->parent->left)
						next = next->parent;
					next = next->parent;
				}
				else
				{
					next = iter->left;
					while (next->right)
						next = next->right;
				}
				return (next);
			};

	};
}

#endif
