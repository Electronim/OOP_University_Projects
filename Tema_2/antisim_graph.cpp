#include "antisim_graph.h"

template < typename T >
antisymmetric_graph<T>::antisymmetric_graph() : graph<T>(), edges(0) { }

template < typename T >
antisymmetric_graph<T>::antisymmetric_graph(const matrix<T>& _M, const int& _nodes, const int& _edges)
    : edges(_edges), graph<T>(_M, _nodes){}

template < typename T >
antisymmetric_graph<T>::antisymmetric_graph(const antisymmetric_graph<T>& other)
    : graph<T>(other.M, other.nodes) {
    edges = other.edges;
}

template < typename T >
antisymmetric_graph<T>& antisymmetric_graph<T>::operator= (const antisymmetric_graph<T>& other){
    edges = other.edges;
    this->M = other.M;
    this->nodes = other.nodes;

    return *this;
}

template < typename T >
bool antisymmetric_graph<T>::operator==(const antisymmetric_graph<T>& other) {
    return (this->M == other.M);
}

template < typename T >
bool antisymmetric_graph<T>::operator!=(const antisymmetric_graph<T>& other) {
    return (this->M != other.M);
}

template < typename T >
bool antisymmetric_graph<T>::operator<(const antisymmetric_graph<T>& other) {
    return (this->M.lin < other.M.lin);
}

template < typename T >
int antisymmetric_graph<T>::findType(const matrix<T>& MDA) const{
    int lin = MDA.lin;
    int col = MDA.col;

    for (int i = 0; i < lin; i++) {
        for (int j = 0; j < col; j++){
            if ((MDA.mat[i][j] != 0) + (MDA.mat[j][i] != 0) == 2)
                return -1;
        }
    }

    return 1;
}

template < typename T >
void antisymmetric_graph<T>::printGraph(std::ostream& out, const matrix<T>& M) const {
    for (int i = 0; i < M.lin; i++)
        for (int j = 0; j < M.col; j++)
            if (M.mat[i][j] != 0)
                out << i << " -> " << j << "\n";
}

template < typename T >
void antisymmetric_graph<T>::print(std::ostream &out) const {
    out << "ANTISYMMETRIC";
}

template < typename T >
std::istream& antisymmetric_graph<T>::readGraph(std::istream& in, matrix<T>& M){
    in >> M;
    return in;
}