#ifndef REDBLACKTREE_HPP
#define REDBLACKTREE_HPP

#include "../containers.hpp"

namespace ft
{
	template <class T, class Compare = std::less<T> >
	struct tree_node
	{
		public:

			tree_node():
				data()
			{
				this->left = nullptr;
				this->right = nullptr;
				this->parent = nullptr;
			}

			tree_node(T data)
			:
				data()
			{
				this->data = data;
				this->left = nullptr;
				this->right = nullptr;
				this->parent = nullptr;
			}

			tree_node(T data, tree_node *parent, tree_node *left, tree_node *right)
			:
				data(data)
			{
			
				this->left = left;
				this->right = right;
				this->parent = parent;
			}

			tree_node (const tree_node& x)
			:
				data()
			{
				this->left = x.left;
				this->right = x.right;
				this->parent = x.parent;
			}

			~tree_node<T>(){}

			tree_node  &operator=(const tree_node& x)
			{
				if (x == *this)
					return (*this);

				this->data = x.data;
				this->left = x.left;
				this->right = x.right;
				this->parent = x.parent;
				return(this);
			}

			bool  operator==(const tree_node& x)
			{
				if(x.data == data)
					return(true);
				return(false);
			}

			T	data;
			tree_node *parent;
			tree_node *left;
			tree_node *right;
	};
}

namespace ft
{
	template <class T, class Compare = std::less<T> >
	class tree_iterator: ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		public:
			
			typedef T    value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category iterator_category;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type   difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer   pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference reference;
			
			tree_iterator(const Compare& comp = Compare()):
				node(),
				last_node(),
				comp(comp)
			{}

			tree_iterator(T * node_p, T * last_node,
						const Compare& comp = Compare())
			:
				node(node_p),
				last_node(last_node),
				comp(comp)
			{}

			tree_iterator(const tree_iterator& t_node)
			:
				node(t_node.node),
				last_node(t_node.last_node),
				comp()
			{}

			virtual ~tree_iterator() { }

			tree_iterator &operator=(const tree_iterator& tree)
			{
				if (*this == tree)
					return (*this);
				this->node = tree.node;
				this->last_node = tree.last_node;
				this->comp = tree.comp;
				return (*this);
			}

			bool operator==(const tree_iterator& tree)
			{ return (this->node == tree.node); }

			bool operator!=(const tree_iterator& tree)
			{ return (this->node != tree.node); }

			reference operator*() const
			{ return (this->node->value); }

			pointer operator->() const
			{ return (&this->node->value); }

			tree_iterator& operator++(void)
			{
				T* cursor = node;

				if (node->right == last_node)
				{
					cursor = node->parent;
					while (cursor != last_node
						&& comp(cursor->value.first, node->value.first))
						cursor = cursor->parent;
					node = cursor;
				}
				else if (cursor == last_node)
					node = last_node->right;
				else
				{
					cursor = node->right;
					if (cursor == last_node->parent
						&& cursor->right == last_node)
						node = cursor;
					else
					{
						while (cursor->left != last_node)
							cursor = cursor->left;
					}
					node = cursor;
				}
				return (*this);
			}

			tree_iterator operator++(int)
			{
				tree_iterator tmp(*this);
				operator++();
				return (tmp);
			}

			tree_iterator& operator--(void)
			{
				T* cursor = node;

				if (node->left == last_node)
				{
					cursor = node->parent;
					while (cursor != last_node
						&& !_comp(cursor->value.first, node->value.first))
						cursor = cursor->parent;
					node = cursor;
				}
				else if (cursor == last_node)
					node = last_node->right;
				else
				{
					cursor = node->left;
					if (cursor == last_node->parent
						&& cursor->left == last_node)
						node = cursor;
					else
					{
						while (cursor->right != last_node)
							cursor = cursor->right;
					}
					node = cursor;
				}
				return (*this);
			}

			tree_iterator operator--(int)
			{
				tree_iterator tmp(*this);
				operator--();
				return (tmp);
			}        

		private:

			T		*node;
			T		*last_node;
			Compare	comp;

	};
}

namespace ft
{
	template<class T, class Compare = std::less<T>, class Node = ft::tree_node<T>, 
	 class Type_Alloc = std::allocator<T>, class Node_Alloc = std::allocator<Node> >
	class RedBlackTree
	{
		typedef ft::tree_node<T> *NodePtr;

		public:


			typedef RedBlackTree  self;
			typedef self&   self_reference;
			typedef T   value_type;
			typedef ft::tree_node<T, Compare> node_type;
			typedef Node *node_pointer;
			typedef Node_Alloc  node_alloc;
			typedef ft::tree_iterator<Node, Compare> iterator;
			typedef ft::tree_iterator<Node, Compare> const_iterator;
			typedef size_t size_type;

			RedBlackTree() 
			{
				last_node = new Node;
				last_node->left = nullptr;
				last_node->right = nullptr;
				root = last_node;
			}

			RedBlackTree(T data, NodePtr left, NodePtr right) 
			{
				last_node = new Node;
				last_node->data = data;
				last_node->left = left;
				last_node->right = right;
				root = last_node;
			}

			void preorder(){ preOrderHelper(this->root);}
			void inorder() { inOrderHelper(this->root);}
			void postorder() { postOrderHelper(this->root);}

			NodePtr searchTree(int k) 
			{
				return searchTreeHelper(this->root, k);
			}

			NodePtr minimum(NodePtr node) 
			{
				while (node->left != last_node)
					node = node->left;
				return node;
			}

			NodePtr maximum(NodePtr node) 
			{
				while (node->right != last_node) 
					node = node->right;
				return node;
			}

			NodePtr successor(NodePtr x)
			{
				if (x->right != last_node)
					return minimum(x->right);
				NodePtr y = x->parent;
				while (y != last_node && x == y->right) 
				{
					x = y;
					y = y->parent;
				}
				return y;
			}

			NodePtr predecessor(NodePtr x) 
			{
				if (x->left != last_node) 
					return maximum(x->left);
				NodePtr y = x->parent;
				while (y != last_node && x == y->left) 
				{
					x = y;
					y = y->parent;
				}
				return y;
			}

			void leftRotate(NodePtr x) 
			{
				NodePtr y = x->right;
				x->right = y->left;
				if (y->left != last_node) 
					y->left->parent = x;
				y->parent = x->parent;
				if (x->parent == nullptr) 
					this->root = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else 
					x->parent->right = y;
				y->left = x;
				x->parent = y;
			}

			void rightRotate(NodePtr x) 
			{
				NodePtr y = x->left;
				x->left = y->right;
				if (y->right != last_node) 
					y->right->parent = x;
				y->parent = x->parent;
				if (x->parent == nullptr) 
					this->root = y;
				else if (x == x->parent->right)
					x->parent->right = y;
				else 
					x->parent->left = y;
				y->right = x;
				x->parent = y;
			}

			// Inserting a node

			/*
			ft::pair<iterator, bool> insertPair(value_type to_insert)
			{
				Node * new_node = _node_alloc.allocate(1);
				Node * prev_node = _last_node;
				Node * start_node = _last_node->parent;

				// side == false = left; side == true = right;
				bool side = true;

				while (start_node != _last_node)
				{
					int curkey = start_node->value.first;
					if (curkey == to_insert.first)
						return (ft::make_pair(iterator(start_node, _last_node), false));
					prev_node = start_node;
					if (to_insert.first > curkey)
					{
						side = true;
						start_node = start_node->right;
					}
					else
					{
						side = false;
						start_node = start_node->left;
					}
				}
				_node_alloc.construct(new_node, Node(to_insert, prev_node, _last_node, _last_node));
				
				if (prev_node == _last_node)
					_last_node->parent = new_node;
				else if (side == true)
					prev_node->right = new_node;
				else
					prev_node->left = new_node;
				
				_last_node->left = _BST_get_lower_node(_last_node->parent);
				_last_node->right = _BST_get_higher_node(_last_node->parent);
				_last_node->value.first += 1;
				return (ft::make_pair(iterator(new_node, _last_node), true));
			}
			*/

			std::pair<iterator,bool> insertPair (value_type val)
			{
				
				node_pointer new_node =  allocator.allocate(1);
				node_pointer prev_node = last_node;
				node_pointer start_node = last_node->parent;

				// side == false = left; side == true = right;
				bool side = true;

				while (start_node != last_node)
				{
					if (start_node->data.first == val.first)
						return (ft::make_pair(iterator(start_node, last_node), false));
					prev_node = start_node;
					if (val.first > start_node->value.first)
					{
						side = true;
						start_node = start_node->right;
					}
					else
					{
						side = false;
						start_node = start_node->left;
					}
				}
				 allocator.construct(new_node, Node(val, prev_node, last_node, last_node));
				
				if (prev_node == last_node)
					last_node->parent = new_node;
				else if (side == true)
					prev_node->right = new_node;
				else
					prev_node->left = new_node;
				
				last_node->left = get_lower_node(last_node->parent);
				last_node->right = get_upper_node(last_node->parent);
				last_node->data.first += 1;
				return (ft::make_pair(iterator(new_node, last_node), true));
			}

			NodePtr getRoot() 
			{
				return this->root;
			}

			void deleteNode(T key) 
			{
				deleteNodeHelper(this->root, key);
			}
			void printTree() 
			{
				if (root)
					printHelper(this->root, "", true);
			}

			node_pointer searchByKey(value_type to_remove)
			{
				node_pointer node = last_node->parent;

				while (node != last_node)
				{
					if (node->data.first == to_remove.first)
						return (node);
					if (node->data.first > to_remove.first)
						node = node->left;
					else
						node = node->right;
				}
				return (node);
			}


		private:

			NodePtr root;
			NodePtr last_node;
			Node_Alloc allocator;

			void initializeNULLNode(NodePtr node, NodePtr parent)
			{
				node->data = T();
				node->parent = parent;
				node->left = nullptr;
				node->right = nullptr;
			}

			// Preorder

			void preOrderHelper(NodePtr node) 
			{
				if (node != last_node) 
				{
					preOrderHelper(node->left);
					preOrderHelper(node->right);
				}
			}

			// Inorder

			void inOrderHelper(NodePtr node) 
			{
				if (node != last_node)
				{
					inOrderHelper(node->left);
					inOrderHelper(node->right);
				}
			}

			// Post order

			void postOrderHelper(NodePtr node)
			{
				if (node != last_node) 
				{
					postOrderHelper(node->left);
					postOrderHelper(node->right);
				}
			}

			NodePtr searchTreeHelper(NodePtr node, T key)
			{
				if (node == last_node || key.first() == node->data->first()) 
					return node;
				if (key.first < node->data->first())
					return searchTreeHelper(node->left, key.first());
				return searchTreeHelper(node->right, key.first());
			}

			void rbTransplant(NodePtr u, NodePtr v) 
			{
				if (u->parent == nullptr)
					root = v;
				else if (u == u->parent->left)
					u->parent->left = v;
				else
					u->parent->right = v;
				v->parent = u->parent;
			}

			node_pointer  get_lower_node(node_pointer root)
			{
				while (root != last_node && root->left != last_node)
					root = root->left;
				return (root);
			}

			/*
			** @brief Give node pointer on higher key.
			*/
			node_pointer get_upper_node(node_pointer root)
			{
				while (root != last_node && root->right != last_node)
					root = root->right;
				return (root);
			}
	};
}
#endif