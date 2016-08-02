# DataStructureAndAlgorithm

A library that contains useful data structures and algorithms written in c/c++.

## Compile and Run

```bash
$ cd src
$ make
$ make run
$ make clean
```

## Data Structures

| Name | Source |
| ---- | ------ |
|[Linked List(support sort)](https://en.wikipedia.org/wiki/Linked_list)|[LinkedList.h](./src/LinkedList.h)|
|[Binary Heap](https://en.wikipedia.org/wiki/Binary_heap)|[BinaryHeap.h](./src/BinaryHeap.h)|
|[AVL Tree](https://en.wikipedia.org/wiki/AVL_tree)|[AVLTree.h](./src/AVLTree.h)|
|[Disjoint Set](https://en.wikipedia.org/wiki/Disjoint-set_data_structure)|[DisjointSet.h](./src/DisjointSet.h) [DisjointSet.cpp](./src/DisjointSet.cpp)|
|[Graph](https://en.wikipedia.org/wiki/Graph_(abstract_data_type))|[Graph.h](./src/Graph.h) [Graph.cpp](./src/Graph.cpp)|

## Algorithms

| Name | Source |
| ---- | ------ |
|[Sorting Algorithm](https://en.wikipedia.org/wiki/Sorting_algorithm)|[SortHelper.h](./src/SortHelper.h)|
|[Random Generation](https://en.wikipedia.org/wiki/Random_number_generation)|[RandomEngine.h](./src/RandomEngine.h) [RandomEngine.cpp](./src/RandomEngine.cpp)|
|[Arithmetic Expression](https://en.wikipedia.org/wiki/Shunting-yard_algorithm)|[ArithmeticExpression.h](./src/ArithmeticExpression.h) [ArithmeticExpression.cpp](./src/ArithmeticExpression.cpp)|
|[N-Puzzle Problem](https://en.wikipedia.org/wiki/15_puzzle)|[NPuzzle.h](./src/NPuzzle.h) [NPuzzle.cpp](./src/NPuzzle.cpp)|
|Simple Algorithms|[Algorithm.h](./src/Algorithm.h) [Algorithm.cpp](./src/Algorithm.cpp)|
|[Factorial](https://en.wikipedia.org/wiki/Factorial)|[factorial()](./src/Algorithm.cpp)|
|[Binary Search](https://en.wikipedia.org/wiki/Binary_search_algorithm)|[binarySearch()](./src/Algorithm.cpp)|
|[Permutation](https://en.wikipedia.org/wiki/Permutation)|[nextPermutation()](./src/Algorithm.cpp)|
|[Combination](https://en.wikipedia.org/wiki/Combination)|[printCombinations()](./src/Algorithm.cpp)|
|[Cantor Expansion](http://www.programering.com/a/MDMwkDNwATc.html) [(zh)](https://zh.wikipedia.org/wiki/%E5%BA%B7%E6%89%98%E5%B1%95%E5%BC%80)|[cantorExpand()](./src/Algorithm.cpp)|
|Graph Algorithms|[AlgorithmGraph.h](./src/AlgorithmGraph.h) [AlgorithmGraph.cpp](./src/AlgorithmGraph.cpp)|
|[Topological Sort](https://en.wikipedia.org/wiki/Topological_sorting)|[topoSort()](./src/AlgorithmGraph.cpp)|
|[Dijkstra(shortest path)](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)|[dijkstra()](./src/AlgorithmGraph.cpp)|
|[Prim(minimum spanning tree)](https://en.wikipedia.org/wiki/Prim%27s_algorithm)|[prim()](./src/AlgorithmGraph.cpp)|

## Utils

| Name | Source |
| ---- | ------ |
|Timer|[Timer.h](./src/Timer.h) [Timer.cpp](./src/Timer.cpp)|

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
