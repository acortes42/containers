#ifndef BINARYTREESEARCH_HPP
#define BINARYTREESEARCH_HPP

#include "../containers.hpp"

namespace ft
{
	template <typename T>
	class BinaryTree
	{
		class Node
		{
			public:

				T		value_;
				Node	*parent_;
				Node	* lchild_;
				Node	* rchild_;

				Node()
				:
					value_(),
					parent_(nullptr_t),
					lchild_(nullptr_t),
					rchild_(nullptr_t)
				{}

				Node (const T& t)
				:
					value_(t),
					parent_(nullptr_t),
					lchild_(nullptr_t),
					rchild_(nullptr_t)
				{}

				Node (const T& t, Node	*parent_, Node	*lchild_, Node	*rchild_)
				:
					value_(t),
					parent_(parent_),
					lchild_(lchild_),
					rchild_(rchild_)
				{}
		} ;

	protected:

		Node * root_;

	public:

		typedef T								ValueType;
		typedef BinaryTreeNavigator<T>			Navigator;
		typedef BinaryTreeIterator<T>			Iterator;
	};

	template <typename T>
	class BinaryTreeIterator: ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		private:

		 	Node next;

		public::
		
			TreeIterator(Node root) 
			{
				next = root;
				if(next == null)
					return;

				while (next.left != null)
				next = next.left;
			}

			boolean hasNext(){ return next != null;}

			Node next()
			{
				if(!hasNext()) throw new NoSuchElementException();
					Node r = next;
				if(next.right != null) 
				{
					next = next.right;
					while (next.left != null)
						next = next.left;
					return r;
				}
				while(true) 
				{
					if(next.parent == null) {
						next = null;
						return r;
					}
					if(next.parent.left == next) 
					{
						next = next.parent;
						return r;
					}
					next = next.parent;
				}
			}
		};
	
	template < typename T >
	class BinaryTreeNavigator
	{
		private:

		BinaryTree<T>::Node	*currNode_;

		public:
			typedef	T						ValueType;
			typedef	BinaryTreeNavigator<T>	Navigator;

			// constructors

			BinaryTreeNavigator           ();
			BinaryTreeNavigator           (const BinaryTree<T>& b);
			BinaryTreeNavigator           (const Navigator& n);
			~BinaryTreeNavigator  		  ();

			// structural information

			bool Valid              () const; // Navigator points to valid element
			bool HasParent          () const; // node has valid parent
			bool HasLeftChild       () const; // node has valid left child
			bool HasRightChild      () const; // node has valid right child
			bool IsLeftChild        () const; // node is the left child of its valid parent
			bool IsRightChild       () const; // node is the right child of its valid parent

			// useful functions

			T&	Retrieve	() const;

			// overloads

			Navigator &operator ++();
			Navigator &operator ++(int);
			Navigator &operator --();

	};

	template < typename T >
	bool BinaryTreeNavigator<T>::HasParent () const
	{
		if (currNode_ != 0 && currNode_ -> parent_ != 0)
			return 1;
		return 0;
	}

	template < typename T >
	bool BinaryTreeNavigator<T>::HasLeftChild () const
	{
		if (currNode_ != 0 && currNode_ -> lchild_ != 0)
			return 1;
		return 0;
	}

	template < typename T >
	bool BinaryTreeNavigator<T>::IsLeftChild () const
	{
		if (currNode_ != 0 && currNode_ -> parent_ != 0 && currNode_ == currNode_ -> parent_ -> lchild_)
			return 1;
		return 0;
	}

	template < typename T >
	bool BinaryTreeNavigator<T>::Valid() const
	{
		return currNode_ != 0;
	}

	template < typename T >
	T& BinaryTreeNavigator<T>::Retrieve() const
	{
		return (currNode_->value);
	}

	template < typename T >
	BinaryTreeNavigator<T> & BinaryTreeNavigator<T>::operator ++()
	{
		if (currNode_ != 0)
			currNode_ = currNode_ -> lchild_;
		return *this;
	}

	template < typename T >
	BinaryTreeNavigator<T> & BinaryTreeNavigator<T>::operator ++(int)
	{
		if (currNode_ != 0)
			currNode_ = currNode_ -> rchild_;
		return *this;
	}

	template < typename T >
	BinaryTreeNavigator<T> & BinaryTreeNavigator<T>::operator --()
	{
		if (currNode_ != 0)
			currNode_ = currNode_ -> parent_;
		return *this;
	}
}


#endif