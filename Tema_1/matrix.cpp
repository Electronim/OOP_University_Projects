#include "matrix.h"
#include "vector.h"

template < typename T >
void Matrix<T>::free(){
    if (vec_size > 0)
        delete[] vec;
}

template < typename T >
Matrix<T>::Matrix() : vec_size(0) {
    vec = new myVec <T>;
}

template < typename T >
Matrix<T>::Matrix(const int nrVec, const int nrElemPerVec) : vec_size(nrVec){
    vec = new myVec<T>[nrVec];
    
    for (int i = 0; i < nrVec; ++i){
        vec[i] = myVec<T>(size);
    }
}

template < typename T >
Matrix<T>::Matrix(const Matrix& other){
    vec_size = other.vec_size;
    vec = new myVec<T>[vec_size];

    for (int i = 0; i < vec_size; ++i){
        vec[i] = other.vec[i];
    }
}

template < typename T >
myVec<T>& Matrix<T>::operator[] (int idx){
    return vec[idx];
}

template < typename T >
Matrix<T>& Matrix<T>::operator= (const Matrix<T> &other){
    free();
    vec_size = other.vec_size;
    vec = new myVec<T>[vec_size];

    for (int i = 0; i < vec_size; ++i){
        vec[i] = other.vec[i];
    }

    return *this;
}

template < typename T >
bool Matrix<T>::operator== (const Matrix<T>& other){
    if (vec_size != other.vec_size) return 0;
    bool u = 1;
    
    for (int i = 0; i < vec_size; ++i){
        u &= (vec[i] == other.vec[i]);
    }

    return u;
}

template < typename T >
bool Matrix<T>::operator!= (const Matrix<T>& other){
    if (vec_size != other.vec_size) return 1;
    bool u = 0;
    
    for (int i = 0; i < other.vec_size; ++i){
        u |= (vec[i] != other.vec[i]);
    }

    return u;
}

template < typename T >
bool Matrix<T>::operator< (const Matrix<T>& other){
    unsigned int len = std::min(vec_size, other.vec_size);
    
    for (int i = 0; i < len; ++i){
        if (other.vec[i] < vec[i]) return 0;
    }

    return 1;
}

template < typename T >
Matrix<T> Matrix<T>::operator+ (Matrix<T> &other){
    Matrix Ans;
    
    if (size() != other.size()){
        std::cerr << "ERROR! Matricile nu au aceleasi dimensiuni!\n";
        return Ans;
    }
    
    if (size() == 0 && other.size() == 0) return Ans;
    
    if (vec[0].size() != other.vec[0].size()){
        std::cerr << "ERROR! Matricile nu au aceleasi dimensiuni!\n";
        return Ans;
    }

    Ans.resize(size(), vec[0].size());

    for (int i = 0; i < vec_size; ++i){
        for (int j = 0; j < vec[i].size(); ++j){
            Ans[i][j] = vec[i][j] + other.vec[i][j];
        }
    }

    return Ans;
}

template < typename T >
unsigned int Matrix<T>::size(){
    return vec_size;
}

// resizes the lines and columns of the object
template < typename T >
void Matrix<T>::resize(unsigned int new_size_vec, unsigned int new_size_arr){
    myVec<T> *new_vec = new myVec<T>[new_size_vec];

    if (new_size_vec < vec_size){
        vec_size = new_size_vec;
    }

    for (int i = 0; i < vec_size; i++){
        new_vec[i] = vec[i];
    }

    for (int i = 0; i < new_size_vec; ++i){
        new_vec[i].resize(new_size_arr);
    }

    free();
    vec_size = new_size_vec;
    vec = new_vec;
}

//resizes ONLY the lines of the object
template < typename T >
void Matrix<T>::resize(unsigned int new_size_vec){
    myVec<T> *new_vec = new myVec<T>[new_size_vec];

    if (new_size_vec < vec_size){
        vec_size = new_size_vec;
    }

    for (int i = 0; i < vec_size; i++){
        new_vec[i] = vec[i];
    }

    free();
    vec_size = new_size_vec;
    vec = new_vec;
}

template < typename T >
void Matrix<T>::push_back(const myVec<T>& elem){
    resize(vec_size + 1);
    vec[vec_size - 1] = elem;
}

template < typename T >
std::istream& operator>> (std::istream& in, Matrix<T>& other){
    int nrCol;
    other.free();

    in >> other.vec_size >> nrCol;
    other.vec = new myVec<T>[other.vec_size];
    
    for (int i = 0; i < other.size(); ++i){
        other.vec[i].set_size(nrCol);
        in >> other.vec[i];
    }

    return in;
}

template < typename T >
std::ostream& operator<< (std::ostream& out, Matrix<T>& other){
    out << "Matricea data are marimea " << other.size() << " x " << (other.size() == 0 ? 0 : other[0].size()) << "\n";
    
    if (other.size() == 0)
        return out; 
    
    out << "Elementele matricei sunt:\n";
    for (int i = 0; i < other.size(); ++i){
        out << other[i];
    }
    
    return out;
}

template < typename T >
Matrix<T>::~Matrix(){
    free();
}