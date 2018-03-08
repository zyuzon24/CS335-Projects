// AvlTree.h
// Zach Yuzon
// An implementation of a AVL Tree class
// March 4, 2018
#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "dsexceptions.h"
#include <algorithm>
#include <iostream> 
using namespace std;

// AvlTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x, num_removes, num_recurs )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// findRecSeq( x )        --> Return true if found; else false
// AverageDepth()         --> Return average depth of the tree
// find( x , count_recurs)--> Return 1 if recognition sequence is found in tree; else 0.
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class AvlTree
{
  public:
    AvlTree( ) : root{ nullptr }
      { }
    
    AvlTree( const AvlTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }

    AvlTree( AvlTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
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
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
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
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        insert( x, root );
    }
     
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x )
    {
        insert( std::move( x ), root );
    }
     
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     * @x: recognition sequence being removed
     * @num_removes: counts the number of successful removes
     * @num_recurs: count the number of recursions made
     */
    void remove( const Comparable & x, float &num_removes, float &num_recurs )
    {
        remove( x, root, num_removes, num_recurs );
    }

    /**
     * Find a recognition sequence in the tree and return the associated enzyme acronym(s).
     * If it doesn't exist, return "Not Found"
     * @x: recognition sequence being searched for in the tree
     */
    bool findRecSeq(const string & x) const{
        return findRecSeq(x,root);
    }
    
    /**
     * Calculate and return the number of nodes within the tree.
     */
    int numOfNodes() const{
        return numOfNodes(root);
    }
    
    /**
     * Calculate and return the Average Depth of the tree.
     */
    float AverageDepth() const{
        return AverageDepth(root, 0)/numOfNodes();
    }
    
    /**
     * Finds a recognition sequence in the tree and reutrns 1 if found. 0 if not found.
     * @x: recognition sequence being searched in the tree
     * @count_recurs: count how many times a recursive call is being made
     */
    float find(const string &x,float &count_recurs) const{
        if(find(x,root,count_recurs)){
            return 1.0;
        }
        return 0.0;
    }
    
  private:
    struct AvlNode
    {
        Comparable element;
        AvlNode   *left;
        AvlNode   *right;
        int       height;

        AvlNode( const Comparable & ele, AvlNode *lt, AvlNode *rt, int h = 0 )
          : element{ ele }, left{ lt }, right{ rt }, height{ h } { }
        
        AvlNode( Comparable && ele, AvlNode *lt, AvlNode *rt, int h = 0 )
          : element{ std::move( ele ) }, left{ lt }, right{ rt }, height{ h } { }
    };

    AvlNode *root;


    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, AvlNode * & t )
    {
        if( t == nullptr )
            t = new AvlNode{ x, nullptr, nullptr };
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        else
            t->element.Merge(x);
        
        balance( t );
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, AvlNode * & t )
    {
        if( t == nullptr )
            t = new AvlNode{ std::move( x ), nullptr, nullptr };
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );
        else
            t->element.Merge(x);
        balance( t );
    }
     
    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove( const Comparable & x, AvlNode * & t, float &num_removes, float &num_recurs )
    {
        if( t == nullptr ){
            return;   // Item not found; do nothing
        }
        if( x < t->element ){
            ++num_recurs;
            remove( x, t->left, num_removes, num_recurs );
        }
        else if( t->element < x ){
            ++num_recurs;
            remove( x, t->right, num_removes, num_recurs );
        }
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            ++num_recurs;
            t->element = findMin( t->right )->element;
            remove( t->element, t->right, num_removes, num_recurs );
        }
        else
        {
            AvlNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
            ++num_removes;
        }
        
        balance( t );
    }
    
    static const int ALLOWED_IMBALANCE = 1;

    // Assume t is balanced or within one of being balanced
    void balance( AvlNode * & t )
    {
        if( t == nullptr ){
            return;
        }
        
        if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE )
        {
            if( height( t->left->left ) >= height( t->left->right ) ){
                rotateWithLeftChild( t );
            }else{
                doubleWithLeftChild( t );
            }
        }else if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE )
        {
            if( height( t->right->right ) >= height( t->right->left ) ){
                rotateWithRightChild( t );
            } else {
                doubleWithRightChild( t );
            }
        }
        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }
    
    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    AvlNode * findMin( AvlNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    AvlNode * findMax( AvlNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     */
    bool contains( const Comparable & x, AvlNode *t ) const
    {
        if( t == nullptr )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }
/****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, AvlNode *t ) const
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
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( AvlNode *t ) const
    {
        if( t != nullptr )
        {
            printTree( t->left );
            cout << t->element << endl;
            printTree( t->right );
        }
    }

    /**
     * Internal method to clone subtree.
     */
    AvlNode * clone( AvlNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
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
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
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
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
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
     * Internal method to find a recognition sequence in the tree.
     * @x: recognition sequence to be search for in the tree
     * @t: node who's recognition sequence is currently being checked
     */
    bool findRecSeq(const string & x, AvlNode *t ) const{
        if( t == nullptr ){
            cout << "Not Found." << endl;
            return false;
        } else if( x < t->element.Get_Rec_Seq() ){
            return findRecSeq( x, t->left );
        } else if( t->element.Get_Rec_Seq() < x ){
            return findRecSeq( x, t->right );
        }else{
            for(int i = 0; i < t->element.Get_Size_of_Enz_Acro(); i++){
                cout << t->element.Get_Enz_Acro(i) << " ";
            }
            cout << endl;
            return true;
        }
    }
    
    /**
     * Calculate and return the number of nodes within the tree
     */
    int numOfNodes(AvlNode *t ) const{
        if( t == nullptr ){
            return 0;
        }
        return (numOfNodes(t->left) + 1 + numOfNodes(t->right));
    }
    
    /**
     * Internal method to calculate the average depth of the tree.
     * @x: the counter keeping track of how many nodes are in the tree
     */
    float AverageDepth(const AvlNode *t, int x ) const{
        
        if(t == nullptr){
            return 0;
        }
        return (x + AverageDepth(t->left, x+1) + AverageDepth(t->right, x+1));
    }
    
    /**
     * Finds a recognition sequence in the tree and reutrns 1 if found. 0 if not found.
     * @x: recognition sequence being searched in the tree
     * @t: node who's recognition sequence is being checked
     * @count_recurs: count how many times a recursive call is being made
     */
    bool find(const string &x, const AvlNode *t, float &count_recurs) const{
        if( t == nullptr ){
            return false;
        } else if( x < t->element.Get_Rec_Seq() ){
            count_recurs++;
            return find( x, t->left,count_recurs );
        } else if( t->element.Get_Rec_Seq() < x ){
            count_recurs++;
            return find( x, t->right, count_recurs );
        }else{
            return true;
        }
    }
};

#endif
