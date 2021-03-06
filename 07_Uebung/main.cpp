#include <iostream>
#include <fstream>
#include "nGramm.h"

using namespace std;

ifstream readFile(const string& path) { // put whole text in one string
    ifstream input_file(path);
    if(input_file.fail()){
        cout << "File does not exist" << endl;
    }
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    return input_file;
}

string readFileIntoString(const string& path) {
    ifstream input_file(path);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    return string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
}

int main() {
    string path;
    cout << "Enter path: ";
    cin >> path;
    //path = "SALAMI IST IM SALAT. LAMA IST ALT.";
    cout << "Enter N: ";
    int n=0;
    cin >> n;

    auto file = readFile(path);
    // train N-Gramm
    NGramm trainGramm(  n);
    string line;
    while(getline(file,line)){
        trainGramm.train_nGramm(line);
    }

    // print N-Gramm
    for(const auto &elem : trainGramm.PrefixMap()){
        cout << elem.first << ": ";
        for(const auto &suffix : elem.second){
            cout << suffix.first << "," <<suffix.second<<", ";
        }
        cout << endl;
    }

    int option=0;
    cout <<"Enter option: 0 = exit Program, 1 = generate Text, 2 = History and Suffix Probability, 3 = Entropy "<<endl;
    string history;
    string suffix;
    string text;
    while(cin>>option){
        switch (option) {
            case 0:
                return 0;
            case 1:
                cout<<trainGramm.generateText()<<endl;
                break;
            case 2:
                cout << "Enter History:"<<endl;
                cin>>history;
                cout << "Enter searched Suffix:"<<endl;
                cin>>suffix;
                cout << "Probability for " << suffix << ": "<<trainGramm.probabilityHistory(history,suffix)*100<<" %"<<endl;
                break;
            case 3:
                cout << "Enter path: " << endl;
                cin >> path;
                text = readFileIntoString(path);
                cout << "Entropy " << trainGramm.calculateEntropy(text) << endl;
                break;
            default:
                cout<<"This option is not available"<<endl;
                break;
        }
        cout <<"Enter option: 0 = exit Program, 1 = generate Text, 2 = History and Suffix Probability, 3 = Entropy"<<endl;

    }

    return 0;
}
