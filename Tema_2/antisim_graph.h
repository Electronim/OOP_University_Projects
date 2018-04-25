#ifndef ANTISIM_GRAPH_H
#define ANTISIM_GRAPH_H
#include <iostream>
#include <fstream>
#include "graph.h"

template < typename T > class graph;

template < typename T >
class antisymmetric_graph : virtual public graph<T>{
protected:
    int edges;
    virtual void print(std::ostream& out) const;
    virtual void printGraph(std::ostream&, const matrix<T>&) const;
    virtual std::istream& readGraph(std::istream&, matrix<T>&);

public:
    antisymmetric_graph();
    antisymmetric_graph(const matrix<T>&, const int&, const int&);
    antisymmetric_graph(const antisymmetric_graph&);

    antisymmetric_graph& operator= (const antisymmetric_graph&);
    bool operator== (const antisymmetric_graph&);
    bool operator!= (const antisymmetric_graph&);
    bool operator< (const antisymmetric_graph&);

    virtual int findType(const matrix<T>&) const;

    virtual ~antisymmetric_graph() = default;
};

#endif //ANTISIM_GRAPH_H