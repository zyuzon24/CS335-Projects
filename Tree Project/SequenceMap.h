// BinarySearchTree.h
// Zach Yuzon
// An implementation of a Sequence Map class
// March 4, 2018
#ifndef SEQUENCEMAP_H
#define SEQUENCEMAP_H

#include <vector>
using namespace std;

class SequenceMap
{
public:

    //Part 1a)
    /**
     * Constructor of a Sequence Map
     * @a_rec_seq: the recognition sequence of the map
     * @an_enz_acro: the enzyme of the map
     */
    SequenceMap(const string &a_rec_seq, const string &an_enz_acro){
        recognition_sequence_ = a_rec_seq;
        enzyme_acronyms_.clear();
        enzyme_acronyms_.push_back(an_enz_acro);
    }
    
    //Part 1b)
    /**
     * Overloading the operator< in order to compare Sequence Maps to each other
     */
    bool operator<(const SequenceMap &rhs) const{
        if(recognition_sequence_ < rhs.recognition_sequence_){
            return true;
        }
        return false;
    }
    
    //Part 1c)
    /**
     * Overloading the operator<< so that Sequence Maps can be printed out
     */
    friend ostream &operator<<(ostream &out, const SequenceMap &a_map) {
        out << "The recognition sequence is: " << a_map.recognition_sequence_ << endl;
        out << "The enzyme(s) inside the vector: " << endl;
        for(int i = 0; i < a_map.enzyme_acronyms_.size(); i++){
            out << a_map.enzyme_acronyms_[i] << endl;
        }
        return out;
    }
    
    //Part 1d)
    /**
     * If a sequence map has the same recognition sequence as the other, combine their enzyme acronyms
     */
    void Merge(const SequenceMap &other_sequence){
        
        if(recognition_sequence_ != other_sequence.recognition_sequence_){
            return;
        }
        for(int i = 0; i < other_sequence.enzyme_acronyms_.size(); i++){
            enzyme_acronyms_.push_back(other_sequence.enzyme_acronyms_[i]);
        }
        return;
        
    }
    
    /**
     * return recognition sequence
     */
    string Get_Rec_Seq() const{
        return recognition_sequence_;
    }
    
    /**
     * return the enzyme acronym at index i
     */
    string Get_Enz_Acro(int i) const{
        return enzyme_acronyms_[i];
    }
    
    /**
     * return the size of the enzyme acronym vector
     */
    int Get_Size_of_Enz_Acro() const{
        return enzyme_acronyms_.size();
    }
private:
    string recognition_sequence_;
    vector<string> enzyme_acronyms_;
};

#endif
