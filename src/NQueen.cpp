#include "NQueen.h"
#include "Timer.h"
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

int NQueenNode::conflictCount() const {
    int cnt = 0;
    for (auto i = 0; i < size; ++i) {
        if (val[i] != -1) {
            for (auto j = 0; j < size; ++j) {
                // Same column or diagnose
                if (conflict(i, j)) {
                    ++cnt;
                    break;
                }
            }
        }
    }
    return cnt;
}

bool NQueenNode::conflict(const int row1, const int row2) const {
    return row1 != row2 && (val[row1] == val[row2]
        || abs(row1 - row2) == abs(val[row1] - val[row2]));
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
                if (node.conflict(i, row)) {
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

void NQueen::test() {
    printf("Test N-Queen:\n\n");
    int n;
    printf("Input queens number: ");
    if (scanf("%d", &n) != 1) {
        printf("Read input error.\n");
        return;
    }

    printf("\nComputing...\n");
    vector<NQueenNode> res;
    Timer timer;
    NQueen::solveWithEnumeration(n, res);
    auto time = timer.elapse();

    printf("Computing finished.\n\n");
    printf("Solutions:\n");
    for (unsigned i = 0; i < res.size(); ++i) {
        printf("\nSolution #%d: (conflict: %d)\n", i + 1, res[i].conflictCount());
        printf("%s\n%s\n", res[i].toPrettyString().c_str(), res[i].toString().c_str());
    }
    printf("\nSolution amount: %d\n", (int)res.size());
    printf("Time elapse: %.3lf ms\n", time);
}
