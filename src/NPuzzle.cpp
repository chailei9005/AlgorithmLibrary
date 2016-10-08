#include "NPuzzle.h"
#include "Random.h"
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

NPuzzleNode::~NPuzzleNode() {
}

NPuzzleNode::NPuzzleNode() {
}

NPuzzleNode::NPuzzleNode(const std::vector<int> &val_, const int row_, const int col_)
    : row(row_), col(col_) {
    init(val_);
}

void NPuzzleNode::init(const std::vector<int> &val_) {
    if (row < 2 || col < 2) {
        throw std::range_error("NPuzzleNode.init(): dimension is at least 2*2");
    }
    if ((int)val_.size() != row * col) {
        throw std::range_error("NPuzzleNode.init(): value size must equal to (row * col)");
    }
    emptyPos = -1;
    for (unsigned i = 0; i < val_.size(); ++i) {
        if (val_[i] == 0) {
            emptyPos = i;
        }
    }
    if (emptyPos == -1) {
        throw std::range_error("NPuzzleNode.init(): value 0 not found");
    }
    val = val_;
}

const std::vector<int>& NPuzzleNode::getVal() const {
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

NPuzzleNode* NPuzzleNode::getNeighbor(const Direction &direc) const {
    NPuzzleNode* n = new NPuzzleNode(*this);
    n->move(direc);
    return n;
}

NPuzzleNode* NPuzzleNode::getMinNeighbor(const NPuzzleNode *const des) const {
    vector<NPuzzleNode*> neighbors;
    NPuzzleNode *res = nullptr;
    int min = 2147483647;
    for (int i = 1; i <= 4; ++i) {
        auto direc = static_cast<Direction>(i);
        if (canMove(direc)) {
            NPuzzleNode *tmp = getNeighbor(direc);
            neighbors.push_back(tmp);
            auto h = tmp->getHeuristic(des);
            if (h < min) {
                min = h;
                res = tmp;
            }
        }
    }
    for (unsigned i = 0; i < neighbors.size(); ++i) {
        if (neighbors[i] != res) {
            delete neighbors[i];
            neighbors[i] = nullptr;
        }
    }
    return res;
}

NPuzzleNode* NPuzzleNode::getRandNeighbor() const {
    Direction direc;
    do {
        direc = static_cast<Direction>(Random::getInstance()->randLib(1, 4));
    } while (!canMove(direc));
    return getNeighbor(direc);
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
        Direction d = Direction(Random::getInstance()->randLib(1, 4));
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

unsigned long long NPuzzleNode::hash() const {
    return Algorithm::cantorExpand(val.size(), val);
    //return std::hash<string>()(toString());
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

void NPuzzleNode::setParent(NPuzzleNode* p) {
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

NPuzzleNode* NPuzzleNode::getParent() const {
    return parent;
}

Direction NPuzzleNode::getDirection() const {
    return direc;
}

NPuzzle::NPuzzle(const NPuzzleNode &src_, const NPuzzleNode &des_)
    : src(src_), des(des_), closeList(1000000, [](const NPuzzleNode *const &x) { return x->hash(); }) {
}

NPuzzle::~NPuzzle() {
}

const std::list<Direction>& NPuzzle::getDirectionPath() const {
    return pathDirec;
}

const std::list<NPuzzleNode>& NPuzzle::getNodePath() const {
    return pathNode;
}

int NPuzzle::getSearchCount() const {
    return searchedCnt;
}

const NPuzzleNode& NPuzzle::getSrc() const {
    return src;
}

const NPuzzleNode& NPuzzle::getDes() const {
    return des;
}

void NPuzzle::setStartNode(const NPuzzleNode &n) {
    src = n;
}

void NPuzzle::setEndNode(const NPuzzleNode &n) {
    des = n;
}

void NPuzzle::printSearchInfo(const NPuzzleNode *const cur) const {
    printf("Searching: %s G:%d H:%d F:%d Total nodes: %d\n",
           cur->toString().c_str(), cur->getG(), cur->getH(),
           cur->getF(), getSearchCount());
}

void NPuzzle::setNodePathEnable(const bool e) {
    nodePathEnable = e;
}

void NPuzzle::setDirecPathEnable(const bool e) {
    direcPathEnable = e;
}

void NPuzzle::setSearchDetailEnable(const bool e) {
    searchDetailEnable = e;
}

void NPuzzle::solveWithAStar() {
    searchedCnt = 0;
    openList.push(&src);
    while (!openList.empty()) {

        // Loop until the open list is empty or finding
        // a node that is not in the close list.
        NPuzzleNode *cur = nullptr;
        do {
            cur = openList.top();
            openList.pop();
        } while (!openList.empty() && isVisit(cur));

        // If all the nodes in the open list is in the
        // close list, then there is no available path
        // between the two nodes.
        if (openList.empty() && isVisit(cur)) {
            return;
        }

        ++searchedCnt;
        closeList.insert(cur);
        if (searchDetailEnable) {
            printSearchInfo(cur);
        }

        if (*cur == des) {
            constructPath(cur);
            freeResources();
            return;
        }

        for (int i = 1; i <= 4; ++i) {
            Direction d = Direction(i);
            if (cur->canMove(d)) {
                NPuzzleNode *adj = cur->getNeighbor(d);
                alloc.push_back(adj);
                if (!isVisit(adj)) {
                    adj->setParent(cur);
                    adj->setDirection(d);
                    adj->setG(cur->getG() + 1);
                    adj->setH(adj->getHeuristic(&des));
                    openList.push(adj);
                }
            }
        }
    }
}

NPuzzleNode NPuzzle::solveWithSteepestHillClimb() {
    NPuzzleNode *cur = &src;
    while (1) {
        NPuzzleNode *next = cur->getMinNeighbor(&des);
        alloc.push_back(next);
        if (next->getHeuristic(&des) >= cur->getHeuristic(&des)) {
            auto node = *cur;
            freeResources();
            return node;
        }
        cur = next;
    }
}

NPuzzleNode NPuzzle::solveWithFirstChoicetHillClimb() {
    NPuzzleNode *cur = &src;
    while (1) {
        int cnt = 0;
        auto h = cur->getHeuristic(&des);
        while (1) {
            NPuzzleNode *next = cur->getRandNeighbor();
            alloc.push_back(next);
            if (next->getHeuristic(&des) < h) {
                cur = next;
                break;
            }
            if (++cnt >= 8) {  // Maximum iterate times
                auto node = *cur;
                freeResources();
                return node;
            }
        }
    }
}

NPuzzleNode NPuzzle::solveWithSA() {
    NPuzzleNode *cur = &src;
    double temperature = 50;
    while (1) {
        temperature *= 0.95;
        if (temperature < 1e-9) {
            auto node = *cur;
            freeResources();
            return node;
        }
        NPuzzleNode *next = cur->getRandNeighbor();
        alloc.push_back(next);
        int delta = next->getHeuristic(&des) - cur->getHeuristic(&des);
        if (delta < 0) {
            cur = next;
        } else {
            double p = exp(-delta / temperature);
            double num = Random::getInstance()->randLib(1, 100);
            if (num <= 100 * p) {
                cur = next;
            }
        }
    }
}

void NPuzzle::constructPath(const NPuzzleNode *n) {
    pathNode.clear();
    pathDirec.clear();
    while (n) {
        if (nodePathEnable) {
            pathNode.push_front(*n);
        }
        if (direcPathEnable) {
            pathDirec.push_front(n->getDirection());
        }
        n = n->getParent();
    }
}

void NPuzzle::freeResources() {
    for (NPuzzleNode *n : alloc) {
        delete n;
    }
    alloc.clear();
    openList.clear();
    closeList.clear();
}

bool NPuzzle::isVisit(NPuzzleNode *const n) const {
    return closeList.has(n);
    //return closeList.find(n) != closeList.end();  // STL version
}

int NPuzzleNode::getHeuristic(const NPuzzleNode *const des) const {
    const auto &desVal = des->getVal();
    const auto &size = getSize();

    // Number of nodes which are in a wrong position
    int wrong = 0;
    for (int i = 0; i < size; ++i) {
        if (val[i] != desVal[i]) {
            ++wrong;
        }
    }

    // Sum up the distance of each element
    int manhatten = 0, geometric = 0;
    for (int i = 0; i < size; ++i) {
        if (val[i]) {  // Escape value 0
            int curR = getRow(i);
            int curC = getCol(i);
            int desR = getRow(val[i] - 1);
            int desC = getCol(val[i] - 1);
            int dR = curR > desR ? curR - desR : desR - curR;
            int dC = curC > desC ? curC - desC : desC - curC;
            manhatten += dR + dC;
            geometric += (int)(sqrt(dR * dR + dC * dC));
        }
    }

    //return 5 * (1 * wrong + 2 * manhatten + 1 * geometric);
    return 1 * (0 * wrong + 1 * manhatten + 0 * geometric);
}

void NPuzzle::test() {
    printf("Test N-Puzzle:\n\n");

#define ORDER 3

#if ORDER == 2  // 2*2

    NPuzzleNode src({1, 2, 0, 3}, 2, 2);
    NPuzzleNode des({1, 2, 3, 0}, 2, 2);

#elif ORDER == 3  // 3*3

    NPuzzleNode src({1, 2, 3, 4, 5, 6, 7, 0, 8}, 3, 3);
    NPuzzleNode des({1, 2, 3, 4, 5, 6, 7, 8, 0}, 3, 3);

#elif ORDER == 4  // 4*4

    NPuzzleNode src({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 15}, 4, 4);
    NPuzzleNode des({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0}, 4, 4);

#elif ORDER == 5  // 5*5

    NPuzzleNode src({14, 0, 24, 13, 23, 21, 20, 22, 18, 11, 6, 1, 16, 3, 10, 7, 17, 4, 8, 2, 9, 15, 19, 5, 12}, 5, 5);
    NPuzzleNode des({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 0}, 5, 5);

#endif

    // Rearrage
    src.shuffle();

    // Create a puzzle calculator
    NPuzzle puzzle(src, des);
    puzzle.setSearchDetailEnable(false);
    puzzle.setDirecPathEnable(true);
    puzzle.setNodePathEnable(false);

    const int caseCnt = 1000;
    testWithCases(puzzle, caseCnt, [&]() { return puzzle.solveWithSteepestHillClimb(); }, "steepest hill climbing");
    testWithCases(puzzle, caseCnt, [&]() { return puzzle.solveWithFirstChoicetHillClimb(); }, "first choice hill climbing");
    testWithCases(puzzle, caseCnt, [&]() { return puzzle.solveWithSA(); }, "simulated annealing");
    testAStar(puzzle);
}

void NPuzzle::testWithCases(NPuzzle &puzzle, const int caseCnt,
                            const std::function<NPuzzleNode(void)> &f,
                            const std::string &info) {
    NPuzzleNode src = puzzle.getSrc();
    NPuzzleNode des = puzzle.getDes();
    Timer timer;
    double time = 0;
    int sucCnt = 0;
    printf("Compute using %s...\n", info.c_str());
    for (int i = 0; i < caseCnt; ++i) {
        timer.reset();
        NPuzzleNode tmp = f();
        time += timer.elapse();
        if (tmp == des) {
            ++sucCnt;
        }
    }
    printf("Compute finished.\n");
    printf("  Begin node: %s\n", src.toString().c_str());
    printf("    End node: %s\n", des.toString().c_str());
    printf(" Case amount: %d\n", caseCnt);
    printf("Success rate: %.3lf%%\n", 100 * (double)sucCnt / caseCnt);
    printf("   Time cost: %.2lf ms/case\n\n", time / caseCnt);
}

void NPuzzle::testAStar(NPuzzle &puzzle) {
    NPuzzleNode src = puzzle.getSrc();
    NPuzzleNode des = puzzle.getDes();
    printf("Compute using A* searching...\n");
    Timer timer;
    puzzle.solveWithAStar();
    auto time = timer.elapse();
    auto pathDirec = puzzle.getDirectionPath();
    auto pathNode = puzzle.getNodePath();
    printf("Compute finished.\n");
    printf("    Begin node: %s\n", src.toString().c_str());
    printf("      End node: %s\n", des.toString().c_str());
    printf("     Time cost: %.2lf ms\n", time);
    printf("Searched nodes: %d\n", puzzle.getSearchCount());
    printf("Search Efficency: %.2lf nodes/ms\n", puzzle.getSearchCount() / time);
    printf("Path length: %d\n", (int)pathDirec.size());
    for (const auto &d : pathDirec) {
        src.move(d);
    }
    printf("Path correctness check: %s\n", src == des ? "pass" : "failed");
    printf("Path of directions: (0->none, 1->left, 2->up, 3->right, 4->down)\n");
    int cnt = 0;
    for (const auto &d : pathDirec) {
        if (cnt++) printf(",");
        printf("%d", d);
    }
    printf("\nPath of nodes:\n");
    int num = 53 / src.getSize();
    cnt = 0;
    for (const auto &d : pathNode) {
        printf("->%s", d.toString().c_str());
        if (++cnt % num == 0) {
            printf("\n");
        }
    }
    printf("\n");
}
