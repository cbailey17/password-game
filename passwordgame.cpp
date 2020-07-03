/* Password Game Project written for CS320 at SDSU 
*  Author: Alex Cameron Bailey    
*  Red ID: 817329494 
*  
*  Author: Mathew Punsalen
*  Red ID: 820328373
*/

#include "password_project.h"


// Driver: PasswordGame
int main(int argc, char** argv) {

    srand(time(NULL)); //set random seed
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
    tokenDetector* detector = new tokenDetector();
    vector<string> parsedWords = detector->getUnique(file);
    cout << "Welcome to The Password Game!\n" << endl;
    cout << "Number of unique tokens in your text file: " << parsedWords.size() << " words." << endl;
  

    // create generator and guesser pointer objects and prompt the user for number of words
    PassWordGenerator* pwGenerator = new PassWordGenerator(parsedWords);

    unsigned int numWords = pwGenerator->prompt();
    pwGenerator->setIterationLength(numWords);
    PassWordGuesser* pg = new PassWordGuesser(*pwGenerator, numWords);


    // create a random password to pass to the threading method in password guesser class
    string pw = pwGenerator->getRandomPassword(numWords);
    cout << "\nYour random password that was generated is: " << pw << "\n" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;


    // add a subscriber object and attach to the publisher
    observer* subscriber = new observer();
    pg->attach(subscriber);


    // run the two threads then dettach the observer
    pg->runThreads(pw, numWords);
    pg->dettach(subscriber);

    cout << "The number of unique password combinations in your file: " << pwGenerator->combinations.size()
        << " unique combinations.\n" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
}