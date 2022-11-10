#include "graph.cpp"

using namespace std;

// int main() {

//  vector<string> keys{"R", "V", "S", "T", "U", "Y", "W", "X"};
//  vector<int> data{3,2,1,1,0,2,1,2};
//  vector<vector<string>> adjs {{"V"}, {"S"}, {"R"}, {"S","U","W"}, {"Y"}, {"W"}, {"X"}, {"U"}};

//  Graph<int, string>* G = new Graph<int, string>(keys, data, adjs);
//  cout << "created graph!" << endl;

//  G->bfs("T");
  // if (G->reachable("D", "B")) {
  //   cout << "TRUE" << endl;
  // } else {
  //   cout << "FALSE" << endl;
  //  G->print_path("T", "V");
  // cout << G->get("D")->data << endl;
  // return 0;
// }

void test_get(Graph<string,string>* G) {
    try {
        if(G->get("S")==nullptr || G->get("S")->data != "C") {
            cout << "Incorrect result getting vertex \"s\"" << endl;
        }
        if(G->get("a") != nullptr) {
            cout << "Incorrect result getting non-existant vertex \"a\"" << endl;
        }
    } catch(exception& e) {
        cerr << "Error getting vertex from graph : " << e.what() << endl;
    }
}

void test_get_v1(Graph<int,string>* G) {
    int v = G->get("V")->data;
    try {
        if(G->get("V")==nullptr || G->get("V")->data != 2) {
            cout << "Incorrect result getting vertex \"v\"" << endl;
        }
        if(G->get("x") != nullptr) {
            cout << "Incorrect result getting non-existant vertex \"x\"" << endl;
        }
    } catch(exception& e) {
        cerr << "Error getting vertex from graph : " << e.what() << endl;
    }
}

void test_get_v2(Graph<int, char>* G) {
    try {
        if(G->get('z')==nullptr || G->get('z')->data != 39) {
            cout << "Incorrect result getting vertex \"v\"" << endl;
        }
        if(G->get(0) != nullptr) {
            cout << "Incorrect result getting non-existant vertex \"x\"" << endl;
        }
    } catch(exception& e) {
        cerr << "Error getting vertex from graph : " << e.what() << endl;
    }
}

void test_reachable(Graph<string,string>* G) {
    try {
        if(!G->reachable("R", "V")) {
            cout << "Incorrectly identified adjacent vertex \"V\" as unreachable from \"R\"" << endl;
        }
        if(!G->reachable("X", "W")) {
            cout << "Incorrectly identified \"W\" as unreachable from \"X\"" << endl;
        }
        if(G->reachable("S", "A")) {
            cout << "Incorrectly identified non-existant vetex \"A\" as reachable from \"S\"" << endl;
        }
    } catch(exception& e) {
        cerr << "Error testing reachable : " << e.what() << endl;
    }
}

void test_reachable_v1(Graph<string,float>* G) {
    try {
        if(!G->reachable(2.336, 2.05)) {
            cout << "Incorrectly identified adjacent vertex \"V\" as unreachable from \"R\"" << endl;
        }
        if(!G->reachable(2.05, 12.179)) {
            cout << "Incorrectly identified \"W\" as unreachable from \"X\"" << endl;
        }
        if(G->reachable(15.612, 0.89)) {
            cout << "Incorrectly identified non-existant vetex \"A\" as reachable from \"S\"" << endl;
        }
    } catch(exception& e) {
        cerr << "Error testing reachable : " << e.what() << endl;
    }
}

void test_bfs(Graph<string,string>* G) {
    try {
        G->bfs("T");
        string vertices[8] = {"V", "R", "S", "W", "T", "X", "U", "Y"};
        int distances[8] = {3,2,1,1,0,2,1,2};
        for(int i = 0; i < 8; i++){
            if(G->get(vertices[i])==nullptr || G->get(vertices[i])->distance != distances[i]) {
                cout << "Incorrect bfs result. Vertex " << vertices[i] << " should have distance " << distances[i] << " from source vertex \"t\"" << endl;
            }
        }
    } catch(exception& e) {
        cerr << "Error testing bfs : " << e.what() << endl;
    }
}

int main() {
  vector<string> A{"R", "V", "S", "T", "U", "Y", "W", "X"};
  vector<int> B{12,21,39,53,47,11};
  vector<string> A1{"A", "B", "C", "D", "E", "F", "G", "H"};
  vector<int> B1{3,2,1,1,0,2,1,2};
  vector<vector<string>> A_edges {{"V"}, {"S"}, {"R"}, {"S","U","W"}, {"Y"}, {"W"}, {"X"}, {"U"}};
  vector<char> F{'x','y','z','t','u','v'};
  vector<string> A2{"aa", "axv", "ata", "auv", "agx", "gau", "xxx", "tax", "gta", "uaa"};
  vector<vector<string>> A2_edges{{"a"}, {"tax", "uaa"}, {"auv"}, {"xxx"}, {"aa", "axv", "ata"}, {"gta"}, {"axv","xxx"},{"ata", "ttt"},{"aa"}, {"gau", "ggg", "auv"}};
  vector<vector<char>> F_edges{{'y','z'},{'x','u'},{'t'},{'x','u','v'},{'x'},{'y','z'}};
  vector<float> C{2.05, 4.11, 8.974, 2.336, 12.179, 15.612, 19.014, 17.152};
  vector<vector<float>> C_edges{{4.11, 15.612}, {}, {12.179, 17.152}, {8.974, 2.05}, {2.336, 19.014}, {15.612, 19.014, 17.152}, {4.11}, {2.05}, {2.336, 12.179}};

  Graph<string, string>* G = new Graph<string, string>(A, A1, A_edges);
  Graph<int, string>* G1 = new Graph<int, string>(A, B1, A_edges);
  Graph<int,char>* G2 = new Graph<int,char>(F,B,F_edges);
  Graph<string,float>* G3 = new Graph<string,float>(C,A, C_edges);
  Graph<string,string> *G4 = new Graph<string,string>(A,A1,A_edges);

  
//   test_get(G);
//   test_get_v1(G1);
//   test_get_v2(G2);
//   test_reachable(G);
  test_reachable_v1(G3);
//   test_bfs(G);
  cout << "Testing completed" << endl;
  return 0;
}