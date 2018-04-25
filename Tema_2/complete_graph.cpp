#include "complete_graph.h"

template < typename T >
complete_graph<T>::complete_graph() : graph<T>(), edges(0) { }

template < typename T >
complete_graph<T>::complete_graph(const matrix<T>& _M, const int& _nodes, const int& _edges) : edges(_edges), graph<T>(_M, _nodes){ }

template < typename T >
complete_graph<T>::complete_graph(const complete_graph<T>& other) :graph<T>(other.M, other.nodes) {
    edges = other.edges;
}

template < typename T >
complete_graph<T>& complete_graph<T>::operator=(const complete_graph<T>& other){
    edges = other.edges;
    this->M = other.M;
    this->nodes = other.nodes;

    return *this;
}

template < typename T >
bool complete_graph<T>::operator==(const complete_graph<T>& other) {
    return (this->M == other.M);
}

template < typename T >
bool complete_graph<T>::operator!=(const complete_graph<T>& other) {
    return (this->M != other.M);
}

template < typename T >
bool complete_graph<T>::operator<(const complete_graph<T>& other) {
    return (this->M.lin < other.M.lin);
}

template < typename T >
int complete_graph<T>::findType(const matrix<T>& MDA) const {
    int lin = MDA.lin;
    int col = MDA.col;
    int counterLinks = 0;

    for (int i = 0; i < lin; i++) {
        for (int j = 0; j < col; j++){
            counterLinks += (((MDA.mat[i][j] != 0) + (MDA.mat[j][i] != 0)) > 0);
        }
    }

    return (counterLinks >= (lin * (lin - 1)) ? 2 : -1);
}

template < typename T >
void complete_graph<T>::printGraph(std::ostream& out, const matrix<T>& M) const {
    for (int i = 0; i < M.lin; i++)
        for (int j = 0; j < M.col; j++)
            if (M.mat[i][j] != 0)
                out << i << " -> " << j << "\n";
}

template < typename T >
void complete_graph<T>::print(std::ostream &out) const {
    out << "COMPLETE";
}

template < typename T >
std::istream& complete_graph<T>::readGraph(std::istream& in, matrix<T>& M){
    in >> M;
    return in;
}