#include "Algorithm.h"
#include <algorithm>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::cin;
using std::vector;
using sl::Algorithm;

void Algorithm::test() {
    //testFactorial();
    //testBinarySearch();
    //testPermutation();
    //testCombination();
    testCantorExpand();
}

unsigned long long Algorithm::factorial(unsigned n) {
    unsigned long long res = 1;
    for (unsigned i = 2; i <= n; ++i) {
        res *= i;
    }
    return res;
}

void Algorithm::testFactorial() {
    cout << "Test factorial:\n\n";
    cin.clear();
    cout << "Input n: ";
    unsigned n;
    cin >> n;
    cout << n << "! = " << factorial(n) << endl;
}

int Algorithm::binarySearch(const int a[], const int n, const int x) {
    // Standard
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (x == a[mid]) {
            return mid;
        } else if (x > a[mid]) {
            low = mid + 1;
        } else if (x < a[mid]) {
            high = mid - 1;
        }
    }
    return -1;

    // Find last appear position
    //int left = 0, right = n - 1;
    //while (left + 1 < right) {
    //    int mid = (left + right) / 2;
    //    if (a[mid] <= x) {
    //        left = mid;
    //    } else {
    //        right = mid;
    //    }
    //}
    //if (a[right] == x) {
    //    return right;
    //} else if (a[left] == x) {
    //    return left;
    //} else {
    //    return -1;
    //}

    // Find first appear position
    //int left = 0, right = n - 1;
    //while (left < right) {
    //    int mid = (left + right) / 2;
    //    if (a[mid] >= x) {
    //        right = mid;
    //    } else {
    //        left = mid + 1;
    //    }
    //}
    //if (a[left] == x) {
    //    return left;
    //} else {
    //    return -1;
    //}
}

void Algorithm::testBinarySearch(void) {
    cout << "Test binary search:\n" << endl;
    cin.clear();
    int a[100], n;
    cout << "Input the size of the array(<=100): ";
    cin >> n;
    cout << "Input elements:" << endl;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    std::sort(a, a + n);
    cout << endl;
    while (1) {
        cout << "Input element to find: ";
        int x;
        cin >> x;
        int pos = binarySearch(a, n, x);
        if (pos == -1) {
            cout << "Element " << x << " not found" << endl;
        } else {
            cout << "Element " << x << " found at position " << pos << endl;
        }
    }
}

bool Algorithm::nextPermutation(int a[], const int n) {
    int i;
    for (i = n - 2; i >= 0; --i) {
        if (a[i] < a[i + 1]) {
            // Swap a[i] with a[swapPos]
            // where swapPos is the index of
            // the minimum element after a[i]
            // that is bigger than a[i].
            int swapPos = i + 1;
            int min = a[i + 1];
            for (int k = i + 1; k < n; ++k) {
                if (a[k] > a[i] && a[k] < min) {
                    min = a[k];
                    swapPos = k;
                }
            }
            swap(a[i], a[swapPos]);

            // Reverse the sequence between
            // index (i + 1) and index (n - 1)
            for (int left = i + 1, right = n - 1;
                 left < right;
                 ++left, --right) {
                swap(a[left], a[right]);
            }
            break;
        }
    }
    // If i equals to -1, then the array
    // is in in descending order, namely
    // the last permutation, return false
    return i != -1;
}

void Algorithm::testPermutation() {
    cout << "Test permutation:\n" << endl;
    cin.clear();
    int a[100], n;
    cout << "Input the size of the array(<=100): ";
    cin >> n;
    cout << "Input elements:" << endl;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    unsigned long long cnt = 0;
    cout << "\nPermutations:" << endl;
    std::sort(a, a + n);
    do {
        for (int i = 0; i < n; ++i) {
            cout << a[i] << " ";
        }
        cout << " (" << (++cnt) << ")" << endl;
    } while (nextPermutation(a, n));
    std::next_permutation(a, a + n);
}

void Algorithm::printCombinations(const int a[], const int n, const int k) {
    // Initialize 01 array.
    // 1 means to choose, 0 means not to choose
    vector<int> mark(n, 0);
    for (int i = 0; i < n; ++i) {
        mark[i] = i < k ? 1 : 0;
    }
    unsigned long long cnt = 0;
    bool hasNext = true;
    while (hasNext) {
        // Print current combination
        for (int i = 0; i < n; ++i) {
            if (mark[i] == 1) {
                cout << a[i] << " ";
            }
        }
        cout << " (" << (++cnt) << ")" << endl;
        // Compute next
        hasNext = false;
        for (int i = 0; i < n - 1; ++i) {
            if (mark[i] == 1 && mark[i + 1] == 0) {
                // Switch 10 to 01
                mark[i] = 0;
                mark[i + 1] = 1;
                // Move all '1' before mark[i] to
                // the left-most side of the set.
                int onesCnt = 0;
                for (int j = 0; j < i; ++j) {
                    if (mark[j] == 1) {
                        ++onesCnt;
                    }
                }
                if (onesCnt < i) {
                    for (int j = 0; j < i; ++j) {
                        if (onesCnt) {
                            mark[j] = 1;
                            --onesCnt;
                        } else {
                            mark[j] = 0;
                        }
                    }
                }
                hasNext = true;
                break;
            }
        }
    }
}

void Algorithm::testCombination() {
    cout << "Test combination:\n" << endl;
    cin.clear();
    int a[100], n, k;
    cout << "Input the size of the array(<=100): ";
    cin >> n;
    cout << "Input k (numbers to select): ";
    cin >> k;
    cout << "Input elements:" << endl;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    cout << "\nCombinations:" << endl;
    printCombinations(a, n, k);
}

unsigned long long Algorithm::cantorExpand(const int n, const int a[]) {
    unsigned long long res = 0;
    for (int i = 0; i < n; ++i) {
        int cnt = 0;
        for (int j = i + 1; j < n; ++j) {
            if (a[j] < a[i]) {
                ++cnt;
            }
        }
        res += cnt * factorial(n - 1 - i);
    }
    return res;
}

void Algorithm::cantorExpandInverse(const int n, unsigned long long val, int a[]) {
    bool *has = new bool[n];
    for (int i = 0; i < n; ++i) {
        has[i] = false;
    }
    for (int i = 0; i < n; ++i) {
        int e = int(val / factorial(n - i - 1));
        for (int j = 0; j <= e; ++j) {
            if (has[j]) {
                ++e;
            }
        }
        a[i] = e;
        has[e] = true;
        val %= factorial(n - i - 1);
    }
    delete[] has;
}

void Algorithm::testCantorExpand() {
    cout << "Test contor expand:\n" << endl;
    cin.clear();
    cout << "Input the size of the permutation array: ";
    int n;
    cin >> n;
    int *a = new int[n];
    cout << "Input permutation array elements: ";
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int *b = new int[n];
    auto val = cantorExpand(n, a);
    cantorExpandInverse(n, val, b);
    cout << "Cantor expand value: " << val << endl;
    cout << "Cantor expand inverse: ";
    for (int i = 0; i < n; ++i) {
        cout << b[i] << " ";
    }
    cout << endl;
    delete[] a;
    delete[] b;
}
