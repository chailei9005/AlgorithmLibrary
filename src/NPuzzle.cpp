#include "NPuzzle.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::stringstream;
using sl::NPuzzleNode;
using sl::NPuzzle;

NPuzzleNode::NPuzzleNode() {
}

NPuzzleNode::NPuzzleNode(const value_type &val_,
                         const unsigned row_,
                         const unsigned col_) {
    checkValid(val_, row_, col_);
    val = val_;
    row = row_;
    col = col_;
}

NPuzzleNode::~NPuzzleNode() {
}

void NPuzzleNode::checkValid(const value_type &val_,
                             const unsigned row_,
                             const unsigned col_) const {
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
    val = val_;
}

const NPuzzleNode::value_type& NPuzzleNode::getVal() const {
    return val;
}

void NPuzzleNode::move(const Direction &direc) {
    int goal = getIndex(direc);
    unsigned cur = val[0];
    unsigned tmp = val[cur];
    val[cur] = val[goal];
    val[goal] = tmp;
    val[0] = goal;
}

void NPuzzleNode::getAllAdjNodes(std::vector<NPuzzleNode> &adjNodes) const {
    adjNodes.clear();
    for (int i = 0; i < 4; ++i) {
        Direction d = static_cast<Direction>(i);
        if (hasAdjNode(d)) {
            adjNodes.push_back(getAdjNode(d));
        }
    }
}

NPuzzleNode NPuzzleNode::getAdjNode(const Direction &direc) const {
    auto res = *this;
    res.move(direc);
    return res;
}

bool NPuzzleNode::hasAdjNode(const Direction &direc) const {
    return getIndex(direc) != -1;
}

int NPuzzleNode::getIndex(const Direction &direc) const {
    int res, d;
    switch (direc) {
        case LEFT:
            d = -1;
            break;
        case UP:
            d = -static_cast<int>(col);
            break;
        case RIGHT:
            d = 1;
            break;
        case DOWN:
            d = col;
            break;
        default:
            break;
    }
    res = val[0] + d;
    if (!(res >= 1 && res <= static_cast<int>(row * col))) {
        res = -1;
    } else if ((d == -1 || d == 1) && (getRow(val[0]) != getRow(res))) {
        res = -1;
    }
    return res;
}

unsigned NPuzzleNode::getRow(const unsigned &index) const {
    return (index - 1) / col;
}

unsigned NPuzzleNode::getCol(const unsigned &index) const {
    return (index - 1) % col;
}

string NPuzzleNode::toString() const {
    stringstream ss;
    ss << "{";
    for (unsigned i = 0; i < val.size(); ++i) {
        if (i) ss << ",";
        ss << val[i];
    }
    ss << "}";
    string res;
    ss >> res;
    return res;
}

NPuzzle::NPuzzle() {
}

NPuzzle::~NPuzzle() {
}

void NPuzzle::test() {
    cout << "Test N-Puzzle:\n\n";
    cin.clear();
    NPuzzleNode goal({8, 1, 2, 3, 4, 5, 6, 7, 0}, 2, 4);
    vector<NPuzzleNode> adjs;
    auto node = goal.getAdjNode(NPuzzleNode::Direction(1)).getAdjNode(NPuzzleNode::Direction(0));
    node.getAllAdjNodes(adjs);
    for (const auto &n : adjs) {
        cout << n.toString() << endl;
    }
}
