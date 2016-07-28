#pragma once

#include <vector>
#include <iostream>
#include <stdexcept>

namespace sl {

/*
A min-root heap data structure.

Type T must overload:
1. operator <  for comparing.
2. operator << for running test. (not compulsory)
3. operator >> for running test. (not compulsory)

For usage, see function test().
*/
template <typename T>
class BinaryHeap {
public:
    BinaryHeap() : size_(0), arr(1) {
    }

    ~BinaryHeap() {
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
        return size_ + 1 == arr.size();
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
            arr.resize(size_ + 2);  // Expand space
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

private:
    unsigned size_;

    /*
    The first element stores at index 1.
    For each arr[i]:
    1. arr[2 * i] is the left child.
    2. arr[2 * i + 1] is the right child.
    3. arr[floor(i / 2)] is a[i]'s father.
    */
    std::vector<T> arr;

public:
    /*
    Test the function of the class.

    Sample #1:
    push 3
    push 2
    push 7
    push 1
    push 9
    push 8
    push 4
    push 0
    push 5
    push 6
    */
    static void test() {
        std::cout << "Test BinaryHeap:\n\n";
        std::cin.clear();
        BinaryHeap<T> heap;
        T tmp;
        std::string oper;
        std::cout << "Operations available:\n"
            << "1. push x (push element x)\n"
            << "2. front  (get front element)\n"
            << "3. pop    (pop an element)\n"
            << "4. size   (get the number of elements in the heap)\n"
            << "5. sort   (front and pop until the heap is empty)\n"
            << std::endl;
        while (1) {
            std::cout << "Input operation: ";
            std::cin >> oper;
            if (oper == "push") {
                std::cin >> tmp;
                heap.push(tmp);
            } else if (oper == "front") {
                std::cout << heap.front() << std::endl;
            } else if (oper == "pop") {
                heap.pop();
            } else if (oper == "size") {
                std::cout << heap.size() << std::endl;
            } else if (oper == "sort") {
                while (!heap.isEmpty()) {
                    T ele = heap.front();
                    std::cout << ele << " ";
                    heap.pop();
                }
                std::cout << std::endl;
            } else {
                std::cout << "Invalid operation." << std::endl;
            }
        }
    }
};

}
