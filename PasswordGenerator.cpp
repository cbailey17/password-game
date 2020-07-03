// Password Generator
// password generator class provides the methods for a sequential search as well as generates a random password

#include "password_project.h"

PassWordGenerator::PassWordGenerator(vector<string> tokens) {
    _tokens = tokens;
    sort(_tokens.begin(), _tokens.end());
    nextIt = 1;
    iterationLength;
    srand(time(NULL));
}

PassWordGenerator::PassWordGenerator(const PassWordGenerator& copy) { // copy constructor
    _tokens = copy._tokens;
    iterationLength = copy.iterationLength;
    nextResult = copy.nextResult;
    nextIt = copy.nextIt;
    combinations = copy.combinations;
}

string PassWordGenerator::getRandomPassword(unsigned int numWords) {
    string result;
    set<unsigned int> indexes;
    vector<string> choices;
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

void PassWordGenerator::setIterationLength(int numWords) {
    iterationLength = numWords;
    combinations.clear(); // clear vector for new use with new iterationLength
    printAllKLength(_tokens.size(), iterationLength); // now use vector

}

string PassWordGenerator::next() {
    if (!hasNext()) {
        return "No more permutations!";
    }
    nextResult = combinations[nextIt];
    nextIt++;
    return nextResult;

}

void PassWordGenerator::permute(string prefix, long double size, long double length) {
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

void PassWordGenerator::printAllKLength(long double n, long double k) {
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
    cout << "Please enter a value between 1 and the number of words in your file: ";
    cin >> num;
    return num;
}
