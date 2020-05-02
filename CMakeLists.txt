cmake_minimum_required(VERSION 3.15)
project(Tweet_Analysis_pt2)

set(CMAKE_CXX_STANDARD 14)

add_executable(Tweet_Analysis_pt2
        README.md main.cpp util/Word.cpp util/RBTree.h util/bstNode.h porter2_stemmer/porter2_stemmer.cpp util/TweetData.cpp
        util/Classifier.h)
