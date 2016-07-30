#pragma once

#include <iostream>
#include <stdexcept>

namespace sl {

/*
A linked-list data structure.

Type T must overload:
1. operator << for running test. (not compulsory)
2. operator >> for running test. (not compulsory)

For usage, see function test().
*/
template <typename T>
class LinkedList {
public:
    /*
    List node definition.
    */
    struct ListNode {
        T val;
        ListNode *next;
        
        ListNode(const T &v, ListNode *n = nullptr)
            : val(v), next(n) {}
    };

    LinkedList() : size_(0),
        head(new ListNode(T())) {  // Use fake head
    }

    ~LinkedList() {
        release();
    }

    /*
    Return the size of the list.
    */
    unsigned size() const {
        return size_;
    }

    /*
    Check whether the list is empty.
    */
    bool isEmpty() const {
        return size_ == 0;
    }

    /*
    Insert an element to at a given position.
    If the position is larger than size, insert
    to the end of the list.

    @param pos the position to place the element
    @param e the element to insert
    */
    void insert(unsigned pos, const T &e) {
        pos = (pos > size_ ? size_ : pos);
        auto prev = getPrevNode(pos);
        prev->next = new ListNode(e, prev->next);;
        ++size_;
    }
    
    /*
    Insert an element at the end of list.

    @param e the element to insert
    */
    void insertBack(const T &e) {
        insert(size_, e);
    }

    /*
    Get an element at the position.

    @param pos the position
    @return the element at the position
    */
    const T& get(const unsigned &pos) const {
        checkValid(pos);
        return getNode(pos)->val;
    }

    /*
    Remove an element from the list.

    @param pos the position to place the element
    @return the element removed
    */
    T remove(const unsigned &pos) {
        checkValid(pos);
        auto prev = getPrevNode(pos);
        auto del = prev->next;
        auto val = del->val;
        prev->next = prev->next->next;
        --size_;
        delete del;
        return val;
    }

    /*
    Remove an element from the end of list.

    @return the element removed
    */
    T removeBack() {
        return remove(size_ - 1);
    }

private:
    unsigned size_;
    ListNode *head;

    /*
    Release the memory space.
    */
    void release() {
        ListNode *tmp = head, *del;
        while (tmp) {
            del = tmp;
            tmp = tmp->next;
            delete del;
        }
        head = nullptr;
    }

    /*
    Check if a position is valid to visit.

    @param pos the position to check
    */
    void checkValid(const unsigned &pos) const {
        if (!(pos >= 0 && pos < size_)) {
            throw std::range_error("LinkedList.checkValid(): invalid position");
        }
    }

    /*
    Get the previous node of the node at a given position.
    (Two version for const and non-const 'this' pointer)

    @param pos the position
    @return the pointer to the previous node.
    */
    ListNode* getPrevNode(const unsigned &pos) {
        ListNode *tmp = head;
        for (unsigned i = 0; i < pos; ++i) {
            tmp = tmp->next;
        }
        return tmp;
    }

    const ListNode* getPrevNode(const unsigned &pos) const {
        ListNode *tmp = head;
        for (unsigned i = 0; i < pos; ++i) {
            tmp = tmp->next;
        }
        return tmp;
    }

    /*
    Get the node at a given position.
    (Two version for const and non-const 'this' pointer)

    @param pos the position
    @return the pointer to the node.
    */
    ListNode* getNode(const unsigned &pos) {
        return getPrevNode(pos)->next;
    }

    const ListNode* getNode(const unsigned &pos) const {
        return getPrevNode(pos)->next;
    }

public:
    /*
    Test the function of the class.
    */
    static void test() {
        std::cout << "Test LinkedList:\n\n";
        std::cin.clear();
        LinkedList<T> l;
        T tmp;
        unsigned pos;
        std::string oper;
        std::cout << "Operations available:\n"
                << "1. i p x (insert element x at position p)\n"
                << "2. ib x  (insert element x at the end of the list)\n"
                << "3. r p   (remove element at position p)\n"
                << "4. rb    (remove element at the end of the list)\n"
                << "5. size  (get the number of elements in the list)\n"
                << "6. p     (print the list content)\n"
                << std::endl;
        while (1) {
            std::cout << "Input operation: ";
            std::cin >> oper;
            if (oper == "i") {
                std::cin >> pos >> tmp;
                l.insert(pos, tmp);
            } else if (oper == "ib") {
                std::cin >> tmp;
                l.insertBack(tmp);
            } else if (oper == "r") {
                std::cin >> pos;
                auto res = l.remove(pos);
                std::cout << "Element " << res << " removed.\n";
            } else if (oper == "rb") {
                auto res = l.removeBack();
                std::cout << "Element " << res << " removed.\n";
            } else if (oper == "size") {
                std::cout << l.size() << std::endl;
            } else if (oper == "p") {
                for (unsigned i = 0; i < l.size(); ++i) {
                    std::cout << l.get(i) << " ";
                }
                std::cout << std::endl;
            } else {
                std::cout << "Invalid operation." << std::endl;
            }
        }
    }
};

}
