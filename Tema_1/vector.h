#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
#include <fstream>

template < typename T > class Matrix;

template < typename T >
class myVec{
    T *arr;
    unsigned int arr_size;
    void free();

public:
    struct maxx{
        T val;
        int poz;
    };

    myVec();
    myVec(const int& size);
    myVec(const myVec<T>& other);
    void read_data(std::ifstream& in);
    void set_size(int size);
    bool operator== (myVec& other);
    bool operator!= (myVec& other);
    bool operator< (myVec& other);
    T& operator[] (int idx);
    myVec<T>& operator= (myVec<T>& other);
    T operator* (myVec& other);
    unsigned int size();
    void resize(unsigned int new_size);
    void push_back(T elem);
    T& Sum();
    maxx Max();
    void Sort();
    template < typename U > friend std::istream& operator>> (std::istream&, myVec<U>&);
    template < typename U > friend std::ostream& operator<< (std::ostream&, myVec<U>&);
    ~myVec();

    friend class Matrix <T>;
};

#endif