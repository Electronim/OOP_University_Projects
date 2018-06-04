#ifndef MAP_H_
#define MAP_H_
#define MAP_SIZE 500009
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>

using namespace std;

template <typename TK, typename TV>
class node{
 public:
    TK key;
    TV value;

    node() = default;
    node(const TK &, const TV &);
    node(const node &);

    TK& getKey() const;
    TV& getValue() const;
    void setValue(const TV &);
    bool operator== (const node<TK, TV> &other);

    ~node() = default;
};

template <typename TK, typename TV, typename TF>
class myMap{
    vector < list < node<TK, TV> > > Bucket;
    TF hashFoo;

 public:
    myMap();

    void put(const TK &, const TV &);
    void remove(const TK &);
    TV get(const TK &);
    bool isMapped(const TK &);

    ~myMap() = default;
};

#include "./map.cpp"

#endif  // MAP_H_
