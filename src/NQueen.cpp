#include "NQueen.h"
#include "Timer.h"
#include "Random.h"
#include <cstdio>
#include <stdexcept>
#include <sstream>
#include <cmath>

using std::string;
using std::vector;
using std::ostringstream;
using sl::NQueenNode;
using sl::NQueen;

NQueenNode::~NQueenNode() {
}

NQueenNode::NQueenNode() {
}

NQueenNode::NQueenNode(const std::vector<int> &val_)
    : size(val_.size()) {
    checkValid(val_);
    val = val_;
}

void NQueenNode::checkValid(const std::vector<int> &val_) const {
    for (const auto &v : val_) {
        if (!(v >= -1 && v < size)) {
            throw std::range_error("NQueenNode.checkValid(): invalid node value");
        }
    }
}

int NQueenNode::conflictCount() const {
    int cnt = 0;
    for (auto i = 0; i < size; ++i) {
        for (auto j = i + 1; j < size; ++j) {
            if (val[i] != -1 && val[j] != -1 && hasConflict(i, j)) {
                ++cnt;
            }
        }
    }
    return cnt;
}

bool NQueenNode::hasConflict(const int row1, const int row2) const {
    // Conflict if same column or diagnose
    return row1 != row2 && (val[row1] == val[row2]
        || abs(row1 - row2) == abs(val[row1] - val[row2]));
}

NQueenNode NQueenNode::getMinConflictNeighbor() const {
    NQueenNode res = *this, tmp = *this;
    auto min = conflictCount();
    for (auto row = 0; row < size; ++row) {
        for (auto col = 0; col < size; ++col) {
            if (col != val[row]) {
                tmp[row] = col;
                auto cnt = tmp.conflictCount();
                if (cnt < min) {
                    min = cnt;
                    res = tmp;
                }
            }
        }
        tmp[row] = val[row];
    }
    return res;
}

NQueenNode NQueenNode::getRandNeighbor() const {
    int desCol = -1, row = Random::getInstance()->randLib(0, size - 1);
    while (1) {
        desCol = Random::getInstance()->randLib(0, size - 1);
        if (val[row] != desCol) {
            break;
        }
    }
    auto res = *this;
    res[row] = desCol;
    return res;
}

string NQueenNode::toString() const {
    ostringstream oss;
    oss << "{";
    for (auto i = 0; i < size; ++i) {
        if (i) oss << ",";
        oss << val[i];
    }
    oss << "}";
    return oss.str();
}

string NQueenNode::toPrettyString() const {
    ostringstream oss;
    for (auto i = 0; i < size; ++i) {
        for (auto j = 0; j < size; ++j) {
            if (val[i] == j) {
                oss << 'X';
            } else {
                oss << '-';
            }
        }
        if (i != size - 1) {
            oss << '\n';
        }
    }
    return oss.str();
}

int& NQueenNode::operator[](const int i) {
    return val[i];
}

const int& NQueenNode::operator[](const int i) const {
    return val[i];
}

int NQueenNode::getSize() const {
    return size;
}

NQueenNode NQueenNode::getRandNode(const int size) {
    vector<int> val_(size, 0);
    for (auto &x : val_) {
        x = Random::getInstance()->randLib(0, size - 1);
    }
    return NQueenNode(val_);
}

void NQueen::solveWithEnumeration(const int n, vector<NQueenNode> &res) {
    res.clear();
    NQueenNode start(vector<int>(n, -1));
    enumerate(start, 0, res);
}

bool NQueen::enumerate(NQueenNode &node, const int row, vector<NQueenNode> &res) {
    auto size = node.getSize();
    if (row == size) {
        res.push_back(node);
        return true;
    } else {
        for (auto col = 0; col < size; ++col) {
            node[row] = col;
            bool conflict = false;
            for (auto i = 0; i < row; ++i) {
                if (node.hasConflict(i, row)) {
                    conflict = true;
                    break;
                }
            }
            if (!conflict && enumerate(node, row + 1, res)) {
                // Comment the line below to get all solutions, otherwise get only one solution
                //return true;
            }
        }
        return false;
    }
}

NQueenNode NQueen::solveWithSteepestHillClimb(const NQueenNode &start) {
    auto cur = start;
    while (1) {
        auto next = cur.getMinConflictNeighbor();
        if (next.conflictCount() >= cur.conflictCount()) {
            return next;
        }
        cur = next;
    }
}

NQueenNode NQueen::solveWithFirstChoiceHillClimb(const NQueenNode &start) {
    auto size = start.getSize();
    auto cur = start;
    while (1) {
        int cnt = 0;
        auto curConflict = cur.conflictCount();
        while (1) {
            auto next = cur.getRandNeighbor();
            if (next.conflictCount() < curConflict) {
                cur = next;
                break;
            }
            if (++cnt >= size * size * 2) {  // Maximum iterate times
                return cur;
            }
        }
    }
}

NQueenNode NQueen::solveWithRandRestartHillClimb(const NQueenNode &start) {
    auto size = start.getSize();
    int cnt = 0;
    while (1) {
        auto res = NQueen::solveWithSteepestHillClimb(NQueenNode::getRandNode(size));
        if (res.conflictCount() == 0) {
            return res;
        }
        if (++cnt >= 50) {  // Maximum iterate times
            return res;
        }
    }
}

NQueenNode NQueen::solveWithSA(const NQueenNode &start) {
    auto cur = start;
    double temperature = 50;
    while (1) {
        temperature *= 0.95;
        if (temperature < 1e-9) {
            return cur;
        }
        auto next = cur.getRandNeighbor();
        int delta = next.conflictCount() - cur.conflictCount();
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

void NQueen::testWithCases(const int size, const int caseCnt,
                           const std::function<NQueenNode(void)> &f,
                           const std::string &info) {
    Timer timer;
    printf("\nCompute using %s...\n", info.c_str());
    double time = 0;
    int sucCnt = 0;
    NQueenNode resNode = vector<int>(size, -1);
    for (int i = 0; i < caseCnt; ++i) {
        timer.reset();
        auto tmp = f();
        time += timer.elapse();
        if (tmp.conflictCount() == 0) {
            resNode = tmp;
            ++sucCnt;
        }
    }
    printf("Compute finished.\n");
    printf(" Case amount: %d\n", caseCnt);
    printf("Success rate: %.2lf%%\n", 100 * (double)sucCnt / caseCnt);
    printf("   Time cost: %.2lf ms/case\n", time / caseCnt);
    printf("One solution: (conflict amount: %d)\n", resNode.conflictCount());
    printf("%s\n%s\n", resNode.toPrettyString().c_str(), resNode.toString().c_str());
}

void NQueen::testEnumeration(const int size) {
    printf("\nCompute using enumeration...\n");
    vector<NQueenNode> resList;
    Timer timer;
    NQueen::solveWithEnumeration(size, resList);
    auto time = timer.elapse();
    printf("Compute finished.\n");
    printf("Time cost: %.2lf ms\n", time);
    printf("Solution amount: %d\n", (int)resList.size());
    printf("One solution:");
    for (unsigned i = 0; i < 1; ++i) {  // Only print one solutions
        printf("\nAnswer #%d: (conflict amount: %d)\n", i + 1, resList[i].conflictCount());
        printf("%s\n%s\n", resList[i].toPrettyString().c_str(), resList[i].toString().c_str());
    }
}

void NQueen::test() {
    printf("Test N-Queen:\n\n");
    int n;
    printf("Input queens amount n(n>=4): ");
    if (scanf("%d", &n) != 1 || n < 4) {
        printf("Input format error.\n");
        return;
    }

    const int caseCnt = 500;
    testWithCases(n, caseCnt, [&]() { return NQueen::solveWithSteepestHillClimb(NQueenNode::getRandNode(n)); }, "steepest hill climbing");
    testWithCases(n, caseCnt, [&]() { return NQueen::solveWithFirstChoiceHillClimb(NQueenNode::getRandNode(n)); }, "first choice hill climbing");
    testWithCases(n, caseCnt, [&]() { return NQueen::solveWithRandRestartHillClimb(NQueenNode::getRandNode(n)); }, "random restart hill climbing");
    testWithCases(n, caseCnt, [&]() { return NQueen::solveWithSA(NQueenNode::getRandNode(n)); }, "simulated annealing");
    testEnumeration(n);
}
