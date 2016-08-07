# DataStructureAndAlgorithm

A library that contains useful data structures and algorithms written in c/c++.

## Compile and Run

```bash
$ cd src
$ make
$ make run
$ make clean
```

## Data Structure

| Name | Source | Comment |
| ---- | ------ | ------- |
|[Linked List](https://en.wikipedia.org/wiki/Linked_list)|[LinkedList.h](./src/LinkedList.h)|support sort|
|[Binary Heap](https://en.wikipedia.org/wiki/Binary_heap)|[BinaryHeap.h](./src/BinaryHeap.h)|priority queue|
|[Hash Table](https://en.wikipedia.org/wiki/Hash_table)|[HashTable.h](./src/HashTable.h)|use bucket list|
|[AVL Tree](https://en.wikipedia.org/wiki/AVL_tree)|[AVLTree.h](./src/AVLTree.h)|support balanced insert and remove|
|[Disjoint Set](https://en.wikipedia.org/wiki/Disjoint-set_data_structure)|[DisjointSet.h](./src/DisjointSet.h) [DisjointSet.cpp](./src/DisjointSet.cpp)|express relation of equivalence|
|[Graph](https://en.wikipedia.org/wiki/Graph_(abstract_data_type))|[Graph.h](./src/Graph.h) [Graph.cpp](./src/Graph.cpp)|use adjacent list or matrix; node stores nonnegative number|

## Algorithm

| Name | Source | Comment |
| ---- | ------ | ------- |
|[Sorting Algorithm](https://en.wikipedia.org/wiki/Sorting_algorithm)|[SortHelper.h](./src/SortHelper.h)|classic sorting algorithms
|[Random Generation](https://en.wikipedia.org/wiki/Random_number_generation)|[RandomEngine.h](./src/RandomEngine.h) [RandomEngine.cpp](./src/RandomEngine.cpp)|pseudorandom number generation|
|[Arithmetic Expression](https://en.wikipedia.org/wiki/Shunting-yard_algorithm)|[ArithmeticExpression.h](./src/ArithmeticExpression.h) [ArithmeticExpression.cpp](./src/ArithmeticExpression.cpp)|arithemetic expression calculation|
|[N-Puzzle Problem](https://en.wikipedia.org/wiki/15_puzzle)|[NPuzzle.h](./src/NPuzzle.h) [NPuzzle.cpp](./src/NPuzzle.cpp)|can search 70 nodes per millisecond in average (compiler: g++ -O2)|
|||
|Simple Algorithms|[Algorithm.h](./src/Algorithm.h) [Algorithm.cpp](./src/Algorithm.cpp)|
|[Factorial](https://en.wikipedia.org/wiki/Factorial)|[Algorithm::factorial()](./src/Algorithm.cpp)|20! is max (return unsigned long long)|
|[Binary Search](https://en.wikipedia.org/wiki/Binary_search_algorithm)|[Algorithm::binarySearch()](./src/Algorithm.cpp)|find first or last appeared position|
|[Permutation](https://en.wikipedia.org/wiki/Permutation)|[Algorithm::nextPermutation()](./src/Algorithm.cpp)|non-recursive version|
|[Combination](https://en.wikipedia.org/wiki/Combination)|[Algorithm::printCombinations()](./src/Algorithm.cpp)|non-recursive version|
|[Cantor Expansion](http://www.programering.com/a/MDMwkDNwATc.html) [(zh)](https://zh.wikipedia.org/wiki/%E5%BA%B7%E6%89%98%E5%B1%95%E5%BC%80)|[Algorithm::cantorExpand()](./src/Algorithm.cpp)|cantor expansion and its inverse|
|[Prime Number](https://en.wikipedia.org/wiki/Prime_number)|[Algorithm::nextPrime()](./src/Algorithm.cpp)|find next prime number (choose appropriate buckets number for hash table)|
|||
|Graph Algorithms|[AlgorithmGraph.h](./src/AlgorithmGraph.h) [AlgorithmGraph.cpp](./src/AlgorithmGraph.cpp)|
|[Topological Sort](https://en.wikipedia.org/wiki/Topological_sorting)|[AlgorithmGraph::topoSort()](./src/AlgorithmGraph.cpp)|check if a graph is cyclic|
|[Dijkstra](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)|[AlgorithmGraph::dijkstra()](./src/AlgorithmGraph.cpp)|shortest path|
|[Prim](https://en.wikipedia.org/wiki/Prim%27s_algorithm)|[AlgorithmGraph::prim()](./src/AlgorithmGraph.cpp)|minimum spanning tree|

## Utility

| Name | Source | Comment |
| ---- | ------ | ------- |
|Timer|[Timer.h](./src/Timer.h) [Timer.cpp](./src/Timer.cpp)|calculate running time|

## License

Copyright 2016 ChuyangLiu

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
