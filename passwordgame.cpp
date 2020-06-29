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

//#include "PassWordGenerator.h"
using namespace std;


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
            string & strPtr = strList[i];
            removePunct(strPtr);

            if (isupper(strList[i][0])) {
                strList[i][0] = tolower(strList[i][0]);
            }
        }
        return strList;
    }

    void removePunct(string &str) {          // remove punctuation 
        if (ispunct(str[str.size() - 1])) {
            str.erase(str.size() - 1, 1);     
            if (str.empty()) { return; }
            removePunct(str);                // recursive call for more than one punctuation at ending
        }
        return;
    }
} detector;



class PassWordGenerator {
public:
<<<<<<< HEAD
    PassWordGenerator(vector<string> tokens);

    PassWordGenerator(const PassWordGenerator &copy);
=======
    PassWordGenerator(vector<string> tokens) {
        cout << "Password generator class constructed" << endl;
        int numWords = tokens.size();
    }
    PassWordGenerator() {}
>>>>>>> 3310eaf7ff436fa8f562cfc7bdcd546c20f52332

    string getRandomPassword(int numWords);

    void setIterationLength(int numWords);

    string next();

    bool hasNext();  // false condition when curser is at length of tokens

private:
<<<<<<< HEAD
    vector<string> _tokens;
    int iterationLength;
    // int wordPlace;
    // int curindex;
};

PassWordGenerator::PassWordGenerator(vector<string> tokens){
    _tokens = tokens;
    cout << "Password generator class constructed" << endl;
    // wordPlace = 0;
    // curindex = 0;
}

PassWordGenerator::PassWordGenerator(const PassWordGenerator &copy){
  std::vector<std::string> _tokens = copy._tokens;
  int iterationLength = copy.iterationLength;

}

string PassWordGenerator::getRandomPassword(int numWords) {
  std::string result;
  std::set<int> indexes;
  std::vector<std::string> choices;
  int max_index = _tokens.size();

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
  for(int i = 0; i < numWords; i++){
    result = result + choices[i] + " ";
    }
  }
  return result;
}
void PassWordGenerator::setIterationLength(int numWords) {
 iterationLength = numWords;
}

std::string PassWordGenerator::next() {
  std::string nextResult;
  static int i,j,k,l = 0;
  if(hasNext()){
    nextResult = _tokens[i] + " " + _tokens[j] + " " + _tokens[k] + " " + _tokens[l] + " ";
    l++;
    if(l == _tokens.size()){
      k++;
      l=0;
    }
    if(k == _tokens.size()){
      j++;
      l=0;
      k=0;
    }
    if(j == _tokens.size()){
      i++;
      l=0;
      k=0;
      j=0;
    }
  }
  return nextResult;
}

bool PassWordGenerator::hasNext() {
  // if  (wordPlace < iterationLength && curindex < _tokens.size()){
  //     return 1;
  // }
  return 0;
}
=======

} passwordGenerator;

>>>>>>> 3310eaf7ff436fa8f562cfc7bdcd546c20f52332

class PassWordGuesser {
public:
    PassWordGuesser(PassWordGenerator& Gen, int numWords);

    void guessPW();

    void bogoSearch(std::string password);

    void sequentialSearch(std::string password);


private:
  std::string correctPassword;
  PassWordGenerator pwgen;
};

PassWordGuesser::PassWordGuesser(PassWordGenerator& Gen, int numWords){
    correctPassword = Gen.getRandomPassword(numWords);
    PassWordGenerator pwgen(Gen);
}

void PassWordGuesser::guessPW(){

}

void PassWordGuesser::bogoSearch(std::string password){
  while(correctPassword != pwgen.getRandomPassword());

}

void PassWordGuesser::sequentialSearch(std::string password){


}

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
    vector<string> parsedWords  = detector.getUnique(file);
    PassWordGenerator* pwGenerator = new PassWordGenerator(parsedWords);
    cout << pwGenerator->getRandomPassword(4) << endl;
    cout << pwGenerator->getRandomPassword(4) << endl;
    cout << pwGenerator->getRandomPassword(4) << endl;
    cout << pwGenerator->getRandomPassword(4) << endl;
    cout << pwGenerator->getRandomPassword(4) << endl;

    cout << pwGenerator->next() << endl;

}
