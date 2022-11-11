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
  dataType data; // data of Node
  keyType key; // key of Node
  bool visited; // equivalent to color of Node
  Node<dataType, keyType>* parent; // equivalent to pi of Node
  int distance; // distance from sourceNode in bfs
  int dTime; // discovery time in dfs
  int fTime; // finish time in dfs
  vector<Node<dataType, keyType>*> neighbors; // Nodes that this Node has edges to 

  Node(dataType d, keyType k) { // constructor for Node
    data = d;
    key = k;
  }

};

template <typename dataType, typename keyType>
class Graph {
public:
  /**
   * Precondition: vector of keys, vector of data, and vector of edges. They are all assumed to be of same size
   * Postcondition: a Graph object is created
   */
  Graph(vector<keyType> keys, vector<dataType> data, vector<vector<keyType>> edges) {
    int n = data.size(); // number of vertices
    graph.reserve(n); // allocate memory for vector of vertices
    
    for (int i = 0; i < n; i++) { // create Nodes from all given keys, store these Nodes in a hash table for fast lookup, and insert each Node in graph 
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

  /**
   * Precondition: no param needed
   * Postcondition: return nothing, but we delete all Node that got allocated with "new"
   */
  ~Graph() {
    for (int i = 0; i<graph.size(); i++) {
      delete graph[i];
    }
  }

  /**
   * Precondition: param k is of type "keyType". k could be invalid key where it doesn't exist
   * Postcondition: return Node whose key is same as k
   */
  Node<dataType, keyType>* get(keyType k) {
    if (table.find(k) == table.end()) {
      // throw std::invalid_argument("key not in set of vertices");
      return nullptr;
    }
    return table[k];
  }

  /**
   * Precondition: params u and v are of type "keyType". u and v could be invalid keys that don't exist
   * Postcondition: return true if v is reachable from u and false otherwise
   */
  bool reachable(keyType u, keyType v) {
    // check if either key is not in set of vertices
    if (table.find(u) == table.end() || table.find(v) == table.end()) {
      return false;
    }
    this->bfs(u);
    return table[v]->visited == true;
  }

  /**
   * Precondition: param s is of type "keyType", s is the source from which the bfs algorithm starts its exploration, s could be invalid key
   * Postcondition: return nothing, we should have an encoded bfs tree via properties such as parent, visited, and distance
   */
  void bfs(keyType s) {
    // check if key is not in set of vertices
    if (table.find(s) == table.end()) {
      // throw std::invalid_argument("key not in set of vertices");
      cout << "";
      return;
    }

    for (int i=0; i<graph.size(); i++) {
      graph[i]->visited = false;
      graph[i]->distance = numeric_limits<int>::max();
      graph[i]->parent = nullptr;
    }
    Node<dataType, keyType>* sNode = table[s];
    sNode->visited = true;
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
        if (v->visited == false) {
          v->visited = true;
          v->distance = u->distance + 1;
          v->parent = u;
          queue.push_back(v);
        }
      }
    }
  }

  /**
   * Precondition: params u and v are of type "keyType". u and v could be invalid keys
   * Postcondition: return nothing, print out the path from u to v if reachable and print empty string otherwise
   */
  
  void print_path(keyType u, keyType v) {
    // check if either key is not in set of vertices
    if (table.find(u) == table.end() || table.find(v) == table.end()) {
      // throw std::invalid_argument("u or v not in set of vertices");
      cout << "";
      return;
    }
    this->bfs(u);
    string path;
    stringstream ss;
    Node<dataType, keyType>* vNode = table[v];
  
    while (vNode && vNode->key != u) { // backtrack via parent
      ss.str("");
      ss << vNode->key;
      path = " -> " + ss.str()  + path;
      vNode = vNode->parent;
    }

    if (vNode) {
      ss.str("");
      ss << vNode->key;
      path = ss.str() + path;
      cout << path;
    } else {
      cout << "";
    }
    
  }

  /**
   * Precondition: param s is of type "keyType", s is the source from which the bfs algorithm starts its exploration, and s could be invalid key where it doesn't exist
   * Postcondition: return nothing, but print out the bfs tree/level order traversal
   */
  
  void bfs_tree(keyType s) {
    // check if key is not in set of vertices
    if (table.find(s) == table.end()) {
      // throw std::invalid_argument("key not in set of vertices");
      cout << "";
      return;
    }

    this->bfs(s);
    map<int, vector<keyType>> res;
    for (int i=0; i<graph.size(); i++) { // put all elements of the same distance into a hashmap where key (distance): value (keys)
      if (graph[i]->distance != numeric_limits<int>::max()) {
        res[graph[i]->distance].push_back(graph[i]->key);
      }
    }

    string string_tree;
    stringstream ss;
    for (int i=0; i<res.size(); i++) { // convert this hashmap into corresponding string to output
      int size = res[i].size();
      for (int j=0; j<size; j++) {
        if (j == size-1) {
          ss.str("");
          ss << res[i][j];
          string_tree += ss.str();
        } else {
          ss.str("");
          ss << res[i][j];
          string_tree += ss.str() + " ";
        }
      }
      if (i != res.size()-1) string_tree += "\n";
    }
    cout << string_tree;
  }


  /**
   * Precondition: params u and v are of type "keyType", u and v could be invalid keys where they don't exist
   * Postcondition: return the type of edge from u to v (if any), return "no edge" otherwise
   */
  string edge_class(keyType u, keyType v) {
    // check if either key is not in set of vertices
    if (table.find(u) == table.end() || table.find(v) == table.end()) {
      // throw std::invalid_argument("u or v not in set of vertices");
      return "no edge";
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
      if (startU >= startV && endU <= endV) { // uInterval is completely contained in vInterval
        return "back edge";
      } else if (startU <= startV && endU >= endV) { // vInterval is completely contained in uInterval
        if (vNode->parent == uNode) {
          return "tree edge";
        }
        return "forward edge";
      } else if (endU < startV || endV < startU) { // uInterval and vInterval are disjoint
        return "cross edge";
      }
    }
    return "no edge";
  }

private:
  vector<Node<dataType, keyType>*> graph;
  map<keyType, Node<dataType, keyType>*> table; // map key to Node that contains key
  int time;

  /**
   * Precondition: params from and to are pointers of type Node
   * Postcondition: return nothing, but add "to" to the list of neighbors of "from"
   */
  void add_edge(Node<dataType, keyType>* from, Node<dataType, keyType>* to) {
    from->neighbors.push_back(to);
  }

  // helper function of main function dfs()
  void dfs_visit(Node<dataType, keyType>* u) {
    time += 1;
    u->dTime = time;
    u->visited = true;
    for (int i=0; i<u->neighbors.size(); i++) {
      Node<dataType, keyType>* v = u->neighbors[i];
      if (!v->visited) {
        v->parent = u;
        dfs_visit(v);
      }
    }
    u->visited = true;
    time += 1;
    u->fTime = time;
  }

  /**
   * Precondition: no param needed
   * Postcondition: return nothing, but we should have an encoded dfs forest via properties such as parent, visited, and we should also have useful properties like discovery time and finish time of every Node to determine edge class
   */
  void dfs() {
    for (int i=0; i<graph.size(); i++) {
      graph[i]->visited = false;
      graph[i]->parent = nullptr;
    }

    time = 0;

    for (int i=0; i<graph.size(); i++) {
      if (!graph[i]->visited) {
        dfs_visit(graph[i]);
      }
    }
  }  
};

#endif
