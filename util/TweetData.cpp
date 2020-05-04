//
// Created by elise on 5/1/2020.
//
#include "TweetData.h"

TweetData::TweetData(){
    readStopWords();
}

void TweetData::readStopWords(){
    std::ifstream inFile;
    inFile.open("../util/stopwords.txt");
    std::string line;
    ignore.add("");
    while(std::getline(inFile,line)){
        ignore.add(line);
    }
}


void TweetData::addWord(Word newWord){
    this->words.add(newWord);
}

bool TweetData::containsWord(Word word){
    return this->words.contains(word);
}

Word& TweetData::getWord(Word word){
    return this->words.get(word);
}

void TweetData::train(std::string trainFile, std::string testFile){
    bool isPositive;
    std::ifstream input1;
    std::ifstream input2;

    input1.open(trainFile);
    if(!input1.is_open()){throw std::invalid_argument("Not a valid file (TweetData Train)");}

    input2.open(testFile);
    if(!input2.is_open()){throw std::invalid_argument("Not a valid file (TweetData Train)");}

    std::string ln_input1;
    std::string ln_input2;
    std::getline(input1, ln_input1);
    std::getline(input2, ln_input2);
    int i = 0;
    while(std::getline(input1, ln_input1) && std::getline(input2,ln_input2)){
        std::istringstream iss1(ln_input1);
        std::istringstream iss2(ln_input2);
        while(std::getline(iss1, ln_input1, ','));
        std::getline(iss2, ln_input2, ',');
        std::getline(iss2, ln_input2, ',');
        switch(std::atoi(ln_input2.c_str())){
            case 4:
                this->positiveTweets++;
                isPositive = 1;
                break;
            case 0:
                this->negativeTweets++;
                isPositive = 0;
                break;
        }
        checkLine(ln_input1, isPositive);

    }

}

void TweetData::copy(){
    std::ifstream dataToCopy;
    dataToCopy.open("tweetData.csv");
    if(!dataToCopy.is_open()){throw std::invalid_argument("Cannot open file");}
    std::string line;
    while(std::getline(dataToCopy, line)){
        std::istringstream iss(line);
        std::string word;
        std::string pos;
        std::string neg;
        std::string tot;
        std::getline(iss,word,',' );
        std::getline(iss,tot, ',');
        std::getline(iss,neg,',' );
        std::getline(iss, pos);
        Word w(word);
        w.setTotalCnt(std::atoi(tot.c_str()));
        this->positiveTweets += std::atoi(pos.c_str());
        this->negativeTweets += std::atoi(neg.c_str());
        w.setNegativeCnt(std::atoi(neg.c_str()));
        w.setPositiveCnt(std::atoi(pos.c_str()));
        this->words.add(w);
    }
}

void TweetData::checkLine(std::string & line, bool pos){
    std::istringstream iss(line);
    std::string word;
    while(std::getline(iss, word,  ' ')){
        if(word.size() < 3) continue;
        remove(word);
        Word w(word);
        w.stem();
        if(this->words.contains(w)){
            pos? words.get(w)++ : words.get(w)--;
        }
        else if(!ignore.contains(w.str()) && w.str().size() > 3){
            pos? w++ : w--;
            this->words.add(w);
        }
    }
}

RBTree<Word> TweetData::getWords(){
    return this->words;
}

void TweetData::outputData(){
    std::ofstream of;
    std::vector<Word> data = this->words.getData();
    of.open("tweetData.csv");
    for(Word& word : data){
        of << word;
        of << ",";
        of << word.getCnt();
        of << ",";
        of << word.getNegativeCnt();
        of << ",";
        of << word.getPositiveCnt();
        of << "\n";
    }
    of.close();
}

