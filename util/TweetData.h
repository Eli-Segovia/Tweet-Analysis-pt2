//
// Created by elise on 5/1/2020.
//

#ifndef TWEET_ANALYSIS_PT2_TWEETDATA_H
#define TWEET_ANALYSIS_PT2_TWEETDATA_H
#include "RBTree.h"
#include "Word.h"
#include <fstream>
#include <sstream>
#include <vector>

class TweetData {
private:
    RBTree<Word> words;
    RBTree<std::string> ignore;
    void readStopWords();
public:
    TweetData();
    void addWord(Word newWord);
    void checkLine(std::string & line, bool pos);
    bool containsWord(Word word);
    Word& getWord(Word word);
    RBTree<Word> getWords();
    void train(std::string trainFil, std::string testFile);
    void copy();
    void outputData();
};


#endif //TWEET_ANALYSIS_PT2_TWEETDATA_H
