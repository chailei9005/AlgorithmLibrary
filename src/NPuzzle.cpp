#include "NPuzzle.h"
#include "RandomEngine.h"
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <cstdio>
#include <cmath>

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
    direc = NONE;
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

void NPuzzleNode::shuffle() {
    for (int i = 0; i < 300; ++i) {
        Direction d = static_cast<Direction>(RandomEngine::randLib(1, 4));
        if (canMove(d)) {
            move(d);
        }
    }
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

unsigned NPuzzleNode::hash(const node_ptr p) {
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

void NPuzzleNode::setParent(const node_ptr p) {
    parent = p;
}

void NPuzzleNode::setDirection(const Direction &d) {
    direc = d;
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

Direction NPuzzleNode::getDirection() const {
    return direc;
}

NPuzzle::NPuzzle(const node_ptr src_, const node_ptr des_)
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
            des = cur;
            constructPath();
            break;
        }

        closeList.insert(cur);
        for (int i = 1; i <= 4; ++i) {
            Direction d = static_cast<Direction>(i);
            auto adj = cur->getAdjNode(d);
            if (adj && closeList.find(adj) == closeList.end()) {
                adj->setParent(cur);
                adj->setDirection(d);
                adj->setG(cur->getG() + 1);
                adj->setH(estimateH(adj));
                openList.push(adj);
            }
        }
    }
}

void NPuzzle::constructPath() {
    path.clear();
    node_ptr tmp = des, p = nullptr;
    while (p = tmp->getParent()) {
        path.push_front(tmp->getDirection());
        tmp = p;
    }
}

void NPuzzle::printSearchInfo(const node_ptr cur) const {
    printf("Current node: %s ", cur->toString().c_str());
    printf("searched number: %lld\n", searchNodeCnt);
}

int NPuzzle::getManhattenDist(const node_ptr n) const {
    // Sum up the manhatten distance of each value
    int dist = 0;
    auto rows = n->getRow(), cols = n->getCol();
    const auto &val = n->getVal();
    for (int i = 1; i <= rows * cols; ++i) {
        if (val[i]) {  // Escape value 0
            int curR = n->getRow(i);
            int curC = n->getCol(i);
            int desR = n->getRow(val[i]);
            int desC = n->getCol(val[i]);
            int dR = abs(curR - desR);
            int dC = abs(curC - desC);
            dist += dR + dC;
        }
    }
    return dist;
}

int NPuzzle::getGeometricDist(const node_ptr n) const {
    // Sum up the geometric distance of each value
    int dist = 0;
    auto rows = n->getRow(), cols = n->getCol();
    const auto &val = n->getVal();
    for (int i = 1; i <= rows * cols; ++i) {
        if (val[i]) {  // Escape value 0
            int curR = n->getRow(i);
            int curC = n->getCol(i);
            int desR = n->getRow(val[i]);
            int desC = n->getCol(val[i]);
            int dR = abs(curR - desR);
            int dC = abs(curC - desC);
            dist += static_cast<int>(sqrt(dR * dR + dC * dC));
        }
    }
    return dist;
}

NPuzzleNode::dist_type NPuzzle::estimateH(const node_ptr n) const {
    const auto &val = n->getVal();
    const auto &desVal = des->getVal();
    auto rows = n->getRow(), cols = n->getCol();

    // Number of nodes which are in a wrong position
    int w = 0;
    for (int i = 1; i <= rows * cols; ++i) {
        if (val[i] != desVal[i]) {
            ++w;
        }
    }

    int m = getManhattenDist(n);
    int g = getGeometricDist(n);

    return 1 * w + 1 * m + 1 * g;
}

const std::list<Direction>& NPuzzle::getPath() const {
    return path;
}

void NPuzzle::test() {
    printf("Test N-Puzzle:\n\n");

    // 3*3
    auto src = shared_ptr<NPuzzleNode>(new NPuzzleNode(
               {4, 1, 2, 3, 0, 4, 6, 7, 5, 8}, 3, 3));
    auto des = shared_ptr<NPuzzleNode>(new NPuzzleNode(
               {9, 1, 2, 3, 4, 5, 6, 7, 8, 0}, 3, 3));

    // 4*4
    //auto src = shared_ptr<NPuzzleNode>(new NPuzzleNode(
    //           {15, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 15}, 4, 4));
    //auto des = shared_ptr<NPuzzleNode>(new NPuzzleNode(
    //           {16, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0}, 4, 4));

    // 5*5
    //auto src = shared_ptr<NPuzzleNode>(new NPuzzleNode(
    //           {24, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 0, 24}, 5, 5));
    //auto des = shared_ptr<NPuzzleNode>(new NPuzzleNode(
    //           {25, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 0}, 5, 5));

    // Rearrage
    src->shuffle();

    NPuzzle puzzle(src, des);
    puzzle.run();
    // Print path
    auto path = puzzle.getPath();
    printf("\nPath: (length: %d)\n", int(path.size()));
    for (const auto &d : path) {
        switch (d) {
            case LEFT:
                printf("L ");
                break;
            case UP:
                printf("U ");
                break;
            case RIGHT:
                printf("R ");
                break;
            case DOWN:
                printf("D ");
                break;
            default:
                break;
        }
    }
    printf("\n");
    // Test path correctness
    for (const auto &d : path) {
        src->move(d);
    }
    bool suc = (*src == *des);
    printf("Path correctness test: %s\n", suc ? "pass" : "failed");
}
