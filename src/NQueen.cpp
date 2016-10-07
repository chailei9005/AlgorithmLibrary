#include "NQueen.h"
#include "Timer.h"
#include "RandomEngine.h"
#include <cstdio>
#include <stdexcept>
#include <sstream>

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

unsigned NQueenNode::conflictCount() const {
    unsigned cnt = 0;
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
    unsigned min = conflictCount();
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
    int desCol = -1, row = RandomEngine::randLib(0, size - 1);
    while (1) {
        desCol = RandomEngine::randLib(0, size - 1);
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
        x = RandomEngine::randLib(0, size - 1);
    }
    return NQueenNode(val_);
}

void NQueen::solveWithEnumeration(const int n, vector<NQueenNode> &res) {
    res.clear();
    NQueenNode start(vector<int>(n, -1));
    enumerate(start, 0, res);
}

void NQueen::enumerate(NQueenNode &node, const int row, vector<NQueenNode> &res) {
    auto size = node.getSize();
    if (row == size) {
        res.push_back(node);
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
            if (!conflict) {
                enumerate(node, row + 1, res);
            }
        }
    }
}

NQueenNode NQueen::solveWithSteepestHillClimb(const NQueenNode &start) {
    NQueenNode cur = start;
    while (1) {
        auto min = cur.getMinConflictNeighbor();
        if (min.conflictCount() >= cur.conflictCount()) {
            return cur;
        }
        cur = min;
    }
}

NQueenNode NQueen::solveWithFirstChoiceHillClimb(const NQueenNode &start) {
    auto size = start.getSize();
    NQueenNode cur = start;
    while (1) {
        int cnt = 0;
        auto curConflict = cur.conflictCount();
        while (1) {
            auto min = cur.getRandNeighbor();
            if (min.conflictCount() < curConflict) {
                cur = min;
                break;
            }
            if (++cnt >= size * size * 2) {  // Maximum iterate times
                return cur;
            }
        }
    }
}

NQueenNode NQueen::solveWithRandRestartHillClimb(const int n) {
    int cnt = 0;
    while (1) {
        auto res = NQueen::solveWithSteepestHillClimb(NQueenNode::getRandNode(n));
        if (res.conflictCount() == 0) {
            return res;
        }
        if (++cnt >= 50) {  // Maximum iterate times
            return res;
        }
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
    Timer timer;
    NQueenNode node(vector<int>(n, -1));

    // Steepest hill climbing
    printf("\nCompute using steepest hill climbing...\n");
    double time = 0;
    int sucCnt = 0;
    for (int i = 0; i < caseCnt; ++i) {
        timer.reset();
        auto tmp = NQueen::solveWithSteepestHillClimb(NQueenNode::getRandNode(n));
        time += timer.elapse();
        if (tmp.conflictCount() == 0) {
            node = tmp;
            ++sucCnt;
        }
    }
    printf("Compute finished.\n");
    printf("Case amount: %d\n", caseCnt);
    printf("Success rate: %.2lf%%\n", 100 * (double)sucCnt / caseCnt);
    printf("Average time elapse: %.3lf ms\n", time / caseCnt);
    printf("One solution: (conflict amount: %d)\n", node.conflictCount());
    printf("%s\n%s\n", node.toPrettyString().c_str(), node.toString().c_str());

    // First choice hill climbing
    printf("\nCompute using first choice hill climbing...\n");
    time = sucCnt = 0;
    for (int i = 0; i < caseCnt; ++i) {
        timer.reset();
        auto tmp = NQueen::solveWithFirstChoiceHillClimb(NQueenNode::getRandNode(n));
        time += timer.elapse();
        if (tmp.conflictCount() == 0) {
            node = tmp;
            ++sucCnt;
        }
    }
    printf("Compute finished.\n");
    printf("Case amount: %d\n", caseCnt);
    printf("Success rate: %.2lf%%\n", 100 * (double)sucCnt / caseCnt);
    printf("Average time elapse: %.3lf ms\n", time / caseCnt);
    printf("One solution: (conflict amount: %d)\n", node.conflictCount());
    printf("%s\n%s\n", node.toPrettyString().c_str(), node.toString().c_str());

    // Random restart choice hill climbing
    printf("\nCompute using random restart hill climbing...\n");
    time = sucCnt = 0;
    for (int i = 0; i < caseCnt; ++i) {
        timer.reset();
        auto tmp = NQueen::solveWithRandRestartHillClimb(n);
        time += timer.elapse();
        if (tmp.conflictCount() == 0) {
            node = tmp;
            ++sucCnt;
        }
    }
    printf("Compute finished.\n");
    printf("Case amount: %d\n", caseCnt);
    printf("Success rate: %.2lf%%\n", 100 * (double)sucCnt / caseCnt);
    printf("Average time elapse: %.3lf ms\n", time / caseCnt);
    printf("One solution: (conflict amount: %d)\n", node.conflictCount());
    printf("%s\n%s\n", node.toPrettyString().c_str(), node.toString().c_str());

    // Enumeration
    printf("\nCompute using enumeration...\n");
    vector<NQueenNode> resList;
    timer.reset();
    NQueen::solveWithEnumeration(n, resList);
    time = timer.elapse();
    printf("Compute finished.\n");
    printf("Time elapse: %.3lf ms\n", time);
    printf("Solution amount: %d\n", (int)resList.size());
    printf("One solution:");
    for (unsigned i = 0; i < 1; ++i) {  // Only print one solutions
        printf("\nAnswer #%d: (conflict amount: %d)\n", i + 1, resList[i].conflictCount());
        printf("%s\n%s\n", resList[i].toPrettyString().c_str(), resList[i].toString().c_str());
    }
}
