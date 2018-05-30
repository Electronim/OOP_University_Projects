// Copyright 2018 PETRASCO SANDU

#ifndef CELL_H_
#define CELL_H_
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#define MAP_SIZE 500009

using namespace std;

class Cell{
 protected:
    virtual istream& readCell(istream &) = 0;
    virtual void printCell(ostream &) const = 0;

 public:
    Cell() = default;
    virtual unsigned int HashFoo() const = 0;
    virtual int getType() const = 0;

    friend istream &operator >> (istream &, Cell &);
    friend ostream &operator << (ostream &, const Cell &);
    virtual Cell* operator + (Cell *);
    virtual bool operator == (Cell *);

    virtual ~Cell() = default;
};

class Number : public Cell{
    long long number;
 
 protected:
    istream& readCell(istream &);
    void printCell(ostream &) const;

 public:
    Number() = default;
    Number(const long long &);
    Number(const Number &);
    Number &operator = (const Number &) = default;
    Number operator + (const Number &);
    bool operator == (const Number &);
    unsigned int HashFoo() const;
    int getType() const;
    int getNumber() const;

    ~Number() = default;
    
};

class Text : public Cell{
    string text;

 protected:
    istream& readCell(istream &);
    void printCell(ostream &) const;

 public:
    Text() = default;
    Text(const string &);
    Text(const Text &);
    Text &operator = (const Text &) = default;
    Text operator + (const Text &);
    bool operator == (const Text &);
    unsigned int HashFoo() const;
    int getType() const;
    string getText() const;

    ~Text() = default;
};

class Complex  : public Cell{
    int real, imag;

 protected:
    istream& readCell(istream &);
    void printCell(ostream &) const;

 public:
    Complex() = default;
    Complex(const int &, const int &);
    Complex(const Complex &);
    Complex &operator = (const Complex &) = default;
    Complex operator + (const Complex &);
    bool operator == (const Complex &);
    unsigned int HashFoo() const;
    int getType() const;
    int getReal() const;
    int getImag() const;
    
    ~Complex() = default;
};

class Address : public Cell{
    string country, county, city, street;
    int number;

 protected:
    istream& readCell(istream &);
    void printCell(ostream &) const;

 public:
    Address() = default;
    Address(const string &, const string &, const string &, const string &, const int &);
    Address(const Address &);
    Address &operator = (const Address &) = default;
    Address operator + (const Address &);
    bool operator == (const Address &);
    unsigned int HashFoo() const;
    int getType() const;
    string getCountry() const;
    string getCounty() const;
    string getCity() const;
    string getStreet() const;
    int getNumber() const;

    ~Address() = default;
};

#include "cell.cpp"

#endif // CELL_H_