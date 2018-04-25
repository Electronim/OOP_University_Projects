#include "matrix.h"

template < typename T >
matrix<T>::matrix() : lin(0), col(0){
    mat = NULL;
}

template < typename T >
matrix<T>::matrix(const int& _lin, const int & _col) : lin(_lin), col(_col){
    mat = new T* [_lin];

    for (int i = 0; i < _lin; i++){
        mat[i] = new T[_col];
        for (int j = 0; j < _col; j++)
            mat[i][j] = 0;
    }
}

template < typename T >
matrix<T>::matrix(const matrix<T>& other){
    lin = other.lin; col = other.col;
    mat = new T* [lin];

    for (int i = 0; i < lin; i++){
        mat[i] = new T [col];
        for (int j = 0; j < col; j++)
            mat[i][j] = other.mat[i][j];
    }
}

template < typename T >
T* & matrix<T>::operator[] (int idx) const{
    return mat[idx];
}

template < typename T >
matrix<T>& matrix<T>::operator= (const matrix<T>& other){
    lin = other.lin; col = other.col;
    mat = new T* [lin];

    for (int i = 0; i < lin; i++){
        mat[i] = new T [col];
        for (int j = 0; j < col; j++)
            mat[i][j] = other.mat[i][j];
    }
}

template < typename T >
bool matrix<T>::operator!= (const matrix<T>& other){
    if (lin != other.lin || col != other.col) return 1;

    for (int i = 0; i < lin; i++)
        for (int j = 0; j < col; j++)
            if (mat[i][j] == other.mat[i][j])
                return 0;
    
    return 1;
}

template < typename T >
bool matrix<T>::operator== (const matrix<T>& other){
    if (lin != other.lin || col != other.col) return 0;

    for (int i = 0; i < lin; i++)
        for (int j = 0; j < col; j++)
            if (mat[i][j] != other.mat[i][j])
                return 0;
    
    return 1;
}

template < typename T >
bool matrix<T>::operator< (const matrix<T>& other){
    for (int i = 0; i < lin; i++)
        for (int j = 0; j < col; j++)
            if (mat[i][j] >= other.mat[i][j])
                return 0;
    
    return 1;
}

template< typename T >
std::istream& operator>> (std::istream& in, matrix<T>& other){
    other.free();
    in >> other.lin;
    
    other.col = other.lin;
    other.mat = new T* [other.lin];

    for (int i = 0; i < other.lin; i++){
        other.mat[i] = new T [other.col];
        for (int j = 0; j < other.col; j++)
            in >> other.mat[i][j];
    }

    return in;
} 

template < typename T >
std::ostream& operator<< (std::ostream& out, matrix<T>& other){
    for (int i = 0; i < other.lin; i++, out << "\n")
        for (int j = 0; j < other.col; j++)
            out << other.mat[i][j] << " ";
    
    return out;
}

template < typename T >
void matrix<T>::free(){
    delete[] mat;
    mat = NULL;
}

template < typename T >
matrix<T>::~matrix(){
    free();
}