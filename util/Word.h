//
// Created by elise on 5/1/2020.
//

#ifndef TWEET_ANALYSIS_PT2_WORD_H
#define TWEET_ANALYSIS_PT2_WORD_H
#include <ostream>
#include "../porter2_stemmer/porter2_stemmer.h"


class Word {
private:
    std::string data;
    int cntPositive;
    int cntNegative;
    int totalCnt;
public:
    Word();
    Word(const char* );
    Word(const std::string &);
    Word(const Word&);
    Word& operator=(const Word&);
    Word  operator++(int);
    Word& operator++();
    Word  operator--(int);
    Word& operator--();
    bool operator<  (const Word&);
    bool operator>  (const Word&);
    bool operator== (const Word&);
    bool operator!= (const Word&);
    bool operator>= (const Word&);
    bool operator<= (const Word&);
    std::string& str();
    void stem();
    int getPositiveCnt() const;
    int getNegativeCnt() const;
    void setPositiveCnt(const int&);
    void setNegativeCnt(const int&);
    void setTotalCnt(const int&);
    int getCnt() const;
    int  getNet() const;
    friend std::ostream& operator<<(std::ostream&, const Word&);
};


#endif //TWEET_ANALYSIS_PT2_WORD_H
