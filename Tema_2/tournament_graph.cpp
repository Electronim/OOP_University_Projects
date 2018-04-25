#include "tournament_graph.h"

template < typename T >
tournament_graph<T>::tournament_graph() : complete_graph<T>(), antisymmetric_graph<T>(){}

template < typename T >
tournament_graph<T>::
tournament_graph(const matrix<T>& _M, const int& _nodes, const int& _edges) : complete_graph<T>(_M, _nodes, _edges),
                                                 antisymmetric_graph<T>(_M, _nodes, _edges), graph<T>(_M, _nodes){ }

template < typename T >
tournament_graph<T>::
tournament_graph(const tournament_graph& other) : complete_graph<T>(other.M, other.nodes, other.edges),
             antisymmetric_graph<T>(other.M, other.nodes, other.edges), graph<T>(other.M, other.nodes){ }

template < typename T >
tournament_graph<T>& tournament_graph<T>::operator= (const tournament_graph& other){
    this->nodes = other.nodes;
    this->edges = other.edges;
    this->M = other.M;

    return *this;
}

template < typename T >
bool tournament_graph<T>::operator==(const tournament_graph<T>& other) {
    return (this->M == other.M);
}

template < typename T >
bool tournament_graph<T>::operator!=(const tournament_graph<T>& other) {
    return (this->M != other.M);
}

template < typename T >
bool tournament_graph<T>::operator<(const tournament_graph<T>& other) {
    return (this->M.lin == other.M.lin);
}

template < typename T >
int tournament_graph<T>::findType(const matrix<T>& M) const {
    return (antisymmetric_graph<T>::findType(M) == 1 && complete_graph<T>::findType(M) == 2 ? 3 : -1);
}

template < typename T >
void tournament_graph<T>::printGraph(std::ostream& out, const matrix<T>& M) const {
    for (int i = 0; i < M.lin; i++)
        for (int j = 0; j < M.col; j++)
            if (M.mat[i][j] != 0)
                out << i << " -> " << j << "\n";
}

template < typename T >
void tournament_graph<T>::print(std::ostream &out) const {
    out << "TOURNAMENT";
}

template < typename T >
std::istream& tournament_graph<T>::readGraph(std::istream& in, matrix<T>& M){
    in >> M;
    return in;
}
