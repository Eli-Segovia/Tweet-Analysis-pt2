//
// Created by elise on 5/3/2020.
//

#include "BayesClassifier.h"


void BayesClassifier::classify() {
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

void BayesClassifier::checkline(std::string &line) {
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
    of << normalize(bayesPositive, bayesNegative) << " " << line << std::endl;
    of.close();
}

void BayesClassifier::calculateAccuracy() {
    std::ofstream of;

    std::ifstream inFile(this->targetFile);
    std::ifstream inFile2("classify.txt");
    if(!inFile.is_open() || !inFile2.is_open()){throw std::invalid_argument("Unable to locate files: " );}
    std::string line;
    std::string line2;
    std::getline(inFile,line);
    double accuracy = 0;
    while(std::getline(inFile,line) && std::getline(inFile2, line2)){
        char rating;
        std::istringstream iss2(line2);
        iss2 >> rating;
        total++;
        std::string rate;
        std::istringstream iss(line);
        std::getline(iss,rate,',');
        std::getline(iss,rate,',');
        if( (rating == '-' && rate == "0") || (rating == '+' && rate =="4")){
            correct ++;
        }
    }
    inFile. close();
    inFile2.close();
    of.open("accuracy.txt");
    if(!of.is_open()){throw std::exception_ptr();}
    accuracy = (double)correct / (double)total;
    std::cout << correct << "/" << total << std::endl;
    of << accuracy;
    of.close();
}

char BayesClassifier::normalize(double &postiveBayes, double &negativeBayes) {
    this->evidenceValue = postiveBayes + negativeBayes;
    double pos = postiveBayes / evidenceValue;
    double neg = negativeBayes / evidenceValue;
    //std::cout << pos << " " << neg << std::endl;
    if(pos == neg){
        posi = !posi;
        return posi? '+' : '-';

    }
    else
        return pos > neg? '+' : '-';
}
