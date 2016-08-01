#include "NPuzzle.h"
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <cstdio>

using std::string;
using std::vector;
using std::stringstream;
using std::shared_ptr;
using std::make_shared;
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
    parent = nullptr;
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

NPuzzleNode::node_ptr NPuzzleNode::getAdjNode(const Direction &direc) const {
    if (!canMove(direc)) {
        return nullptr;
    }
    node_ptr res = make_shared<NPuzzleNode>(*this);
    res->move(direc);
    return res;
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

int NPuzzleNode::getRow() const {
    return row;
}

int NPuzzleNode::getRow(const int &index) const {
    return (index - 1) / col;
}

int NPuzzleNode::getCol() const {
    return col;
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
    ss << "} g:" << g << " h:" << h;
    string res, tmp;
    while (ss >> tmp) {
        res += tmp + " ";
    }
    return res;
}

unsigned NPuzzleNode::hash(const node_ptr &p) {
    std::hash<int> h;
    return p->val[0] * h(p->val[p->row * p->col / 2]);
}

bool NPuzzleNode::operator==(const NPuzzleNode &a) const {
    return getVal() == a.getVal();
}

bool NPuzzleNode::operator<(const NPuzzleNode &a) const {
    return getF() < a.getF();
}

bool NPuzzleNode::operator>(const NPuzzleNode &a) const {
    return getF() > a.getF();
}

bool NPuzzleNode::operator<=(const NPuzzleNode &a) const {
    return getF() <= a.getF();
}

bool NPuzzleNode::operator>=(const NPuzzleNode &a) const {
    return getF() >= a.getF();
}

void NPuzzleNode::setG(const dist_type g_) {
    g = g_;
}

void NPuzzleNode::setH(const dist_type h_) {
    h = h_;
}

void NPuzzleNode::setParent(const node_ptr &p) {
    parent = p;
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

NPuzzleNode::node_ptr NPuzzleNode::getParent() const {
    return parent;
}

NPuzzle::NPuzzle(const node_ptr &src_, const node_ptr &des_)
    : src(src_), des(des_), searchNodeCnt(0), closeList(100, NPuzzleNode::hash) {
}

NPuzzle::~NPuzzle() {
}

void NPuzzle::run() {
    src->setG(0);
    openList.push(src);
    while (!openList.empty()) {
        // Loop until the open list is empty or finding
        // a node that is not in the close list.
        node_ptr cur;
        do {
            cur = openList.top();
            openList.pop();
        } while (!openList.empty() && closeList.find(cur) != closeList.end());

        // If all the nodes on the map is in the close list,
        // then there is no available path between the two
        // nodes.
        if (openList.empty() && closeList.find(cur) != closeList.end()) {
            break;
        }

        ++searchNodeCnt;
        printSearchInfo(cur);

        if (*cur == *des) {
            //constructPath();
            break;
        }

        closeList.insert(cur);
        for (int i = 1; i <= 4; ++i) {
            Direction d = static_cast<Direction>(i);
            auto adj = cur->getAdjNode(d);
            if (adj && closeList.find(adj) == closeList.end()) {
                adj->setParent(cur);
                adj->setG(cur->getG() + 1);
                adj->setH(estimateH(adj));
                openList.push(adj);
            }
        }
    }
}

void NPuzzle::printSearchInfo(const node_ptr &cur) const {
    printf("Current node: %s ", cur->toString().c_str());
    printf("searched number: %lld\n", searchNodeCnt);
}

NPuzzleNode::dist_type NPuzzle::estimateH(const node_ptr &n) const {
    int s = 0;  // Number of nodes whose next node is in wrong position
    int rows = n->getRow(), cols = n->getCol();
    for (int i = 1; i < rows * cols; ++i) {
        if (n->getVal()[i] + 1 != n->getVal()[i + 1]) {
            ++s;
        }
    }
    return s;
}

void NPuzzle::test() {
    printf("Test N-Puzzle:\n\n");
    auto src = shared_ptr<NPuzzleNode>(new NPuzzleNode({5, 1, 2, 3, 4, 0, 6, 7, 5, 8}, 3, 3));
    auto des = shared_ptr<NPuzzleNode>(new NPuzzleNode({9, 1, 2, 3, 4, 5, 6, 7, 8, 0}, 3, 3));
    NPuzzle(src, des).run();
}
