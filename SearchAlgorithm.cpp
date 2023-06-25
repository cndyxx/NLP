#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <chrono>
#include <mutex>

using namespace std;


std::vector<string> createWordList()
{
    std::vector<std::string> letters = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
    std::string word;
    std::vector<std::string> wordList;

    for (int i = 0; i < letters.size(); i++)
    {
        for (int j = 0; j < letters.size(); j++)
        {
            for (int k = 0; k < letters.size(); k++)
            {
                for (int l = 0; l < letters.size(); l++)
                {
                    word = letters[i] + letters[j] + letters[k] + letters[l];
                    wordList.push_back(word);
                }
            }
        }
    }

    return wordList;
}

//Lineare Suche in der Word Liste mit allen Kombinationen von AAAA-ZZZZ
void searchString(std::vector<std::string> wordList, std::string searchString, int start, int end)
{
    std::vector<std::string> wordsOfList;
    int sizeOfSearchString = searchString.size();
    for (int i = start; i < end; i++)
    {
        if (wordList[i].substr(0, sizeOfSearchString) == searchString)
        {
            wordsOfList.push_back(wordList[i]);
            std::cout << wordList[i] << std::endl;
        }
    }
}

int main()
{
    //Anzahl der Cores ermitteln 
    int coreCount = std::thread::hardware_concurrency();
    std::vector<std::thread> threadHandler;
    //Liste mit allen Kombinationen von AAAA-ZZZZ erstellen 
    std::vector<std::string> testList = createWordList();
    //Liste auf die Anzahl der Cores aufteilen
    int splitWordList = testList.size() / coreCount;
    std::string inputString; 
    std::cout << "Bitte geben Sie das Suchmusert ein: " << std::endl; 
    std::cin >> inputString; 
    std::cout << "Das Suchmuster wurde in den folgenden Ergebnissen gefunden:" << std::endl; 
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < coreCount; i++)
    {
        int start = i * splitWordList;
        int end = (i + 1) * splitWordList;
        threadHandler.emplace_back(searchString, std::ref(testList), inputString, start, end);
    }

    for (auto &t : threadHandler)
    {
        t.join();
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    long long nanoseconds = duration;
    double seconds = static_cast<double>(nanoseconds) / 1e9;

    std::cout << "Dauer: " << seconds << " Sekunden" << std::endl;
    
    return 0;
}
