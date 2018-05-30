// Copyright 2018 PETRASCO SANDU

#include "cell.h"

struct intHash{
    unsigned int operator()(const int &nbr) const{
        return nbr % MAP_SIZE;
    }
};

struct stringHash{
    unsigned int operator()(const string &str) const{
        if (str.empty()) return 0;

        unsigned int Power[str.size()];
        unsigned int result;

        Power[0] = 1;
        result = (unsigned int)str[0];

        for (unsigned int i = 1; i < str.size(); i++){
            Power[i] = 255 * Power[i - 1] % MAP_SIZE;
            result = result + ((unsigned int)str[i] * Power[i]) % MAP_SIZE;
            result %= MAP_SIZE;
        }

        return result % MAP_SIZE;
    }
};

istream &operator >> (istream &in, Cell &other){
    other.readCell(in);

    return in;
}

ostream &operator << (ostream &out, const Cell &other){
    other.printCell(out);

    return out;
}

Cell* Cell::operator + (Cell *ptr){
    if (ptr->getType() == 1){
        Number *elem1 = static_cast< Number *>(this);
        Number *elem2 = static_cast< Number *>(ptr);
        Number *res = new Number(*elem1 + *elem2);

        return res;
    }

    if (ptr->getType() == 2){
        Text *elem1 = static_cast< Text *>(this);
        Text *elem2 = static_cast< Text *>(ptr);
        Text *res = new Text(*elem1 + *elem2);

        return res;
    }

    if (ptr->getType() == 3){
        Complex *elem1 = static_cast< Complex *>(this);
        Complex *elem2 = static_cast< Complex *>(ptr);
        Complex *res = new Complex(*elem1 + *elem2);

        return res;
    }

    if (ptr->getType() == 4){
        Address *elem1 = static_cast< Address *>(this);
        Address *elem2 = static_cast< Address *>(ptr);
        try{
            Address *res = new Address(*elem1 + *elem2);
            return res;
        } catch (invalid_argument &exception){
            cout << exception.what() << "\n";
            exit(0);
        }
    }
}

bool Cell::operator == (Cell *ptr){
    if (ptr->getType() == 1){
        Number *elem1 = static_cast< Number *>(this);
        Number *elem2 = static_cast< Number *>(ptr);
        return elem1 == elem2;
    }

    if (ptr->getType() == 2){
        Text *elem1 = static_cast< Text *>(this);
        Text *elem2 = static_cast< Text *>(ptr);
        return elem1 == elem2;
    }

    if (ptr->getType() == 3){
        Complex *elem1 = static_cast< Complex *>(this);
        Complex *elem2 = static_cast< Complex *>(ptr);
        return elem1 == elem2;
    }

    if (ptr->getType() == 4){
        Address *elem1 = static_cast< Address *>(this);
        Address *elem2 = static_cast< Address *>(ptr);
        return elem1 == elem2;
    }
}

Number::Number(const long long &_number) : number(_number){ }

Number::Number(const Number &other){
    number = other.number;
}

Number Number::operator + (const Number &other){
    Number res;

    res.number = number + other.number;
    return res;
}

bool Number::operator == (const Number &other){
    return number == other.number;
}

istream &Number::readCell(istream &in){
    cout << "Write the NUMBER: ";
    in >> number;

    return in;
}

void Number::printCell(ostream &out) const{
    out << "This cell contains a NUMBER: [";
    out << number << "]\n";
}

unsigned int Number::HashFoo() const{
    return intHash()(number);
}

int Number::getType() const{
    return 1;
}

int Number::getNumber() const{
    return number;
}

Text::Text(const string &_text) : text(_text){ }

Text::Text(const Text &other){
    text = other.text;
}

Text Text::operator + (const Text &other){
    Text res;

    res.text = text + other.text;
    return res;
}

bool Text::operator == (const Text &other){
    return text == other.text;
}

istream &Text::readCell(istream &in){
    cout << "Write the TEXT: ";
    getline(in, text);
    getline(in, text);
}

void Text::printCell(ostream &out) const{
    out << "This cell contains a TEXT: [";
    out << text << "]\n";
}

unsigned int Text::HashFoo() const{
    return stringHash()(text);
}

int Text::getType() const{
    return 2;
}

string Text::getText() const{
    return text;
}

Complex::Complex(const int &_real, const int &_imag) : real(_real), imag(_imag){ }

Complex::Complex(const Complex &other){
    real = other.real;
    imag = other.imag;
}

Complex Complex::operator + (const Complex &other){
    Complex res;

    res.real = real + other.real;
    res.imag = imag + other.imag;
    return res;
}

bool Complex::operator == (const Complex &other){
    return (real == other.real && imag == other.imag);
}

istream &Complex::readCell(istream &in){
    cout << "Write the REAL component: "; in >> real;
    cout << "Write the IMAGINARY component: "; in >> imag;

    return in;
}

void Complex::printCell(ostream &out) const{
    out << "This cell contains a COMPLEX NUMBER: [";
    out << real << " + " << imag << "i]\n";
}

unsigned int Complex::HashFoo() const{
    unsigned int value1 = intHash()(real);
    unsigned int value2 = intHash()(imag);

    return (value1 + value2) % MAP_SIZE;
}

int Complex::getType() const{
    return 3;
}

int Complex::getReal() const{
    return real;
}

int Complex::getImag() const{
    return imag;
}

Address::Address(const string &_country, const string &_county, const string &_city, const string &_street, const int &_number)
    : country(_country)
    , county(_county)
    , city(_city)
    , street(_street)
    , number(_number)
    { }

Address::Address(const Address &other){
    country = other.country;
    county = other.county;
    city = other.city;
    street = other.street;
    number = other.number;
}

Address Address::operator + (const Address &other){
    Address res;
    throw invalid_argument("ERROR! Two ADDRESSES have the same NAME, which is FORBIDDEN!\n");

    return res;
}

bool Address::operator == (const Address &other){
    return (country == other.country && county == other.county && city == other.city && street == other.street && number == other.number);
}

istream &Address::readCell(istream &in){
    cout << "Write the ADDRESS!\n";
    cout << "Country: "; in >> country;
    cout << "County: "; in >> county;
    cout << "City: "; in >> city;
    cout << "Street: "; in >> street;
    cout << "Number: "; in >> number;

    return in;
}

void Address::printCell(ostream &out) const{
    out << "This cell contains an ADDRESS: [";
    out << country << " " << county << " " << city << " " << street << " " << number << "]\n";
}

unsigned int Address::HashFoo() const{
    unsigned int value1 = stringHash()(country);
    unsigned int value2 = stringHash()(county);
    unsigned int value3 = stringHash()(city);
    unsigned int value4 = stringHash()(street);
    unsigned int value5 = intHash()(number);

    value1 += value2; value1 %= MAP_SIZE;
    value1 += value3; value1 %= MAP_SIZE;
    value1 += value4; value1 %= MAP_SIZE;
    value1 += value5; value1 %= MAP_SIZE;

    return value1;
}

int Address::getType() const{
    return 4;
}

string Address::getCountry() const{
    return country;
}

string Address::getCounty() const{
    return county;
}

string Address::getCity() const{
    return city;
}

string Address::getStreet() const{
    return street;
}

int Address::getNumber() const{
    return number;
}