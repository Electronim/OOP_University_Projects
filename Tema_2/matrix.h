#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <fstream>

template < typename T >
class matrix{
    void free();

public:
    T **mat;
    int lin, col;
    matrix();
    matrix(const int&, const int&);
    matrix(const matrix&);

    T* & operator[] (int) const;
    matrix& operator= (const matrix&);
    bool operator!= (const matrix&);
    bool operator== (const matrix&);
    bool operator< (const matrix&);
    
    template < typename U > friend std::istream& operator>>(std::istream&, matrix<U>&);
    template < typename U > friend std::ostream& operator<<(std::ostream&, matrix<U>&);
    ~matrix();
};

#endif //MATRIX_H