#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
#include <fstream>

template < typename T >
class vector{
    T *arr;
    unsigned int arr_size;
    void free();

public:
    vector();
    vector(const int&);
    vector(const vector&);

    bool operator== (const vector&);
    bool operator!= (const vector&);
    bool operator< (const vector&);
    T& operator[] (const int);
    vector& operator= (const vector&);

    void set_size(int);
    unsigned int size();
    void resize(unsigned int);
    void push_back(T);
    void sort();

    template < typename U > friend std::istream& operator>> (std::istream&, vector<U>&);
    template < typename U > friend std::ostream& operator<< (std::ostream&, vector<U>&);
    ~vector();
};

#endif