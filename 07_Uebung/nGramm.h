//
// Created by Cindy Hainz on 13.05.22.
//
#include <string>
#include <map>
#ifndef SRC_NGRAMM_H
#define SRC_NGRAMM_H

using namespace std;

class NGramm{
public:
    NGramm(unsigned int n_value){
        n = n_value;
    }
    void train_nGramm(string textFile);
    string generateText();
    float calculateEntropy(string text);
    map<string, map<string,float>> PrefixMap();
    float probabilityHistory(string history, string suffix);
private:
    void addPrefixSuffix(string prefix, string suffix);
    string randomSuffix(string prefix);
    float calculateProbability(string prefix, string suffix);
    int n;
    map<string, map<string,float>> prefixMap;
    map<string, int> prefixCount;
    string startSymbol ="<s>";
    string endSymbol = "</s>";

};
#endif //SRC_NGRAMM_H
