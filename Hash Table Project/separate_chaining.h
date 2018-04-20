// separate_chaining.h
// Zach yuzon
// An implementation of a hash table using separate chaining to deal with collisions
// April 8, 2018
#ifndef SEPARATE_CHAINING_H
#define SEPARATE_CHAINING_H

#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;

#include "is_prime.h"
#include "HashNode.h"

// SeparateChaining Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items

template <typename KeyType, typename ItemType>
class HashSeparateChaining {
public:
    explicit HashSeparateChaining(int size = 101) : current_size_{0} {
        the_lists_.resize( 101 ); }
    
    // Contains
    // @k: the Key to check if is currently ACTIVE within the map
    // @return a bool is returned. true if it is found within the table. otherwise false.
    bool Contains( const KeyType & x ) const {
        auto & which_list = the_lists_[ MyHash( x )];
        for(int i = 0; i < which_list.size(); ++i){
            if(which_list[i].getKey() == x){
                return true;
            }
        }
        return false;
    }
    
    // MakeEmpty
    // Makes entire table empty
    void MakeEmpty( ) {
        for( auto & this_list : the_lists_ )
            this_list.clear( );
    }
    
    bool Insert( const KeyType & k, const ItemType & itm ) {
        auto & which_list = the_lists_[ MyHash( k ) ];
        
        if( Contains(k) ){
            for(int i = 0; i < which_list.size(); i++){
                if(which_list[i].getKey() == k){
                    which_list[i].Insert(k, itm);
                    if( current_size_ > the_lists_.size( ) ){
                        Rehash( );
                    }
                    return false;
                }
                
            
            }
        }
        HashNode<KeyType,ItemType> newNode( k , itm);
        which_list.push_back(newNode);
        
        // Rehash; see Section 5.5
        if( ++current_size_ > the_lists_.size( ) )
            Rehash( );
        return true;
        
    }
    
    bool Insert( KeyType && k, ItemType && itm ) {
        
        auto & which_list = the_lists_[ MyHash( k ) ];
        if( Contains(k) ){
            for(int i = 0; i < which_list.size(); i++){
                if(which_list[i].getKey() == k){
                    which_list[i].Insert(std::move(k), std::move(itm));
                    
                    if( current_size_ > the_lists_.size( ) ){
                        Rehash( );
                    }
                    
                    return false;
                }
    
            }
            
            
        }
        HashNode<KeyType,ItemType> newNode( std::move(k), std::move(itm));
        which_list.push_back(newNode);
        // Rehash; see Section 5.5
        if( ++current_size_ > the_lists_.size( ) )
            Rehash( );
                
        return true;
        
        
    }
    
    bool Remove( const KeyType & k  ) {
        auto & which_list = the_lists_[ MyHash( k ) ];
                

        if(Contains(k) == false){
            return false;
        }
        for(int i = 0; i < which_list.size(); ++i){
            if(which_list[i].key_ == k){
                HashNode<KeyType,ItemType> temp = which_list[i];
                which_list.remove(temp);
                --current_size_;
                return true;
            }
        }
    }
    
    // getItemsFromMap
    // @k: used to check if exists in the map. if it doesn't, then do nothing.
    // @v: used to store the vector of Items found in the HashNode with KeyType k
    void getItemsFromMap( const KeyType &k, vector<ItemType> &v ) const {
        if(Contains(k) == false){
            return;
        }
        auto & which_list = the_lists_[ MyHash( k )];
        for(int i = 0; i < which_list.size(); ++i){
            if(which_list[i].getKey() == k){
                v = which_list[i].getVecItems();
                return;
            }
        }
        return;
    }
    
    // Traverse
    // used to print out all the buckets in the map
    void Traverse(){
        for(int i = 0; i < the_lists_.size(); ++i){
            vector<HashNode<KeyType, ItemType>> check = the_lists_[i];
            for(int j = 0; j < check.size(); ++j){
            
                cout << "Key: " << check[j].getKey() << endl;
        
                cout << "Values: " << endl;
                for(int k = 0; k < check[j].getSize(); ++k){
                    cout << check[j].getItem(k) << " ";
                }
                cout << "\n\n";
            }
        }
    }
            
private:
    vector<vector<HashNode<KeyType, ItemType>>> the_lists_;
    int  current_size_;
            
    void Rehash( ) {
        vector<vector<HashNode<KeyType, ItemType>>> old_lists = the_lists_;
        
        // Create new double-sized, empty table
        the_lists_.resize( PrimeProject::NextPrime( 2 * the_lists_.size( ) ) );
        for( auto & this_list : the_lists_ ){
            this_list.clear();
        }
        // Copy table over
        
        
        current_size_ = 0;
        
        for(int i = 0; i < old_lists.size(); ++i){
            for(int j = 0; j < old_lists[i].size(); ++j){
                
                for(int k = 0; k < old_lists[i][j].getSize(); ++k){
                    Insert( old_lists[i][j].getKey() , old_lists[i][j].getItem(k) );
                }
                
            }
        }
        
    }
    
    size_t MyHash( const KeyType & x ) const {
        static hash<KeyType> hf;
        return hf( x ) % the_lists_.size( );
    }
    
};
        
#endif
