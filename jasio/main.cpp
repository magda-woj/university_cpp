#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
vector <vector <int>> adj_list;     // listy sasiedztwa.
int N;

void add_edge (int u,int v)
{
    adj_list[u].push_back(v);adj_list[v].push_back(u);
}

void construct_graph()
{
    ifstream plo;
    plo.open("test.txt");
    plo >> N;
    adj_list.resize(N+1);
    int i = 1;
    while(!plo.eof()){
        int u;
        plo >> u;
        add_edge(u, i);
    }
    plo.close();
}

int main(){
    construct_graph();
}