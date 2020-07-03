/* Password Game P/* Password Game Project written for CS320 at SDSU
*  Author: Alex Cameron Bailey
*  Red ID: 817329494
*
*  Author: Mathew Punsalen
*  Red ID: 820328373
*/

#include "password_project.h"
//-----------------------------------------------------------------------------------------------------------------------------------
// Driver: PasswordGame
int main(int argc, char** argv) {
    tokenDetector detector;
    srand(time(NULL)); //set random seed
    // make sure file was given at runtime
    if (argc != 2) {
        std::cout << "ASCII coded text file needed!\n" << std::endl;
        return 0;
    }
    // make sure file exists and can be opened
    ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cout << "Could not open the file or it does not exist!\n" << std::endl;
        return 0;
    }

    // run the parser to tokenize the file
    vector<string> parsedWords = detector.getUnique(file);
    cout << "Welcome to The Password Game!\n" << endl;
    cout << "Number of unique tokens in your text file: " << parsedWords.size() << " words." << endl;


    // create generator and guesser pointer objects and prompt the user for number of words
    PassWordGenerator* pwGenerator = new PassWordGenerator(parsedWords);
    cout << "The number of unique password combinations in your file: " << pwGenerator->combinations.size()
        << " unique combinations.\n" << endl;

    unsigned int numWords = pwGenerator->prompt();
    pwGenerator->setIterationLength(numWords);
    PassWordGuesser* pg = new PassWordGuesser(*pwGenerator, numWords);


    // create a random password to pass to the threading method in password guesser class
    string pw = pwGenerator->getRandomPassword(numWords);
    cout << "\nYour random password that was generated is: " << pw << "\n" << endl;


    // add a subscriber object and attach to the publisher
    observer* subscriber = new observer();
    pg->attach(subscriber);


    // perform timing operations and run the two threads
    auto start = chrono::high_resolution_clock::now();
    pg->runThreads(pw, numWords);
    auto stop = chrono::high_resolution_clock::now();
    pg->dettach(subscriber);
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "\nTime taken for the function to find the password: " << duration.count() << " microseconds" << endl;
}
