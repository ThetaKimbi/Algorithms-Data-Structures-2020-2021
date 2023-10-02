# Algorithms-Data-Structures-2021-2022
Algorithms and Data Structures Project | Academic Year 2020-2021 | Politecnico di Milano

## Description
The goal of the project is to manage a ranking system for weighted directed graphs. The ranking keeps track of the top k "best" graphs.

The program to be implemented takes two parameters as input, only once (on the first line of the file, separated by a space):

- `d`: the number of nodes in the graphs
- `k`: the length of the ranking
  
A sequence of commands including:
- `AggiungiGrafo[adjacency-matrix]`
- `TopK`

### `AggiungiGrafo`
It requires adding a graph to those considered for ranking. It is followed by the adjacency matrix of the graph itself, printed one row per line, with elements separated by commas.

The nodes of the graph are logically labeled with an integer index between `0` and `d - 1`; the node at position `0` is the one whose outgoing edges are described by the first row of the matrix.

The weights of the graph's edges are integers in the range `[0, 2^32 – 1]`.

### `TopK`
Consider each graph from the beginning of the program until the `TopK` command labeled with an integer index corresponding to the number of graphs read before it (starting from `0`).

`TopK` requires the program to print the integer indices of the `k` graphs having the `k` smallest values of the following metric: the sum of the shortest paths between node `0` and all other nodes in the graph reachable from `0`.

If there are multiple graphs with the same value of the metric, priority is given to the ones that were read first.

The distances of nodes not reachable from `0` are considered to be zero.

The `k` integer indices are printed on a single line, separated by spaces, in any order.

## Implementation 
The program has been designed to efficiently compute the selected metric for each graph by employing Dijkstra's algorithm. Additionally, it uses a heap data structure to efficiently manage and update the top k graphs based on this metric. 

This combination of algorithms ensures optimal performance and accurate ranking of graphs within the given constraints.

## Overview
Challenge| Time Limit      | Memory Limit      | Total Score
-------- | --------------- | ----------------- | ---------------------
UpTo18   | 2.400 seconds   | 90.0 MiB          | 18/18
UpTo30   | 2.080 seconds   | 82.0 MiB          | 12/12
CumLaude | 1.700 seconds   |  1.0 MiB          | 1/1
