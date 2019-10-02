#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "dsexceptions.h"
#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream> 
using namespace std;

// AvlTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x (unimplemented)
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class AvlTree
{
  public:
    int q = 0;
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
     */
    void remove( const Comparable & x, float &removeCounter)
    {
        remove( x, root, removeCounter);
    }

    int countNumberNodesPublic(){
        return countNumberNodesPrivate(root);
    }

    Comparable findPublicFunction(const Comparable &x){
        return findPrivateFunction(x, root);
    }

    float findPublicFunctionForRecurrences(const Comparable &x, float &recurrenceCounter, float &query){
        return findPrivateFunctionForRecurrences(x, root, recurrenceCounter, query);
    }


    float averageDepthPublic(){
        return averageDepthPrivate(root);
    }

    float depthTransversalPublic(const Comparable &x){
        return depthTransversalPrivate(root);
    }

    int getFoundQueriesPublic(){
        return getFoundQueriesPrivate(q);
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
        
        balance( t );
    }
     
    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove( const Comparable & x, AvlNode * & t, float &removeCounter)
    {
        
        if( t == nullptr )
            return;   // Item not found; do nothing
        
        if( x < t->element )
            remove( x, t->left, removeCounter );
        else if( t->element < x )
            remove( x, t->right, removeCounter );
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin( t->right )->element;
            remove( t->element, t->right, removeCounter );
        }
        else
        {
            ++removeCounter;
            AvlNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
            //cout << "This is number of successfuly remove calls: " << removeCounter << endl;
        }
        
        balance( t );
    }
    
    static const int ALLOWED_IMBALANCE = 1;

    // Assume t is balanced or within one of being balanced
    void balance( AvlNode * & t )
    {
        if( t == nullptr )
            return;
        
        if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE ) {
            if( height( t->left->left ) >= height( t->left->right ) )
                rotateWithLeftChild( t );
            else
                doubleWithLeftChild( t );
        } else if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE ) {
            if( height( t->right->right ) >= height( t->right->left ) )
                rotateWithRightChild( t );
            else
                doubleWithRightChild( t );
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

    Comparable findPrivateFunction(const Comparable &x, AvlNode * & t){

        if( t == nullptr )
            return Comparable("", "not found");
        else if( x < t->element )
            return findPrivateFunction( x, t->left);
        else if( t->element < x )
            return findPrivateFunction( x, t->right);
        else
            //cout << "This is number of recursive calls: " << c << endl;
            //++query;
            //getFoundQueriesPrivate(query);
            //cout << "Number of queries: " << query << endl;

            return t->element;    // Match
    }

    int countNumberNodesPrivate(AvlNode *& t){
        int rootNodeCounter = 1; 

        if(t == nullptr){
            return 0;
        }else if(t->left != nullptr){
            countNumberNodesPrivate(t->left);
        }else if(t->right != nullptr){
            countNumberNodesPrivate(t->right);
        }
        return countNumberNodesPrivate(t->left) + countNumberNodesPrivate(t->right) + rootNodeCounter;
    }


    int sumOfHeights(AvlNode *& t){
        int rootNodeCounter = height(t);

        if(t == nullptr){
            return 0;
        }else if(t->left != nullptr){
            sumOfHeights(t->left);
        }else if(t->right != nullptr){
            sumOfHeights(t->right);
        }
        
        return sumOfHeights(t->left) + sumOfHeights(t->right) + rootNodeCounter;
    }

    float nodeDepthPrivate(AvlNode *& x, AvlNode *& t){
        if( t == nullptr )
            return 0;
        else if(t == x)
            return 0; 

        if( x->element < t->element )
            return nodeDepthPrivate( x, t->left ) + 1;
        if( t->element < x->element )
            return nodeDepthPrivate( x, t->right ) + 1;
          // Match
    }

    float depthTransversalPrivate(AvlNode *& t){
        if(t == nullptr){
            return 0;
        }
        return depthTransversalPrivate(t->left) + depthTransversalPrivate(t->right) + nodeDepthPrivate(t, root); 
    }

    float averageDepthPrivate(AvlNode *& t){
        float averageDepth = depthTransversalPrivate(t) / countNumberNodesPrivate(t);
        return averageDepth;
    }

    int getFoundQueriesPrivate(int q){
        vector<int> successfulQueriesFound;
        successfulQueriesFound.push_back(q);
        int totalQueries = 0;

        for(int i = 0; i < successfulQueriesFound.size(); i++){
            cout << successfulQueriesFound[i] << endl;
            totalQueries += successfulQueriesFound[i];
        }

        return totalQueries;
    }

    float findPrivateFunctionForRecurrences(const Comparable &x, AvlNode * & t, float &recurrenceCounter, float &query){
        ++recurrenceCounter;
        

        if( t == nullptr )
            //return Comparable("", "not found");
            return 0.0;
        else if( x < t->element )
            return findPrivateFunctionForRecurrences( x, t->left, recurrenceCounter, query);
        else if( t->element < x )
            return findPrivateFunctionForRecurrences( x, t->right, recurrenceCounter, query);
        else
            //cout << "This is number of recursive calls: " << recurrenceCounter << endl;
            ++query;
            /*
            successfulQueryVector.push_back(query);
            
            for(int i = 0; i < successfulQueryVector.size(); i++){
                result += successfulQueryVector[i];
            }
            */
            //getFoundQueriesPrivate(query);
            //cout << "Number of queries: " << query << endl;
            //cout << "This is number of queries: " << query << endl;
            return query;   // Match
    }
};

#endif
