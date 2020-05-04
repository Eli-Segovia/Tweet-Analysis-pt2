//
// Created by elise on 5/2/2020.
//
#include "functions.h"

void remove(std::string& word){
    while(word.size() > 0){
        for(char& i : word){
            if(std::isalpha(i)){
                i = std::towlower(i);
            }
        }
        if(word.at(0) == ':'){
            word.erase(0,1);
        }
        if(word.at(0) == '+'){
            word.erase(0,1);
        }

        while( (word.find("&quot;") >= 0 && word.find("&quot;") <= word.size()) ){
            word.erase(word.find("&quot;"), 6);
            continue;
        }
        while( (word.find("&amp;") >= 0 && word.find("&amp;") <= word.size()) ){
            word.erase(word.find("&amp;"), 5);
            continue;
        }
        while( (word.find("(") >= 0 && word.find("(") <= word.size()) ){
            word.erase(word.find("("), 1);
            continue;
        }
        while( (word.find(")") >= 0 && word.find(")") <= word.size()) ){
            word.erase(word.find(")"), 1);
            continue;
        }
        while( (word.find("?") >= 0 && word.find("?") <= word.size()) ){
            word.erase(word.find("?"), 1);
            continue;
        }
        while( (word.find("!") >= 0 && word.find("!") <= word.size()) ){
            word.erase(word.find("!"), 1);
            continue;
        }
        while( (word.find("-") >= 0 && word.find("-") <= word.size()) ){
            word.erase(word.find("-"), 1);
            continue;
        }
        while( (word.find(",") >= 0 && word.find(",") <= word.size()) ){
            word.erase(word.find(","), 1);
            continue;
        }

        while( (word.find("\"") >= 0 && word.find("\"") <= word.size()) ){
            word.erase(word.find("\""), 1);
            continue;
        }
        while( (word.find(";") >= 0 && word.find(";") <= word.size()) ){
            word.erase(word.find(";"), 1);
            continue;
        }
        while( (word.find(":") >= 0 && word.find(":") <= word.size()) ){
            word.erase(word.find(":"), 1);
            continue;
        }
        while( (word.find("/") >= 0 && word.find("/") <= word.size()) ){
            word.erase(word.find("/"), 1);
            continue;
        }
        while( (word.find("#") >= 0 && word.find("#") <= word.size()) ){
            word.erase(word.find("#"), 1);
            continue;
        }
        while( (word.find("*") >= 0 && word.find("*") <= word.size()) ){
            word.erase(word.find("*"), 1);
            continue;
        }
        while( (word.find(".") >= 0 && word.find(".") <= word.size()) ){
            word.erase(word.find("."), 1);
            continue;
        }
        while( (word.find("~") >= 0 && word.find("~") <= word.size()) ){
            word.erase(word.find("~"), 1);
            continue;
        }
        while( (word.find("&lt;") >= 0 && word.find("&lt;") <= word.size()) ){
            word.erase(word.find("&lt;"), 4);
            continue;
        }while( (word.find("&gt;") >= 0 && word.find("&gt;") <= word.size()) ){
            word.erase(word.find("&gt;"), 4);
            continue;
        }
        while( (word.find("&gt") >= 0 && word.find("&gt") <= word.size()) ){
            word.erase(word.find("&gt"), 3);
            continue;
        }
        while( (word.find("&lt") >= 0 && word.find("&lt") <= word.size()) ){
            word.erase(word.find("&lt"), 3);
            continue;
        }

        break;
    }

}

bool choose(){
    std::string choices;
    std::cout << "Do you want to reclassify tweets or use previous classification?" << std::endl;
    std::cout << "1) Reclassify" << std::endl << "0) Use Previous Classification" << std::endl;
    std::getline(std::cin, choices);
    int choice = std::atoi(choices.c_str());
    if(!(choice == 1 || choice == 0)){throw std::invalid_argument(choice + " is not a valid choice");}
    else return choice;
}

bool chooseTrain(){
    std::string choices;
    std::cout << "Do you want to retrain or use previous training?" << std::endl;
    std::cout << "1) Retrain" << std::endl << "0) Use Previous training" << std::endl;
    std::getline(std::cin, choices);
    int choice = std::atoi(choices.c_str());
    if(!(choice == 1 || choice == 0)){throw std::invalid_argument(choice + " is not a valid choice");}
    else return choice;
}

