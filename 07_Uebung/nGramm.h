//
// Created by Cindy Hainz on 13.05.22.
//
#include <string>
#include <map>
#include <list>
#ifndef SRC_NGRAMM_H
#define SRC_NGRAMM_H

using namespace std;

class NGramm{
public:
    NGramm(unsigned int n_value){
        n = n_value;
    }

    void countSymbol(string symbol);
    void train_nGramm(string textFile);
    string generateText();
    float calculateEntropy(string text);
    map<string, map<string,float>> PrefixMap();
    float probabilityHistory(string history, string suffix);

    void setLaplaceDiscounting(bool value);
private:
    void addPrefixSuffix(string prefix, string suffix);
    string randomSuffix(string prefix);
    float calculateProbability(string prefix, string suffix);
    float calculateLaplaceDiscount(string prefix, string suffix);
    int n;
    map<string, map<string,float>> prefixMap;
    map<string, int> prefixCount;
    list<string> symbolCount;
    string startSymbol ="<s>";
    string endSymbol = "</s>";
    bool laplaceDiscounting;



};
#endif //SRC_NGRAMM_H
