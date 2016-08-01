#include "LinkedList.h"
#include "BinaryHeap.h"
#include "AVLTree.h"
#include "DisjointSet.h"
#include "Graph.h"
#include "SortHelper.h"
#include "RandomEngine.h"
#include "ArithmeticExpression.h"
#include "NPuzzle.h"
#include "Algorithm.h"
#include "AlgorithmGraph.h"

using namespace sl;

void test() {
    //LinkedList<int>::test();
    //BinaryHeap<int>::test();
    //AVLTree<int>::test();
    //DisjointSet::test();
    //Graph::test();
    //SortHelper<int>::test();
    //RandomEngine::test();
    //ArithmeticExpression::test();
    NPuzzle::test();
    //Algorithm::test();
    //AlgorithmGraph::test();
}

int main() {
    {
        test();
    }
#ifdef _MSC_VER
    _CrtDumpMemoryLeaks();
#endif
    return 0;
}
