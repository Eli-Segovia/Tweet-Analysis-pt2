//
// Created by elise on 5/3/2020.
//

#ifndef TWEET_ANALYSIS_PT2_BAYESCLASSIFIER_H
#define TWEET_ANALYSIS_PT2_BAYESCLASSIFIER_H
#include "Classifier.h"

class BayesClassifier : public Classifier {
private:
    double evidenceValue = 0;
    bool posi = 0;
public:
    BayesClassifier(std::string trainData, std::string trainTarget, std::string data, std::string target)
    : Classifier(trainData, trainTarget, data, target){}
    virtual void classify();
    virtual void checkline(std::string& line);
    virtual void calculateAccuracy();
    char normalize(double& postiveBayes, double& negativeBayes);
};


#endif //TWEET_ANALYSIS_PT2_BAYESCLASSIFIER_H
