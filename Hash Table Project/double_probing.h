// double_probing.h
// Zach Yuzon
// An implementation of a Double Probing hash table
// April 8, 2018

#ifndef DOUBLE_PROBING_H
#define DOUBLE_PROBING_H

#include <vector>

 #include "is_prime.h"
 #include "HashNode.h"

using namespace std;

template<typename KeyType, typename ItemType>
class HashTableDouble
{
public:
    
  explicit HashTableDouble(size_t size = 101) : array_(PrimeProject::NextPrime(size))
    { MakeEmpty(); }
  
  // Contains
  // @k: the Key to check if is currently ACTIVE within the map
  // @return a bool is returned. true if it is found within the table. otherwise false.
  bool Contains(const KeyType & k) const {
    return IsActive(FindPos(k));
  }
    
  // MakeEmpty
  // Makes entire table empty
  void MakeEmpty() {
    current_size_ = 0;
    for (auto &entry : array_)
        entry.setInfo(EMPTY);
  }
    
  bool Insert(const KeyType & k, const ItemType & itm) {
    // Insert k as active
    size_t current_pos = FindPos(k);
    if (IsActive(current_pos)){
        if(array_[current_pos].getKey() == k){
            
            array_[current_pos].Insert( k, itm);
            
        }
        return false;
    }
    HashNode<KeyType,ItemType> newEntry( k , itm );
    array_[current_pos] = newEntry;
      
        // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
        Rehash();
    return true;
  }
    
  bool Insert(KeyType && k, ItemType && itm) {
    size_t current_pos = FindPos(k);
    if (IsActive(current_pos)){
        if(array_[current_pos].getKey() == k){
            
            array_[current_pos].Insert( std::move(k), std::move(itm) );
            
                
        }
        return false;
    }
        
    HashNode<KeyType,ItemType> newEntry( std::move(k) , std::move(itm) );
    array_[current_pos] = newEntry;
        
        // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
        Rehash();
        
    return true;
  }
    
    
  bool Remove(const KeyType & k) {
    size_t current_pos = FindPos(k);
    if (!IsActive(current_pos))
        return false;
        
    array_[current_pos].setInfo(DELETED);
    return true;
  }
    
  // getItemsFromMap
  // @k: used to check if exists in the map. if it doesn't, then do nothing.
  // @v: used to store the vector of Items found in the HashNode with KeyType k
  void getItemsFromMap( const KeyType &k, std::vector<ItemType> &v ) const {
    size_t current_pos = FindPos(k);
    if( Contains(k) == false ){
        return;
    }
    v = array_[current_pos].getVecItems();
    return;
  }
    
  // Traverse
  // used to print out all the buckets in the map
  void Traverse(){
    for(int i = 0; i < array_.size(); ++i){
        cout << "Key: " << array_[i].getKey() << endl;
        cout << "Values: ";
        for(int j = 0; j < array_[i].getSize(); ++j){
            cout << array_[i].getItem(j) << " ";
        }
        cout << "\n\n";
    }
  }
    
private:
 
  std::vector<HashNode<KeyType,ItemType>> array_;
  size_t current_size_;
    
  bool IsActive(size_t current_pos) const
  { return array_[current_pos].getInfo() == ACTIVE; }
    
  size_t FindPos(const KeyType & k) const {
    size_t offset = 1;
    size_t current_pos = InternalHash(k);
        
    while (array_[current_pos].getInfo() != EMPTY && array_[current_pos].getKey() != k) {
        current_pos = (InternalHash(k) + (offset * SecondHash(k))) % current_size_;
        offset += 1;
        if (current_pos >= array_.size()){
            current_pos -= array_.size();
        }
    }
    return current_pos;
  }
    
  void Rehash() {
    std::vector<HashNode<KeyType,ItemType>> old_array = array_;
        
    // Create new double-sized, empty table.
    array_.resize(PrimeProject::NextPrime(2 * old_array.size()));
    for (auto & entry : array_)
        entry.setInfo(EMPTY);
        
    // Copy table over.
    current_size_ = 0;
    for (auto & entry :old_array){
        if (entry.getInfo() == ACTIVE){
            for(int i = 0; i < entry.getSize(); ++i){
                Insert(std::move(entry.getKey()), std::move(entry.getItem(i)));
            }
        }
    }
  }
    
  size_t InternalHash(const KeyType & k) const {
    static std::hash<KeyType> hf;
    return hf(k) % array_.size( );
  }
    
  size_t SecondHash(const KeyType & k) const {
    static std::hash<KeyType> hf;
    return 7 - (hf(k) % 7);
  }
};

#endif

