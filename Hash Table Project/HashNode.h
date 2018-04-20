// HashNode.h
// Zach Yuzon
// An implementation of a HashNode class
// April 8, 2018
#ifndef HASHNODE_H
#define HASHNODE_H

#include <vector>
using namespace std;

enum EntryType {ACTIVE, EMPTY, DELETED};
template<typename KeyType, typename ItemType>
class HashNode
{
public:
/*************
* CONSTRUCTORS *
 *************/
    
    // Default Constructor
    HashNode(){
        key_ = "";
        size_ = 0;
        info_ = EMPTY;
    }
    
    // Constructor
    // @k: key to assign to the HashNode
    // @itm: first item to assign into HashNode
    HashNode(const KeyType &k, const ItemType &itm){
        key_ = k;
        items_.push_back(itm);
        size_ = 1;
        info_ = ACTIVE;
    }
    
    // Constructor
    // @k: key to assign to the HashNode
    HashNode(const KeyType &k){
        key_ = k;
        size_ = 0;
        info_ = ACTIVE;
    }
    
/*************
 * ACCESSORS *
 *************/
    KeyType getKey() const{
        return key_;
    }
    
    ItemType getItem(int i) const{
        return items_[i];
    }
    
    vector<ItemType> getVecItems() const{
        return items_;
    }
    
    int getSize() const{
        return size_;
    }
    
    EntryType getInfo() const{
        return info_;
    }
/*************
*  MUTATORS *
*************/
    void setInfo(const EntryType & ent){
        info_ = ent;
        return;
    }
    
    void setInfo(EntryType && ent){
        info_ = std::move(ent);
        return;
    }
    
    // Insert
    // @k: used to check if key already exists, simply pushback itm into items_
    // @itm: item to be pushed back to items_
    void Insert(const KeyType &k, const ItemType &itm){
        if(k == key_){
            items_.push_back(itm);
            info_ = ACTIVE;
            size_++;
            return;
        }
        key_ = k;
        items_.push_back(itm);
        info_ = ACTIVE;
        size_++;
        return;
    }
    
    // Insert for R-Type Values
    // @k: used to check if key already exists, simply pushback itm into items_
    // @itm: item to be pushed back to items_
    void Insert( KeyType &&k, ItemType &&itm){
        if(k == key_){
            items_.push_back(std::move(itm));
            info_ = ACTIVE;
            size_++;
            return;
        }
        key_ = std::move(k);
        items_.push_back(std::move(itm));
        info_ = ACTIVE;
        size_++;
        return;
    }
    
    // Operator== Overload
    // @rhs: HashNode to compare to this HashNode
    // @returns a bool. false if the keys of the two nodes do not match. otherwise return true.
    bool operator==(const HashNode &rhs) const{
        if(key_ == rhs.key){
            return true;
        }
        return false;
    }
    
    // DisplayNode
    // used to print out all the items in this HashNode
    void displayNode() const{
        cout << "Key: " << key_ << endl;
        cout << "Items: " << endl;
        for(int i = 0; i < items_.size(); ++i){
            cout << items_[i] << endl;
        }
        cout << "\n";
    }
    
    // clear
    // used to delete all items in items_ vector
    void clear(){
        items_.clear();
    }
    
private:
    KeyType key_;
    vector<ItemType> items_;
    EntryType info_;
    int size_;
};

#endif
