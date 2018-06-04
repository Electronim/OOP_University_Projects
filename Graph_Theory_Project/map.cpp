#include "map.h"
#include <string>

template <typename TK, typename TV>
node<TK, TV>::node(const TK &_key, const TV &_value)
    : key(_key)
    , value(_value)
    {}

template <typename TK, typename TV>
node<TK, TV>::node(const node &other){
    key = other.key;
    value = other.value;
}

template <typename TK, typename TV>
TK& node<TK, TV>::getKey() const{
    return key;
}

template <typename TK, typename TV>
TV& node<TK, TV>::getValue() const{
    return value;
}

template <typename TK, typename TV>
void node<TK, TV>::setValue(const TV &_value){
    value = _value;
}

template <typename TK, typename TV>
bool node<TK, TV>::operator== (const node<TK, TV> &other){
    return (key == other.key && value == other.value);
}

template <typename TK, typename TV, typename TF>
myMap<TK, TV, TF>::myMap(){
    Bucket.resize(MAP_SIZE);
}

template <typename TK, typename TV, typename TF>
void myMap<TK, TV, TF>::put(const TK &key, const TV &value){
    unsigned int index = hashFoo(key);
    bool marked = 0;

    for (auto it : Bucket[index]){
        if (it.key == key){
            it.value = value;
            marked = 1;
        }
    }

    if (marked == 0){
        node<TK, TV> elem(key, value);
        Bucket[index].push_back(elem);
    }
}

template <typename TK, typename TV, typename TF>
void myMap<TK, TV, TF>::remove(const TK &key){
    unsigned int index = hashFoo(key);

    for (auto it : Bucket[index]){
        if (it.key == key){
            int val = it.value;
            Bucket[index].remove({key, val});
            break;
        }
    }
}

template <typename TK, typename TV, typename TF>
TV myMap<TK, TV, TF>::get(const TK &key){
    unsigned int index = hashFoo(key);
    TV value = TV();

    for (auto it : Bucket[index]){
        if (it.key == key){
            value = it.value;
            break;
        }
    }

    return value;
}

template <typename TK, typename TV, typename TF>
bool myMap<TK, TV, TF>::isMapped(const TK &key){
    unsigned int index = hashFoo(key);

    for (auto it : Bucket[index]){
        if (it.key == key){
            return true;
        }
    }

    return false;
}

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

struct myPair{
    int first, second;

    unsigned int operator()(const myPair &other) const{
        return (other.first + other.second) % MAP_SIZE;
    }

    bool operator== (const myPair &other){
        return first == other.first && second == other.second;
    }
};
