//
// Created by Cindy Hainz on 13.05.22.
//

#include "nGramm.h"
#include <string>
#include <iostream>
#include <cmath>
#include <sys/time.h>

using namespace std;

float NGramm::calculateProbability(string prefix, string suffix){
    float probability;
    if (prefixMap.end() != prefixMap.find(prefix)) {
        auto suffixMap=prefixMap[prefix];
        if (suffixMap.end() != suffixMap.find(suffix)) {
            probability=suffixMap[suffix]/prefixCount[prefix];
            cout <<suffixMap[suffix]<<"/"<<prefixCount[prefix]<<endl;
        }
        else{
            probability=0.0;
        }
    }
    else{
        probability=0.0;
    }
    return probability;
}

float NGramm::calculateEntropy(string textFile){
    string text;
    int index;
    float entropy;
    int textSizeWithoutEndsymbol = textFile.size()-endSymbol.size();
    string suffix, prefix;
    float probability;

    //add startsymbol and endsymbol
    for(int i = 0;i<n-1;i++){
        text+=startSymbol;
    }
    text +=textFile+endSymbol;

    index=(n-1)*startSymbol.size(); //index of first suffix

    for(int x = 1;x<n;x++){
        prefix = "";
        suffix = text[index]; //first letter in original string
        // get current prefix
        for (int j = 0; j <n-x; j++) {
            prefix += startSymbol;
        }
        for(int k = x-1; k>0;k--){
            prefix+=text[index-k];
        }
        probability = calculateProbability(prefix,suffix);
        if(probability != 0){
            entropy += probability * log2f(probability);
        }

        index +=1;
    }

    prefix = prefix.substr(2 );
    for(int i = index; i < textSizeWithoutEndsymbol; i++){
        suffix =text[i-1]; //old suffix
        prefix += suffix;
        prefix = prefix.substr(1);
        suffix = text[i];
        probability = calculateProbability(prefix, suffix);
        if(probability != 0){
            //entropy += log2f(probability);
            entropy += probability * log2f(probability);
        }
    }
   // entropy /= textFile.size();
    entropy *= (-1);
    return entropy;

}

void NGramm::train_nGramm(string textFile){

    string text = "";
    for(int i = 0;i<n-1;i++){
        text+=startSymbol;
    }
    text +=textFile+endSymbol;

    string prefix = "";
    string suffix;
    int index=(n-1)*startSymbol.size(); //index of first suffix
    for(int x =1;x<n;x++){
        prefix = "";
        suffix = text[index]; //first letter in original string
        // get current prefix
        for (int j = 0; j <n-x; j++) {
            prefix += startSymbol;
        }

        for(int k = x-1; k>0;k--){
            prefix+=text[index-k];
        }
        addPrefixSuffix(prefix,suffix);
        index +=1;
    }
    // go through text, letter by letter
    for (int i = index; i < text.size(); i++) {
        prefix = "";
        suffix = text[i];
        // get current prefix
        for (int j = n - 1; j > 0; j--) {
            prefix += text[i - j];
        }
        if(i==text.size()-endSymbol.size()){
            addPrefixSuffix(prefix,endSymbol);
            break;
        }
        //Look up in map if prefix exist
        addPrefixSuffix(prefix,suffix);
    }
}

string NGramm::generateText(){
    string output;

    // make the generation truly random
    timeval t1;
    gettimeofday(&t1, NULL);
    srand(t1.tv_usec * t1.tv_sec);

    string prefix;
    for(int i = 0;i<n-1;i++){
        prefix+=startSymbol;
    }
    output+=prefix;

    string suffix;
    for(int i =0;i<n-1;i++){
        suffix = randomSuffix(prefix);
        output+=suffix;
        prefix+=suffix;
        prefix = prefix.substr(startSymbol.size());
    }

    while(suffix!=endSymbol){
        suffix = randomSuffix(prefix);
        output+=suffix;
        prefix+=suffix;
        prefix = prefix.substr(1);
    }
    return output;
}

void NGramm::addPrefixSuffix(string prefix, string suffix) {
    if (prefixMap.end() != prefixMap.find(prefix)) {
        // if so add current suffix to the value list for the prefix
        auto suffixMap = prefixMap.at(prefix);

        suffixMap[suffix] += 1;  //Add suffix to list
        prefixMap[prefix] = suffixMap;
        prefixCount[prefix]+=1;
    } else {
        // if prefix does not exist in the map add a new list with the current suffix
        map<string , float> suffMap;
        suffMap[suffix] = 1.0;
        prefixMap[prefix] = suffMap;
        //assert(prefixMap.find(prefix)->second == suffMap); // Create new Value for prefix and add suffix
        prefixCount[prefix]=1;
    }
}

map<string, map<string , float>> NGramm::PrefixMap() {
    return prefixMap;
}

string NGramm::randomSuffix(string prefix){
    auto currMap=prefixMap[prefix];
    auto randomNumber =  rand() % prefixCount[prefix]+1; // choose random prefix to begin the generation
    //double randomProbability = randomNumber/prefixCount[prefix];
    int mapProbability=0;
    string output;
    string suffix;
    for(auto & currSuffix : currMap){
        if(randomNumber>mapProbability){
            mapProbability+=currSuffix.second;
            suffix=currSuffix.first;
        }else{
            break;
        }
    }
    output=suffix;
    return output;
}

float NGramm::probabilityHistory(string history, string suffix) {
    string prefix = "";
    float probability=0.0;

    if(history.size()<n-1){
        for(int i =0;i<n-1-history.size();i++){
            prefix+=startSymbol;
        }
        prefix+=history;
    } else if(history.size()==n-1){
        prefix = history;
    }
    else{
        auto start = history.size()-n+1;
        prefix=history.substr(start);
    }
    probability = calculateProbability(prefix, suffix);
    return probability;

}
