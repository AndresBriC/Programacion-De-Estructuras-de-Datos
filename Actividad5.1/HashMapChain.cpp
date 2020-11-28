//
//  HashMapChain.cpp
//  HashMap
//
//  Created by inigo guerra on 23/11/20.
//

#include "HashMapChain.hpp"
#include "HashNode.hpp"
#include <vector>

template <class K, class V>
class HashMapChain {
    int _capacity = 0;
    
    std::vector<K> _keys;
    std::vector<std::vector<HashNode<K, V>>> _values;
    std::vector<std::string> _status;
    
    int _size = 0;
    
    int hash_function(K) const;
    
public:
    HashMapChain(int);
    ~HashMapChain();
    
    bool empty() const;
    int size() const;
    
    bool put(K,V);
    //int rehash(int);
    V get(K);
};

template <class K, class V>
HashMapChain<K,V>::HashMapChain(int capacity)
{
    this->_capacity = capacity;
    this->_status = std::vector<std::string>(capacity);
    this->_keys = std::vector<K>(capacity);
    this->_values = std::vector<std::vector<HashNode<K, V>>>(capacity);
    
    fill(_status.begin(), _status.end(), "vacio");
}

template <class K, class V>
HashMapChain<K,V>::~HashMapChain()
{
    /*
    delete this->_status;
    delete this->_values;
    delete this->_keys;
     */
}

template <class K, class V>
bool HashMapChain<K,V>::empty() const
{
    return this->_size == 0;
}

template <class K, class V>
int HashMapChain<K,V>::size() const
{
    return this->_size;
}

template <class K, class V>
int HashMapChain<K,V>::hash_function(K key) const
{
    return key % this->_capacity;
}

//Complejidad O(1)
template <class K, class V>
bool HashMapChain<K,V>::put(K key,V value)
{
    std::string ocupado = "ocupado";
    int indice = hash_function(key);
    HashNode<K, V> node;
    node.setValue(value);
    node.setKey(key);
    node.setStatus(ocupado);

    if (this->_status[indice] == "ocupado") {
        _values[indice].push_back(node);
    }else if (indice > -1) {
        this->_keys[indice] = key;
        this->_values[indice].push_back(node);
        this->_status[indice] = "ocupado";
    }
    
    return true;
}

/*
template <class K, class V>
int HashMapChain<K,V>::rehash(int indice)
{
    if (indice < this->_capacity && steps < this->_capacity) {
        
        ++indice;
        
        if (indice == this->_capacity) indice = 0;
        
        if (this->_status[indice] == "ocupado")
        {
            indice = rehash(indice, ++steps);
        }
        
        return indice;
    }
    else {
        return -1;
    }
     
}
 */

//Complejidad O(n)
template <class K, class V>
V HashMapChain<K,V>::get(K key)
{
    bool found = false;
    long int size;
    
    int indice = hash_function(key);
    V value;
    
    
    if (this->_status[indice] == "ocupado") {
        size = _values[indice].size();
        for (int i = 0; i < size; i++){
            if (_values[indice][i].getKey() == key){
                value = _values[indice][i].getValue();
                found = true;
            }
        }
    }
    else{
        found = false;
    }
    
   
    if (found) return value;
    else
        return -1;
}
