#include "DisjointSet.h"
#include <iostream>

using std::cout;
using std::endl;
using std::cin;
using sl::DisjointSet;

DisjointSet::DisjointSet(const unsigned &size) : arr(size, -1) {
}

DisjointSet::~DisjointSet() { 
}

unsigned DisjointSet::find(const unsigned &x) {
    return arr[x] < 0 ? x : arr[x] = find(arr[x]);
}

void DisjointSet::union_(const unsigned &a, const unsigned &b) {
    int root1 = find(a);
    int root2 = find(b);
    if (root1 != root2) {
        if (arr[root2] < arr[root1]) {
            arr[root2] += arr[root1];  // Update size
            arr[root1] = root2;
        } else {
            arr[root1] += arr[root2];  // Update size
            arr[root2] = root1;
        }
    }
}

int& DisjointSet::operator[](const unsigned &i) {
    return arr[i];
}

const int& DisjointSet::operator[](const unsigned &i) const {
    return arr[i];
}

unsigned DisjointSet::size() const {
    return (unsigned)arr.size();
}

void DisjointSet::test() {
    DisjointSet s(10);
    while (true) {
        cout << "Input two numbers you want to add to the same set: (-1 to end)\n";
        int a, b;
        cin >> a >> b;
        if (a == -1 || b == -1) break;
        s.union_(a, b);
    }
    cout << "\nBefore path compression:\n";
    for (unsigned i = 0; i < s.size(); ++i) {
        cout << "Array[" << i << "] = " << s[i];
        cout << " / Root of vertex " << i << ": " << s.find(i) << endl;
    }
    cout << "\nAfter path compression:\n";
    for (unsigned i = 0; i < s.size(); ++i) {
        cout << "Array[" << i << "] = " << s[i];
        cout << " / Root of vertex " << i << ": " << s.find(i) << endl;
    }
}
