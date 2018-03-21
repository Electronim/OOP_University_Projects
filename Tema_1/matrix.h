#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>

template < typename T > class myVec;

template < typename T >
class Matrix{
    unsigned int vec_size;
    myVec <T>* vec;
    void free();

public:
    Matrix();
    Matrix(const int nrVec, const int nrElemPerVec);
    Matrix(const Matrix<T>& other);

    myVec<T>& operator[] (int idx);
    Matrix<T>& operator= (const Matrix<T> &other);
    bool operator== (const Matrix<T>& other);
    bool operator!= (const Matrix<T>& other);
    bool operator< (const Matrix<T>& other);
    Matrix<T> operator+ (Matrix<T> &other);
    unsigned int size();
    // resizes the lines and columns of the object
    void resize(unsigned int new_size_vec, unsigned int new_size_arr);
    //resizes ONLY the lines of the object
    void resize(unsigned int new_size_vec);
    void push_back(const myVec<T>& elem);

    ~Matrix();

    template < typename U >friend std::istream& operator>> (std::istream&, Matrix<U>&);
    template < typename U >friend std::ostream& operator<< (std::istream&, Matrix<U>&);
};

#endif