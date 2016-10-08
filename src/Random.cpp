#include "Random.h"
#include <iostream>
#include <ctime>

using sl::Random;
using std::cout;
using std::cin;
using std::endl;

Random::~Random() {
}

Random::Random()
    : seed(time(nullptr)), A(48271), M(2147483647), Q(M / A), R(M % A) {
}

Random* Random::getInstance() {
    // According to C++11, static field constructor is thread-safe
    static Random instance;
    return &instance;
}

double Random::rand() {
    value_type tmpSeed = A * (seed % Q) - R * (seed / Q);
    if (tmpSeed >= 0) {
        seed = tmpSeed;
    } else {
        seed = tmpSeed + M;
    }
    return static_cast<double>(seed) / M;
}

double Random::randDouble(const double min, const double max) {
    return rand() * (max - min) + min;
}

unsigned long long Random::randInt(const unsigned long long min,
                                         const unsigned long long max) {
    return static_cast<unsigned long long>(rand() * (max - min + 1) + min);
}

unsigned Random::randLib(const unsigned min, const unsigned max) {
    static bool seedSet = false;
    if (!seedSet) {
        srand(static_cast<unsigned>(time(nullptr)));
        seedSet = true;
    }
    return std::rand() % (max - min + 1) + min;
}

void Random::setSeed(value_type seed_) {
    seed = seed_;
}

void Random::test() {
    std::cout << "Test Random:\n\n";
    std::cin.clear();
    unsigned min, max, n = 10;
    cout << "Input the range of the random number: ";
    cin >> min >> max;
    cout << "\nGenerate " << n << " integers:" << endl;
    for (unsigned i = 0; i < n; ++i) {
        auto num = Random::getInstance()->randInt(min, max);
        cout << num << endl;
    }
    cout << "\nGenerate " << n << " integers using library methods:" << endl;
    for (unsigned i = 0; i < n; ++i) {
        auto num = Random::getInstance()->randInt(min, max);
        cout << num << endl;
    }
    cout << "\nGenerate " << n << " double numbers:" << endl;
    for (unsigned i = 0; i < n; ++i) {
        auto num = Random::getInstance()->randDouble(min, max);
        cout << num << endl;
    }
    cout << "\nRandomly rearrange an array of size 10:\n";
    for (unsigned i = 0; i < n; ++i) {
        std::vector<int> arr;
        for (int i = 0; i < 10; ++i) {
            arr.push_back(i);
        }
        Random::getInstance()->randomChange(arr);
        for (unsigned j = 0; j < arr.size(); ++j) {
            cout << arr[j] << " ";
        }
        cout << endl;
    }
}
