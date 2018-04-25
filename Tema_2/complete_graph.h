#ifndef COMPLETE_GRAPH_H
#define COMPLETE_GRAPH_H
#include <iostream>
#include <fstream>
#include "graph.h"

template < typename T > class graph;
template < typename T >
class complete_graph : virtual public graph<T>{
protected:
    int edges;
    virtual void print(std::ostream& out) const;
    virtual void printGraph(std::ostream&, const matrix<T>&) const;
    virtual std::istream& readGraph(std::istream&, matrix<T>&);

public:
    complete_graph();
    complete_graph(const matrix<T>&, const int&, const int&);
    complete_graph(const complete_graph&);

    complete_graph& operator= (const complete_graph&);
    bool operator== (const complete_graph&);
    bool operator!= (const complete_graph&);
    bool operator< (const complete_graph&);

    virtual int findType(const matrix<T>&) const;

    virtual ~complete_graph() = default;
};

#endif //COMPLETE_GRAPH_H