//WAZNA UWAGA W LINIJCE 56
#include <iostream>
#include <list>
using namespace std;

struct edge{
    int v;
    int cost;

    edge(int _v, int _cost){
        v = _v;
        cost = _cost;
    }
};

class GraphDijkstra {
public:

    int nOfVertices;
    list <edge>* adj_list;     // listy sasiedztwa
    int *tableOfCosts;
    int *d;
    int *P; // odkomentowac zeby dostawac tez dokladna sciezke
    bool *visited;

    void add_edge (int u,int v, int cost)
    {
        edge e(v, cost);
        adj_list[u].push_back(e);
    }

};

void constructGraphs(GraphDijkstra &G1, GraphDijkstra &G2) //konstruktujemy graf z zadania i graf z odwóconymi do niego krawędziami
{
    cin >> G1.nOfVertices;
    G2.nOfVertices = G1.nOfVertices;

    G1.tableOfCosts = new int[G1.nOfVertices];
    G1.adj_list = new list <edge>[G1.nOfVertices];
    G1.d = new int [G1.nOfVertices];
    G1.P = new int [G1.nOfVertices];
    G1.visited = new bool [G1.nOfVertices];

    G2.tableOfCosts = new int[G2.nOfVertices];
    G2.adj_list = new list <edge>[G2.nOfVertices];
    G2.d = new int [G2.nOfVertices];
    G2.P = new int [G2.nOfVertices];
    G2.visited = new bool [G2.nOfVertices];

    for (int i = 0; i < G1.nOfVertices; i++) {
        cin >> G1.tableOfCosts[i];
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) { //UWAGA! u mnie m to dokladna liczba krawedzi - tak jak w tresci zadania. Ale zauwazylam ze w Pana testach (z pegaza) krawedzi jest m+1
        int u, v, cost;
        cin >> u >> v >> cost;
        G1.add_edge(u-1, v-1, cost);
        G2.add_edge(v-1,u-1,cost);
    }
}
int priorityQueue(int size, GraphDijkstra &G) // 'popuje' wartosc z najmniejsza odlegloscia = najwyzszym priorytetem
{
    int mini=INT_MAX,pop;
    for(int i=0; i < size; i++)
    {
        if(!G.visited[i] && G.d[i] <= mini)
        {
            mini = G.d[i];
            pop=i;
        }
    }
    G.visited[pop] = true;
    return pop;
}

void relax(int u, GraphDijkstra& G){
    for(auto e: G.adj_list[u]){
        if(G.d[e.v] > G.d[u] + e.cost) {
            G.d[e.v] = G.d[u] + e.cost;
            G.P[e.v] = u;
        }
    }
}
void dijkstra(int source, GraphDijkstra &G) {
    int d[G.nOfVertices];
    int P[G.nOfVertices];

    for (int i = 0; i < G.nOfVertices; i++) {
        G.d[i] = INT_MAX;
        G.P[i] = -1;
        G.visited[i] = false;
    }
    G.d[source] = 0;
    G.P[source] = source;
    for (int i = 0; i < G.nOfVertices; i++) {
        int u = priorityQueue(G.nOfVertices, G);
        relax(u, G);
    }
    cout << endl;
}

int main() {

    GraphDijkstra G;
    GraphDijkstra oppG;
    constructGraphs(G, oppG);
    dijkstra(0, G); //szukamy najkrotszych sciezek do wszystkich metali ze zlota
    dijkstra(0, oppG); //szukamy najkrotszych sciezek ze wszyskich metali do zlota -> czyli od zlota do metali w odwroconym grafie
    int minCost = INT_MAX;
    int minVertex = 0;
    for(int i = 0; i < G.nOfVertices; i++){
        if(G.P[i] != -1 && oppG.P[i] != -1){
            int cost = G.d[i] + oppG.d[i] + G.tableOfCosts[i]/2; //calosciowy koszt to droga w obie strony i polowa ceny metalu
            if(cost < minCost) {
                minCost = cost;
                minVertex = i;
            }
        }
    }

    // cout << endl << minVertex << " ";
    cout << minCost << endl;

//    for(int i = 0; i < G.nOfVertices; i++){
//        cout << G.P[i] << " ";
//    }
//    cout << endl;
//    for(int i = 0; i < G.nOfVertices; i++){
//        cout << oppG.P[i] << " ";
//    }

//mozna odkomentowac zeby dostac ktory metal prztapiamy i jaka jest sciezka ((ALE UWAGA, JA NUMERUJE OD 0))
}
