//
// Created by elise on 5/1/2020.
//
#include "TweetData.h"

TweetData::TweetData(){         // fills up the stop words tree
    readStopWords();
}

void TweetData::readStopWords(){               // reads the stop words.txt and puts it into the tree.
    std::ifstream inFile;
    inFile.open("../util/stopwords.txt");
    std::string line;
    ignore.add("");
    while(std::getline(inFile,line)){
        ignore.add(line);
    }
}


void TweetData::addWord(Word newWord){   // adds a new word to the words treee
    this->words.add(newWord);
}

bool TweetData::containsWord(Word word){  // chekcs if a word is within the tree
    return this->words.contains(word);
}

Word& TweetData::getWord(Word word){    // retruns a word by reference from the tree.
    return this->words.get(word);
}

void TweetData::train(std::string trainFile, std::string testFile){  // trains the classifier by marking tweets
    bool isPositive;                                                // as postivie or negative based on the words
    std::ifstream input1;                                         // that are in that tweet.
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
        std::getline(iss1, ln_input1, ',');
        std::getline(iss1, ln_input1, ',');
        std::getline(iss1, ln_input1, ',');
        std::getline(iss1, ln_input1, ',');
        std::getline(iss2, ln_input2, ',');
        std::getline(iss2, ln_input2, ',');
        switch(std::atoi(ln_input2.c_str())){     // after delimiting, here we're observing the psitivity of a tweet
            case 4:                               // if it's a four, then it is postivie if it is a zero then it is
                this->positiveTweets++;          // a negative tweet
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

void TweetData::copy(){              // copy simply uses the previous data used for training.
    std::ifstream dataToCopy;
    dataToCopy.open("tweetData.csv");
    if(!dataToCopy.is_open()){throw std::invalid_argument("Cannot open file");}
    std::string line;
    std::getline(dataToCopy,line);
    std::string element;
    std::istringstream input(line);
    std::getline(input, element, ',');
    this->positiveTweets = std::atoi(element.c_str());
    std::getline(input, element);
    this->negativeTweets = std::atoi(element.c_str());
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
        w.setNegativeCnt(std::atoi(neg.c_str()));
        w.setPositiveCnt(std::atoi(pos.c_str()));
        this->words.add(w);
    }
    std::cout << this->getPositiveTweets() << std::endl;
    std::cout << this->getNegativeTweets() << std::endl;
    std::cout << this->getTotalTweets() << std::endl;
}

void TweetData::checkLine(std::string & line, bool pos){   // chekcline goes through the line we are currently examining
    std::istringstream iss(line);                        // it then extracts the useful information we need in order to
    std::string word;                                      // properly train the classifier
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

RBTree<Word> TweetData::getWords(){  // returns the tree thathas all of the words collected in training
    return this->words;
}

void TweetData::outputData(){                        //outputs all of the data that we have collected and puts it in txt
    std::ofstream of;                               // file that we can use further in the future instead of reading all
    std::vector<Word> data = this->words.getData(); // over again
    of.open("tweetData.csv");
    of << this->positiveTweets;
    of << ",";
    of << this->negativeTweets;
    of << "\n";
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

