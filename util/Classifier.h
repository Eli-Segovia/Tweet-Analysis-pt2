//
// Created by elise on 5/1/2020.
//

#ifndef TWEET_ANALYSIS_PT2_CLASSIFIER_H
#define TWEET_ANALYSIS_PT2_CLASSIFIER_H
#include <iostream>

class Classifier {
private:
    std::string dataFile;
    std::string targetFile;
public:
    Classifier(std::string data, std::string target){
        this->dataFile   = data;
        this->targetFile = target;
    }
    virtual void classify() = 0;

};


#endif //TWEET_ANALYSIS_PT2_CLASSIFIER_H
