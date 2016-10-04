# AlgorithmLibrary

A library containing some data structures and algorithms written in c/c++.

## Compile and Run

```bash
$ make
$ make run
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
|[N-Puzzle Problem](https://en.wikipedia.org/wiki/15_puzzle)|[NPuzzle.h](./src/NPuzzle.h) [NPuzzle.cpp](./src/NPuzzle.cpp)|able to search 240 nodes per millisecond in average(5*5 puzzle; compiler: g++ -O2); [GUI demo](https://github.com/chuyangLiu/NPuzzle-AI) [博客](http://blog.csdn.net/qq_22885773/article/details/52144827)|
|[Sorting](https://en.wikipedia.org/wiki/Sorting_algorithm)|[SortHelper.h](./src/SortHelper.h)|classic sorting algorithms
|[Random Generation](https://en.wikipedia.org/wiki/Random_number_generation)|[RandomEngine.h](./src/RandomEngine.h) [RandomEngine.cpp](./src/RandomEngine.cpp)|pseudorandom number generation|
|[Arithmetic Expression](https://en.wikipedia.org/wiki/Shunting-yard_algorithm)|[ArithmeticExpression.h](./src/ArithmeticExpression.h) [ArithmeticExpression.cpp](./src/ArithmeticExpression.cpp)|arithemetic expression calculation|
|[MD5](https://en.wikipedia.org/wiki/MD5) [MD5(CN)](http://baike.baidu.com/link?url=bO26fMBDaRRQZkoObKjuCAHRLG_JkvfvCOVWdBfXZhiiwqLvUHfFRJaBHg9xLDwPf5iXAWafVgy7BxjSFCQDaa)|[MD5.h](./src/MD5.h) [MD5.cpp](./src/MD5.cpp)|message encrypt|
|[Factorial](https://en.wikipedia.org/wiki/Factorial)|[Algorithm::factorial()](./src/Algorithm.cpp)|20! is max (return unsigned long long)|
|[Binary Search](https://en.wikipedia.org/wiki/Binary_search_algorithm)|[Algorithm::binarySearch()](./src/Algorithm.cpp)|find first or last appeared position|
|[Permutation](https://en.wikipedia.org/wiki/Permutation)|[Algorithm::nextPermutation()](./src/Algorithm.cpp)|non-recursive version|
|[Combination](https://en.wikipedia.org/wiki/Combination)|[Algorithm::printCombinations()](./src/Algorithm.cpp)|non-recursive version|
|[Cantor Expansion](http://www.programering.com/a/MDMwkDNwATc.html) [(CN)](https://zh.wikipedia.org/wiki/%E5%BA%B7%E6%89%98%E5%B1%95%E5%BC%80)|[Algorithm::cantorExpand()](./src/Algorithm.cpp)|cantor expansion and its inverse|
|[Prime Number](https://en.wikipedia.org/wiki/Prime_number)|[Algorithm::nextPrime()](./src/Algorithm.cpp)|find next prime number (choose appropriate buckets number for hash table)|
|[Topological Sort](https://en.wikipedia.org/wiki/Topological_sorting)|[AlgorithmGraph::topoSort()](./src/AlgorithmGraph.cpp)|check if a graph is cyclic|
|[Dijkstra](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)|[AlgorithmGraph::dijkstra()](./src/AlgorithmGraph.cpp)|shortest path|
|[Prim](https://en.wikipedia.org/wiki/Prim%27s_algorithm)|[AlgorithmGraph::prim()](./src/AlgorithmGraph.cpp)|minimum spanning tree|
|[Hungarian](https://en.wikipedia.org/wiki/Hungarian_algorithm)|[AlgorithmGraph::hungarian()](./src/AlgorithmGraph.cpp)|solve unweighted [bipartite graph](https://en.wikipedia.org/wiki/Bipartite_graph) matching problem; [博客](http://blog.csdn.net/pi9nc/article/details/11848327)|
|[Kuhn Munkras(KM)](https://en.wikipedia.org/wiki/Hungarian_algorithm)|[AlgorithmGraph::km()](./src/AlgorithmGraph.cpp)|solve optimal weighted [bipartite graph](https://en.wikipedia.org/wiki/Bipartite_graph) matching problem; [博客](http://blog.csdn.net/rappy/article/details/1790647)|
|[Edmonds–Karp](https://en.wikipedia.org/wiki/Edmonds%E2%80%93Karp_algorithm)|[AlgorithmGraph::EdmondKarp()](./src/AlgorithmGraph.cpp)|solve [maximum flow problem](https://en.wikipedia.org/wiki/Maximum_flow_problem); [博客](http://www.cnblogs.com/zsboy/archive/2013/01/27/2878810.html)|

## Utility

| Name | Source | Comment |
| ---- | ------ | ------- |
|Timer|[Timer.h](./src/Timer.h) [Timer.cpp](./src/Timer.cpp)|calculate program execution time|

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
