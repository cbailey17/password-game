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
    string line;
    string temp_str;
    vector<string> strList;

    vector<string> getUnique(ifstream& file) {
        while (getline(file, line)) {
            for (int i = 0; i <= line.size(); i++) {

                if (ispunct(line[i])) {
                    line.erase(i, 1);
                    i -= 1;
                }

                if (isupper(line[i])) {
                    line[i] = tolower(line[i]);
                }
            }

            stringstream ss(line);
            while (getline(ss, temp_str, ' ')) {
                if (fileWords.count(temp_str) > 0) {
                    fileWords[temp_str] += 1;
                }
                else {
                    fileWords.insert(pair<string, int>(temp_str, 1));
                    strList.push_back(temp_str);
                }
            }
        }
        for (unsigned int i = 0; i < strList.size(); ++i) {
            cout << strList[i] << endl;
        }
        return strList;
    }

} detector;



class PassWordGenerator {
public:
    PassWordGenerator(vector<string> tokens);

    PassWordGenerator(const PassWordGenerator &copy);

    string getRandomPassword(int numWords);

    void setIterationLength(int numWords);

    string next();

    bool hasNext();  // false condition when curser is at length of tokens

private:
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
