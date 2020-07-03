#include "password_project.h"

// Unique Token Detector
// token detector performs the necessary trimming of the ASCII text file and creates a vector of unique tokens

vector<string> tokenDetector::getUnique(ifstream& file) {  // add tokens from the file to a map in order to make sure theyre unique and then add to the vector
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
    }
    return finalList;
}

vector<string> tokenDetector::editString(vector<string> strList) {  // remove capitalization and call remove punctuation
    for (unsigned int i = 0; i < strList.size(); ++i) {
        string& strPtr = strList[i];
        removePunct(strPtr);

        if (isupper(strList[i][0])) {
            strList[i][0] = tolower(strList[i][0]);
        }
    }
    return strList;
}

void tokenDetector::removePunct(string& str) {          // remove punctuation
    if (ispunct(str[str.size() - 1])) {
        str.erase(str.size() - 1, 1);
        if (str.empty()) { return; }
        removePunct(str);                // recursive call for more than one punctuation at ending
    }
    return;
}
