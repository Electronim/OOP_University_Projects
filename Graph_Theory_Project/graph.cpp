#include "./graph.h"
#include <vector>

template <typename T>
GraphNode<T>::GraphNode(const T &_info, const T &_info2)
    : info(_info)
    , info2(_info2)
    { }

template <typename T>
GraphNode<T>::GraphNode(const GraphNode<T> &other){
    info = other.info;
    info2 = other.info2;
}

template <typename T>
GraphEdge<T>::GraphEdge(const T &_from, const T &_to, const T &_val)
    : from(_from)
    , to(_to)
    , val(_val)
    { }

template <typename T>
GraphEdge<T>::GraphEdge(const GraphEdge<T> &other){
    from = other.from;
    to = other.to;
    val = other.val;
}

template <typename T>
Graph<T>::Graph(){
    nrNodes = 0;
    nrEdges = 0;
    LDA = NULL;
    ILDA = NULL;
}

template <typename T>
Graph<T>::Graph(const int &_nrNodes, const int &_nrEdges,
const vector < GraphEdge <T> > &_edges, const vector < GraphNode <T> > &_nodes)
    : nrNodes(_nrNodes)
    , nrEdges(_nrEdges)
    , nodes(_nodes)
    , edges(_edges){
    buildGraph();
}

template <typename T>
Graph<T>::Graph(const Graph<T> &other){
    nrNodes = other.nrNodes;
    nrEdges = other.nrEdges;
    nodes = other.nodes;
    edges = other.edges;
    LDA = new vector < GraphNode <T> > [nrNodes];
    ILDA = new vector < GraphNode <T> > [nrNodes];

    for (int i = 0; i < nrNodes; i++){
        LDA[i] = other.LDA[i];
        ILDA[i] = other.ILDA[i];
    }
}

template <typename T>
void Graph<T>::buildGraph(){
    LDA = new vector < GraphNode <T> > [nrNodes];
    ILDA = new vector < GraphNode <T> > [nrNodes];

    for (auto it : edges){
        LDA[it.from].push_back({it.to, 0});
        ILDA[it.to].push_back({it.from, 0});
    }
}

template <typename T>
Graph<T>::~Graph(){
    delete[] LDA;
    delete[] ILDA;
}
