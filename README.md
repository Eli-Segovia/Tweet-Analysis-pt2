# Classifiers

## Info
I made some last second adjustments, as I could not find good implementations of
recommendation algorithms that wouldn't take more than two weeks to truly understand.
So I took one step back and worked on classification algorithms, which are 
not at all that different from recommendation algorithms. I implement three to 
make up for the fact that I could not really find a traditional "trivial" 
implementation of classifiers. Here are the three algorithms I try to implement:

* Data Structures Word Analaysis Algorithm
* Naive Bayes Algorithm
* K Nearest Neighbor (KNN) Algorithm

## Things to know
In order to test these algorithms, I reused data from DS Sentiment Analysis
project, as that data is structured well and easily available. Although I cut 
down some tweets from this data, it is on the heavy side: I apologize if that's
an issue.

### Command Line arguments
-k : KNN Classifier

-b : Naive Bayes Classifier

-t : CS2341 Classifier


### Output
Within the build folder, there will be several files this program outputs:
* accuracy.txt: shows the accuracy of the latest run
* classify.txt: shows the classification of tweets in descending order
* tweetData.csv: shows some statistics of the words and how many postivit/negative tweets they show up in
* plot.txt : used by the KNNClassifier to map out the plots of the train data


