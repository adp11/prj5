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
  bool color; // true: black; false: white
  Node<dataType, keyType>* parent;
  int distance;
  int dTime;
  int fTime;
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
    graph.reserve(n); // allocate memory for vector of vertices
    
    for (int i = 0; i < n; i++) { // create Nodes, store these Nodes in a hash table for fast lookup, and insert each Node in graph 
      Node<dataType, keyType> *newNode = new Node<dataType, keyType> (data[i], keys[i]);
      graph.insert(graph.begin()+i, newNode);
      table[keys[i]] = newNode;
    }

    for (int i=0; i < n; i++) { // add edges to each Node
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

  ~Graph() {
    deallocate();
  }

  Node<dataType, keyType>* get(keyType k) {
    return table[k]; // return Node via fast lookup in hash table
  }

  bool reachable(keyType u, keyType v) {
    // check if either key is not in set of vertices
    if (table.find(u) == table.end() || table.find(v) == table.end()) {
      return false;
    }
    this->bfs(u);
    return table[v]->color == true;
  }

  void bfs(keyType s) {
    // check if key is not in set of vertices
    if (table.find(s) == table.end()) {
      throw std::invalid_argument("key not in set of vertices");
    }

    for (int i=0; i<graph.size(); i++) {
      graph[i]->color = false;
      graph[i]->distance = numeric_limits<int>::max();
      graph[i]->parent = nullptr;
    }
    Node<dataType, keyType>* sNode = table[s];
    sNode->color = true;
    sNode->distance = 0;
    sNode->parent = nullptr;

    list<Node<dataType, keyType>*> queue; // use DLL for queue here
    queue.push_back(sNode);
    while (!queue.empty()) {
      Node<dataType, keyType>* u = queue.front();
      queue.pop_front();
      vector<Node<dataType, keyType>*> neighbors = u->neighbors;
      for (int i = 0; i<neighbors.size(); i++) {
        Node<dataType, keyType>* v = neighbors[i];
        if (v->color == false) {
          v->color = true;
          v->distance = u->distance + 1;
          v->parent = u;
          queue.push_back(v);
        }
      }
    }
  }


  void print_path(keyType u, keyType v) {
    this->bfs(u);
    string path;
    Node<dataType, keyType>* vNode = table[v];
    while (vNode && vNode->key != u) { // backtrack via parent
      path = " -> " + vNode->key  + path;
      vNode = vNode->parent;
    }

    if (vNode) {
      path = vNode->key + path;
      cout << path;
    } else {
      cout << "";
    }
    
  }

  void bfs_tree(keyType s) {
    // check if key is not in set of vertices
    if (table.find(s) == table.end()) {
      throw std::invalid_argument("key not in set of vertices");
    }

    this->bfs(s);
    int maxDepth = 0;
    for (int i=0; i<graph.size(); i++) {
      if (graph[i]->distance > maxDepth) {
        maxDepth = graph[i]->distance;
      }
    }

    vector<vector<string>> res;
    res.resize(maxDepth+1);
    for (int i=0; i<graph.size(); i++) {
      
      keyType key = graph[i]->key;
      int d = graph[i]->distance;
      res[d].push_back(key);
    }

    string string_tree;
    // string_tree += s;
    for (int i=0; i<res.size(); i++) {
      int size = res[i].size();
      for (int j=0; j<size; j++) {
        if (j == size-1) {
          string_tree += res[i][j];
        } else {
          string_tree += res[i][j] + " ";
        }
      }
      if (i != res.size()-1) string_tree += "\n";
    }
    cout << string_tree;
  }


  
  string edge_class(keyType u, keyType v) {
    // check if either key is not in set of vertices
    if (table.find(u) == table.end() || table.find(v) == table.end()) {
      throw std::invalid_argument("key not in set of vertices");
    }

    dfs();
    Node<dataType, keyType>* uNode = table[u];
    Node<dataType, keyType>* vNode = table[v];
    int startU = uNode->dTime;
    int endU = uNode->fTime;
    int startV = vNode->dTime;
    int endV = vNode->fTime;
    bool edgeExist = false;

    for (int i=0; i<uNode->neighbors.size();i++) {
      if (uNode->neighbors[i]->key == vNode->key) {
        edgeExist = true;
      }
    }

    if (edgeExist) {
      if (startU >= startV && endU <= endV) {
        return "back edge";
      } else if (startU <= startV && endU >= endV) {
        if (vNode->parent == uNode) {
          return "tree edge";
        }
        return "forward edge";
      } else if (endU < startV || endV < startU) {
        return "cross edge";
      }
    }
    return "no edge";
  }

private:
  vector<Node<dataType, keyType>*> graph;
  map<keyType, Node<dataType, keyType>*> table; // map key to Node that contains key
  int time;

  void add_edge(Node<dataType, keyType>* from, Node<dataType, keyType>* to) {
    from->neighbors.push_back(to);
  }

  void dfs_visit(Node<dataType, keyType>* u) {
    time += 1;
    u->dTime = time;
    u->color = true;
    for (int i=0; i<u->neighbors.size(); i++) {
      Node<dataType, keyType>* v = u->neighbors[i];
      if (!v->color) {
        v->parent = u;
        dfs_visit(v);
      }
    }
    u->color = true;
    time += 1;
    u->fTime = time;
  }

  void dfs() {
    for (int i=0; i<graph.size(); i++) {
      graph[i]->color = false;
      graph[i]->parent = nullptr;
    }

    time = 0;

    for (int i=0; i<graph.size(); i++) {
      if (!graph[i]->color) {
        dfs_visit(graph[i]);
      }
    }
  }

  void deallocate() {
    for (int i = 0; i<graph.size(); i++) {
      delete graph[i];
    }
    graph.clear();
  }
  
};

#endif
