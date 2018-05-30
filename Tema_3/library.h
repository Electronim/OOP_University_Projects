// Copyright 2018 PETRASCO SANDU

#ifndef LIBRARY_H_
#define LIBRARY_H_
using namespace std;

template < typename TK, typename TV, typename TN >
class Node{
 public:
    TK *key;
    TV value;
    TN name;

    Node() = default;
    Node(TK *, const TV &, const TN &);
    Node(const Node &);
    
    template < typename UK, typename UV, typename UN >
    friend ostream& operator << (ostream&, const Node<UK, UV, UN> &);
    Node &operator = (const Node &);
    bool operator == (const Node &);

    ~Node(){ delete key; }
};

class Library{ // SINGLETON
    vector < list < Node < Cell, int, string > > > Bucket;
    
    Library();
    static Library* m_pInstance;
    static int counter;
 
 public:
    static Library* getInstance();
    void put(Cell *, const string &); // DONE
    void remove(ostream &, const int &); // DONE
    void remove(ostream &, const string &); // DONE
    void get(ostream &, const string &); // DONE
    void get(ostream &, const int &); // DONE

    friend ostream &operator << (ostream &, const Library &);

    ~Library() = default;
};


#include "library.cpp"

#endif // LIBRARY_H_
