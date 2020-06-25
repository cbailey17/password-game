#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <vector>

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


/*
class PassWordGenerator {
public:
    PassWordGenerator(vector<string> tokens) {}

    string getRandomPassword(int numWords) {}

    void setIterationLength(int numWords) {}

    string next() {}

    bool hasNext() {}  // false condition when curser is at length of tokens

private:
    vector<string> _tokens;

} passwordGenerator;

PassWordGenerator::PassWordGenerator(vector<string> tokens) : _tokens(tokens) {
    cout << "Password generator class constructed" << endl;
    int numWords = tokens.size();
}

string PassWordGenerator::getRandomPassword(int numWords) {

}
*/



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
