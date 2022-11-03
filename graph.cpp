#ifndef GRAPH_H
#define GRAPH_H

#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

template <typename dataType, typename keyType>
struct Node {
public:
  dataType data;
  keyType key;
  vector<Node> neighbors;

  Node(dataType data, keyType key, vector<keyType> edges) {
    // create node with neighbors
    data = data;
    key = key;
    int n = edges.size(); // number of neighbors
    neighbors.reserve(n);
    for (int i = 0; i < n; i++) {
      // newNeighbor = new Node<>
      // neighbors[i] = 
    }
  }
};

template <typename dataType, typename keyType>
class Graph
{
public:
  Graph(vector<keyType> keys, vector<dataType> data, vector<vector<keyType>> edges) {
    // create graph out of edges
    int n = data.size();
    graph.reserve(n);

    for (int i = 0; i < n; i++) {
      Node<dataType, keyType> *newNode = new Node<dataType, keyType> (data[i], keys[i], edges[i]);
      graph[i] = newNode;
    }
  }

  ~Graph() {
    // deallocate
  }

  Node get(keyType k);
  bool reachable(keyType u, keyType v);
  void bfs(keyType s);
  void print_path(keyType u, keyType v);
  void bfs_tree(keyType s);
  string edge_class(keyType u, keyType v);

  string to_string();

private:
  vector<Node> graph;

  void deallocate(); // private method for destructor
};

#endif