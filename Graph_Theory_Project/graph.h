#ifndef GRAPH_H_
#define GRAPH_H_
#define NMAX 30005
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>

using std::vector;
using std::list;
using std::string;
using std::cin;
using std::ofstream;
using std::endl;
using std::max;

template <typename T>
class GraphNode{
 public:
    T info;
    T info2;

    GraphNode() = default;
    GraphNode(const T &, const T &);
    GraphNode(const GraphNode &);

    ~GraphNode() = default;
};

template <typename T>
class GraphEdge{
 public:
    T from, to, val;

    GraphEdge() = default;
    GraphEdge(const T &, const T &, const T &);
    GraphEdge(const GraphEdge &);

    ~GraphEdge() = default;
};

template <typename T>
class Graph{
    void buildGraph();
 public:
    int nrNodes;
    int nrEdges;
    vector < GraphNode <T> > nodes;
    vector < GraphEdge <T> > edges;
    vector < GraphNode <T> > *LDA, *ILDA;

    Graph();
    Graph(const int &, const int &, const vector < GraphEdge <T> > &,
    const vector < GraphNode <T> > &);

    Graph(const Graph &);

    ~Graph();
};

#include "./graph.cpp"

#endif  // GRAPH_H_
