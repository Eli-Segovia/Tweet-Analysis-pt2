//
// Created by elise on 5/3/2020.
//

#include "KNNClassifier.h"

int KNNClassifier::k = 3;

void KNNClassifier::plotTrain() {                               //plotting the data gathered from training onto a "graph"
    std::cout << "plotting train data (for KNN)" << std::endl;  // we will use this graph to compare to later determine
    std::ifstream inFIle("plot.txt");                       // the proximity that the future tweets have with respect
    if(inFIle.is_open()){                                      // to these plotted data.
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
        std::cout << "using new plot " << std::endl;             // uses a new plot rather than the existing one
        std::ifstream trainFile(this->trainData);
        std::ifstream trTargetFile(this->targetTrain);
        if(!(trainFile.is_open() && trTargetFile.is_open())){
            throw "unable to open files in KNNClassifier ln 22";
        }
        std::string line1;
        std::string line2;
        int i = 1;

        while(std::getline(trainFile, line1) && std::getline(trTargetFile, line2)){
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

void KNNClassifier::plotPoints(double posScore, double negScore, bool pos){   // plots the points as a vector
    this->plot.push_back(std::pair<double,bool>(std::sqrt((posScore * posScore) + (negScore * negScore)),pos));
   // std::cout << plot.at(plot.size() - 1).first << std::endl;
}

void KNNClassifier::checklinePlot(std::string &line, std::string& line2) {
    std::ifstream iFile("plot.txt");                  // checks the statistics of the tweet and plots it by
    std::ofstream of;                                  // calculating a score using the bayes method.
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
    double evidenceValue = postiveBayes + negativeBayes;   // normalizes the bayes values received by simply multiplying
    double pos = postiveBayes  / evidenceValue;            // values
    double neg = negativeBayes / evidenceValue;
    return std::pair<double,double>(pos,neg);
}

void KNNClassifier::classify() {
    plotTrain();                                                  // like the other ones, simply does some io stuff
    std::cout << "classifying tweets..." << std::endl;           // and passes pertinent data to the the other methods.
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

char KNNClassifier::getKNearest(double posV, double negV, int kth) {  // finds the values with the smaller distances
    double value = std::sqrt((posV * posV) + (negV * negV));        // based on the calculated score
    std::vector<int> values;                                          // if the distance is small enough we consider
    for(auto kValue : this->plot){                                 //it and determine the positivity based on the votes
        if(values.size() == 3) break;                               // that the top three tweet plots have.
        if(std::abs(kValue.first - value) <= 0.001){
            values.push_back(kValue.second);
        }
    }
    double avg = 0;
    for(auto i : values){
        avg += i;
    }
    avg = avg / values.size();
    //std::cout << avg << std::endl;
    if(avg >= 0.5){
        return '+';
    }
    else
        return '-';

}

void KNNClassifier::calculateAccuracy() {
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