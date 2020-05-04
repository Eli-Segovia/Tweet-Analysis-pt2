//
// Created by elise on 5/1/2020.
//

#ifndef TWEET_ANALYSIS_PT2_CLASSIFIER_H
#define TWEET_ANALYSIS_PT2_CLASSIFIER_H
#include "TweetData.h"

class Classifier {
protected:
    std::string   trainData;
    std::string targetTrain;
    std::string    dataFile;
    std::string  targetFile;
    TweetData     tweetData;
    int total = 0;
    int correct = 0;
    bool reClassify;
    bool mode = 1;

public:

    Classifier(std::string trainData, std::string trainTarget, std::string data, std::string target){
        this->trainData   =   trainData;
        this->targetTrain = trainTarget;
        this->dataFile    =        data;
        this->targetFile  =      target;
        loadData();
    }

    virtual void selectMode(bool choice){
        std::cout << choice << std::endl;
        this->reClassify = choice;
    }



    virtual void loadData(){
        std::ifstream inFile("tweetData.csv");
        if(!inFile.is_open()){
            std::cout << "training..." << std::endl;
            tweetData.train(this->trainData, this->targetTrain);
            tweetData.outputData();
        }
        else{
            std::cout << "loading data..." << std::endl;
            inFile.close();
            tweetData.copy();
        }
    }


    virtual RBTree<Word> getTree(){
        return this->tweetData.getWords();
    }


    virtual void classify() = 0;
    virtual void checkline(std::string& line) = 0;
    virtual void calculateAccuracy() = 0;
    //virtual void outputResults() = 0;

};


#endif //TWEET_ANALYSIS_PT2_CLASSIFIER_H
