//
//  HashNode.hpp
//  HashMap
//
//  Created by inigo guerra on 23/11/20.
//


#ifndef HashNode_hpp
#define HashNode_hpp

#include <iostream>

template <class K, class V>
class HashNode {
private:
    K _key;
    V _value;
    std::string _status;
    HashNode<K, V> * next = nullptr;
    
public:
    /* Constructores */
    HashNode() { };
    HashNode(const K & key, const V & value) : _key(key), _value(value){}
    HashNode(const HashNode<K, V> & );
    
    /* Destructor */
    virtual ~HashNode();
    
    /* Getter y Setter */
    K getKey() const { return _key; }
    void setKey(K & value) { _key = value; }
    
    V getValue() const { return _value; }
    void setValue(V & value) { _value = value; }
    
    std::string getStatus() const { return _status; }
    void setStatus(std::string & value) { _status = value; }
    
    HashNode<K, V> * getNext() const { return next; }
    void setNext(HashNode<K, V> * value) { next = value; }
    
    /* Sobrecarga operador == */
    bool operator ==(HashNode<K, V> &);
    
    /* Sobrecarga operador << */
    template <typename Kn, typename Vn>
    friend std::ostream & operator << (std::ostream & os, const HashNode<Kn, Vn> & node);
};

template <class K, class V>
HashNode<K, V>::HashNode(const HashNode<K, V> & other)
{
    _key = other._key;
    _value = other._value;
    _status = other._status;
    next = other.next;
}

template <class K, class V>
HashNode<K, V>::~HashNode()
{
    _key.~K();
    _value.~V();
    next = nullptr;
}

template <class K, class V>
bool HashNode<K, V>::operator ==(HashNode<K, V> & other)
{
    return (_key == other._key) && (next == other.next) && (_value == other._value);
}

template <class K, class V>
std::ostream & operator << (std::ostream & os, const HashNode<K, V> & node)
{
    os << node._value;
    
    return os;
}

#endif /* HashNode_hpp */
