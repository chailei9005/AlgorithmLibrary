#include "NPuzzle.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::stringstream;
using sl::NPuzzleNode;
using sl::NPuzzle;
using sl::Direction;

NPuzzleNode::NPuzzleNode() {
}

NPuzzleNode::NPuzzleNode(const value_type &val_,
                         const int row_,
                         const int col_) {
    checkValid(val_, row_, col_);
    val = val_;
    row = row_;
    col = col_;
    h = 0;
    g = 0;
    parent = NONE;
}

NPuzzleNode::~NPuzzleNode() {
}

void NPuzzleNode::checkValid(const value_type &val_,
                             const int row_,
                             const int col_) const {
    if (row_ < 2 || col_ < 2) {
        throw std::range_error("NPuzzleNode.checkValid(): dimension is at least 2*2");
    }
    if (val_.size() != row_ * col_ + 1) {
        throw std::range_error("NPuzzleNode.checkValid(): val_.size() must equal to (row_ * col_ + 1)");
    }
    if (!(val_[0] >= 1 && val_[0] <= row_ * col_)
        || val_[val_[0]] != 0) {
        throw std::range_error("NPuzzleNode.checkValid(): val_[0] must store the index of value 0");
    }
}

void NPuzzleNode::setVal(const value_type &val_) {
    checkValid(val_, row, col);
    val = val_;
}

const NPuzzleNode::value_type& NPuzzleNode::getVal() const {
    return val;
}

void NPuzzleNode::move(const Direction &direc) {
    int goalPos = val[0] + getDisplacement(direc);
    std::swap(val[val[0]], val[goalPos]);
    val[0] = goalPos;
}

bool NPuzzleNode::canMove(const Direction &direc) const {
    switch (direc) {
        case LEFT:
            return getCol(val[0]) != 0;
        case UP:
            return getRow(val[0]) != 0;
        case RIGHT:
            return getCol(val[0]) != col - 1;
        case DOWN:
            return getRow(val[0]) != row - 1;
        case NONE:
            return true;
        default:
            return false;
    }
}

int NPuzzleNode::getDisplacement(const Direction &direc) const {
    switch (direc) {
        case LEFT:
            return -1;
        case UP:
            return -col;
        case RIGHT:
            return 1;
        case DOWN:
            return col;
        case NONE:
        default:
            return 0;
    }
}

int NPuzzleNode::getRow(const int &index) const {
    return (index - 1) / col;
}

int NPuzzleNode::getCol(const int &index) const {
    return (index - 1) % col;
}

string NPuzzleNode::toString() const {
    stringstream ss;
    ss << "{";
    for (unsigned i = 0; i < val.size(); ++i) {
        if (i) ss << ",";
        ss << val[i];
    }
    ss << "} g:" << g << " h:" << h << "\n";
    string res, tmp;
    while (ss >> tmp) {
        res += tmp + " ";
    }
    return res;
}

bool operator==(const NPuzzleNode &a, const NPuzzleNode &b) {
    return a.getVal() == b.getVal();
}

void NPuzzleNode::setG(const dist_type g_) {
    g = g_;
}

void NPuzzleNode::setH(const dist_type h_) {
    h = h_;
}

void NPuzzleNode::setParent(const Direction &d) {
    parent = d;
}

NPuzzleNode::dist_type NPuzzleNode::getG() const {
    return g;
}

NPuzzleNode::dist_type NPuzzleNode::getH() const {
    return h;
}

NPuzzleNode::dist_type NPuzzleNode::getF() const {
    return g + h;
}

Direction NPuzzleNode::getParent() const {
    return parent;
}

NPuzzle::NPuzzle() {
}

NPuzzle::~NPuzzle() {
}

void NPuzzle::test() {
    cout << "Test N-Puzzle:\n\n";
    cin.clear();
    NPuzzleNode goal({9, 1, 2, 3, 4, 5, 6, 7, 8, 0}, 3, 3);
    for (int i = 1; i <= 4; ++i) {
        NPuzzleNode tmp = goal;
        auto direc = Direction(i);
        if (tmp.canMove(direc)) {
            tmp.move(direc);
            cout << tmp.toString() << endl;
        }
    }
}
