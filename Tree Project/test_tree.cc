// test_tree.cc
// Zach Yuzon
// Main file for Part2(b) of Homework 2.
// March 4, 2018
#include "AvlTree.h"
#include "BinarySearchTree.h"
#include "SequenceMap.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
using namespace std;

namespace {

// @db_filename: an input database filename.
// @seq_filename: an input sequences filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree) {
  // Code for running Part2(b)
    ifstream inFile;
    string seq_data;
    vector<string> sequences;
    inFile.open(db_filename);
    
    //skip the first 10 lines since they
    //have nothing to do with the sequences or enzymes
    for(int i = 0; i < 10; i++){
        getline(inFile,seq_data);
    }
    
    //get each line from the file
    while(getline(inFile,seq_data)){
        istringstream ss(seq_data);
        
        //split the line by the '/' and push back to a vector
        for(string each_split; getline(ss, each_split, '/');){
            if(each_split != "/" && each_split.find_first_not_of(' ') != each_split.npos){
            //if(each_split != "/"){
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
    inFile.close();
    
    cout << "2: " << a_tree.numOfNodes() << endl;
    cout << "3a: " << a_tree.AverageDepth() << endl;
    cout << "3b: " << a_tree.AverageDepth()/log2(a_tree.numOfNodes()) << endl;
    
    //open the file containing the sequences
    inFile.open(seq_filename);
    int sum_of_success_quer = 0;
    float total_quer = 0;
    float count_find_recurs = 0;
    
    //calculate the number of: successful queries, recursions done, and total amount of queries
    while(getline(inFile,seq_data)){
        if(a_tree.find(seq_data,count_find_recurs) == 1){
            sum_of_success_quer += 1;
        }
        ++total_quer;
    }
    inFile.close();
    cout << "4a: " << sum_of_success_quer << endl;
    cout << "4b: " << count_find_recurs/total_quer<< endl;
    
    float num_of_remove_calls = 0;
    float num_of_success_removes = 0;
    float num_remove_recurs = 0;
    int count = 0;
    //reopen the file containing the sequences
    inFile.open(seq_filename);
    
    //calculate the number of: successful removes, recursions done, and total amount of remove calls
    while(getline(inFile,seq_data)){
        if(count % 2 == 0){
            num_of_remove_calls++;
            SequenceMap new_map (seq_data,"");
            a_tree.remove(new_map, num_of_success_removes, num_remove_recurs);
        }
        count++;
    }
    inFile.close();
    cout << "5a: " << num_of_success_removes << endl;
    cout << "5b: " << num_remove_recurs/num_of_remove_calls << endl;
    
    cout << "6a: " << a_tree.numOfNodes() << endl;
    cout << "6b: " << a_tree.AverageDepth() << endl;
    cout << "6c: " << a_tree.AverageDepth()/log2(a_tree.numOfNodes()) << endl;
}

}  // namespace

int
main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename> <tree-type>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string seq_filename(argv[2]);
  const string param_tree(argv[3]);
  cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;
  cout << "Type of tree is " << param_tree << endl;
  if (param_tree == "BST") {
    // Note that you will replace BinarySearchTree<int> with BinarySearchTree<SequenceMap>
    BinarySearchTree<SequenceMap> a_tree;
    TestTree(db_filename, seq_filename, a_tree);
  } else if (param_tree == "AVL") {
    // Note that you will replace AvlTree<int> with AvlTree<SequenceMap>
    AvlTree<SequenceMap> a_tree;
    TestTree(db_filename, seq_filename, a_tree);
  } else {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}
