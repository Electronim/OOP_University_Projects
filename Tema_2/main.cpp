#include "Utils.h"

using namespace std;

int main(){

    ifstream cin("test.in");
    ofstream cout("test.out");

    matrix< int > M;
    graph< int > *G = NULL;

    //first method to read the graph(general way)
    // cin >> M;
    // int nodes = M.lin;
    // int edges = getEdges(M);
    // try{
    //     G = determineGraphType(M, nodes, edges);
    // } catch(char const* Error){
    //     return cerr << Error, 0;
    // }
    
    // cout << *G;
    // G->graphLinks(cout, M);

    //second method to read the graph(particular)
    readKnownTypeGraph(cin, &G); //implemented with factory design pattern
    cout << *G;

    vector < int > *V = G->DFS();
    cout << *V;

    delete V; delete G;
    cin.close(); cout.close();
    return 0;
}

//de facut!!
//dfs/bfs/conexitate(cate componente tare-conexe sunt?!) // nu initilizeaza nodes!
//sortarea topologica cu exceptii pentru cicluri
//operatorul + pentru reuniunea arcelor a doua grafuri
