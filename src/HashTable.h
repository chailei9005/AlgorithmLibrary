#pragma once

#include "Base.h"
#include <vector>
#include <functional>
#include <iostream>
#include <stdexcept>

NS_BEGIN

/*
A hashFunc table data structure.

Template arguments:
1. T: the data type
To run test, T must overload operator '<<' and '>>'.
2. cmp: the comparator that overload operator()
Use to compare equality of two elements of type T.
(default is using operator '==')

For usage, see function test().
*/
template <typename T, typename cmp = std::equal_to<T>>
class HashTable {
public:
    typedef unsigned size_type;

    /*
    Initialize the hashFunc table.

    @param bucketsNum_ the minimum number of buckets
    @param hashFunc_ the hash function.
    */
    HashTable(const size_type bucketsNum_,
              const std::function<unsigned long long(const T&)> &hashFunc_
              = [](const T &x) { return std::hash<T>()(x); }) : hashFunc(hashFunc_) {
        rehash(bucketsNum_);
    }

    /*
    Release the space
    */
    ~HashTable() {
        clear();
        delete[] buckets;
    }

    /*
    Return the number of elements in the hash table
    */
    size_type size() const {
        return size_;
    }

    /*
    Clear the elements in the hash table.
    */
    void clear() {
        for (size_type i = 0; i < bucketsNum; ++i) {
            ListNode *tmp = buckets[i], *del;
            while (tmp) {
                del = tmp;
                tmp = tmp->next;
                delete del;
            }
            buckets[i] = nullptr;
            size_ = 0;
        }
    }

    /*
    Insert an element to the hashFunc table.
    If the element exists, do nothing.

    @param e the element
    */
    void insert(const T &e) {
        size_type pos = hash(e);
        if (!buckets[pos]) {
            buckets[pos] = new ListNode(e);
            ++size_;
        } else {
            ListNode *tmp = buckets[pos];
            while (tmp->next) {
                if (cmp_(tmp->val, e)) {
                    return;
                }
                tmp = tmp->next;
            }
            if (!cmp_(tmp->val, e)) {
                tmp->next = new ListNode(e);
                ++size_;
            }
        }
    }
    
    /*
    Check if an element is in the hashFunc table.

    @param e the element
    */
    bool has(const T &e) const {
        size_type pos = hash(e);
        if (buckets[pos]) {
            ListNode *tmp = buckets[pos];
            while (tmp) {
                if (cmp_(tmp->val, e)) {
                    return true;
                }
                tmp = tmp->next;
            }
        }
        return false;
    }

    /*
    Remove an element from the hashFunc table.
    If the element does not exist, do nothing.

    @param e the element
    */
    void remove(const T &e) {
        size_type pos = hash(e);
        if (buckets[pos]) {
            auto tmp = buckets[pos];
            if (cmp_(tmp->val, e)) {
                delete tmp;
                buckets[pos] = nullptr;
                --size_;
            } else {
                while (tmp->next && !cmp_(tmp->next->val, e));
                if (tmp->next) {
                    auto del = tmp->next;
                    tmp->next = tmp->next->next;
                    delete del;
                    --size_;
                }
            }
        }
    }

    /* 
    Rehash the hash table.

    @param bucketsNum_ the minimum number of buckets
    */
    void rehash(const size_type bucketsNum_) {
        // Calculate new buckets number
        size_type newNum = MIN_BUCKETS;
        while (newNum < bucketsNum_) {
            newNum <<= 1;
        }
        // Record old buckets
        ListNode **oldBuckets = buckets;
        size_type oldBucketsNum = bucketsNum;
        // Rehash
        size_ = 0;
        bucketsNum = newNum;
        buckets = new ListNode*[bucketsNum];
        for (size_type i = 0; i < bucketsNum; ++i) {
            buckets[i] = nullptr;
        }
        for (size_type i = 0; i < oldBucketsNum; ++i) {
            ListNode *p = oldBuckets[i];
            while (p) {
                insert(p->val);
                p = p->next;
            }
        }
        delete[] oldBuckets;
    }

private:
    /*
    Definition of list nodes in a bucket
    */
    struct ListNode {
        T val;
        ListNode *next;
        ListNode(const T &e, ListNode *n = nullptr)
            : val(e), next(n) {}
    };

    ListNode **buckets = nullptr;

    size_type size_ = 0;
    size_type bucketsNum = 0;

    std::function<unsigned long long(const T&)> hashFunc;

    cmp cmp_;

    static const size_type MIN_BUCKETS = 8;

    /*
    The hash function.
    Use bitwise AND to displace mod operation.
    Thus the buckets number must be a power of 2 (2^n).

    @param x the element
    @return the hash value of the element x
    */
    size_type hash(const T &x) const {
        return static_cast<size_type>(hashFunc(x) & (bucketsNum - 1));
    }

public:
    /*
    Test the function of the class.
    */
    static void test() {
        std::cout << "Test HashTable:\n\n";
        std::cin.clear();
        HashTable<T> table(3);
        T tmp;
        std::string oper;
        std::cout << "Operations available:\n"
            << "1. i x  (insert element x)\n"
            << "2. r x  (remove element x)\n"
            << "3. f x  (find element x)\n"
            << "4. size (print the size)\n"
            << "5. rh x (rehash the hash table with minimum buckets number x)"
            << "5. clr  (clear the table)\n"
            << "6. exit (exit test)\n"
            << std::endl;
        try {
            while (1) {
                std::cout << "Input operation: ";
                std::cin >> oper;
                if (oper == "i") {
                    std::cin >> tmp;
                    table.insert(tmp);
                } else if (oper == "r") {
                    std::cin >> tmp;
                    table.remove(tmp);
                } else if (oper == "f") {
                    std::cin >> tmp;
                    if (table.has(tmp)) {
                        std::cout << "Element " << tmp << " found\n";
                    } else {
                        std::cout << "Element " << tmp << " not found\n";
                    }
                } else if (oper == "size") {
                    std::cout << table.size() << std::endl;
                } else if (oper == "rh") {
                    std::cin >> tmp;
                    table.rehash(tmp);
                } else if (oper == "clr") {
                    table.clear();
                } else if (oper == "exit") {
                    break;
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
