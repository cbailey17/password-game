#pragma once
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include <thread>
#include <list>

using namespace std;

static bool threadFinished;

struct tokenDetector
{
    map<string, int>  fileWords;
    string line, temp_str;
    vector<string> strList;

    vector<string> getUnique(ifstream& file);         // add tokens from the file to a map in order to make sure theyre unique and then add to the vector
    vector<string> editString(vector<string> strList);// remove capitalization and call remove punctuation
    void removePunct(string& str);                    // remove punctuation

};

struct observer {
    ~observer() {};
    void update(string update);
};

class PassWordGenerator {
public:
    PassWordGenerator(vector<string> tokens);
    PassWordGenerator(const PassWordGenerator& copy);
    string getRandomPassword(unsigned int numWords);
    void setIterationLength(int numWords);
    string next();
    bool hasNext();  // false condition when curser is at length of tokens
    unsigned int prompt();
    void permute(string prefix, long double size, long double length);
    void printAllKLength(long double n, long double k);
    vector<string> combinations;

private:
    vector<string> _tokens;
    unsigned int iterationLength;
    string nextResult;
    unsigned int nextIt;
};

class PassWordGuesser {
public:
    PassWordGuesser(PassWordGenerator& gen, int numWords);
    void bogoSearch(string password, unsigned int numWords);
    void sequentialSearch(string password);
    void runThreads(string pw, unsigned int numWords);
    void attach(observer* obs);
    void dettach(observer* obs);
    void notify(string update);

private:
    string correctPassword;
    PassWordGenerator* gen;
    unsigned int pwLength;
    list<observer*> observers;
};
