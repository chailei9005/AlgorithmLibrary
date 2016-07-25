#pragma once

#include <functional>

namespace sl {

/*
An AVL-Tree data structure.

The definition of balance:
abs(Height(left subtree) - Height(right subtree)) <= 1

Precondition: Type T must overload operator< and 
              operator== function.
              To run AVLTree<T>::test(), operator>>
              and operator<< must also be implemented.

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
        // TODO insert
    }

    /*
    Test the function of the class.

    Sample #1:
    3 2 1 4 5 6 7 16 15 14 13 12 11 10 8 9 0
    */
    static void test() {
        AVLTree<T> tree;
        cout << "Input elements to be inserted into the AVL tree: (EOF to end)" << endl;
        T tmp;
        while (cin >> tmp) {
            tree.insert(tmp);
        }
        auto f = [&](const T &ele) {
            cout << ele << " ";
        };
        cout << "\nPostorder: \n";
        tree.traverseInPostorder(f);
        cout << "\nInorder: \n";
        tree.traverseInInorder(f);
        cout << "\nPreorder: \n";
        tree.traverseInPreorder(f);
        cout << "\n" << endl;
        cin.clear();
        while (cin) {
            cout << "Input element you want to find: ";
            cin >> tmp;
            if (tree.has(tmp)) {
                cout << "Element " << tmp << " found.\n";
            } else {
                cout << "Element " << tmp << " not found.\n";
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
    Find an element in the tree.

    @param ele the element to find.
    @param root the root of current tree.
    @return the position of the element in the tree.
            Return nullptr if the element is not in
            the tree.
    */
    TreeNode* find(const T &ele, TreeNode *root) const {
        if (root == nullptr || root->val == ele) {
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
