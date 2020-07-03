#include "password_project.h"

void observer::update(string update, __int64 time, int numAttempts, string password) {
    string finished = update;
    cout << "\n" << update << endl;
    if (password.size() > 1) {
        cout << "The password is: " << password << endl;
    }
    cout << "Time elapsed: " << time << " microseconds" << endl;
    cout << "Number of attempts: " << numAttempts << "\n" << endl;
}
