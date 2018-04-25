#include "graph.h"

template < typename T >
graph<T>::graph() : M(){
    nodes = 0;
}

template < typename T >
graph<T>::graph(const matrix<T>& _M, const int& _nodes) : nodes(_nodes), M(_M){ }

template < typename T >
graph<T>::graph(const graph& other){
    nodes = other.nodes;
    M = other.M;
}

template < typename T >
graph<T>::graph(const graph&& other) : nodes(other.nodes), M(other.M){
    other.nodes = 0;
    other.M = 0;
}

template  < typename T >
graph<T>& graph<T>::operator= (const graph& other) {
    nodes = other.nodes;
    M = other.M;

    return *this;
}

template < typename T >
bool graph<T>::operator==(const graph<T>& other) {
    return (M == other.M);
}

template < typename T >
bool graph<T>::operator!=(const graph<T>& other) {
    return (M != other.M);
}

template < typename T >
bool graph<T>::operator<(const graph<T>& other) {
    return M.lin < other.M.lin;
}

template < typename T >
void graph<T>::graphLinks(std::ostream& out, const matrix<T>& M) const {
    out << "The graph has the following links: \n";
    printGraph(out, M);
    out << "\n";
}

template < typename T >
vector<T>* graph<T>::DFS(){
    nodes = M.lin;
    vector<T>* vec = new vector<T>;

    bool *vis = new bool[nodes];
    for (int i = 0; i < nodes; i++) vis[i] = 0;

    for (int i = 0; i < nodes; i++){
        if (vis[i] == 0){
            vector <T> *result = new vector<T>;

            dfs(i, result, &vis);
            for (int j = 0; j < result->size(); j++){
                vec->push_back((*result)[j]);
            }

            delete result;
        }
    }

    delete[] vis;
    return vec;
}

template < typename T >
void graph<T>::dfs(T node, vector<T>* vec, bool **vis){
    vec->push_back(node);
    (*vis)[node] = 1;

    for (int i = 0; i < nodes; i++){
        if (M[node][i] != 0 && (*vis)[i] == 0){
            dfs(i, vec, vis);
        }
    }
}

template < typename T >
std::ostream& operator<< (std::ostream& out, graph<T>& other){
    out << "The current graph is a "; other.print(out); out << " graph\n";
    out << "The adjacency matrix is as follows:\n";
    out << other.M << "\n";
    other.graphLinks(out, other.M);

    return out;
}

template < typename T >
std::istream& operator>> (std::istream& in, graph<T>& other){
    return other.readGraph(in, other.M);
}