#include "vector.h"

template < typename T >
vector<T>::vector() : arr_size(0) {
    arr = NULL;
}

template < typename T >
vector<T>::vector(const int& size){
    arr_size = size;
    arr = new T[size];
}

template < typename T >
vector<T>::vector(const vector<T>& other){
    arr_size = other.arr_size;
    arr = new T[arr_size];

    for (int i = 0; i < arr_size; ++i){
        arr[i] = other.arr[i];
    }
}

template < typename T >
void vector<T>::free(){
    delete[] arr;
    arr = NULL;
}

template < typename T >
void vector<T>::set_size(int size){
    arr_size = size;
}

template < typename T >
T& vector<T>::operator[] (const int idx){
    return arr[idx];
}

template < typename T >
vector<T>& vector<T>::operator= (const vector<T>& other){
    free();
    arr_size = other.arr_size;
    arr = new T[arr_size];

    for (int i = 0; i < arr_size; ++i){
        arr[i] = other.arr[i];
    }

    return *this;
}

template < typename T >
bool vector<T>::operator== (const vector<T>& other){
    if (arr_size != other.arr_size) return 0;

    bool u = 1;
    for (int i = 0; i < arr_size; ++i){
        u &= (arr[i] == other.arr[i]);
    }

    return u;
}

template < typename T >
bool vector<T>::operator!= (const vector<T>& other){
    if (arr_size != other.arr_size) return 1;

    bool u = 0;
    for (int i = 0; i < other.arr_size; ++i){
        u |= (arr[i] != other.arr[i]);
    }

    return u;
}

template < typename T >
bool vector<T>::operator< (const vector<T>& other){
    unsigned int len = std::min(arr_size, other.arr_size);

    for (int i = 0; i < len; ++i){
        if (other.arr[i] <= arr[i]) return 0;
    }

    return 1;
}

template < typename T >
unsigned int vector<T>::size(){
    return arr_size;
}

template < typename T >
void vector<T>::resize(unsigned int new_size){
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
void vector<T>::push_back(T elem){
    resize(arr_size + 1);
    arr[arr_size - 1] = elem;
}

template < typename T >
void vector<T>::sort(){
    for (int i = 0; i < arr_size; ++i)
        for (int j = i + 1; j < arr_size; ++j)
            if (arr[i] > arr[j])
                std::swap(arr[i], arr[j]);
}

template < typename T >
std::istream& operator>> (std::istream& in, vector<T>& other){
    other.free();
    other.arr = new T[other.arr_size];
    
    for (int i = 0; i < other.size(); ++i){
       in >> other.arr[i];
    }

    return in;
}

template < typename T >
std::ostream& operator<< (std::ostream& out, vector<T>& other){
    for (int i = 0; i < other.size(); ++i){
        out << other[i] << " ";
    }
    out << "\n";

    return out;
}

template < typename T >
vector<T>::~vector(){
    free();
}