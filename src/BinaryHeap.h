#pragma once

#include <vector>
#include <iostream>
#include <stdexcept>

using std::cout;
using std::endl;
using std::cin;

namespace sl {

/*
A min-heap.
Type T must overload operator< function.
*/
template <typename T>
class BinaryHeap {
public:
    BinaryHeap(const unsigned &maxSize)
        : capacity_(maxSize), size_(0), arr(maxSize + 1) {
    }

    ~BinaryHeap() {
    }

    /*
    Return the capacity of the binary heap
    */
    unsigned capacity() const {
        return capacity_;
    }

    /*
    Return the size of the binary heap
    */
    unsigned size() const {
        return size_;
    }

    /*
    Return whether the heap is full.
    */
    bool isFull() const {
        return size_ == capacity_;
    }

    /*
    Return whether the heap is empty.
    */
    bool isEmpty() const {
        return size_ == 0;
    }

    /*
    Insert a new element to the heap.

    @param x the element to be pushed into the heap.
    */
    void push(const T &x) {
        if (isFull()) {
            throw std::range_error("BinaryHeap.push(): Heap is full");
        }
        // Element 'x' percolates up in the heap
        int i;
        for (i = ++size_; i != 1 && x < arr[i >> 1]; i >>= 1) {
            arr[i] = arr[i >> 1];
        }
        arr[i] = x;
    }

    /*
    Return the root element of the heap.
    */
    T front() const {
        if (isEmpty()) {
            throw std::range_error("BinaryHeap.front(): Heap is empty");
        }
        return arr[1];
    }

    /*
    Delete the root element of the heap.
    */
    void pop() {
        if (isEmpty()) {
            throw std::range_error("BinaryHeap.pop(): Heap is empty");
        }
        T rootEle = arr[1], lastEle = arr[size_--];
        unsigned i, child;
        // Empty hole percolate down in the heap
        for (i = 1; i * 2 <= size_; i = child) {
            child = i * 2;
            // Find smaller child
            if (child != size_ && arr[child + 1] < arr[child]) {
                ++child;
            }
            if (lastEle <= arr[child]) {
                break;
            } else {
                arr[i] = arr[child];
            }
        }
        arr[i] = lastEle;
    }

    /*
    Test the function of the class.

    Sample #1:
    21 16 36 65 32 24 31 19 68 13 0

    Sample #2:
    150 80 40 30 10 70 110 100 20 90 60 50 120 140 130 0
    */
    static void test() {
        BinaryHeap<T> h(100);
        cout << "Input elements to insert to the binary heap: (0 to end)" << endl;
        while (1) {
            T tmp;
            cin >> tmp;
            if (tmp == 0) break;
            h.push(tmp);
        }
        cout << "\nHeap array content:" << endl;
        for (unsigned i = 0; i <= h.size(); ++i) {
            cout << "arr[" << i << "] = " << h.arr[i] << endl;
        }
        cout << "\nPop until the heap is empty:" << endl;
        while (!h.isEmpty()) {
            T ele = h.front();
            cout << ele << " ";
            h.pop();
        }
        cout << endl;
    }

private:
    unsigned capacity_;
    unsigned size_;

    /*
    The first element stores at index 1.
    For each arr[i]:
    1. arr[2 * i] is the left child.
    2. arr[2 * i + 1] is the right child.
    3. arr[i / 2] is a[i]'s father.
    */
    std::vector<T> arr;
};

}
