//
// Created by elise on 5/3/2020.
//

#ifndef TWEET_ANALYSIS_PT2_KNNCLASSIFIER_H
#define TWEET_ANALYSIS_PT2_KNNCLASSIFIER_H
#include "Classifier.h"
#include <math.h>

class KNNClassifier: public Classifier {
private:
    int someValIWillDelete = 0;
    bool posi = 1;
    static int k;
    std::vector< std::pair< double, bool > > plot;
public:

    KNNClassifier(std::string trainData, std::string trainTarget, std::string data, std::string target)
    : Classifier(trainData, trainTarget, data, target){}

    void plotTrain();
    char getKNearest(double, double, int kth = k);

    void plotPoints(double, double, bool);

    void checklinePlot(std::string&, std::string& pos);
    std::pair<double,double> normalize(double&, double&);


    virtual void classify();
    virtual void checkline(std::string& line);
    virtual void calculateAccuracy();

};


#endif //TWEET_ANALYSIS_PT2_KNNCLASSIFIER_H
