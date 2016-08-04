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

    /*
    Initialize the hashFunc table.

    @param bucketsNum the number of buckets
    @param hashFunc_ the hash function.
    */
    HashTable(const unsigned &bucketsNum,
              const std::function<unsigned long long(const T&)> &hashFunc_
              = [](const T &x) { return std::hash<T>()(x); })
        : size_(0), buckets(bucketsNum, nullptr), hashFunc(hashFunc_) {}

    /*
    Release the space
    */
    ~HashTable() {
        clear();
    }

    /*
    Return the number of elements in the hash table
    */
    unsigned size() const {
        return size_;
    }

    /*
    Clear the elements in the hash table.
    */
    void clear() {
        for (unsigned i = 0; i < buckets.size(); ++i) {
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
        unsigned pos = hash(e);
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
        unsigned pos = hash(e);
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
        unsigned pos = hash(e);
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

    std::vector<ListNode*> buckets;

    std::function<unsigned long long(const T&)> hashFunc;

    cmp cmp_;

    unsigned size_;

    /*
    The hash function

    @param x the element
    @return the hash value of the element x
    */
    unsigned hash(const T &x) const {
        return static_cast<unsigned>(hashFunc(x) & (buckets.size() - 1));
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
