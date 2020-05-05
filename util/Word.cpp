//
// Created by elise on 5/1/2020.
//

#include <iostream>
#include "Word.h"                      // Word holds all of the data for each one of the words that we find in a tweet
                                       // a lot of its functionality works off of that data the program collects
Word::Word(){
    this->data        = "";
    this->cntPositive = 0;
    this->cntNegative = 0;
    this->totalCnt    = 0;
}

Word::Word(const char * rval) {
    this->data        = rval;
    this->cntPositive = 0;
    this->cntNegative = 0;
    this->totalCnt    = 0;
}

Word::Word(const std::string & rval) {
    this->data        = rval;
    this->cntPositive = 0;
    this->cntNegative = 0;
    this->totalCnt    = 0;
}

Word::Word(const Word& w){
    this->data = w.data;
    this->cntNegative = w.cntNegative;
    this->cntPositive = w.cntPositive;
    this->totalCnt    = w.totalCnt;
}

Word Word::operator++(int){ // word++
    Word temp = *this;
    this->cntPositive++;
    this->totalCnt++;
    return temp;
}

Word& Word::operator++(){
    this->cntPositive++;
    this->totalCnt++;
    return *this;
}

Word Word::operator--(int) {
    Word temp = *this;
    this->cntNegative++;
    this->totalCnt++;
    return temp;
}

Word& Word::operator--() {
    this->cntNegative++;
    this->totalCnt++;
    return *this;
}

void Word::setPositiveCnt(const int& cnt){
    this->cntPositive = cnt;
}

void Word::setNegativeCnt(const int& cnt){
    this->cntNegative = cnt;
}

void Word::setTotalCnt(const int& cnt){
    this->totalCnt = cnt;
}

Word& Word::operator=(const Word & w) {
    this->data = w.data;
    this->cntPositive = w.cntPositive;
    this->cntNegative = w.cntNegative;
    this->totalCnt    = w.totalCnt;
    return *this;
}

bool Word::operator<  (const Word& rhs){
    return this->data < rhs.data;
}

bool Word::operator>  (const Word& rhs){
    return this->data > rhs.data;
}

bool Word::operator== (const Word& rhs){
    return this->data == rhs.data;
}

bool Word::operator!= (const Word& rhs){
    return this->data != rhs.data;
}

bool Word::operator>= (const Word& rhs){
    return this->data >= rhs.data;
}

bool Word::operator<= (const Word& rhs){
    return this->data <= rhs.data;
}

std::string& Word::str(){
    return this->data;
}

void Word::stem() {
    Porter2Stemmer::stem(this->data);
}


int Word::getPositiveCnt() const{
    return this->cntPositive;
}

int Word::getNegativeCnt() const {
    return this->cntNegative;
}

int Word::getCnt() const{
    return this->totalCnt;
}

int Word::getNet() const {
    return cntPositive - cntNegative;
}

std::ostream& operator<<(std::ostream& os, const Word& w){
    os << w.data;
    return os;
}


