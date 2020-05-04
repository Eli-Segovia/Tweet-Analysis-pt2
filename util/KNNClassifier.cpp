//
// Created by elise on 5/3/2020.
//

#include "KNNClassifier.h"

int KNNClassifier::k = 3;

void KNNClassifier::plotTrain() {
    std::cout << "plotting train data (for KNN)" << std::endl;
    std::ifstream inFIle("plot.txt");
    if(inFIle.is_open()){
        std::cout << " Using old plot" << std::endl;
        std::string line;
        while(std::getline(inFIle, line)){
            std::istringstream iss(line);
            std::string str;
            double rPos;
            double rNeg;
            bool rVal;
            iss >> str;
            rPos = std::atof(str.c_str());
            iss >> str;
            rNeg = std::atof(str.c_str());
            iss >> str;
            rVal = std::atoi(str.c_str()) == 4;
            plotPoints(rPos, rNeg, rVal);
        }
        inFIle.close();
    }
    else{
        std::cout << "using new plot " << std::endl;
        std::ifstream trainFile(this->trainData);
        std::ifstream trTargetFile(this->targetTrain);
        if(!(trainFile.is_open() && trTargetFile.is_open())){
            throw "unable to open files in KNNClassifier ln 22";
        }
        std::string line1;
        std::string line2;
        int i = 1;

        while(std::getline(trainFile, line1) && std::getline(trTargetFile, line2)){
            std::cout << i++ << std::endl;
            std::istringstream iss1(line1);
            std::istringstream iss2(line2);
            while(std::getline(iss1, line1, ','));
            std::getline(iss2, line2, ',');
            std::getline(iss2, line2, ',');

            checklinePlot(line1, line2);


        }
        trainFile.close();
        trTargetFile.close();
    }
}

void KNNClassifier::plotPoints(double posScore, double negScore, bool pos){
    this->plot.push_back(std::pair<double,bool>(std::sqrt((posScore * posScore) + (negScore * negScore)),pos));
}

void KNNClassifier::checklinePlot(std::string &line, std::string& line2) {
    std::ifstream iFile("plot.txt");
    std::ofstream of;
    if(iFile.is_open() && mode){
        mode = 0;
        of.open("plot.txt");
    }
    else of.open("plot.txt", std::ios_base::app);
    std::istringstream iss(line);
    std::string word;
    double bayesPositive = (double)this->tweetData.getPositiveTweets() / (double)this->tweetData.getTotalTweets();
    double bayesNegative = (double)this->tweetData.getNegativeTweets() / (double)this->tweetData.getTotalTweets();
    while(std::getline(iss, word,  ' ')){
        if(word.size() < 3) continue;
        remove(word);
        Word w(word);
        w.stem();

        if(this->tweetData.containsWord(w)){
            bayesPositive *= ((double)tweetData.getWord(w).getPositiveCnt() / (double)tweetData.getPositiveTweets());
            bayesNegative *= ((double)tweetData.getWord(w).getNegativeCnt() / (double)tweetData.getNegativeTweets());
        }
    }
    std::pair<double,double> output;
    output = normalize(bayesPositive, bayesNegative);
    plotPoints(output.first, output.second, std::atoi(line2.c_str()) == 4);
    of << output.first<< " " << output.second << " " << line2 << std::endl;
    of.close();
}

std::pair<double,double> KNNClassifier::normalize(double &postiveBayes, double &negativeBayes) {
    double evidenceValue = postiveBayes + negativeBayes;
    double pos = postiveBayes  / evidenceValue;
    double neg = negativeBayes / evidenceValue;
    return std::pair<double,double>(pos,neg);
}

void KNNClassifier::classify() {
    std::cout << "classifying tweets..." << std::endl;
    if(this->reClassify){
        std::cout << "Reclassifying..." << std::endl;
        std::ifstream inFile;
        inFile.open(dataFile);
        if(!inFile.is_open()){throw std::invalid_argument("No such file: " + dataFile);}
        std::string line;
        std::getline(inFile,line); // getting rid of first line
        while(std::getline(inFile,line)){
            std::istringstream iss(line);
            while(std::getline(iss, line, ','));
            checkline(line);
        }
        calculateAccuracy();
    }
    else{
        std::cout << "using previous..." << std::endl;
        calculateAccuracy();
    }
}

void KNNClassifier::checkline(std::string &line) {
    std::cout << someValIWillDelete++ << std::endl;
    std::ifstream iFile("classify.txt");
    std::ofstream of;
    if(iFile.is_open() && mode){
        mode = 0;
        of.open("classify.txt");
    }
    else of.open("classify.txt", std::ios_base::app);
    std::istringstream iss(line);
    std::string word;
    double bayesPositive = (double)this->tweetData.getPositiveTweets() / (double)this->tweetData.getTotalTweets();
    double bayesNegative = (double)this->tweetData.getNegativeTweets() / (double)this->tweetData.getTotalTweets();
    while(std::getline(iss, word,  ' ')){
        if(word.size() < 3) continue;
        remove(word);
        Word w(word);
        w.stem();

        if(this->tweetData.containsWord(w)){
            bayesPositive *= ((double)tweetData.getWord(w).getPositiveCnt() / (double)tweetData.getPositiveTweets());
            bayesNegative *= ((double)tweetData.getWord(w).getNegativeCnt() / (double)tweetData.getNegativeTweets());
        }
    }
    auto normalization = normalize(bayesPositive,bayesNegative);
    of << getKNearest(normalization.first,normalization.second) << " " << line << std::endl;
    of.close();
}

bool KNNClassifier::getKNearest(double posV, double negV, int kth) {

    return 1;
}

void KNNClassifier::calculateAccuracy() {
    std::cout << " Hello there you stupid ass bitch " << std::endl;
}