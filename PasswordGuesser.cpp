#include "password_project.h"

// Password Guesser
// guesser class acts as a publisher as well as performs the searches and initiates the threads

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

void PassWordGuesser::notify(string update, __int64 time, int numAttempts, string password) {
    for (observer* cur : observers)
        cur->update(update, time, numAttempts, password);
}

void PassWordGuesser::bogoSearch(std::string correctPassword, unsigned int numWords) {
    cout << "Attempting to guess the password with bogo search\n" << endl;
    auto start = chrono::high_resolution_clock::now();
    int attemptsB = 0;

    threadFinished = false;
    while (!threadFinished) {
        string tempPwd = gen->getRandomPassword(numWords);
        attemptsB += 1;
        if (attemptsB % 30 == 0) {
            auto stop = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
            notify("Still searching bogo style...", duration.count(), attemptsB, "");
        }

        if (tempPwd == correctPassword) {
            auto stop = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
            notify("Password found with bogo search", duration.count(), attemptsB, tempPwd);
            threadFinished = true;
        }
    }
    return;
}

void PassWordGuesser::sequentialSearch(std::string correctPassword) {
    cout << "Attempting to guess the password with sequential search\n" << endl;
    auto start = chrono::high_resolution_clock::now();
    int attemptsS = 0;

    threadFinished = false;
    while (!threadFinished) {
        string tempPwd2 = gen->next();
        attemptsS += 1;
        if (attemptsS % 30 == 0) {
            auto stop = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
            notify("Still searching sequentially...", duration.count(), attemptsS, "");
        }

        if (tempPwd2 == correctPassword) {
            auto stop = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
            notify("Password found with sequential search", duration.count(), attemptsS, tempPwd2);
            threadFinished = true;
        }
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