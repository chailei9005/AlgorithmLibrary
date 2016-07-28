#include "Algorithms.h"
#include <algorithm>
#include <iostream>

using std::cout;
using std::endl;
using std::cin;
using sl::Algorithms;

void Algorithms::test() {
    testBinarySearch();
}

int Algorithms::binarySearch(const int a[], const int n, const int x) {
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

void Algorithms::testBinarySearch(void) {
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
