#ifndef AVL_TREE_H
#define AVL_TREE_H

//#include "dsexceptions.h"
#include <algorithm>
#include <iostream> 
#include <string>
#include <assert.h>
#include "RotationGame.h"
using namespace std;

// AvlTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x 
// void removeMin( )      --> Remove the lowest value in tree
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************


template <typename Etype>
class AvlTree
{
  public:
    AvlTree( ) : root( NULL )
      { }
    
    AvlTree( const AvlTree & rhs ) : root( NULL )
    {
        root = clone( rhs.root );
    }

    AvlTree( AvlTree && rhs ) : root( rhs.root )
    {
        rhs.root = NULL;
    }
    
    ~AvlTree( )
    {
        makeEmpty( );
    }

    /**
     * Deep copy.
     */
    AvlTree & operator=( const AvlTree & rhs )
    {
        AvlTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /**
     * Move.
     */
    AvlTree & operator=( AvlTree && rhs )
    {
        std::swap( root, rhs.root );
        
        return *this;
    }
    
    /**
     * Find the smallest item in the tree.
     */
    const Etype & findMin( ) const
    {
        assert(! isEmpty( ) );
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     */
    const Etype & findMax( ) const
    {
        assert( !isEmpty( ) );
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Etype & x ) const
    {
        return contains( x, root );
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == NULL;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printTree( root );
    }
	/**
	* Print the tree contents in tree form
	**/
	string toString() const
	{
		return toString( root, "  ");
	}
    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Etype & x )
    {
        insert( x, root, getparent(root) );
    }
     
    /**
     * Insert x into the tree; duplicates are ignored.
     * && is termed an rvalue reference. 
     * a good explanation is at http://thbecker.net/articles/rvalue_references/section_01.html
     */
    void insert( Etype && x )
    {
        insert( std::move( x ), root, getparent(root) );
    }
     
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const Etype & x )
    {
        remove( x, root );
    }

	/**
	 * Remove the lowest value from the tree.
	 */
	void removeMin()
	{
		AvlNode* ptr = findMin(root);
		if( ptr == NULL )
            return;   // Item not found; do nothing
        
        AvlNode *oldNode = ptr;
        ptr = ( ptr->left != NULL ) ? ptr->left : ptr->right;
		if(ptr != NULL)
			ptr->parent = oldNode->parent;
		oldNode->parent->left = ptr;
		if(ptr == NULL)
			ptr = oldNode->parent;
        delete oldNode;
		
		while(ptr!=NULL)
		{
			balance( ptr );
			ptr=ptr->parent;
		}	
			
	}

  private:
    struct AvlNode
    {
        Etype element;
        AvlNode   *left;
        AvlNode   *right;
		AvlNode   *parent;
        int       height;

        AvlNode( const Etype & ele, AvlNode *lt, AvlNode *rt, AvlNode *pt, int h = 0 )
          : element( ele ), left( lt ), right( rt ), parent( pt ), height( h ) { }
        
        AvlNode( Etype && ele, AvlNode *lt, AvlNode *rt, AvlNode *pt, int h = 0 )
          : element( std::move( ele ) ), left( lt ), right( rt ), parent( pt ), height( h ) { }
    };

    AvlNode *root;


    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Etype & x, AvlNode * & t, AvlNode * p )
    {
        if( t == NULL )
            t = new AvlNode( x, NULL, NULL, p );
        else if( x < t->element )
            insert( x, t->left, t );
        else if( t->element < x )
            insert( x, t->right, t );
        
        balance( t );
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Etype && x, AvlNode * & t, AvlNode * p )
    {
        if( t == NULL )
            t = new AvlNode( std::move( x ), NULL, NULL, p );
        else if( x < t->element )
            insert( std::move( x ), t->left, t );
        else if( t->element < x )
            insert( std::move( x ), t->right, t );
        
        balance( t );
    }
     
    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove( const Etype & x, AvlNode * & t )
    {
        if( t == NULL )
            return;   // Item not found; do nothing
        
        if( x < t->element )
            remove( x, t->left );
        else if( t->element < x )
            remove( x, t->right );
        else if( t->left != NULL && t->right != NULL ) // Two children
        {
            t->element = findMin( t->right )->element;
            remove( t->element, t->right );
        }
        else
        {
            AvlNode *oldNode = t;
            t = ( t->left != NULL ) ? t->left : t->right;
            delete oldNode;
        }
        
        balance( t );
    }
    
    static const int ALLOWED_IMBALANCE = 1;

    // Assume t is balanced or within one of being balanced
    void balance( AvlNode * & t )
    {
        if( t == NULL )
            return;
        
        if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE )
            if( height( t->left->left ) >= height( t->left->right ) )
                rotateWithLeftChild( t );
            else
                doubleWithLeftChild( t );
        else
        if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE )
            if( height( t->right->right ) >= height( t->right->left ) )
                rotateWithRightChild( t );
            else
                doubleWithRightChild( t );
                
        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }
    
    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    AvlNode * findMin( AvlNode *t ) const
    {
        if( t == NULL )
            return NULL;
        if( t->left == NULL )
            return t;
        return findMin( t->left );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    AvlNode * findMax( AvlNode *t ) const
    {
        if( t != NULL )
            while( t->right != NULL )
                t = t->right;
        return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     */
    bool contains( const Etype & x, AvlNode *t ) const
    {
        if( t == NULL )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }
/****** NONRECURSIVE VERSION*************************
    bool contains( const Etype & x, AvlNode *t ) const
    {
        while( t != nullptr )
            if( x < t->element )
                t = t->left;
            else if( t->element < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }
*****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( AvlNode * & t )
    {
        if( t != NULL )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = NULL;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( AvlNode *t ) const
    {
        if( t != NULL )
        {
            printTree( t->left );
            cout << t->element << endl;
            printTree( t->right );
        }
    }

	/**
	* Internal method to print subtree rooted at t in tree form
	*/
	string toString(AvlNode *t, string indent) const 
	{ 
		if(t == NULL)
			return "";
		indent+="    ";
		string temp = toString(t->right, indent);
		temp+= indent + to_string(t->element)+"("+getParentElementAsString(t->parent)+")\n";
		temp+= toString(t->left, indent);
		return temp; 
	} 
	string getParentElementAsString(AvlNode *parent) const //used in print function
	{
		if(parent == NULL)
			return "No Parent";
		return to_string(parent->element);
	}
    /**
     * Internal method to clone subtree.
     */
    AvlNode * clone( AvlNode *t ) const
    {
        if( t == NULL )
            return NULL;
        else
            return new AvlNode{ t->element, clone( t->left ), clone( t->right ), t->height };
    }
        // Avl manipulations
    /**
     * Return the height of node t or -1 if nullptr.
     */
    int height( AvlNode *t ) const
    {
        return t == nullptr ? -1 : t->height;
    }

    int max( int lhs, int rhs ) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild( AvlNode * & k2 )
    {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;

		k1->parent = k2->parent;
		k2->parent = k1;
		

        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;

		//make sure that you dont lose parent pointers of k1 by changeing k1 to equal k2
		//the following if statements make sure of that
		if(k2->right !=NULL && (k2->right)->left !=NULL)
			((k2->right)->left)->parent = k2->right;//idk if this even works
		if(k2->right !=NULL && (k2->right)->right !=NULL)
			((k2->right)->right)->parent = k2->right;
		if(k2->parent !=NULL)
			(((k2->parent)->element < k2->element) ? k2->parent->right : k2->parent->left) = k2;
		else
			root = k2;
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild( AvlNode * & k1 )
    {
        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;

		k2->parent = k1->parent;
		k1->parent = k2;
	
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;

		k1 = k2;
		//make sure that you dont lose parent pointers of k1 by changeing k1 to equal k2
		//the following if statements make sure of that
		if(k1->left !=NULL && (k1->left)->right !=NULL)
			((k1->left)->right)->parent = k1->left;//idk if this even works
		if(k1->left !=NULL && (k1->left)->left !=NULL)
			((k1->left)->left)->parent = k1->left;
		if(k1->parent !=NULL)
			(((k1->parent)->element > k1->element) ? k1->parent->left : k1->parent->right) = k1;
		else
			root = k1;
	
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild( AvlNode * & k3 )
    {
        rotateWithRightChild( k3->left );
        rotateWithLeftChild( k3 );
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild( AvlNode * & k1 )
    {
        rotateWithLeftChild( k1->right );
        rotateWithRightChild( k1 );
    }

	/**
	 * returns the parent avlNode*
	 * purpose is to return NULL pointer if looking for the parent of the root
	 */
	AvlNode * getparent(AvlNode * root)
	{
		if(root==NULL)
		return NULL;
		return root->parent;
	}


};

#endif