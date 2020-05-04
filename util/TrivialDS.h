//
// Created by elise on 5/2/2020.
//

#ifndef TWEET_ANALYSIS_PT2_TRIVIALDS_H
#define TWEET_ANALYSIS_PT2_TRIVIALDS_H
#include "Classifier.h"

class TrivialDS : public Classifier {
private:
    bool pos = 1;
public:
    TrivialDS(std::string trainData, std::string trainTarget, std::string data, std::string target)
    : Classifier(trainData, trainTarget, data, target){}

    virtual void classify();
    virtual void checkline(std::string& line);
    virtual void calculateAccuracy();

};


#endif //TWEET_ANALYSIS_PT2_TRIVIALDS_H
