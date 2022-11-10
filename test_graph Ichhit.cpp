/*
Authors: 
Date: November 11 , 2022
CS271 Fall 2022
*/

#include <fstream>
#include <sstream>
#include "graph.cpp"

Graph<string, string>* generate_graph(string fname){
    string line;
    ifstream infile(fname);
    vector<string> keys;
    vector<string> data;
    vector<vector<string> > adjs;
    if(infile.is_open()){
        while(getline(infile, line)){
            unsigned long delim = line.find(":");
            string key = line.substr(0, delim);
            string adj = line.substr(delim+1);
            
            keys.push_back(key);
            data.push_back(key + " data");
            delim = adj.find(",");
            vector<string> adj_lst;
            while(delim != string::npos){
                adj_lst.push_back(adj.substr(0, delim));
                adj = adj.substr(delim+1);
                delim = adj.find(",");
            }
            adj_lst.push_back(adj);
            adjs.push_back(adj_lst);
        }
    }
    Graph<string,string>* G = new Graph<string, string>(keys, data, adjs);
    return G;
}

void test_print_path_string(Graph<string,string>* G) {
    try {
        stringstream buffer;
        streambuf* prevbuf = cout.rdbuf(buffer.rdbuf());
        G->print_path("T", "V");
        cout.rdbuf(prevbuf);
        if(buffer.str()!="T -> S -> R -> V") {
            cout << "Incorrect path from vertex \"T\" to vertex \"V\". Expected: T -> S -> R -> V but got : " << buffer.str() << endl;
        }

        //not sure if this is the best way to clear the previous print output?
        buffer.str("");        
        prevbuf = cout.rdbuf(buffer.rdbuf());

        G->print_path("T", "W");
        cout.rdbuf(prevbuf);
        if(buffer.str()!="T -> W") {
            cout << "Incorrect path from vertex \"T\" to vertex \"W\". Expected: T -> W but got : " << buffer.str() << endl;
        }

        buffer.str("");        
        prevbuf = cout.rdbuf(buffer.rdbuf());

        G->print_path("R", "S");
        cout.rdbuf(prevbuf);
        if(buffer.str()!="R -> V -> S") {
            cout << "Incorrect path from vertex \"R\" to vertex \"S\". Expected: R -> V -> S but got : " << buffer.str() << endl;
        }

        buffer.str("");        
        prevbuf = cout.rdbuf(buffer.rdbuf());

        G->print_path("S", "R");
        cout.rdbuf(prevbuf);
        if(buffer.str()!="S -> R") {
            cout << "Incorrect path from vertex \"S\" to vertex \"R\". Expected: S -> R but got : " << buffer.str() << endl;
        }

        buffer.str("");        
        prevbuf = cout.rdbuf(buffer.rdbuf());

        G->print_path("W", "B");
        cout.rdbuf(prevbuf);
        if(buffer.str()!="") {
            cout << "Incorrect path from vertex \"W\" to vertex \"B\". Expected:  but got : " << buffer.str() << endl;
        }

        buffer.str("");        
        prevbuf = cout.rdbuf(buffer.rdbuf());

        G->print_path("R", "X");
        cout.rdbuf(prevbuf);
        if(buffer.str()!="") {
            cout << "Incorrect path from vertex \"R\" to vertex \"X\". Expected:  but got : " << buffer.str() << endl;
        }


    } catch(exception& e) {
        cerr << "Error testing print path : " << e.what() << endl;
    }
}

void test_print_path_int(Graph<int,int>* G){
   
     try {
        stringstream buffer;
        streambuf* prevbuf = cout.rdbuf(buffer.rdbuf());
        G->print_path(4, 1);
        cout.rdbuf(prevbuf);
       
        if(buffer.str()!="4 -> 2 -> 1") {
            cout << "Incorrect path from vertex \"4\" to vertex \"1\". Expected: 4 -> 2 -> 1 but got : " << buffer.str() << endl;
        }

        buffer.str("");        
        prevbuf = cout.rdbuf(buffer.rdbuf());

        G->print_path(3, 1);
        cout.rdbuf(prevbuf);
      
        if(buffer.str()!="") {
            cout << "Incorrect path from vertex \"3\" to vertex \"1\". Expected: but got : " << buffer.str() << endl;
        }

        buffer.str("");        
        prevbuf = cout.rdbuf(buffer.rdbuf());

        G->print_path(5, 2);
        cout.rdbuf(prevbuf);
       
        if(buffer.str()!="5 -> 1 -> 2") {
            cout << "Incorrect path from vertex \"3\" to vertex \"1\". Expected: 5 -> 1 -> 2 but got : " << buffer.str() << endl;
        }

        buffer.str("");        
        prevbuf = cout.rdbuf(buffer.rdbuf());

        G->print_path(6,100);
        cout.rdbuf(prevbuf);
       
        if(buffer.str()!="") {
            cout << "Incorrect path from vertex \"6\" to vertex \"100\". Expected: but got : " << buffer.str() << endl;
        }

    } catch(exception& e) {
        cerr << "Error testing print path : " << e.what() << endl;
    }  
}

void test_print_path_float(Graph<float,float>* G){
   
     try {
        stringstream buffer;
        streambuf* prevbuf = cout.rdbuf(buffer.rdbuf());
        
        G->print_path(0.5f, 9.910f);
        cout.rdbuf(prevbuf);
        cout << buffer.str() << endl;
        if(buffer.str()!="0.5 -> 5.99 -> 9.910") {
            cout << "Incorrect path from vertex \"0.5\" to vertex \"9.910\". Expected: 0.5 -> 5.99 -> 9.910 but got : " << buffer.str() << endl;
        }

        buffer.str("");        
        prevbuf = cout.rdbuf(buffer.rdbuf());

        G->print_path(6.32f, 7.67f);
        cout.rdbuf(prevbuf);
        cout << buffer.str() << endl;
        if(buffer.str()!="") {
            cout << "Incorrect path from vertex \"6.32\" to vertex \"7.67\". Expected: but got : " << buffer.str() << endl;
        }

        buffer.str("");        
        prevbuf = cout.rdbuf(buffer.rdbuf());

        G->print_path(6.30f, 7.6f);
        cout.rdbuf(prevbuf);
        cout << buffer.str() << endl;
        if(buffer.str()!="") {
            cout << "Incorrect path from vertex \"6.30\" to vertex \"7.6\". Expected: but got : " << buffer.str() << endl;
        }

        buffer.str("");        
        prevbuf = cout.rdbuf(buffer.rdbuf());

        G->print_path(3.21f, 3.21f);
        cout.rdbuf(prevbuf);
        cout << buffer.str() << endl;
        if(buffer.str()!="3.21 -> 3.21") {
            cout << "Incorrect path from vertex \"3.21\" to vertex \"3.21\". Expected: but got : " << buffer.str() << endl;
        }
    } catch(exception& e) {
        cerr << "Error testing print path : " << e.what() << endl;
    }  
}

void test_print_path_char(Graph<char,char>* G){
   
     try {
        stringstream buffer;
        streambuf* prevbuf = cout.rdbuf(buffer.rdbuf());
        G->print_path('a', 'b');
        cout.rdbuf(prevbuf);
        cout << buffer.str() << endl;
        if(buffer.str()!="") {
            cout << "Incorrect path from vertex \"a\" to vertex \"b\". Expected: but got : " << buffer.str() << endl;
        }

        buffer.str("");        
        prevbuf = cout.rdbuf(buffer.rdbuf());

        G->print_path('a', 'a');
        cout.rdbuf(prevbuf);
        cout << buffer.str() << endl;
        if(buffer.str()!="a -> a") {
            cout << "Incorrect path from vertex \"a\" to vertex \"a\". Expected: a -> a but got : " << buffer.str() << endl;
        }

        buffer.str("");        
        prevbuf = cout.rdbuf(buffer.rdbuf());

        G->print_path('1', '3');
        cout.rdbuf(prevbuf);
        cout << buffer.str() << endl;
        if(buffer.str()!="") {
            cout << "Incorrect path from vertex \"1\" to vertex \"3\". Expected: but got : " << buffer.str() << endl;
        }

    } catch(exception& e) {
        cerr << "Error testing print path : " << e.what() << endl;
    }  
}

void test_print_path_empty(Graph<string,string>* G) {
    try {
        stringstream buffer;
        streambuf* prevbuf = cout.rdbuf(buffer.rdbuf());
        G->print_path("T", "V");
        cout.rdbuf(prevbuf);
        if(buffer.str()!="") {
            cout << "Incorrect path from vertex \"T\" to vertex \"V\". Expected: but got : " << buffer.str() << endl;
        }

    } catch(exception& e) {
        cerr << "Error testing print path : " << e.what() << endl;
    }
}

void test_edge_class_string(Graph<string,string>* G) {
    try {
        string e_class =  G->edge_class("R", "V"); // tree edge
        if(e_class != "tree edge") {
            cout << "Misidentified tree edge (\"R\", \"V\") as : " << e_class << endl;
        }
        e_class = G->edge_class("X", "U"); // back edge
        if(e_class != "back edge") {
            cout << "Misidentified back edge (\"X\", \"U\") as : " << e_class << endl;
        }
        e_class =  G->edge_class("R", "U"); // no edge
        if(e_class != "no edge") {
            cout << "Misidentified non-existant edge (\"R\", \"U\") as : " << e_class << endl;
        }
        e_class = G->edge_class("T", "W"); // forward edge
        if(e_class != "forward edge") {
            cout << "Misidentified forward edge (\"T\", \"W\") as : " << e_class << endl;
        }
        e_class = G->edge_class("T", "S"); // cross edge
        if(e_class != "cross edge") {
            cout << "Misidentified forward edge (\"T\", \"S\") as : " << e_class << endl;
        }

        e_class =  G->edge_class("A", "B"); // no edge
        if(e_class != "no edge") {
            cout << "Misidentified non-existant edge (\"A\", \"B\") as : " << e_class << endl;
        }

        e_class =  G->edge_class("R", "B"); // no edge
        if(e_class != "no edge") {
            cout << "Misidentified non-existant edge (\"R\", \"B\") as : " << e_class << endl;
        }

    } catch(exception& e) {
        cerr << "Error testing edge class : " << e.what() << endl;
    }
    
}

void test_edge_class_int(Graph<int,int>* G) {
    try {
        string e_class =  G->edge_class(1, 2); // tree edge
        if(e_class != "tree edge") {
            cout << "Misidentified tree edge (\"1\", \"2\") as : " << e_class << endl;
        }
        e_class = G->edge_class(6, 2); // cross edge
        if(e_class != "cross edge") {
            cout << "Misidentified cross edge (\"6\", \"2\") as : " << e_class << endl;
        }
        e_class =  G->edge_class(1, 5); // no edge
        if(e_class != "no edge") {
            cout << "Misidentified non-existant edge (\"1\", \"4\") as : " << e_class << endl;
        }
        e_class = G->edge_class(1, 3); // no edge
        if(e_class != "no edge") {
            cout << "Misidentified non-existant edge (\"1\", \"3\") as : " << e_class << endl;
        }
        e_class = G->edge_class(3,3); // back edge
        if(e_class != "back edge") {
            cout << "Misidentified back edge (\"3\", \"3\") as : " << e_class << endl;
        }
        e_class = G->edge_class(5,2); // no edge
        if(e_class != "no edge") {
            cout << "Misidentified non-existant edge (\"5\", \"2\") as : " << e_class << endl;
        }
    } catch(exception& e) {
        cerr << "Error testing edge class : " << e.what() << endl;
    }
    
}

void test_edge_class_float(Graph<float,float>* G) {
    try {
        string e_class =  G->edge_class(0.5f, 5.99f); // tree edge
        if(e_class != "tree edge") {
            cout << "Misidentified tree edge (\"0.5\", \"5.99\") as : " << e_class << endl;
        }
        e_class =  G->edge_class(2.66f, 4.75757f); // tree edge
        if(e_class != "tree edge") {
            cout << "Misidentified tree edge (\"2.66\", \"4.75757\") as : " << e_class << endl;
        }
        e_class =  G->edge_class(8.2222f, 9.910f); // tree edge
        if(e_class != "tree edge") {
            cout << "Misidentified tree edge (\"8.2222\", \"9.910\") as : " << e_class << endl;
        }
        e_class = G->edge_class(1.2f, 3.21f); // back edge
        if(e_class != "back edge") {
            cout << "Misidentified back edge (\"1.2\", \"3.21\") as : " << e_class << endl;
        }
         e_class = G->edge_class(6.32f, 0.5f); // back edge
        if(e_class != "back edge") {
            cout << "Misidentified back edge (\"6.32\", \"0.5\") as : " << e_class << endl;
        }
        e_class =  G->edge_class(6.32f, 7.67f); // no edge
        if(e_class != "no edge") {
            cout << "Misidentified non-existant edge (\"6.32\", \"7.67\") as : " << e_class << endl;
        }
        e_class = G->edge_class(2.66f, 9.910f); // forward edge
        if(e_class != "forward edge") {
            cout << "Misidentified forward edge (\"2.66\", \"9.910\") as : " << e_class << endl;
        }
        e_class = G->edge_class(7.67f, 4.75757f); // cross edge
        if(e_class != "cross edge") {
            cout << "Misidentified cross edge (\"7.67\", \"4.75757\") as : " << e_class << endl;
        }
        e_class = G->edge_class(7.67f, 3.21f); // cross edge
        if(e_class != "cross edge") {
            cout << "Misidentified cross edge (\"7.67\", \"3.21\") as : " << e_class << endl;
        }
        e_class = G->edge_class(5.99f, 0.5f); // cross edge
        if(e_class != "cross edge") {
            cout << "Misidentified cross edge (\"5.99\", \"0.5\") as : " << e_class << endl;
        }
    } catch(exception& e) {
        cerr << "Error testing edge class : " << e.what() << endl;
    }
    
}

void test_edge_class_char(Graph<char,char>* G) {
    try {
        string e_class =  G->edge_class('r', 'v'); // no edge
        if(e_class != "no edge") {
            cout << "Misidentified no edge (\"r\", \"v\") as : " << e_class << endl;
        }

        //not 100% sure which edge this would classify as??
        e_class = G->edge_class('a', 'a'); // back edge??
        if(e_class != "back edge") {
            cout << "Misidentified back edge (\"a\", \"a\") as : " << e_class << endl;
        } 
    } catch(exception& e) {
        cerr << "Error testing edge class : " << e.what() << endl;
    }
    
}

void test_edge_class_empty(Graph<string,string>* G) {
    try {
        string e_class =  G->edge_class("R", "V"); // no edge
        if(e_class != "no edge") {
            cout << "Misidentified tree edge (\"R\", \"V\") as : " << e_class << endl;
        }
        e_class = G->edge_class("X", "U"); // no edge
        if(e_class != "no edge") {
            cout << "Misidentified non-existant edge (\"X\", \"U\") as : " << e_class << endl;
        }
        e_class =  G->edge_class("R", "U"); // no edge
        if(e_class != "no edge") {
            cout << "Misidentified non-existant edge (\"R\", \"U\") as : " << e_class << endl;
        }
        e_class = G->edge_class("T", "W"); // no edge
        if(e_class != "no edge") {
            cout << "Misidentified forward edge (\"T\", \"W\") as : " << e_class << endl;
        }
        e_class = G->edge_class("T", "S"); // no edge
        if(e_class != "no edge") {
            cout << "Misidentified forward edge (\"T\", \"S\") as : " << e_class << endl;
        }

        e_class =  G->edge_class("A", "B"); // no edge
        if(e_class != "no edge") {
            cout << "Misidentified non-existant edge (\"A\", \"B\") as : " << e_class << endl;
        }

        e_class =  G->edge_class("R", "B"); // no edge
        if(e_class != "no edge") {
            cout << "Misidentified non-existant edge (\"R\", \"B\") as : " << e_class << endl;
        }

    } catch(exception& e) {
        cerr << "Error testing edge class : " << e.what() << endl;
    }
    
}

void test_bfs_tree_string(Graph<string,string>* G) {
    try {
        stringstream buffer;
        streambuf* prevbuf = cout.rdbuf(buffer.rdbuf());
        G->bfs_tree("T");
        cout.rdbuf(prevbuf);
        if(buffer.str() != "T\nS U W\nR Y X\nV") {
            cout << "Incorrect bfs tree. Expected : \nT\nS U W\nR Y X\nV \nbut got :\n" << buffer.str() << endl;
        }

        buffer.str("");        
        prevbuf = cout.rdbuf(buffer.rdbuf());

        G->bfs_tree("R");
        cout.rdbuf(prevbuf);
        if(buffer.str() != "R\nV\nS") {
            cout << "Incorrect bfs tree. Expected : \nR\nV\nS \nbut got :\n" << buffer.str() << endl;
        }

        buffer.str("");        
        prevbuf = cout.rdbuf(buffer.rdbuf());

        G->bfs_tree("A");
        cout.rdbuf(prevbuf);
        if(buffer.str() != "") {
            cout << "Incorrect bfs tree. Expected : \nbut got :\n" << buffer.str() << endl;
        }

    } catch(exception& e) {
        cerr << "Error testing bfs tree : " << e.what() << endl;
    }
    
}

void test_bfs_tree_int(Graph<int,int>* G) {
    try {
        stringstream buffer;
        streambuf* prevbuf = cout.rdbuf(buffer.rdbuf());
        G->bfs_tree(5);
        cout.rdbuf(prevbuf);
        if(buffer.str() != "5\n1\n2") {
            cout << "Incorrect bfs tree. Expected : \n5\n1\n2 \nbut got :\n" << buffer.str() << endl;
        }

        buffer.str("");        
        prevbuf = cout.rdbuf(buffer.rdbuf());

        G->bfs_tree(6);
        cout.rdbuf(prevbuf);
        if(buffer.str() != "6\n2\n1") {
            cout << "Incorrect bfs tree. Expected : \n6\n2\n1 \nbut got :\n" << buffer.str() << endl;
        }

        buffer.str("");        
        prevbuf = cout.rdbuf(buffer.rdbuf());

        G->bfs_tree(3);
        cout.rdbuf(prevbuf);
        if(buffer.str() != "3") {
            cout << "Incorrect bfs tree. Expected : 3 \nbut got :\n" << buffer.str() << endl;
        }

        buffer.str("");        
        prevbuf = cout.rdbuf(buffer.rdbuf());

        G->bfs_tree(10);
        cout.rdbuf(prevbuf);
        if(buffer.str() != "") {
            cout << "Incorrect bfs tree. Expected : \nbut got :\n" << buffer.str() << endl;
        }


    } catch(exception& e) {
        cerr << "Error testing bfs tree : " << e.what() << endl;
    }
    
}

void test_bfs_tree_float(Graph<float,float>* G) {
    try {
        stringstream buffer;
        streambuf* prevbuf = cout.rdbuf(buffer.rdbuf());
        G->bfs_tree(0.5f);
        cout.rdbuf(prevbuf);
        if(buffer.str() != "0.5\n5.99\n2.66\n9.910 3.21 4.75757") {
            cout << "Incorrect bfs tree. Expected : \n0.5\n5.99\n2.66\n9.910 3.21 4.75757 \nbut got :\n" << buffer.str() << endl;
        }

        buffer.str("");        
        prevbuf = cout.rdbuf(buffer.rdbuf());

        G->bfs_tree(0.56f);
        cout.rdbuf(prevbuf);
        if(buffer.str() != "") {
            cout << "Incorrect bfs tree. Expected : \n \nbut got :\n" << buffer.str() << endl;
        }

        buffer.str("");        
        prevbuf = cout.rdbuf(buffer.rdbuf());

        G->bfs_tree(7.67f);
        cout.rdbuf(prevbuf);
        if(buffer.str() != "7.67\n3.21 4.75757\n0.5\n5.99\n2.66\n9.910 3.21 4.75757") {
            cout << "Incorrect bfs tree. Expected : \n7.67\n3.21 4.75757\n0.5\n5.99\n2.66\n9.910 3.21 4.75757 \nbut got :\n" << buffer.str() << endl;
        }

        buffer.str("");        
        prevbuf = cout.rdbuf(buffer.rdbuf());

        G->bfs_tree(3.21f);
        cout.rdbuf(prevbuf);
        if(buffer.str() != "3.21") {
            cout << "Incorrect bfs tree. Expected : \n3.21 \nbut got :\n" << buffer.str() << endl;
        }

        buffer.str("");        
        prevbuf = cout.rdbuf(buffer.rdbuf());

        G->bfs_tree(8.2222f);
        cout.rdbuf(prevbuf);
        if(buffer.str() != "8.2222\n9.910") {
            cout << "Incorrect bfs tree. Expected : \n8.2222\n9.910 \nbut got :\n" << buffer.str() << endl;
        }


    } catch(exception& e) {
        cerr << "Error testing bfs tree : " << e.what() << endl;
    }
    
}

void test_bfs_tree_char(Graph<char,char>* G) {
    try {
        stringstream buffer;
        streambuf* prevbuf = cout.rdbuf(buffer.rdbuf());
        G->bfs_tree('a');
        cout.rdbuf(prevbuf);
        if(buffer.str() != "a") {
            cout << "Incorrect bfs tree. Expected : \na \nbut got :\n" << buffer.str() << endl;
        }
    } catch(exception& e) {
        cerr << "Error testing bfs tree : " << e.what() << endl;
    }
    
}

void test_bfs_tree_empty(Graph<string,string>* G) {
    try {
        stringstream buffer;
        streambuf* prevbuf = cout.rdbuf(buffer.rdbuf());
        G->bfs_tree("T");
        cout.rdbuf(prevbuf);
        if(buffer.str() != "") {
            cout << "Incorrect bfs tree. Expected : \nbut got :\n" << buffer.str() << endl;
        }

        buffer.str("");        
        prevbuf = cout.rdbuf(buffer.rdbuf());

        G->bfs_tree("R");
        cout.rdbuf(prevbuf);
        if(buffer.str() != "") {
            cout << "Incorrect bfs tree. Expected : \nbut got :\n" << buffer.str() << endl;
        }

        buffer.str("");        
        prevbuf = cout.rdbuf(buffer.rdbuf());

        G->bfs_tree("A");
        cout.rdbuf(prevbuf);
        if(buffer.str() != "") {
            cout << "Incorrect bfs tree. Expected : \nbut got :\n" << buffer.str() << endl;
        }

    } catch(exception& e) {
        cerr << "Error testing bfs tree : " << e.what() << endl;
    }
    
}


int main() {

    Graph<string,string>* stringG = generate_graph("graph_description.txt");

    vector<int> keys1{1,2,3,4,5,6};
    vector<int> data1{0, 18, 3, 77, 2, 4};
    vector<vector<int> > edges1{{2},{1},{3},{2,5},{1},{2}};
    Graph<int,int>* intG = new Graph<int,int>(keys1, data1, edges1);

    vector<float> keys2{0.5f,1.2f,2.66f,3.21f,4.75757f,5.99f,6.32f,7.67f,8.2222f,9.910f};
    vector<float> data2{0.58f, 18.4f, 3.2f, 77.77f, 2.2f, 4.67f, 60.0f, 854.02f, 644.23f};
    vector<vector<float> > edges2{{5.99f},{3.21f,7.67f},{4.75757f,3.21f,8.2222f,9.910f},{3.21f},{0.5f},{2.66f,0.5f},{0.5f},{7.67f,4.75757f,3.21f},{8.2222f,9.910f},{9.910}};
    Graph<float,float>* floatG = new Graph<float,float>(keys2, data2, edges2);

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
    test_print_path_float(floatG);
    test_print_path_char(charG);
    test_print_path_empty(emptyG);
   
    test_edge_class_string(stringG);
    test_edge_class_int(intG);
    test_edge_class_float(floatG);
    test_edge_class_char(charG);
    test_edge_class_empty(emptyG);

    test_bfs_tree_string(stringG);
    test_bfs_tree_int(intG);
    test_bfs_tree_float(floatG);
    test_bfs_tree_char(charG);
    test_bfs_tree_empty(emptyG);


    cout << "Testing completed" << endl;

    delete stringG;
    delete charG;
    delete intG;
    delete floatG;

    return 0;
}
