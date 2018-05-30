// Copyright 2018 PETRASCO SANDU

#include "library.h"

Library* Library::m_pInstance = NULL;
int Library::counter = 0;

Library* Library::getInstance(){
    if (!m_pInstance){
        m_pInstance = new Library;
        return m_pInstance;
    }
}

template < typename TK, typename TV, typename TN >
Node< TK, TV, TN >::Node(TK *_key, const TV &_value, const TN &_name){
    value = _value;
    name = _name;

    if (_key->getType() == 1){
        Number *elem = static_cast<Number *>(_key);
        key = new Number(elem->getNumber());

    } else if (_key->getType() == 2){
        Text *elem = static_cast<Text *>(_key);
        key = new Text(elem->getText());

    } else if (_key->getType() == 3){
        Complex *elem = static_cast<Complex *>(_key);
        key = new Complex(elem->getReal(), elem->getImag());

    }else if (_key->getType() == 4){
        Address *elem = static_cast<Address *>(_key);
        key = new Address(elem->getCountry(), elem->getCounty(), elem->getCity(), elem->getStreet(), elem->getNumber());
    }
}

template < typename TK, typename TV, typename TN >
Node< TK, TV, TN >::Node(const Node &other){
    value = other.value;
    name = other.name;

    if (other.key->getType() == 1){
        Number *elem = static_cast< Number * >(other.key);
        key = new Number(elem->getNumber());

    }else if (other.key->getType() == 2){
        Text *elem = static_cast< Text * >(other.key);
        key = new Text(elem->getText());

    }else if (other.key->getType() == 3){
        Complex *elem = static_cast< Complex * >(other.key);
        key = new Complex(elem->getReal(), elem->getImag());

    }else if (other.key->getType() == 4){
        Address *elem = static_cast< Address * >(other.key);
        key = new Address(elem->getCountry(), elem->getCounty(), elem->getCity(), elem->getStreet(), elem->getNumber());
    }
}

template < typename TK, typename TV, typename TN >
ostream &operator << (ostream& out, const Node<TK, TV, TN> &other){
    out << "The info of a cell with NAME [" << other.name << "] and with INDEX [" << other.value << "]:\n";
    out << *other.key;

    return out;
}

template < typename TK, typename TV, typename TN >
Node<TK, TV, TN>  &Node<TK, TV, TN>::operator = (const Node<TK, TV, TN> &other){
    value = other.value;
    name = other.name;

    if (other.key->getType() == 1){
        Number *elem = static_cast< Number * >(other.key);
        key = new Number(elem->getNumber());

    }else if (other.key->getType() == 2){
        Text *elem = static_cast< Text * >(other.key);
        key = new Text(elem->getText());

    } else if (other.key->getType() == 3){
        Complex *elem = static_cast< Complex * >(other.key);
        key = new Complex(elem->getReal(), elem->getImag());

    }else if (other.key->getType() == 4){
        Address *elem = static_cast< Address * >(other.key);
        key = new Address(elem->getCountry(), elem->getCounty(), elem->getCity(), elem->getStreet(), elem->getNumber());
    }
}

template < typename TK, typename TV, typename TN >
bool Node<TK, TV, TN>::operator == (const Node<TK, TV, TN> &other){
    return (*key == other.key && value == other.value && name == other.name);
}

Library::Library(){
    Bucket.resize(MAP_SIZE);
}

void Library::put(Cell *info, const string &name){
    unsigned int pos = info->HashFoo();
    bool marked = 0;

    for (auto &it : Bucket){
        for (auto &it2 : it){
            if (it2.name == name){
                if (it2.key->getType() != info->getType()){
                    throw invalid_argument("Two infos with the same NAME, but with different TYPES");
                }

                marked = 1;
                it2.key = *(it2.key) + info;
            }
        }
    }

    if (marked == 0){
        Node< Cell, int, string > elem(info, ++counter, name);
        Bucket[pos].push_back(elem);
    }
    
}

void Library::get(ostream& out, const string &name){
    bool marked = 0;

    for (auto it : Bucket){
        for (auto it2 : it){
            if (it2.name == name){
                out << it2 << "\n";
                marked = 1;
            }
        }
    }

    if (marked == 0){
        out << "No info with such NAME [" << name << "] found!\n";
    }
}

void Library::get(ostream& out, const int &index){
    bool marked = 0;

    for (auto it : Bucket){
        for (auto it2 : it){
            if (it2.value == index){
                out << it2 << "\n";
                marked = 1;
                return ;
            }
        }
    }

    if (marked == 0){
        out << "No info with such ID [" << index << "] found!\n";
    }
}

void Library::remove(ostream &out, const string &name){
    for (auto &it : Bucket){
        for (auto it2 = it.begin(); it2 != it.end(); it2++){
            if (it2->name == name){
                it.erase(it2);
                out << "The info with the NAME [" << name << "] was REMOVED!\n";
                return ;
            }
        }
    }

    out << "No info with such NAME [" << name << "] found!\n";
}

void Library::remove(ostream &out, const int &index){
    for (auto &it : Bucket){
        for (auto it2 = it.begin(); it2 != it.end(); it2++){
            if (it2->value == index){
                it.erase(it2);
                out << "The info with the ID [" << index << "] was REMOVED!\n";
                return ;
            }
        }
    }

    out << "No info with such ID [" << index << "] found!\n";
}

ostream &operator << (ostream &out, const Library &other){
    bool isEmpty = 0;

    for (auto it : other.Bucket){
        isEmpty |= (it.size() > 0);
        for (auto it2 : it)
            out << it2 << "++++++++++++++++++++++++++++\n";
    }

    if (!isEmpty){
        out << "There isn't any INFO in the LIBRARY!!!\n";
    }

    return out;
}