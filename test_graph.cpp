#include "graph.cpp"

using namespace std;

int main() {

  vector<string> keys{"R", "V", "S", "T", "U", "Y", "W", "X"};
  vector<int> data{3,2,1,1,0,2,1,2};
  vector<vector<string>> adjs {{"V"}, {"S"}, {"R"}, {"S","U","W"}, {"Y"}, {"W"}, {"X"}, {"U"}};

  Graph<int, string>* G = new Graph<int, string>(keys, data, adjs);
  cout << "created graph!" << endl;

  // G->bfs("T");
  // if (G->reachable("D", "B")) {
  //   cout << "TRUE" << endl;
  // } else {
  //   cout << "FALSE" << endl;
  // }
  // G->print_path("Y", "Y");
  // cout << G->get("D")->data << endl;
  G->bfs_tree("T");
  return 0;
}