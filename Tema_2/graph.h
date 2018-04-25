#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <fstream>
#include "matrix.h"

enum GraphType{
    GT_Antisymmetric, GT_Complete, GT_Tournament, ERROR
};

template < typename T >
class graph{
protected:
    virtual void print(std::ostream& out) const = 0;
    virtual void printGraph(std::ostream&, const matrix<T>&) const = 0;
    virtual std::istream& readGraph(std::istream&, matrix<T>&) = 0;

public:
    int nodes;
    matrix<T> M;
    graph();
    graph(const matrix<T>&, const int&);
    graph(const graph&);
    graph(const graph&&);

    void graphLinks(std::ostream&, const matrix<T>&) const;
    static graph* Create(GraphType);

    vector<T>* DFS();//DONE
    void dfs(T node, vector<T>*, bool**); //DONE

    vector<T>* BFS();
    vector<T>* bfs(T node);
    
    vector<T>* topologicalSort();
    vector<T>* topological(T node);
    
    bool hasCycles();
    bool hascycles(T node);

    vector<T>* conexComponents();

    graph& operator= (const graph&);
    bool operator== (const graph&);
    bool operator!= (const graph&);
    bool operator< (const graph&);
    template < typename U > friend std::ostream& operator<< (std::ostream&, graph<U>&);
    template < typename U > friend std::istream& operator>> (std::istream&, graph<U>&);

    virtual ~graph() = default;
};

#endif //GRAPH_H