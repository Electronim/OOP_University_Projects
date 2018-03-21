#include "vector.h"
#include <iostream>


template < typename T >
myVec<T>::myVec() : arr_size(0) {
    arr = new T;
}

template < typename T >
myVec<T>::myVec(const int& size){
    arr_size = size;
    arr = new T[size];
}

template < typename T >
myVec<T>::myVec(const myVec<T>& other){
    arr_size = other.arr_size;
    arr = new T[arr_size];

    for (int i = 0; i < arr_size; ++i){
        arr[i] = other.arr[i];
    }
}

template < typename T >
void myVec<T>::free(){
if (arr_size > 0)
    delete[] arr;
}

template < typename T >
void myVec<T>::read_data(std::ifstream& in){
    int n;
    in >> n;
    set_size(n);
    in >> *this;
}

template < typename T >
void myVec<T>::set_size(int size){
    arr_size = size;
}

template < typename T >
T& myVec<T>::operator[] (int idx){
    return arr[idx];
}

template < typename T >
myVec<T>& myVec<T>::operator= (myVec& other){
    free();
    arr_size = other.arr_size;
    arr = new T[arr_size];

    for (int i = 0; i < arr_size; ++i){
        arr[i] = other.arr[i];
    }

    return *this;
}

template < typename T >
bool myVec<T>::operator== (myVec& other){
    if (arr_size != other.arr_size) return 0;
    bool u = 1;
    for (int i = 0; i < arr_size; ++i){
        u &= (arr[i] == other.arr[i]);
    }
    return u;
}

template < typename T >
bool myVec<T>::operator!= (myVec& other){
    if (arr_size != other.arr_size) return 1;
    bool u = 0;
    for (int i = 0; i < other.arr_size; ++i){
        u |= (arr[i] != other.arr[i]);
    }
    return u;
}

template < typename T >
bool myVec<T>::operator< (myVec& other){
    unsigned int len = std::min(arr_size, other.arr_size);
    for (int i = 0; i < len; ++i){
        if (other.arr[i] < arr[i]) return 0;
    }
    return 1;
}

template < typename T >
T myVec<T>::operator* (myVec& other){
    if (arr_size != other.arr_size){
        std::cerr << "ERROR! Vectorii nu au aceeasi lungime!\n";
        return T(0);
    }
    
    T sum = 0;
    
    for (int i = 0; i < arr_size; ++i){
        sum += arr[i] * other.arr[i];
    }

    return sum;
}

template < typename T >
unsigned int myVec<T>::size(){
    return arr_size;
}

template < typename T >
void myVec<T>::resize(unsigned int new_size){
    T *new_arr = new T[new_size];
    
    if (new_size < arr_size){
        arr_size = new_size;
    }

    for (int i = 0; i < arr_size; ++i){
        new_arr[i] = arr[i];
    }

    free();
    arr_size = new_size;
    arr = new_arr;
}

template < typename T >
void myVec<T>::push_back(T elem){
    resize(arr_size + 1);
    arr[arr_size - 1] = elem;
}

template < typename T >
T& myVec<T>::Sum(){
    T sum = 0;
    for (int i = 0; i < arr_size; ++i){
        sum += arr[i];
    }
    return sum;
}


template < typename T >
typename myVec<T>::maxx myVec<T>::Max(){
    maxx E;
    E.val = arr[0];
    E.poz = 0;
    for (int i = 0; i < arr_size; ++i){
        if (arr[i] > E.val){
            E.val = arr[i];
            E.poz = i;
        }
    }
    return E;
}

template < typename T >
void myVec<T>::Sort(){
    for (int i = 0; i < arr_size; ++i)
        for (int j = i + 1; j < arr_size; ++j)
            if (arr[i] > arr[j])
                std::swap(arr[i], arr[j]);
}

template < typename T >
std::istream& operator>> (std::istream& in, myVec<T>& other){
    other.free();
    other.arr = new T[other.arr_size];
    
    for (int i = 0; i < other.size(); ++i){
       in >> other.arr[i];
    }

    return in;
}

template < typename T >
std::ostream& operator<< (std::ostream& out, myVec<T>& other){
    for (int i = 0; i < other.size(); ++i){
        out << other[i] << " ";
    }
    out << "\n";

    return out;
}

template < typename T >
myVec<T>::~myVec(){
    free();
}