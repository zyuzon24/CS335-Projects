// test_hash_map.cc
// Zach Yuzon
// The main file used to run and create the hash table
// April 8, 2018
#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "quadratic_probing.h"
#include "separate_chaining.h"
#include "double_probing.h"
#include "HashNode.h"

using namespace std;


template <typename HashTableType>
void TestComputeAdjacentWords(HashTableType &hash_table, const vector<string> &words) {
    // This is for computing timing.
    const auto begin = chrono::high_resolution_clock::now();

    hash_table.MakeEmpty();
    //..Insert your own code using algorithm described in Figure 4.73
    vector<string> orig = words;
    int length = 1;
    int count = 0;
    
    while( (orig.empty() == false) ){
        vector<string> wordsByLength;
        while(count < orig.size()){                                         //fill wordsByLength by each length size
            if(orig[count].length() == length){
                wordsByLength.push_back(orig[count]);
                orig.erase( orig.begin() + count);
                --count;
            }
            ++count;
        }
        
        
        if(wordsByLength.size() > 0){                                       //go through every possible character in each word
            
            for(int i = 0; i < length; ++i){
                vector<string> repToWord;
                
                for(int j = 0; j < wordsByLength.size(); ++j){              //for every word of the current 'length' in 'wordsByLength' erase the same position
                                                                            //and store the shortened word to a new vector called repToWord
                    string rep = wordsByLength[j];
                    rep.erase(i,1);
                    repToWord.push_back(rep);
                    
                }
                
                for(int p = 0; p < repToWord.size(); ++p){                //Compare the shortened strings to each other.
                                                                          //If they are exactly the same, put them into the map with both as values.
                    for(int q = p + 1; q < repToWord.size(); ++q){
                        
                        if(repToWord[p] == repToWord[q]){

                            hash_table.Insert(wordsByLength[p],wordsByLength[q]);
                            hash_table.Insert(wordsByLength[q],wordsByLength[p]);

                        }
                        
                    
                    }
                    
                }
                

                
                repToWord.clear();
            
            }
        }

        
        ++length;
        wordsByLength.clear();
        count = 0;
    }
    //cout << "All the values inside the table" << endl;
    //hash_table.Traverse();                            //used to print out all buckets in the map
    const auto end = chrono::high_resolution_clock::now();
    
    cout << chrono::duration_cast<chrono::nanoseconds>(end-begin).count() << "ns" << endl;
    cout << chrono::duration_cast<chrono::milliseconds>(end-begin).count() << "ms" << endl;
    
    string input;
    cout << "Please enter a word to check its adjacent words in the Dictionary." << endl;
    cin >> input;
    vector<string> ans;
    hash_table.getItemsFromMap(input, ans);
    cout << "Key: " << input << endl;
    cout << "Values: ";
    for(int i = 0; i < ans.size(); ++i){
        cout << ans[i] << " ";
    }
    ans.clear();
    cout << "\n\n";
    
    cout << "Please enter another word to check its adjacent words in the Dictionary." << endl;
    cin >> input;
    hash_table.getItemsFromMap(input, ans);
    cout << "Key: " << input << endl;
    cout << "Values: ";
    
    for(int i = 0; i < ans.size(); ++i){
        cout << ans[i] << " ";
    }
    cout << endl;
   

}

vector<string> ReadWordsFromFile(const string &words_filename) {
    vector<string> the_words;
    // Implement this...
    ifstream inFile;
    inFile.open(words_filename);
    string word;
    while(getline(inFile,word)){
        the_words.push_back(word);
    }
    inFile.close();
    return the_words;
}

// Sample main for program CreateAndTestHash
int main(int argc, char **argv) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " words_file_name hash_type (chaining, quadratic or double)" << endl;
        return 0;
    }
  
    const string words_filename(argv[1]);
    const vector<string> the_words = ReadWordsFromFile(words_filename);

    const string param_flag(argv[2]);

    if (param_flag == "chaining") {
        HashSeparateChaining<string,string> separate_chaining_table;
        TestComputeAdjacentWords(separate_chaining_table, the_words);
    } else if (param_flag == "quadratic") {
        HashQuadraticProbing<string,string> quadratic_probing_table;
        TestComputeAdjacentWords(quadratic_probing_table, the_words);
    } else if (param_flag == "double") {
        HashTableDouble<string,string> double_probing_table;
        TestComputeAdjacentWords(double_probing_table, the_words);
    } else {
        cout << "Uknown tree type " << param_flag << " (User should provide linear, quadratic, or double)" << endl;
    }
    return 0;
}
