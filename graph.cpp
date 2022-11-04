#ifndef GRAPH_H
#define GRAPH_H

#include <cstdlib>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <set>
#include <list>
#include <limits>

using namespace std;

template <typename dataType, typename keyType>
struct Node {
public:
  dataType data;
  keyType key;
  string color;
  Node<dataType, keyType>* parent;
  int distance;
  vector<Node<dataType, keyType>*> neighbors;

  Node(dataType d, keyType k) {
    data = d;
    key = k;
  }
};

template <typename dataType, typename keyType>
class Graph {
public:
  // graph is a vector of Nodes where each Node has key, data, and neighbors
  Graph(vector<keyType> keys, vector<dataType> data, vector<vector<keyType>> edges) {
    int n = data.size(); // number of vertices
    graph.reserve(n); // allocate memory for graph
    
    for (int i = 0; i < n; i++) { // create Nodes for all keys and store their pointers
      Node<dataType, keyType> *newNode = new Node<dataType, keyType> (data[i], keys[i]);
      graph.insert(graph.begin()+i, newNode);
      table[keys[i]] = newNode;
    }

    for (int i=0; i < n; i++) { // add edges for all Nodes
      Node<dataType, keyType>* from = table[keys[i]];
      vector<keyType> neighbors = edges[i];
      int neiSize = neighbors.size();
      from->neighbors.reserve(neiSize);
      for (int j = 0; j < neiSize; j++) {
        Node<dataType, keyType>* to = table[edges[i][j]];
        add_edge(from, to);
      }
    }
  }

  // ~Graph() {
  //   // deallocate
  // }

  Node<dataType, keyType>* get(keyType k) {
    return table[k];
  }

  bool reachable(keyType u, keyType v) {
    this->bfs(u);
    return table[v]->color == "black";
  }

  void bfs(keyType s) {
    for (int i=0; i<graph.size(); i++) {
      graph[i]->color = "white";
      graph[i]->distance = numeric_limits<int>::max();
      graph[i]->parent = nullptr;
    }

    Node<dataType, keyType>* sNode = table[s];
    sNode->color = "grey";
    sNode->distance = 0;
    sNode->parent = nullptr;
    list<Node<dataType, keyType>*> queue;
    queue.push_back(sNode);

    while (!queue.empty()) {
      Node<dataType, keyType>* u = queue.front();
      queue.pop_front();
      vector<Node<dataType, keyType>*> neighbors = u->neighbors;
      // cout << "queue size: " << queue.size() << endl;
      // cout << "u data: " << u->data << endl;
      for (int i = 0; i<neighbors.size(); i++) {
        Node<dataType, keyType>* v = neighbors[i];
        if (v->color == "white") {
          v->color = "grey";
          v->distance = u->distance + 1;
          v->parent = u;
          queue.push_back(v);
        }
      }
      u->color = "black";
    }
  }

  void print_path(keyType u, keyType v) {
    this->bfs(u);
    string path;
    Node<dataType, keyType>* vNode = table[v];
    // cout << table[u]->key << endl;
    while (vNode->key != u) {
      path = " -> " + vNode->key  + path;
      vNode = vNode->parent;
    }

    path = vNode->key + path;
    cout << "print_path result: " << path << endl;
  }

  void bfs_tree(keyType s) { // allocate space??
    this->bfs(s);
    int maxDepth = 0;
    for (int i=0; i<graph.size(); i++) {
      if (graph[i]->distance > maxDepth) {
        maxDepth = graph[i]->distance;
      }
    }

    vector<vector<string>> bfsLevel;
    bfsLevel.reserve(maxDepth);
    for (int i=0; i<graph.size(); i++) {
      int level = graph[i]->distance;
      keyType key = graph[i]->key;
      bfsLevel[level].push_back(key);
    }

    // for (int i=0; i<bfsLevel.size(); i++) {
      
    // }
  }

  // string edge_class(keyType u, keyType v);

private:
  vector<Node<dataType, keyType>*> graph;
  map<keyType, Node<dataType, keyType>*> table; // map key to Node that contains key

  void add_edge(Node<dataType, keyType>* from, Node<dataType, keyType>* to) {
    from->neighbors.push_back(to);
  }

  // void deallocate(); // private method for destructor
  // void find_path(Node<dataType, keyType>* from, Node<dataType, keyType>* to) {
  //   set<keyType> visit;
  //   list<Node<dataType, keyType>*> queue;
  //   queue.push_back(from);
  //   vector<keyType> path;

  //   while (!queue.empty()) {
  //     Node<dataType, keyType>* node = queue.pop_front();
  //     bool inVisit = visit.find(node) != visit.end();
  //     if (!inVisit) {
  //       vector<Node<dataType, keyType>*> neighbors = node->neighbors;
  //       for (int i = 0; i<neighbors.size(); i++) {
          
  //       }
  //     }
  //   }
  // }
};

#endif
