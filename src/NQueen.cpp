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

NQueenNode NQueen::solveWithHillClimb(const int n) {
    // Generate first node randomly
    vector<int> start(n, 0);
    for (auto &x : start) {
        x = RandomEngine::randLib(0, n - 1);
    }
    NQueenNode cur(start);
    while (1) {
        auto min = cur.getMinConflictNeighbor();
        if (min.conflictCount() >= cur.conflictCount()) {
            return cur;
        }
        cur = min;
    }
}

void NQueen::test() {
    printf("Test N-Queen:\n\n");
    int n;
    printf("Input queens number: ");
    if (scanf("%d", &n) != 1) {
        printf("Read input error.\n");
        return;
    }

    printf("\nCompute by hill climbing...");
    Timer timer;
    NQueenNode res2 = NQueen::solveWithHillClimb(n);
    auto time2 = timer.elapse();
    printf("\nCompute finished.\n");
    printf("Time elapse: %.3lf ms\n", time2);
    printf("Solution: (conflict amount: %d)\n", res2.conflictCount());
    printf("%s\n%s\n", res2.toPrettyString().c_str(), res2.toString().c_str());

    printf("\n\nCompute by enumerating...\n");
    vector<NQueenNode> res1;
    timer.reset();
    NQueen::solveWithEnumeration(n, res1);
    auto time1 = timer.elapse();
    printf("Compute finished.\n");
    printf("Time elapse: %.3lf ms\n", time1);
    printf("Solution amount: %d\n", (int)res1.size());
    printf("Solutions:");
    for (unsigned i = 0; i < res1.size(); ++i) {
        printf("\nAnswer #%d: (conflict amount: %d)\n", i + 1, res1[i].conflictCount());
        printf("%s\n%s\n", res1[i].toPrettyString().c_str(), res1[i].toString().c_str());
    }
}
