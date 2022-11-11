#include <fstream>
#include <sstream>
#include "graph.cpp"

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
    Graph<string,string>* G = new Graph<string, string>(keys, data, adjs);
    return G;
}

void test_bfs_tree(Graph<string,string>* G) {
    G->bfs_tree("R");
    G->bfs_tree("V");
    G->bfs_tree("S");
    G->bfs_tree("T");
    G->bfs_tree("U");
    G->bfs_tree("Y");
    G->bfs_tree("W");
    // try {
    //     // stringstream buffer;
    //     // streambuf* prevbuf = cout.rdbuf(buffer.rdbuf());
    //     // G->bfs_tree("T");
    //     // cout.rdbuf(prevbuf);
    //     // if(buffer.str() != "T\nS U W\nR Y X\nV") {
    //     //     cout << "Incorrect bfs tree. Expected : \nT\nS U W\nR Y X\nV \nbut got :\n" << buffer.str() << endl;
    //     // }
    //     G->bfs_tree("R");
    //     // cout.rdbuf(prevbuf);
    //     // if (buffer.str() != "R\nV\nS")
    //     // {
    //     //     cout << "Incorrect bfs tree. Expected : \nR\nV\nS \nbut got :\n"
    //     //          << buffer.str() << endl;
    //     // }
    // } catch(exception& e) {
    //     cerr << "Error testing bfs tree : " << e.what() << endl;
    // }

}

int main()
{

    Graph<string, string> *G = generate_graph("graph_description.txt");
    test_bfs_tree(G);

    cout << "Testing completed" << endl;

    delete G;

    return 0;
}