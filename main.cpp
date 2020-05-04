//
// Created by elise on 5/1/2020.
//
#include <iostream>
#include <fstream>
#include "util/Classifier.h"
#include "util/TrivialDS.h"
#include "util/BayesClassifier.h"
#include "util/KNNClassifier.h"


int main(){
   bool choice  = choose();
   bool choice2 = chooseTrain();
    Classifier* cc = new BayesClassifier("../data/dev-train-data.csv",
                                   "../data/dev-train-target.csv",
                                   "../data/dev-test-data.csv",
                                   "../data/dev-test-target.csv");
    cc->selectMode(choice);
    cc->trainMode(choice2);
    cc->classify();

//    RBTree<Word> tree = cc->getTree();

    std::cout << "done classifyig... " << std::endl;

}


