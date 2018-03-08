// query_tree.cc
// Zach Yuzon
// Main file for Part2(a) of Homework 2.
// March 4, 2018

#include "AvlTree.h"
#include "BinarySearchTree.h"
#include "SequenceMap.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

namespace {

// @db_filename: an input filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void QueryTree(const string &db_filename, TreeType &a_tree) {
    ifstream inFile;
    string seq_data;
    vector<string> sequences;
    inFile.open(db_filename);
    
    //skip the first 10 lines of the code since
    //it does not pertain to the sequences or enzymes
    for(int i = 0; i < 10; i++){
        getline(inFile,seq_data);
    }
    
    //get each line from the file
    while(getline(inFile,seq_data)){
        istringstream ss(seq_data);
        
        //split the line by the '/' and push back to a vector
        for(string each_split; getline(ss, each_split, '/');){
            if(each_split != "/" && each_split.find_first_not_of(' ') != each_split.npos){
                sequences.push_back(each_split);
            }
        }
        
        //the first item in the vector will be the recognition sequence
        string enzymes = sequences[0];
        
        //the rest of the items will be enzymes
        //create a Sequence Map for each enzyme with the given recognition sequence
        //add the Sequence Map to the tree.
        for(int i = 1; i < sequences.size(); i++){
            SequenceMap new_seq_map (sequences[i], enzymes);
            a_tree.insert(new_seq_map);
        }
        sequences.clear();
    }
    
    //get input from the user
    string check1, check2, check3;
    cin >> check1 >> check2 >> check3;
    //find the recognition sequences in the tree.
    a_tree.findRecSeq(check1);
    a_tree.findRecSeq(check2);
    a_tree.findRecSeq(check3);
    
// Code for running Part2(a)
  // You can use public functions of TreeType. For example:
  /*
    a_tree.insert(10);
    a_tree.insert(10);*/
    //a_tree.printTree();
}

}  // namespace

int main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <tree-type>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string param_tree(argv[2]);
  cout << "Input filename is " << db_filename << endl;
  cout << "Type of tree is " << param_tree << endl;
  if (param_tree == "BST") {
    // Note that you will replace BinarySearchTree<int> with BinarySearchTree<SequenceMap>
    BinarySearchTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
  } else if (param_tree == "AVL") {
    // Note that you will replace AvlTree<int> with AvlTree<SequenceMap>
    AvlTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
  } else {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}
