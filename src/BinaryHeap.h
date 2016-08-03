#pragma once

#include "Base.h"
#include <vector>
#include <iostream>
#include <stdexcept>
#include <functional>

NS_BEGIN

/*
A binary heap data structure.

Template arguments:
1. T: the data type
   To run test, T must overload operator '<<' and '>>'.
2. cmpT: the comparator that overload operator()
   The structure will make sure that
   cmp()(parent_tree_node, child_tree_node) == true
   (default is using operator '<=')

For usage, see function test().
*/
template <typename T, typename cmpT = std::less_equal<T>>
class BinaryHeap {
public:
    ~BinaryHeap() {
    }

    BinaryHeap() : size_(0), arr(1) {
    }

    /*
    Return the number of elements in the heap
    */
    long size() const {
        return size_;
    }

    /*
    Return whether the heap is empty.
    */
    bool empty() const {
        return size_ == 0;
    }

    /*
    Clear the heap.
    */
    void clear() {
        size_ = 0;
    }

    /*
    Insert a new element to the heap.

    @param x the element to be pushed into the heap.
    */
    void push(const T &x) {
        if (isFull()) {
            arr.resize((size_ << 1) + 2);  // Expand space
        }
        // Element 'x' percolates up in the heap
        int i;
        for (i = ++size_; i != 1 && !cmp(arr[i >> 1], x); i >>= 1) {
            arr[i] = arr[i >> 1];
        }
        arr[i] = x;
    }

    /*
    Return the root element of the heap.
    */
    T top() const {
        if (empty()) {
            throw std::range_error("BinaryHeap.top(): heap is empty");
        }
        return arr[1];
    }

    /*
    Delete the root element of the heap.
    */
    void pop() {
        if (empty()) {
            throw std::range_error("BinaryHeap.pop(): heap is empty");
        }
        T rootEle = arr[1], lastEle = arr[size_--];
        long i, child;
        // Empty hole percolate down in the heap
        for (i = 1; (i << 1) <= size_; i = child) {
            child = i << 1;
            if (child != size_ && cmp(arr[child + 1], arr[child])) {
                ++child;
            }
            if (cmp(lastEle, arr[child])) {
                break;
            } else {
                arr[i] = arr[child];
            }
        }
        arr[i] = lastEle;
    }

private:
    long size_;

    // The comparator
    cmpT cmp;

    /*
    Content array.
    The first element stores at index 1.
    For each arr[i]:
    1. arr[2 * i] is the left child.
    2. arr[2 * i + 1] is the right child.
    3. arr[floor(i / 2)] is a[i]'s father.
    */
    std::vector<T> arr;

    /*
    Return whether the heap is full.
    */
    bool isFull() const {
        return size_ + 1 == arr.size();
    }

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
        //BinaryHeap<T> heap; // Min-root heap
        BinaryHeap<T, std::greater_equal<T>> heap;  // Max-root heap
        T tmp;
        std::string oper;
        std::cout << "Operations available:\n"
            << "1. push x (push element x)\n"
            << "2. top    (get top element)\n"
            << "3. pop    (pop an element)\n"
            << "4. size   (get the number of elements in the heap)\n"
            << "5. sort   (top and pop until the heap is empty)\n"
            << std::endl;
        try {
            while (1) {
                std::cout << "Input operation: ";
                std::cin >> oper;
                if (oper == "push") {
                    std::cin >> tmp;
                    heap.push(tmp);
                } else if (oper == "top") {
                    std::cout << heap.top() << std::endl;
                } else if (oper == "pop") {
                    heap.pop();
                } else if (oper == "size") {
                    std::cout << heap.size() << std::endl;
                } else if (oper == "sort") {
                    while (!heap.empty()) {
                        T ele = heap.top();
                        std::cout << ele << " ";
                        heap.pop();
                    }
                    std::cout << std::endl;
                } else {
                    std::cout << "Invalid operation." << std::endl;
                }
            }
        } catch (const std::exception &e) {
            std::cout << "Catch exception: " << e.what() << std::endl;
        }
    }
};

NS_END
