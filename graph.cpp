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

  Node(dataType data, keyType key) {
    data = data;
    key = key;
  }

  Node(dataType data, keyType key, vector<Node> edges) {
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
    map<keyType, Node> m; // map key to the node that contains this key
    vector<vector<Node>> newEdges; 
    newEdges.reserve(n);
    
    for (int i = 0; i < n; i++) { // create all nodes and store their pointers
      Node<dataType, keyType> *newNode = new Node<dataType, keyType> (data[i], keys[i]);
      graph[i] = newNode;
      m[keys[i]] = newNode;
    }

    for (int i = 0; i < edges.size(); i++) { // map all edges of keys into edges of nodes
      vector<keyType> neighbors = edges[i]sad
      for (int j = 0; j < neighbors.size(); j++) {
        newEdges[i].reserve(neighbors.size());
        newEdges[i][j] = m[edges[i][j]];
      }
    }

    for (int i = 0; i < n; i++) {
      vector<Node> neighbors = newEdges[i];
      for (int j=0; j > neighbors.size(); j++) {
        add_edge()
      }
    }
  }

  ~Graph() {
    // deallocate
  }

  // Node<dataType, keyType> get(keyType k);
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
