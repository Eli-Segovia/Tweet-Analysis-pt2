//
// Created by elise on 5/1/2020.
//
#include <iostream>
#include "util/Word.h"
#include "util/RBTree.h"
#include <fstream>
#include "util/TweetData.h"


void removez(std::string& word){
    while( (word.find("&quot;") >= 0 && word.find("&quot;") <= word.size())){
        word.erase(word.find("&quot;"), 6);
    }
}
int main(){
    TweetData td;
    td.train("../data/dev-train-data.csv", "../data/dev-train-target.csv");
    //td.copy();
    td.outputData();
    RBTree<Word> tree = td.getWords();

    std::cout << "done doing thing " << std::endl;
    while(true){
       std::string word;
       std::cin >> word;
       Word w = word;
       w.stem();
       if(tree.contains(w))
           std::cout << word << " is in the tree " << std::endl;
       else
           std::cout << word << " is not in the tree" << std::endl;
   }

//    std::string m = "&quot;hellothere&quot;";
//    std::cout << m.find("&quot;") << std::endl;
//    removez(m);
//    std::cout << m << std::endl;
}


