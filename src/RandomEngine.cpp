#include "RandomEngine.h"
#include <iostream>
#include <ctime>

using sl::RandomEngine;
using std::cout;
using std::cin;
using std::endl;

RandomEngine::value_type RandomEngine::seed = time(nullptr);
const RandomEngine::value_type RandomEngine::A = 48271;
const RandomEngine::value_type RandomEngine::M = 2147483647;
const RandomEngine::value_type RandomEngine::Q = M / A;
const RandomEngine::value_type RandomEngine::R = M % A;

double RandomEngine::random() {
    value_type tmpSeed = A * (seed % Q) - R * (seed / Q);
    if (tmpSeed >= 0) {
        seed = tmpSeed;
    } else {
        seed = tmpSeed + M;
    }
    return static_cast<double>(seed) / M;
}

double RandomEngine::randDouble(const double min, const double max) {
    return random() * (max - min) + min;
}

unsigned long long RandomEngine::randInt(const unsigned long long min,
                                         const unsigned long long max) {
    return static_cast<unsigned long long>(random() * (max - min + 1) + min);
}

unsigned RandomEngine::randLib(const unsigned min, const unsigned max) {
    static bool seedSet = false;
    if (!seedSet) {
        srand(static_cast<unsigned>(time(nullptr)));
        seedSet = true;
    }
    return rand() % (max - min + 1) + min;
}

void RandomEngine::setSeed(value_type seed_) {
    seed = seed_;
}

void RandomEngine::test() {
    std::cout << "Test RandomEngine:\n\n";
    std::cin.clear();
    unsigned min, max, n = 10;
    cout << "Input the range of the random number: ";
    cin >> min >> max;
    cout << "\nGenerate " << n << " integers:" << endl;
    for (unsigned i = 0; i < n; ++i) {
        auto num = RandomEngine::randInt(min, max);
        cout << num << endl;
    }
    cout << "\nGenerate " << n << " integers using library methods:" << endl;
    for (unsigned i = 0; i < n; ++i) {
        auto num = RandomEngine::randInt(min, max);
        cout << num << endl;
    }
    cout << "\nGenerate " << n << " double numbers:" << endl;
    for (unsigned i = 0; i < n; ++i) {
        auto num = RandomEngine::randDouble(min, max);
        cout << num << endl;
    }
    cout << "\nRandomly rearrange an array of size 10:\n";
    for (unsigned i = 0; i < n; ++i) {
        std::vector<int> arr;
        for (int i = 0; i < 10; ++i) {
            arr.push_back(i);
        }
        RandomEngine::randomChange(arr);
        for (unsigned j = 0; j < arr.size(); ++j) {
            cout << arr[j] << " ";
        }
        cout << endl;
    }
}
