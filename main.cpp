//
// Created by elise on 5/1/2020.
//
#include <iostream>
#include <fstream>
#include "util/Classifier.h"
#include "util/TrivialDS.h"
#include "util/BayesClassifier.h"
#include "util/KNNClassifier.h"


int main(int argc, char* argv[]){
    bool choice  = choose();
    bool choice2 = chooseTrain();
    Classifier* cc = nullptr;
    if (argc == 1) throw std::invalid_argument("Please provide command line flag to to properly process");
    std::cout << argv[1] << std::endl;
    std::string arg = argv[1];
   if(argc == 2 && arg.compare("-k") == 0){
       cc = new KNNClassifier("../data/dev-train-data.csv",
               "../data/dev-train-target.csv",
              "../data/dev-test-data.csv",
              "../data/dev-test-target.csv");
   }
   else if(argc == 2 && arg.compare("-t") == 0){
       cc = new TrivialDS("../data/dev-train-data.csv",
                             "../data/dev-train-target.csv",
                             "../data/dev-test-data.csv",
                             "../data/dev-test-target.csv");
   }
   else if(argc == 2 && arg.compare("-b") == 0){
       cc = new BayesClassifier("../data/dev-train-data.csv",
                          "../data/dev-train-target.csv",
                          "../data/dev-test-data.csv",
                          "../data/dev-test-target.csv");
   }
   else{
       throw std::invalid_argument("You need to provide a flag as a commad line arg:\n-b: Bayes\n-k: knn\n-t: trivial");
   }


    cc->selectMode(choice);
    cc->trainMode(choice2);
    cc->classify();

//    RBTree<Word> tree = cc->getTree();

    std::cout << "done classifyig... " << std::endl;

}


