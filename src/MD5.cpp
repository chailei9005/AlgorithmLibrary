#include "MD5.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::string;
using sl::MD5;

string MD5::encrypt(const string &msg) {
    return msg;
}

void MD5::test() {
    cout << "Test MD5:\n\n";
    cin.clear();
    string msg;
    while (1) {
        cout << "Input message to be encrypted:" << endl;
        getline(cin, msg);
        cout << "Ciphertext:" << endl
            << MD5::encrypt(msg) << endl << endl;
    }
}
