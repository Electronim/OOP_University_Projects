#include "utils.h"

template < typename T >
graph<T>* determineGraphType(const matrix<T>& M, const int& nodes, const int& edges){
    antisymmetric_graph<T> AS(M, nodes, edges);
    complete_graph<T> CG(M, nodes, edges);
    tournament_graph<T> TG(M, nodes, edges);

    int as = AS.findType(M);
    int cg = CG.findType(M);
    int tg = TG.findType(M);

    if (tg != -1) return new tournament_graph<T>(M, nodes, edges);
    if (cg != -1) return new complete_graph<T>(M, nodes, edges);
    if (as != -1) return new antisymmetric_graph<T>(M, nodes, edges);
    throw("ERROR! The graph ISN'T a complete/antisymmetric/tournament graph!\n");
    return NULL;
}

template < typename T >
int getEdges(const matrix<T>& M){
    int counter = 0;

    for (int i = 0; i < M.lin; i++){
        for (int j = 0; j < M.col; j++) {
            counter += (M[i][j] != 0);
        }
    }

    return counter;
}

template < typename T >
graph<T>* graph<T>::Create(GraphType type){
    if (type == GT_Antisymmetric)
        return new antisymmetric_graph<T>;
    
    if (type == GT_Complete)
        return new complete_graph<T>;

    if (type == GT_Tournament)
        return new tournament_graph<T>;

    if (type == ERROR){
        std::cerr << "ERROR! The graph ISN'T a complete/antisymmetric/tournament graph!\n";
        exit(0);
    }
}

template < typename T >
void readKnownTypeGraph(std::istream& in, graph<T>** G){
    std::string type;
    in >> type;

    GraphType numberType;
    if (type == "ANTISYMMETRIC") numberType = GT_Antisymmetric;
    if (type == "COMPLETE") numberType = GT_Complete;
    if (type == "TOURNAMENT") numberType = GT_Tournament;
    if (type == "ERROR") numberType = ERROR;

    *G = graph<T>::Create(numberType);

    in >> **G;
}
