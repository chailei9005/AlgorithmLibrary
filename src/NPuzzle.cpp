#include "NPuzzle.h"
#include "RandomEngine.h"
#include "Timer.h"
#include "Algorithm.h"
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <cstdio>

using std::string;
using std::vector;
using std::stringstream;
using sl::NPuzzleNode;
using sl::NPuzzle;
using sl::Direction;
using sl::Timer;
using sl::Algorithm;

/*
N-Puzzle node definition.
*/

NPuzzleNode::~NPuzzleNode() {
}

NPuzzleNode::NPuzzleNode() {
}

NPuzzleNode::NPuzzleNode(const value_type &val_, const int row_, const int col_)
    : row(row_), col(col_) {
    init(val_);
}

void NPuzzleNode::init(const value_type &val_) {
    if (row < 2 || col < 2) {
        throw std::range_error("NPuzzleNode.init(): dimension is at least 2*2");
    }
    if (val_.size() != row * col) {
        throw std::range_error("NPuzzleNode.init(): value size must equal to (row * col)");
    }
    emptyPos = -1;
    for (unsigned i = 0; i < val_.size(); ++i) {
        if (val_[i] == 0) {
            emptyPos = i;  // Record index of value 0
        }
    }
    if (emptyPos == -1) {
        throw std::range_error("NPuzzleNode.init(): value 0 not found");
    }
    val = val_;
}

const NPuzzleNode::value_type& NPuzzleNode::getVal() const {
    return val;
}

void NPuzzleNode::move(const Direction &direc) {
    int displace;
    switch (direc) {
        case LEFT:
            displace = -1;
            break;
        case UP:
            displace = -col;
            break;
        case RIGHT:
            displace = 1;
            break;
        case DOWN:
            displace = col;
            break;
        case NONE:
        default:
            displace = 0;
            break;
    }
    int goalPos = emptyPos + displace;
    Algorithm::swap(val[emptyPos], val[goalPos]);
    emptyPos = goalPos;
}

bool NPuzzleNode::canMove(const Direction &direc) const {
    switch (direc) {
        case LEFT:
            return getCol(emptyPos) != 0;
        case UP:
            return getRow(emptyPos) != 0;
        case RIGHT:
            return getCol(emptyPos) != col - 1;
        case DOWN:
            return getRow(emptyPos) != row - 1;
        case NONE:
            return true;
        default:
            return false;
    }
}

NPuzzleNode::node_ptr NPuzzleNode::getAdjNode(const Direction &direc) const {
    if (!canMove(direc)) {
        return nullptr;
    } else {
        node_ptr n(new NPuzzleNode(*this));
        n->move(direc);
        return n;
    }
}

int NPuzzleNode::getRow(const int &i) const {
    return i / col;
}

int NPuzzleNode::getCol(const int &i) const {
    return i % col;
}

int NPuzzleNode::getSize() const {
    return val.size();
}

void NPuzzleNode::shuffle() {
    for (int i = 0; i < 1000; ++i) {
        Direction d = Direction(RandomEngine::randLib(1, 4));
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
    ss << "}";
    string res, tmp;
    while (ss >> tmp) {
        res += tmp;
    }
    return res;
}

unsigned NPuzzleNode::hash(const NPuzzleNode &n) {
    return (unsigned)Algorithm::cantorExpand(n.getSize(), n.getVal());
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

void NPuzzleNode::setG(const int g_) {
    g = g_;
}

void NPuzzleNode::setH(const int h_) {
    h = h_;
}

void NPuzzleNode::setParent(node_ptr p) {
    parent = p;
}

void NPuzzleNode::setDirection(const Direction &d) {
    direc = d;
}

int NPuzzleNode::getG() const {
    return g;
}

int NPuzzleNode::getH() const {
    return h;
}

int NPuzzleNode::getF() const {
    return g + h;
}

NPuzzleNode::node_ptr NPuzzleNode::getParent() const {
    return parent;
}

Direction NPuzzleNode::getDirection() const {
    return direc;
}


/*
N-Puzzle algorithm definition
*/

NPuzzle::NPuzzle(const node &src_, const node &des_)
    : src(src_), des(des_), closeList(100000, node::hash) {
}

NPuzzle::~NPuzzle() {
}

const std::list<Direction>& NPuzzle::getDirectionPath() const {
    return pathDirec;
}

const std::list<NPuzzle::node>& NPuzzle::getNodePath() const {
    return pathNode;
}

int NPuzzle::getSearchCount() const {
    return closeList.size();
}

void NPuzzle::setStartNode(const node &n) {
    src = n;
}

void NPuzzle::setEndNode(const node &n) {
    des = n;
}

void NPuzzle::init() {
    openList.clear();
    closeList.clear();
    pathDirec.clear();
    pathNode.clear();
    openList.push(src);
}

void NPuzzle::printSearchInfo(const node &cur) const {
    printf("Searching: %s G:%d H:%d F:%d total: %d\n",
           cur.toString().c_str(), cur.getG(), cur.getH(),
           cur.getF(), getSearchCount());
}

void NPuzzle::constructPath(const node &n) {
    pathNode.push_front(n);
    pathDirec.push_front(n.getDirection());
    node_ptr p = n.getParent();
    while (p) {
        pathNode.push_front(*p);
        pathDirec.push_front(p->getDirection());
        p = p->getParent();
    }
}

void NPuzzle::run() {
    init();
    node cur;
    while (!openList.empty()) {
        // Loop until the open list is empty or finding
        // a node that is not in the close list.
        do {
            cur = openList.top();
            openList.pop();
        } while (!openList.empty() && closeList.find(cur) != closeList.end());
        // If all the nodes in the open list is in the
        // close list, then there is no available path
        // between the two nodes.
        if (openList.empty() && closeList.find(cur) != closeList.end()) {
            break;
        }
        closeList.insert(cur);
        printSearchInfo(cur);
        if (cur == des) {  // Find destination
            constructPath(cur);
            break;
        }
        for (int i = 1; i <= 4; ++i) {  // Traverse adj
            Direction d = Direction(i);
            node_ptr adj = cur.getAdjNode(d);
            if (adj && closeList.find(*adj) == closeList.end()) {
                adj->setParent(node_ptr(new node(cur)));
                adj->setDirection(d);
                adj->setG(cur.getG() + 1);
                adj->setH(estimateH(*adj));
                openList.push(*adj);
            }
        }
    }
}

int NPuzzle::getEstimateDist(const node &n) const {
    const auto &val = n.getVal();
    const auto &desVal = des.getVal();
    const auto &size = n.getSize();

    // Sum up the distance of each element
    int manhatten = 0, geometric = 0;
    for (int i = 0; i < size; ++i) {
        if (val[i]) {  // Escape value 0
            int curR = n.getRow(i);
            int curC = n.getCol(i);
            int desR = n.getRow(val[i] - 1);
            int desC = n.getCol(val[i] - 1);
            int dR = curR > desR ? curR - desR : desR - curR;
            int dC = curC > desC ? curC - desC : desC - curC;
            manhatten += dR + dC;
            geometric += (int)(sqrt(dR * dR + dC * dC));
        }
    }
    return 1 * manhatten + 1 * geometric;
}

int NPuzzle::estimateH(const node &n) const {
    const auto &val = n.getVal();
    const auto &desVal = des.getVal();
    const auto &size = n.getSize();
    // Number of nodes whose next node is in a wrong position
    int s = 0;
    for (int i = 0; i < size - 1; i++) {
        if (val[i] + 1 != val[i + 1]) {
            s++;
        }
    }
    // Number of nodes which are in a wrong position
    int w = 0;
    for (int i = 0; i < size; ++i) {
        if (val[i] != desVal[i]) {
            ++w;
        }
    }
    // Estimate distance
    int d = getEstimateDist(n);
    return 50 * (1 * s + 1 * w + 3 * d);
}

void NPuzzle::test() {
    printf("Test N-Puzzle:\n\n");
    Timer timer;  // Record running time

    // 3*3
    //NPuzzle::node src({1, 5, 2, 7, 0, 4, 6, 3, 8}, 3, 3);
    //NPuzzle::node des({1, 2, 3, 4, 5, 6, 7, 8, 0}, 3, 3);

    // 4*4
    //NPuzzle::node src({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 15}, 4, 4);
    //NPuzzle::node des({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0}, 4, 4);

    // 4*5
    //NPuzzle::node src({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 0, 19}, 4, 5);
    //NPuzzle::node des({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 0}, 4, 5);

    // 5*4
    //NPuzzle::node src({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 0, 19}, 5, 4);
    //NPuzzle::node des({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 0}, 5, 4);

    // 5*5
    NPuzzle::node src({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 0, 24}, 5, 5);
    NPuzzle::node des({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 0}, 5, 5);

    // Rearrage
    src.shuffle();

    // Run
    NPuzzle puzzle(src, des);
    timer.reset();
    puzzle.run();

    // Get result
    auto time = timer.elapse();
    const auto &pathDirec = puzzle.getDirectionPath();
    const auto &pathNode = puzzle.getNodePath();

    // Print result
    printf("\nSearching finished.\n");
    printf(" Begin node: %s\n", src.toString().c_str());
    printf("   End node: %s\n", des.toString().c_str());
    printf("Time elapse: %.2lf ms\n", time);
    printf("Searched number: %d\n", puzzle.getSearchCount());
    printf("Path length: %d\n", (int)pathDirec.size());
    for (const auto &d : pathDirec) {
        src.move(d);
    }
    printf("Path correctness check: %s\n", src == des ? "pass" : "failed");
    printf("Path of directions:\n");
    for (const auto &d : pathDirec) {
        printf("%d ", d);
    }
    printf("\nPath of nodes:\n");
    //int cnt = 0, num = 53 / src.getSize();
    //for (const auto &d : pathNode) {
    //    printf("->%s", d.toString().c_str());
    //    if (++cnt % num == 0) {
    //        printf("\n");
    //    }
    //}
    printf("\n");
}
