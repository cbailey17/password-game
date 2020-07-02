#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <vector>
#include <time.h>
#include <thread>

//#include "PassWordGenerator.h"
using namespace std;

static bool threadFinished = false;


//----------------------------------------------------------------------------------------------
// Unique Token Detector
struct tokenDetector {
    map<string, int>  fileWords;
    string line, temp_str;
    vector<string> strList;

    vector<string> getUnique(ifstream& file) {  // add tokens from the file to a map in order to make sure theyre unique and then add to the vector
        while (getline(file, line)) {
            stringstream ss(line);
            while (!ss.eof() && getline(ss, temp_str, ' ')) {
                if (fileWords.count(temp_str) > 0) {
                    fileWords[temp_str] += 1;
                }
                else {
                    fileWords.insert(pair<string, int>(temp_str, 1));
                    strList.push_back(temp_str);
                }
            }
        }

        vector<string> finalList = editString(strList);  // After adding tokens to the map and vector, remove caps and trailing punctuation and remove empties
        for (unsigned int i = 0; i < finalList.size(); i++) {
            if (finalList[i].empty()) {
                finalList.erase(finalList.begin() + i);
            }
            cout << finalList[i] << endl;
        }
        return finalList;
    }

    vector<string> editString(vector<string> strList) {  // remove capitalization and call remove punctuation
        for (unsigned int i = 0; i < strList.size(); ++i) {
            string& strPtr = strList[i];
            removePunct(strPtr);

            if (isupper(strList[i][0])) {
                strList[i][0] = tolower(strList[i][0]);
            }
        }
        return strList;
    }

    void removePunct(string& str) {          // remove punctuation
        if (ispunct(str[str.size() - 1])) {
            str.erase(str.size() - 1, 1);
            if (str.empty()) { return; }
            removePunct(str);                // recursive call for more than one punctuation at ending
        }
        return;
    }
} detector;


//----------------------------------------------------------------------------------------------
// Password Generator
class PassWordGenerator {
public:
    PassWordGenerator(vector<string> tokens);

    PassWordGenerator(const PassWordGenerator& copy);

    string getRandomPassword(unsigned int numWords);

    void setIterationLength(unsigned int numWords);

    string next();

    bool hasNext();  // false condition when curser is at length of tokens

    unsigned int prompt();

    void permute(string prefix, unsigned int size, unsigned int length);

    void printAllKLength(unsigned int n, unsigned int k);

private:
    vector<string> _tokens;
    unsigned int iterationLength;
    string nextResult;
    unsigned int nextIt;
    vector<string> combinations;

};

PassWordGenerator::PassWordGenerator(vector<string> tokens) {
    _tokens = tokens;
    cout << "Password generator class constructed" << endl;
    //std::sort(_tokens.begin(), _tokens.end());
    nextIt = 1;
    iterationLength;

}

PassWordGenerator::PassWordGenerator(const PassWordGenerator& copy) { // copy constructor
    _tokens = copy._tokens;
    iterationLength = copy.iterationLength;
    nextResult = copy.nextResult;
    nextIt = copy.nextIt;
    combinations = copy.combinations;
}

string PassWordGenerator::getRandomPassword(unsigned int numWords) {
    std::string result;
    std::set<int> indexes;
    std::vector<std::string> choices;
    unsigned int max_index = _tokens.size();

    while (indexes.size() < min(numWords, max_index))
    {
        int random_index = rand() % max_index;
        if (indexes.find(random_index) == indexes.end())
        {
            choices.push_back(_tokens[random_index]);
            indexes.insert(random_index);
        }
    }
    if (!choices.empty())
    {
        // Convert all but the last element to avoid a trailing ","
        for (unsigned int i = 0; i < numWords; i++) {
            result = result + choices[i] + " ";
        }
    }
    return result;
}

void PassWordGenerator::setIterationLength(unsigned int numWords) {
    iterationLength = numWords;
    combinations.clear(); // clear vector for new use with new iterationLength
    printAllKLength(_tokens.size(), iterationLength); // now use vector

}

string PassWordGenerator::next() {
    if (!hasNext()) {
        return "No more permutations!";
    }
    // printAllKLength(_tokens, maxi, iterationLength);

    nextResult = combinations[nextIt];
    nextIt++;
    cout << nextResult<< endl;
    return nextResult;

}

void PassWordGenerator::permute(string prefix, unsigned int size, unsigned int length) {
    // Base case: length is 0 so push into new vector
    // print prefix
    if (length == 0) {
        combinations.push_back(prefix);
        return;
    }

    // One by one add all characters
    // from tokenslist and recursively
    for (unsigned int i = 0; i < size; i++) {

        //TODO can find and replace duplicates
        string newPrefix;
        // next string added
        newPrefix = prefix + _tokens[i] + " ";
        // added new string
        permute(newPrefix, size, length - 1);
    }
}

void PassWordGenerator::printAllKLength(unsigned int n, unsigned int k) {
    permute("", n, k);
}

bool PassWordGenerator::hasNext() {
    if (nextIt < combinations.size()) {
        return 1;
    }
    return 0;
}

unsigned int PassWordGenerator::prompt() {
    unsigned int num;
    cout << "Please enter a value between 1 and 6 for your number of passwords! ";
    cin >> num;
    return num;
}





//----------------------------------------------------------------------------------------------
// Password Guesser
class PassWordGuesser {
public:
    PassWordGuesser(PassWordGenerator& gen, int numWords);

    void guessPW();

    bool bogoSearch(std::string password);

    bool sequentialSearch(std::string password);


private:
    std::string correctPassword;
    PassWordGenerator* gen;
    int pwLength;

};

PassWordGuesser::PassWordGuesser(PassWordGenerator& gen, int numWords) : gen(&gen) {
    correctPassword = gen.getRandomPassword(numWords);
    pwLength = numWords;
}

void PassWordGuesser::guessPW() {

}

bool PassWordGuesser::bogoSearch(std::string correctPassword) {
    string guess;
    cout << "Attempting to randomly guess the password" << endl;
    while (correctPassword != guess){
      guess = gen->getRandomPassword(pwLength);
      cout << guess << endl;
    }

    cout << "bogoSearch found the password!" << endl;
    cout << "Correct Password: " << correctPassword << endl;
    return 1;
}

bool PassWordGuesser::sequentialSearch(std::string correctPassword) {
    cout << "Attempting to sequentially guess the password" << endl;
    while (correctPassword != gen->next());
    cout << "sequentialSearch found the password!" << endl;
    cout << "Correct Password: " << correctPassword << endl;
    return 1;
}



//----------------------------------------------------------------------------------------------
// Driver: PasswordGame
int main(int argc, char** argv) {

    // make sure file was given at runtime
    if (argc != 2) {
        std::cout << "ASCII coded text file needed!\n" << std::endl;
        return 0;
    }

    // make sure file exists and can be opened
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cout << "Could not open the file or it does not exist!\n" << std::endl;
        return 0;
    }


    // run the parser to tokenize the file
    vector<string> parsedWords = detector.getUnique(file);

    PassWordGenerator* pwGenerator = new PassWordGenerator(parsedWords);

    unsigned int numWords = pwGenerator->prompt();

    PassWordGuesser* pg = new PassWordGuesser(*pwGenerator, numWords);

    pwGenerator->setIterationLength(numWords);

    string pw = pwGenerator->getRandomPassword(numWords);

    cout << "\nYour random password is: " << pw << endl;

    cout << pwGenerator->getRandomPassword(numWords) << endl;
    // cout << pwGenerator->next()<< endl;
    // cout << pwGenerator->next()<< endl;
    // cout << pwGenerator->next()<< endl;
    // cout << pwGenerator->next()<< endl;

    while(!pg->bogoSearch(pw));
    //std::thread bogo(pg->bogoSearch, pw);

    //bogo.join();

    cout << "Waiting" << endl;

   // std::thread sequentialSearch(&PassWordGuesser::sequentialSearch, pwGenerator);*/

}
