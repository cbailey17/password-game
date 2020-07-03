// Password Guesser
// password Guesser class provides the methods for a threaded search of random passwords
#include "password_project.h"

PassWordGuesser::PassWordGuesser(PassWordGenerator& gen, int numWords) : gen(&gen) {
    correctPassword = gen.getRandomPassword(numWords);
    pwLength = numWords;
}

void PassWordGuesser::attach(observer* obs) {
    observers.push_back(obs);
}

void PassWordGuesser::dettach(observer* obs) {
    observers.remove(obs);
}

void PassWordGuesser::notify(string update) {
    for (observer* cur : observers)
        cur->update(update);
}

void PassWordGuesser::bogoSearch(std::string correctPassword, unsigned int numWords) {
    cout << "Attempting to guess the password with bogo" << endl;

    while (!threadFinished) {
        string tempPwd = gen->getRandomPassword(numWords);
        cout << "bongo guess: " << tempPwd << endl;
        if (tempPwd == correctPassword) {
            cout << "bogoSearch found the password!" << endl;
            cout << "The password from bogo is: " << tempPwd << endl;
            threadFinished = true;
            notify("The password has been found");
        }
        notify("The password has not been found");
    }
    return;
}

void PassWordGuesser::sequentialSearch(std::string correctPassword) {
    cout << "Attempting to guess the password with sequential" << endl;
    threadFinished = false;
    while (!threadFinished) {
        string tempPwd2 = gen->next();
        cout << "sequential guess: " << tempPwd2 << endl;
        if (tempPwd2 == correctPassword) {
            cout << "sequential Search found the password!" << endl;
            cout << "The password from sequential is: " << tempPwd2 << endl;
            threadFinished = true;
            notify("The password has been found");
        }
        notify("The password has not been found");
    }
    return;
}

void PassWordGuesser::runThreads(string pw, unsigned int numWords) {
    srand(rand());  // reset rand seed before search
    thread bogo(&PassWordGuesser::bogoSearch, this, pw, numWords);
    thread sequential(&PassWordGuesser::sequentialSearch, this, pw);
    bogo.join();
    sequential.join();
}
