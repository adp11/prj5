#include <fstream>
#include <sstream>
#include "graph.cpp"

using namespace std;

Graph<string, string> *generate_graph(string fname)
{
    string line;
    ifstream infile(fname);
    vector<string> keys = {};
    vector<string> data = {};
    vector<vector<string>> adjs = {};
    if (infile.is_open())
    {
        while (getline(infile, line))
        {
            unsigned long delim = line.find(":");
            string key = line.substr(0, delim);
            string adj = line.substr(delim + 1);

            keys.push_back(key);
            data.push_back(key + " data");
            delim = adj.find(",");
            vector<string> adj_lst = {};
            // while (delim != string::npos)
            while (delim < adj.length())
            {
                adj_lst.push_back(adj.substr(0, delim));
                adj = adj.substr(delim + 1);
                delim = adj.find(",");
            }
            adj_lst.push_back(adj);
            adjs.push_back(adj_lst);
        }
    }
    Graph<string, string> *G = new Graph<string, string>(keys, data, adjs);
    return G;
}

// --------------------------------------------------------------
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
    try {
      if(G->get("2") == nullptr) {
          cout << "Incorrect result getting vertex \"v\"" << endl;
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
        if(!G->reachable(2.05, 2.05)) {
            cout << "Incorrectly identified \"W\" as unreachable from \"X\"" << endl;
        }
        if(G->reachable(15.612, 0.89)) {
            cout << "Incorrectly identified non-existant vetex \"0.89\" as reachable from \"15.612\"" << endl;
        }
    } catch(exception& e) {
        cerr << "Error testing reachable : " << e.what() << endl;
    }
}

void test_reachable_v2(Graph<float,string>* G) {
    try {
        if(!G->reachable("ata", "agx")) {
            cout << "Incorrectly identified adjacent vertex \"V\" as unreachable from \"R\"" << endl;
        }
        if(!G->reachable("a", "agx")) {
            cout << "Incorrectly identified \"W\" as unreachable from \"X\"" << endl;
        }
        if(G->reachable("b", "")) {
            cout << "Incorrectly identified non-existant vetex \"0.89\" as reachable from \"15.612\"" << endl;
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

        // // data type of vertex  != data type of new_distance
        // G->bfs("R");
        // float new_distance[8] = {3.1,0.2,0.5,1.245,0.11,1.81,2.22,2.09};
        // for(int i = 0; i < 8; i++){
        //     if(G->get(vertices[i])==nullptr || G->get(vertices[i])->distance != new_distance[i]) {
        //         cout << "Incorrect bfs result. Vertex " << vertices[i] << " should have distance " << distances[i] << " from source vertex \"t\"" << endl;
        //     }
        // }
    } catch(exception& e) {
        cerr << "Error testing bfs : " << e.what() << endl;
    }
}

void test_bfs_v1(Graph<int,char>* G) {
    try {
        G->bfs('y');
        char vertices[6] = {'y','x','u','z','t','v'};
        int distances[6] = {0,1,1,2,3,4};
        for(int i = 0; i < 6; i++){
            if(G->get(vertices[i])==nullptr || G->get(vertices[i])->distance != distances[i]) {
                cout << "Incorrect bfs result. Vertex " << vertices[i] << " should have distance " << distances[i] << " from source vertex \"y\"" << endl;
            }
        }
    } catch(exception& e) {
        cerr << "Error testing bfs : " << e.what() << endl;
    }
}

void test_bfs_v2(Graph<float,char>* G) {
    try {
      // get a node that does not exist in the graph
        G->bfs('s');
        char vertices[6] = {'y','x','u','z','t','v'};
        int distances[6] = {0,1,1,2,3,4};
        for(int i = 0; i < 6; i++){
            if(G->get(vertices[i])==nullptr || G->get(vertices[i])->distance != distances[i]) {
                cout << "Incorrect bfs result. Vertex " << vertices[i] << " should have distance " << distances[i] << " from source vertex \"y\"" << endl;
            }
        }
    } catch(exception& e) {
        cerr << "Error testing bfs : " << e.what() << endl;
    }
}
// --------------------------------------------------------------
void test_print_path_string(Graph<string, string> *G)
{
    try
    {
        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G->print_path("T", "V");
        cout.rdbuf(prevbuf);
        if (buffer.str() != "T -> S -> R -> V")
        {
            cout << "Incorrect path from vertex \"T\" to vertex \"V\". Expected: T -> S -> R -> V but got : " << buffer.str() << endl;
        }

        // not sure if this is the best way to clear the previous print output?
        buffer.str("");
        prevbuf = cout.rdbuf(buffer.rdbuf());

        G->print_path("T", "W");
        cout.rdbuf(prevbuf);
        if (buffer.str() != "T -> W")
        {
            cout << "Incorrect path from vertex \"T\" to vertex \"W\". Expected: T -> W but got : " << buffer.str() << endl;
        }

        buffer.str("");
        prevbuf = cout.rdbuf(buffer.rdbuf());

        G->print_path("R", "S");
        cout.rdbuf(prevbuf);
        if (buffer.str() != "R -> V -> S")
        {
            cout << "Incorrect path from vertex \"R\" to vertex \"S\". Expected: R -> V -> S but got : " << buffer.str() << endl;
        }

        buffer.str("");
        prevbuf = cout.rdbuf(buffer.rdbuf());

        G->print_path("S", "R");
        cout.rdbuf(prevbuf);
        if (buffer.str() != "S -> R")
        {
            cout << "Incorrect path from vertex \"S\" to vertex \"R\". Expected: S -> R but got : " << buffer.str() << endl;
        }

        buffer.str("");
        prevbuf = cout.rdbuf(buffer.rdbuf());

        G->print_path("W", "B");
        cout.rdbuf(prevbuf);
        if (buffer.str() != "")
        {
            cout << "Incorrect path from vertex \"W\" to vertex \"B\". Expected:  but got : " << buffer.str() << endl;
        }

        buffer.str("");
        prevbuf = cout.rdbuf(buffer.rdbuf());

        G->print_path("R", "X");
        cout.rdbuf(prevbuf);
        if (buffer.str() != "")
        {
            cout << "Incorrect path from vertex \"R\" to vertex \"X\". Expected:  but got : " << buffer.str() << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing print path : " << e.what() << endl;
    }
}

void test_print_path_int(Graph<int, int> *G)
{
    try
    {
        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G->print_path(4, 1);
        cout.rdbuf(prevbuf);

        if (buffer.str() != "4 -> 2 -> 1")
        {
            cout << "Incorrect path from vertex \"4\" to vertex \"1\". Expected: 4 -> 2 -> 1 but got : " << buffer.str() << endl;
        }

        buffer.str("");
        prevbuf = cout.rdbuf(buffer.rdbuf());

        G->print_path(3, 1);
        cout.rdbuf(prevbuf);

        if (buffer.str() != "")
        {
            cout << "Incorrect path from vertex \"3\" to vertex \"1\". Expected: but got : " << buffer.str() << endl;
        }

        buffer.str("");
        prevbuf = cout.rdbuf(buffer.rdbuf());

        G->print_path(5, 2);
        cout.rdbuf(prevbuf);

        if (buffer.str() != "5 -> 1 -> 2")
        {
            cout << "Incorrect path from vertex \"3\" to vertex \"1\". Expected: 5 -> 1 -> 2 but got : " << buffer.str() << endl;
        }

        buffer.str("");
        prevbuf = cout.rdbuf(buffer.rdbuf());

        G->print_path(6, 100);
        cout.rdbuf(prevbuf);

        if (buffer.str() != "")
        {
            cout << "Incorrect path from vertex \"6\" to vertex \"100\". Expected: but got : " << buffer.str() << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing print path : " << e.what() << endl;
    }
}

// void test_print_path_double(Graph<double, double> *G)
// {

//     try
//     {
//         stringstream buffer;
//         streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());

//         G->print_path(0.5, 9.910);
//         cout.rdbuf(prevbuf);
//         cout << buffer.str() << endl;
//         if (buffer.str() != "0.5 -> 5.99 -> 9.910")
//         {
//             cout << "Incorrect path from vertex \"0.5\" to vertex \"9.910\". Expected: 0.5 -> 5.99 -> 9.910 but got : " << buffer.str() << endl;
//         }

//         buffer.str("");
//         prevbuf = cout.rdbuf(buffer.rdbuf());

//         G->print_path(6.32, 7.67);
//         cout.rdbuf(prevbuf);
//         cout << buffer.str() << endl;
//         if (buffer.str() != "")
//         {
//             cout << "Incorrect path from vertex \"6.32\" to vertex \"7.67\". Expected: but got : " << buffer.str() << endl;
//         }

//         buffer.str("");
//         prevbuf = cout.rdbuf(buffer.rdbuf());

//         G->print_path(6.30, 7.6);
//         cout.rdbuf(prevbuf);
//         cout << buffer.str() << endl;
//         if (buffer.str() != "")
//         {
//             cout << "Incorrect path from vertex \"6.30\" to vertex \"7.6\". Expected: but got : " << buffer.str() << endl;
//         }

//         buffer.str("");
//         prevbuf = cout.rdbuf(buffer.rdbuf());

//         G->print_path(3.21, 3.21);
//         cout.rdbuf(prevbuf);
//         cout << buffer.str() << endl;
//         if (buffer.str() != "3.21 -> 3.21")
//         {
//             cout << "Incorrect path from vertex \"3.21\" to vertex \"3.21\". Expected: but got : " << buffer.str() << endl;
//         }
//     }
//     catch (exception &e)
//     {
//         cerr << "Error testing print path : " << e.what() << endl;
//     }
// }

void test_print_path_char(Graph<char, char> *G)
{

    try
    {
        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G->print_path('a', 'b');
        cout.rdbuf(prevbuf);
        if (buffer.str() != "")
        {
            cout << "Incorrect path from vertex \"a\" to vertex \"b\". Expected: but got : " << buffer.str() << endl;
        }

        buffer.str("");
        prevbuf = cout.rdbuf(buffer.rdbuf());

        G->print_path('a', 'a');
        cout.rdbuf(prevbuf);
        if (buffer.str() != "a")
        {
            cout << "Incorrect path from vertex \"a\" to vertex \"a\". Expected: a but got : " << buffer.str() << endl;
        }

        buffer.str("");
        prevbuf = cout.rdbuf(buffer.rdbuf());

        G->print_path('1', '3');
        cout.rdbuf(prevbuf);
        if (buffer.str() != "")
        {
            cout << "Incorrect path from vertex \"1\" to vertex \"3\". Expected: but got : " << buffer.str() << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing print path : " << e.what() << endl;
    }
}

void test_print_path_empty(Graph<string, string> *G)
{
    try
    {
        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G->print_path("T", "V");
        cout.rdbuf(prevbuf);
        if (buffer.str() != "")
        {
            cout << "Incorrect path from vertex \"T\" to vertex \"V\". Expected: but got : " << buffer.str() << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing print path : " << e.what() << endl;
    }
}

void test_edge_class_string(Graph<string, string> *G)
{
    try
    {
        string e_class = G->edge_class("R", "B"); // no edge
        if (e_class != "no edge")
        {
            cout << "Misidentified non-existant edge (\"R\", \"B\") as : " << e_class << endl;
        }

        // string e_class = G->edge_class("R", "V"); // tree edge
        // if (e_class != "tree edge")
        // {
        //     cout << "Misidentified tree edge (\"R\", \"V\") as : " << e_class << endl;
        // }
        // e_class = G->edge_class("X", "U"); // back edge
        // if (e_class != "back edge")
        // {
        //     cout << "Misidentified back edge (\"X\", \"U\") as : " << e_class << endl;
        // }
        // e_class = G->edge_class("R", "U"); // no edge
        // if (e_class != "no edge")
        // {
        //     cout << "Misidentified non-existant edge (\"R\", \"U\") as : " << e_class << endl;
        // }
        // e_class = G->edge_class("T", "W"); // forward edge
        // if (e_class != "forward edge")
        // {
        //     cout << "Misidentified forward edge (\"T\", \"W\") as : " << e_class << endl;
        // }
        // e_class = G->edge_class("T", "S"); // cross edge
        // if (e_class != "cross edge")
        // {
        //     cout << "Misidentified forward edge (\"T\", \"S\") as : " << e_class << endl;
        // }

        // e_class = G->edge_class("A", "B"); // no edge
        // if (e_class != "no edge")
        // {
        //     cout << "Misidentified non-existant edge (\"A\", \"B\") as : " << e_class << endl;
        // }
        
    }
    catch (exception &e)
    {
        cerr << "Error testing edge class : " << e.what() << endl;
    }
}

void test_edge_class_int(Graph<int, int> *G)
{
    try
    {
        string e_class = G->edge_class(1, 2); // tree edge
        if (e_class != "tree edge")
        {
            cout << "Misidentified tree edge (\"1\", \"2\") as : " << e_class << endl;
        }
        e_class = G->edge_class(6, 2); // cross edge
        if (e_class != "cross edge")
        {
            cout << "Misidentified cross edge (\"6\", \"2\") as : " << e_class << endl;
        }
        e_class = G->edge_class(1, 5); // no edge
        if (e_class != "no edge")
        {
            cout << "Misidentified non-existant edge (\"1\", \"4\") as : " << e_class << endl;
        }
        e_class = G->edge_class(1, 3); // no edge
        if (e_class != "no edge")
        {
            cout << "Misidentified non-existant edge (\"1\", \"3\") as : " << e_class << endl;
        }
        e_class = G->edge_class(3, 3); // back edge
        if (e_class != "back edge")
        {
            cout << "Misidentified back edge (\"3\", \"3\") as : " << e_class << endl;
        }
        e_class = G->edge_class(5, 2); // no edge
        if (e_class != "no edge")
        {
            cout << "Misidentified non-existant edge (\"5\", \"2\") as : " << e_class << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing edge class : " << e.what() << endl;
    }
}

// void test_edge_class_double(Graph<double, double> *G)
// {
//     try
//     {
//         string e_class = G->edge_class(0.5f, 5.99f); // tree edge
//         if (e_class != "tree edge")
//         {
//             cout << "Misidentified tree edge (\"0.5\", \"5.99\") as : " << e_class << endl;
//         }
//         e_class = G->edge_class(2.66f, 4.75757f); // tree edge
//         if (e_class != "tree edge")
//         {
//             cout << "Misidentified tree edge (\"2.66\", \"4.75757\") as : " << e_class << endl;
//         }
//         e_class = G->edge_class(8.2222f, 9.910f); // tree edge
//         if (e_class != "tree edge")
//         {
//             cout << "Misidentified tree edge (\"8.2222\", \"9.910\") as : " << e_class << endl;
//         }
//         e_class = G->edge_class(1.2f, 3.21f); // back edge
//         if (e_class != "back edge")
//         {
//             cout << "Misidentified back edge (\"1.2\", \"3.21\") as : " << e_class << endl;
//         }
//         e_class = G->edge_class(6.32f, 0.5f); // back edge
//         if (e_class != "back edge")
//         {
//             cout << "Misidentified back edge (\"6.32\", \"0.5\") as : " << e_class << endl;
//         }
//         e_class = G->edge_class(6.32f, 7.67f); // no edge
//         if (e_class != "no edge")
//         {
//             cout << "Misidentified non-existant edge (\"6.32\", \"7.67\") as : " << e_class << endl;
//         }
//         e_class = G->edge_class(2.66f, 9.910f); // forward edge
//         if (e_class != "forward edge")
//         {
//             cout << "Misidentified forward edge (\"2.66\", \"9.910\") as : " << e_class << endl;
//         }
//         e_class = G->edge_class(7.67f, 4.75757f); // cross edge
//         if (e_class != "cross edge")
//         {
//             cout << "Misidentified cross edge (\"7.67\", \"4.75757\") as : " << e_class << endl;
//         }
//         e_class = G->edge_class(7.67f, 3.21f); // cross edge
//         if (e_class != "cross edge")
//         {
//             cout << "Misidentified cross edge (\"7.67\", \"3.21\") as : " << e_class << endl;
//         }
//         e_class = G->edge_class(5.99f, 0.5f); // cross edge
//         if (e_class != "cross edge")
//         {
//             cout << "Misidentified cross edge (\"5.99\", \"0.5\") as : " << e_class << endl;
//         }
//     }
//     catch (exception &e)
//     {
//         cerr << "Error testing edge class : " << e.what() << endl;
//     }
// }

void test_edge_class_char(Graph<char, char> *G)
{
    try
    {
        string e_class = G->edge_class('r', 'v'); // no edge
        if (e_class != "no edge")
        {
            cout << "Misidentified no edge (\"r\", \"v\") as : " << e_class << endl;
        }

        // not 100% sure which edge this would classify as??
        e_class = G->edge_class('a', 'a'); // back edge??
        if (e_class != "back edge")
        {
            cout << "Misidentified back edge (\"a\", \"a\") as : " << e_class << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing edge class : " << e.what() << endl;
    }
}

void test_edge_class_empty(Graph<string, string> *G)
{
    try
    {
        string e_class = G->edge_class("R", "V"); // no edge
        if (e_class != "no edge")
        {
            cout << "Misidentified tree edge (\"R\", \"V\") as : " << e_class << endl;
        }
        e_class = G->edge_class("X", "U"); // no edge
        if (e_class != "no edge")
        {
            cout << "Misidentified non-existant edge (\"X\", \"U\") as : " << e_class << endl;
        }
        e_class = G->edge_class("R", "U"); // no edge
        if (e_class != "no edge")
        {
            cout << "Misidentified non-existant edge (\"R\", \"U\") as : " << e_class << endl;
        }
        e_class = G->edge_class("T", "W"); // no edge
        if (e_class != "no edge")
        {
            cout << "Misidentified forward edge (\"T\", \"W\") as : " << e_class << endl;
        }
        e_class = G->edge_class("T", "S"); // no edge
        if (e_class != "no edge")
        {
            cout << "Misidentified forward edge (\"T\", \"S\") as : " << e_class << endl;
        }

        e_class = G->edge_class("A", "B"); // no edge
        if (e_class != "no edge")
        {
            cout << "Misidentified non-existant edge (\"A\", \"B\") as : " << e_class << endl;
        }

        e_class = G->edge_class("R", "B"); // no edge
        if (e_class != "no edge")
        {
            cout << "Misidentified non-existant edge (\"R\", \"B\") as : " << e_class << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing edge class : " << e.what() << endl;
    }
}

void test_bfs_tree_string(Graph<string, string> *G)
{
    try
    {
        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G->bfs_tree("T");
        cout.rdbuf(prevbuf);
        if (buffer.str() != "T\nS U W\nR Y X\nV")
        {
            cout << "Incorrect bfs tree. Expected : \nT\nS U W\nR Y X\nV \nbut got :\n"
                 << buffer.str() << endl;
        }

        buffer.str("");
        prevbuf = cout.rdbuf(buffer.rdbuf());
        
        G->bfs_tree("R");
        cout.rdbuf(prevbuf);
        if (buffer.str() != "R\nV\nS")
        {
            cout << "Incorrect bfs tree. Expected : \nR\nV\nS \nbut got :\n"
                 << buffer.str() << endl;
        }

        buffer.str("");
        prevbuf = cout.rdbuf(buffer.rdbuf());

        G->bfs_tree("A");
        cout.rdbuf(prevbuf);
        if (buffer.str() != "")
        {
            cout << "Incorrect bfs tree. Expected : \nbut got :\n"
                 << buffer.str() << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing bfs tree : " << e.what() << endl;
    }
}

void test_bfs_tree_int(Graph<int, int> *G)
{
    try
    {
        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G->bfs_tree(5);
        cout.rdbuf(prevbuf);
        if (buffer.str() != "5\n1\n2")
        {
            cout << "Incorrect bfs tree. Expected : \n5\n1\n2 \nbut got :\n"
                 << buffer.str() << endl;
        }

        buffer.str("");
        prevbuf = cout.rdbuf(buffer.rdbuf());

        G->bfs_tree(6);
        cout.rdbuf(prevbuf);
        if (buffer.str() != "6\n2\n1")
        {
            cout << "Incorrect bfs tree. Expected : \n6\n2\n1 \nbut got :\n"
                 << buffer.str() << endl;
        }

        buffer.str("");
        prevbuf = cout.rdbuf(buffer.rdbuf());

        G->bfs_tree(3);
        cout.rdbuf(prevbuf);
        if (buffer.str() != "3")
        {
            cout << "Incorrect bfs tree. Expected : 3 \nbut got :\n"
                 << buffer.str() << endl;
        }

        buffer.str("");
        prevbuf = cout.rdbuf(buffer.rdbuf());

        G->bfs_tree(10);
        cout.rdbuf(prevbuf);
        if (buffer.str() != "")
        {
            cout << "Incorrect bfs tree. Expected : \nbut got :\n"
                 << buffer.str() << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing bfs tree : " << e.what() << endl;
    }
}

// void test_bfs_tree_double(Graph<double, double> *G)
// {
//     try
//     {
//         stringstream buffer;
//         streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
//         G->bfs_tree(0.5f);
//         cout.rdbuf(prevbuf);
//         if (buffer.str() != "0.5\n5.99\n2.66\n9.910 3.21 4.75757")
//         {
//             cout << "Incorrect bfs tree. Expected : \n0.5\n5.99\n2.66\n9.910 3.21 4.75757 \nbut got :\n"
//                  << buffer.str() << endl;
//         }

//         buffer.str("");
//         prevbuf = cout.rdbuf(buffer.rdbuf());

//         G->bfs_tree(0.56f);
//         cout.rdbuf(prevbuf);
//         if (buffer.str() != "")
//         {
//             cout << "Incorrect bfs tree. Expected : \n \nbut got :\n"
//                  << buffer.str() << endl;
//         }

//         buffer.str("");
//         prevbuf = cout.rdbuf(buffer.rdbuf());

//         G->bfs_tree(7.67f);
//         cout.rdbuf(prevbuf);
//         if (buffer.str() != "7.67\n3.21 4.75757\n0.5\n5.99\n2.66\n9.910 3.21 4.75757")
//         {
//             cout << "Incorrect bfs tree. Expected : \n7.67\n3.21 4.75757\n0.5\n5.99\n2.66\n9.910 3.21 4.75757 \nbut got :\n"
//                  << buffer.str() << endl;
//         }

//         buffer.str("");
//         prevbuf = cout.rdbuf(buffer.rdbuf());

//         G->bfs_tree(3.21f);
//         cout.rdbuf(prevbuf);
//         if (buffer.str() != "3.21")
//         {
//             cout << "Incorrect bfs tree. Expected : \n3.21 \nbut got :\n"
//                  << buffer.str() << endl;
//         }

//         buffer.str("");
//         prevbuf = cout.rdbuf(buffer.rdbuf());

//         G->bfs_tree(8.2222f);
//         cout.rdbuf(prevbuf);
//         if (buffer.str() != "8.2222\n9.910")
//         {
//             cout << "Incorrect bfs tree. Expected : \n8.2222\n9.910 \nbut got :\n"
//                  << buffer.str() << endl;
//         }
//     }
//     catch (exception &e)
//     {
//         cerr << "Error testing bfs tree : " << e.what() << endl;
//     }
// }

void test_bfs_tree_char(Graph<char, char> *G)
{
    try
    {
        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G->bfs_tree('a');
        cout.rdbuf(prevbuf);
        if (buffer.str() != "a")
        {
            cout << "Incorrect bfs tree. Expected : \na \nbut got :\n"
                 << buffer.str() << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing bfs tree : " << e.what() << endl;
    }
}

void test_bfs_tree_empty(Graph<string, string> *G)
{
    try
    {
        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G->bfs_tree("T");
        cout.rdbuf(prevbuf);
        if (buffer.str() != "")
        {
            cout << "Incorrect bfs tree. Expected : \nbut got :\n"
                 << buffer.str() << endl;
        }

        buffer.str("");
        prevbuf = cout.rdbuf(buffer.rdbuf());

        G->bfs_tree("R");
        cout.rdbuf(prevbuf);
        if (buffer.str() != "")
        {
            cout << "Incorrect bfs tree. Expected : \nbut got :\n"
                 << buffer.str() << endl;
        }

        buffer.str("");
        prevbuf = cout.rdbuf(buffer.rdbuf());

        G->bfs_tree("A");
        cout.rdbuf(prevbuf);
        if (buffer.str() != "")
        {
            cout << "Incorrect bfs tree. Expected : \nbut got :\n"
                 << buffer.str() << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing bfs tree : " << e.what() << endl;
    }
}

int main() {
    // Ichhit's test cases
    Graph<string,string>* stringG = generate_graph("graph_description.txt");

    vector<int> keys1{1,2,3,4,5,6};
    vector<int> data1{0, 18, 3, 77, 2, 4};
    vector<vector<int> > edges1{{2},{1},{3},{2,5},{1},{2}};
    Graph<int,int>* intG = new Graph<int,int>(keys1, data1, edges1);

    vector<double> keys2{0.5,1.2,2.66,3.21,4.75757,5.99,6.32,7.67,8.2222,9.910};
    vector<double> data2{0.58, 18.4, 3.2, 77.77, 2.2, 4.67, 60.0, 854.02, 644.23};
    vector<vector<double> > edges2{{5.99},{3.21,7.67},{4.75757,3.21,8.2222,9.910},{3.21},{0.5},{2.66,0.5},{0.5},{7.67,4.75757,3.21},{8.2222,9.910},{9.910}};
    Graph<double,double>* doubleG = new Graph<double,double>(keys2, data2, edges2);

    vector<char> keys3{'a'};
    vector<char> data3{'s'};
    vector<vector<char> > edges3{{'a'}};
    Graph<char,char>* charG = new Graph<char,char>(keys3, data3, edges3);

    vector<string> keys4;
    vector<string> data4;
    vector<vector<string> > edges4;
    Graph<string,string>* emptyG = new Graph<string,string>(keys4, data4, edges4);

    test_print_path_string(stringG);
    test_print_path_int(intG);
    // test_print_path_double(doubleG);
    test_print_path_char(charG);
    test_print_path_empty(emptyG);

    test_edge_class_string(stringG);
    test_edge_class_int(intG);
    // test_edge_class_double(doubleG);
    test_edge_class_char(charG);
    test_edge_class_empty(emptyG);

    test_bfs_tree_string(stringG);
    test_bfs_tree_int(intG);
    // test_bfs_tree_double(doubleG);
    test_bfs_tree_char(charG);
    test_bfs_tree_empty(emptyG);

    delete stringG;
    delete charG;
    delete intG;
    delete doubleG;

    cout << "Testing completed 1" << endl;

    // // Tran's test cases
    // vector<string> A{"R", "V", "S", "T", "U", "Y", "W", "X"};
    // vector<int> B{12,21,39,53,47,11};
    // vector<string> A1{"A", "B", "C", "D", "E", "F", "G", "H"};
    // vector<int> B1{3,2,1,1,0,2,1,2};
    // vector<vector<string>> A_edges {{"V"}, {"S"}, {"R"}, {"S","U","W"}, {"Y"}, {"W"}, {"X"}, {"U"}};
    // vector<char> F{'x','y','z','t','u','v'};
    // vector<string> A2{"aa", "axv", "ata", "auv", "agx", "gau", "xxx", "tax", "gta", "uaa"};
    // vector<vector<string>> A2_edges{{"a"}, {"tax", "uaa"}, {"auv"}, {"xxx"}, {"aa", "axv", "ata"}, {"gta"}, {"axv","xxx"},{"ata", "ttt"},{"aa"}, {"gau", "ggg", "auv"}};
    // vector<vector<char>> F_edges{{'y','z'},{'x','u'},{'t'},{'x','u','v'},{'x'},{'y','z'}};
    // vector<float> C{2.05, 4.11, 8.974, 2.336, 12.179, 15.612, 19.014, 17.152};
    // vector<vector<float>> C_edges{{4.11, 15.612}, {}, {12.179, 17.152}, {8.974, 2.05}, {2.336, 19.014}, {15.612, 19.014, 17.152}, {4.11}, {2.05}, {2.336, 12.179}};

    // Graph<string, string>* G = new Graph<string, string>(A, A1, A_edges);
    // Graph<int, string>* G1 = new Graph<int, string>(A, B1, A_edges);
    // Graph<int,char>* G2 = new Graph<int,char>(F,B,F_edges);
    // Graph<string,float>* G3 = new Graph<string,float>(C,A, C_edges);
    // Graph<string,string> *G4 = new Graph<string,string>(A,A1,A_edges);
    // // Graph<float,char> *G5 = new Graph<float,char>(F,C,F_edges);
    // // Graph<float,string> *G6 = new Graph<float,string>(A2,C,A2_edges);

    // test_get(G);
    // // test_get_v1(G1);
    // test_get_v2(G2);

    // test_reachable(G);
    // test_reachable_v1(G3);
    // // test_reachable_v2(G6);
    
    // test_bfs(G);
    // test_bfs_v1(G2);
    // // test_bfs_v2(G5);

    // delete G;
    // delete G1;
    // delete G2;
    // delete G3;
    // delete G4;
    
    // cout << "Testing completed 2" << endl;
    return 0;
}
