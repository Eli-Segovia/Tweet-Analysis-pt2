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

### Datasets
In order to test these algorithms, I reused data from DS Sentiment Analysis
project, as that data is structured well and easily available. Although I cut 
down some tweets from this data, it is still on the heavy side: I apologize if that's
an issue.


### Hardcoded Data
Although not following the best practices, I decided to have my data sets hardcoded. You can change them out with files that carry the same naming convention, however I decided that not providing extra command line arguments would simplifiy things for this project. For future develpments in this project, I will probably look into providing some way that makes datasets a little more dynamic, but for now, I this will do.


### Command Line arguments
-k : KNN Classifier

-b : Naive Bayes Classifier

-t : CS2341 Classifier

### Execution
Running this program requires command line arguments listed above. You simply run with one of these flags, and you should be good to go.

This program uses a simple UI, giving the user some simple decisions to make. The UI will prompt with a question: whether or not you want to reclassify the tweets or use a previous classification. This is meant to speed up the process if you would like to simply get the accuracy of the recent classification. It will then ask if you would like to use the same testing data from previous runs. Again, this is to speed things up and not waste time training the classifier if it has already been trained.

 On the very first run, you should definitely answer yes to both questions as there will not have been any data and any classification.


### Output
Within the build folder, there will be several files this program outputs:
* accuracy.txt: shows the accuracy of the latest run
* classify.txt: shows the classification of tweets in descending order
* tweetData.csv: shows some statistics of the words and how many postivite/negative tweets they show up in
* plot.txt : used by the KNNClassifier to map out the plots of the train data


