#ifndef TOURNAMENT_GRAPH_H
#define TOURNAMENT_GRAPH_H
#include <iostream>
#include <fstream>
#include "complete_graph.h"
#include "antisim_graph.h"

template < typename T > class graph;
template < typename T > class complete_graph;
template < typename T > class antisymmetric_graph;

template < typename T >
class tournament_graph : public complete_graph<T>, public antisymmetric_graph<T>{
protected:
    virtual void print(std::ostream& out) const;
    virtual void printGraph(std::ostream&, const matrix<T>&) const;
    virtual std::istream& readGraph(std::istream&, matrix<T>&);

public:
    tournament_graph();
    tournament_graph(const matrix<T>&, const int&, const int&);
    tournament_graph(const tournament_graph&);

    tournament_graph& operator= (const tournament_graph&);
    bool operator== (const tournament_graph&);
    bool operator!= (const tournament_graph&);
    bool operator< (const tournament_graph&);

    virtual int findType(const matrix<T>&) const;

    ~tournament_graph() = default;
};

#endif //TOURNAMENT_GRAPH_H