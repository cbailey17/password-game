#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <vector>

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
    PassWordGenerator(vector<string> tokens) {
        cout << "Password generator class constructed" << endl;
        int numWords = tokens.size();
    }
    PassWordGenerator() {}

    string getRandomPassword(int numWords) {}

    void setIterationLength(int numWords) {}

    string next() {}

    bool hasNext() {}  // false condition when curser is at length of tokens

private:

} passwordGenerator;




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

}
