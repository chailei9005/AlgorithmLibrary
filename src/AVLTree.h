#pragma once

#include <functional>
#include <stdexcept>
#include <new>
#include <algorithm>
#include <string>

namespace sl {

/*
An AVL-Tree data structure.

Definition of a balanced tree:
abs(height(left-subtree) - height(right-subtree)) <= 1

Type T must overload:
1. operator <  for comparing.
1. operator >  for comparing.
2. operator == for comparing.
3. operator << for running test. (not compulsory)
4. operator >> for running test. (not compulsory)

For usage, see function test().
*/
template <typename T>
class AVLTree {
public:
    /*
    Definition of tree node.
    */
    struct TreeNode {
        T val;
        TreeNode* left;
        TreeNode* right;
        int height;
        TreeNode(const T &v, TreeNode *l = nullptr, TreeNode *r = nullptr) 
            : val(v), left(l), right(r), height(0) {}
    };

    /*
    Forbid copy.
    */
    AVLTree(const AVLTree<T> &tree) = delete;;
    AVLTree<T>& operator=(const AVLTree<T> &tree) = delete;

    AVLTree() {
    }

    ~AVLTree() {
        release(root);
        root = nullptr;
    }

    /*
    Check if element ele is in the tree.

    @param ele the element to check.
    @return true if the element is in the tree, false otherwise.
    */
    bool has(const T &ele) const {
        return find(ele, root) != nullptr;
    }

    /*
    Return whether the tree is empty.
    */
    bool isEmpty() const {
        return !root;
    }

    /*
    Return the minimum element of the tree.
    */
    T min() const {
        if (isEmpty()) {
            throw std::range_error("AVLTree.min(): Tree is empty");
        }
        return findMin(root)->val;
    }

    /*
    Return the maximum element of the tree.
    */
    T max() const {
        if (isEmpty()) {
            throw std::range_error("AVLTree.max(): Tree is empty");
        }
        return findMax(root)->val;
    }

    /*
    Traverse the tree in postorder.
    */
    void traverseInPostorder(const std::function<void(const T&)> &f) const {
        postorder(root, f);
    }

    /*
    Traverse the tree in inorder.
    */
    void traverseInInorder(const std::function<void(const T&)> &f) const {
        inorder(root, f);
    }

    /*
    Traverse the tree in preorder.
    */
    void traverseInPreorder(const std::function<void(const T&)> &f) const {
        preorder(root, f);
    }

    /*
    Insert an element into the tree.

    @param ele the element to be inserted.
    */
    void insert(const T &ele) {
        root = balancedInsert(ele, root);
    }

    /*
    Remove an element from the tree.

    @param ele the element to be removed.
    */
    void remove(const T &ele) {
        root = balancedRemove(ele, root);
    }

    /*
    Test the function of the class.

    Sample #1:
    i 3
    i 2
    i 1
    i 4
    i 5
    i 6
    i 7
    i 16
    i 15
    i 14
    i 13
    i 12 
    i 11
    i 10 
    i 8
    i 9

    Result:
    Postorder:
    1 3 2 5 6 4 8 10 9 12 11 14 16 15 13 7
    Inorder:
    1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
    Preorder:
    7 4 2 1 3 6 5 13 11 9 8 10 12 15 14 16
    */
    static void test() {
        AVLTree<T> tree;
        T tmp;
        std::string oper;
        auto f = [](const T &ele) {
            cout << ele << " ";
        };
        cout << "Operations available:\n"
            << "1. i x  (insert element x)\n"
            << "2. f x  (find element x)\n"
            << "3. r x  (remove element x)\n"
            << "4. post (print the tree in postorder)\n"
            << "5. in   (print the tree in inorder)\n"
            << "6. pre  (print the tree in preorder)\n"
            << "7. min  (print the minimum element of the tree)\n"
            << "8. max  (print the maximum element of the tree)\n"
            << endl;
        while (1) {
            cout << "Input operation: ";
            cin >> oper;
            if (oper == "i") {
                cin >> tmp;
                tree.insert(tmp);
            } else if (oper == "f") {
                cin >> tmp;
                if (tree.has(tmp)) {
                    cout << "Element " << tmp << " found\n";
                } else {
                    cout << "Element " << tmp << " not found\n";
                }
            } else if (oper == "r") {
                cin >> tmp;
                if (tree.has(tmp)) {
                    tree.remove(tmp);
                    cout << "Element " << tmp << " removed\n";
                } else {
                    cout << "Element " << tmp << " not found\n";
                }
            } else if (oper == "post") {
                tree.traverseInPostorder(f);
                cout << endl;
            } else if (oper == "in") {
                tree.traverseInInorder(f);
                cout << endl;
            } else if (oper == "pre") {
                tree.traverseInPreorder(f);
                cout << endl;
            } else if (oper == "min") {
                cout << tree.min() << endl;
            } else if (oper == "max") {
                cout << tree.max() << endl;
            } else {
                cout << "Invalid operation." << endl;
            }
        }
    }

private:
    TreeNode *root = nullptr;

    /*
    Compute the height of a tree.

    @param root the root of the tree to compute.
    @return the height of the tree. The height
            of an empty tree will be defined as -1.
    */
    int height(TreeNode *root) const {
        return root ? root->height : -1;
    }

    /*
    Update the height of the tree.

    @param root the root of the tree.
    */
    void updateHeight(TreeNode *root) {
        root->height = 1 + std::max(height(root->left), height(root->right));
    }

    /*
    Find an element in the tree.

    @param ele the element to find.
    @param root the root of current tree.
    @return the position of the element in the tree.
            Return nullptr if the element is not in
            the tree.
    */
    TreeNode* find(const T &ele, TreeNode *root) const {
        if (!root || root->val == ele) {
            return root;
        } else if (ele < root->val) {
            return find(ele, root->left);
        } else if (ele > root->val) {
            return find(ele, root->right);
        } else {
            return nullptr;
        }
    }

    /*
    Find the minimum element in the tree.

    @param root the root of current tree.
    @return the position of the minimum element in the tree.
    */
    TreeNode* findMin(TreeNode *root) const {
        if (!root || root->left == nullptr) {
            return root;
        } else {
            return findMin(root->left);
        }
    }

    /*
    Find the maximum element in the tree.

    @param root the root of current tree.
    @return the position of the maximum element in the tree.
    */
    TreeNode* findMax(TreeNode *root) const {
        if (!root || root->right == nullptr) {
            return root;
        } else {
            return findMax(root->right);
        }
    }

    /*
    Traverse the tree in postorder.

    @param root the root of current tree.
    @param f the function to manipulate each element
             during traversing.
    */
    void postorder(TreeNode *root, const std::function<void(const T&)> &f) const {
        if (root != nullptr) {
            postorder(root->left, f);
            postorder(root->right, f);
            f(root->val);
        }
    }

    /*
    Traverse the tree in inorder.

    @param root the root of current tree.
    @param f the function to manipulate each element
    during traversing.
    */
    void inorder(TreeNode *root, const std::function<void(const T&)> &f) const {
        if (root != nullptr) {
            inorder(root->left, f);
            f(root->val);
            inorder(root->right, f);
        }
    }

    /*
    Traverse the tree in preorder.

    @param root the root of current tree.
    @param f the function to manipulate each element
    during traversing.
    */
    void preorder(TreeNode *root, const std::function<void(const T&)> &f) const {
        if (root != nullptr) {
            f(root->val);
            preorder(root->left, f);
            preorder(root->right, f);
        }
    }

    /*
    Insert an element to the tree and maintain the balance.

    @param e the element to insert
    @param root the root of the current tree
    @return the new root of the tree that has
            inserted the element.
    */
    TreeNode* balancedInsert(const T &e, TreeNode *root) {
        if (root == nullptr) {
            root = new (std::nothrow) TreeNode(e);
            if (!root) {
                throw std::bad_alloc();
            }
        } else if (e < root->val) {
            root->left = balancedInsert(e, root->left);
            if (height(root->left) - height(root->right) == 2) {  // Balance is broken
                if (e < root->left->val) {
                    root = rotateSingleLeft(root);
                } else if (e > root->left->val) {
                    root = rotateDoubleLeft(root);
                }
            }
        } else if (e > root->val) {
            root->right = balancedInsert(e, root->right);
            if (height(root->right) - height(root->left) == 2) {  // Balance is broken
                if (e > root->right->val) {
                    root = rotateSingleRight(root);
                } else if (e < root->right->val) {
                    root = rotateDoubleRight(root);
                }
            }
        }
        updateHeight(root);
        return root;
    }

    /*
    Remove an element from the tree and maintain the balance.

    @param e the element to remove
    @param root the root of the current tree
    @return the new root of the tree that has
            removed the element.
    */
    TreeNode* balancedRemove(const T &e, TreeNode *root) {
        if (!root) {
            throw std::range_error("AVLTree.balancedRemove(): Element not found");
        } else if (e < root->val) {
            root->left = balancedRemove(e, root->left);
        } else if (e > root->val) {
            root->right = balancedRemove(e, root->right);
        } else if (e == root->val) {
            if (root->left && root->right) {  // Two child
                TreeNode* node = findMin(root->right);
                root->val = node->val;
                root->right = balancedRemove(node->val, root->right);
            } else {  // One or zero child
                TreeNode* del = root;
                if (root->left == nullptr) {  // Also handle the zero child situation
                    root = root->right;
                } else if (root->right == nullptr) {
                    root = root->left;
                }
                delete del;
            }

        }
        if (root) {
            updateHeight(root);
        }
        // TODO maintain balance
        return root;
    }

    /*
    Single rotation with left when inserting into
    the left subtree of the left child.

    @param param root the root of the tree to be rotated
    @return the new root of the tree after rotation
    */
    TreeNode* rotateSingleLeft(TreeNode* root) {
        TreeNode* leftChild = root->left;
        root->left = leftChild->right;
        leftChild->right = root;
        updateHeight(root);
        updateHeight(leftChild);
        return leftChild;
    }

    /*
    Single rotation with right when inserting into
    the right subtree of the right child.

    @param param root the root of the tree to be rotated
    @return the new root of the tree after rotation
    */
    TreeNode* rotateSingleRight(TreeNode* root) {
        TreeNode* rightChild = root->right;
        root->right = rightChild->left;
        rightChild->left = root;
        updateHeight(root);
        updateHeight(rightChild);
        return rightChild;
    }

    /*
    Double rotation with left when inserting into
    the right subtree of the left child.

    @param param root the root of the tree to be rotated
    @return the new root of the tree after rotation
    */
    TreeNode* rotateDoubleLeft(TreeNode* root) {
        root->left = rotateSingleRight(root->left);
        return rotateSingleLeft(root);
    }

    /*
    Double rotation with right when inserting into
    the left subtree of the right child.

    @param param root the root of the tree to be rotated
    @return the new root of the tree after rotation
    */
    TreeNode* rotateDoubleRight(TreeNode* root) {
        root->right = rotateSingleLeft(root->right);
        return rotateSingleRight(root);
    }

    /*
    Release the memory space occupied by the tree.

    @param root the root of current tree.
    */
    void release(TreeNode *root) {
        if (root != nullptr) {
            release(root->left);
            release(root->right);
            delete root;
        }
    }
};

}
