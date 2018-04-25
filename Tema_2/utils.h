#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <fstream>
#include <string>
#include "Vector.h"
#include "Matrix.h"
#include "Graph.h"
#include "Complete_graph.h"
#include "Antisim_graph.h"
#include "Tournament_graph.h"

template < typename T >
graph<T>* determineGraphType(const matrix<T>&, const int&, const int&);

template < typename T >
int getEdges(const matrix<T>&);

template < typename T >
void readKnownTypeGraph(std::istream&);

#endif //UTILS_H
