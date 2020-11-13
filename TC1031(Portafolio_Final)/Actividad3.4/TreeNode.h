#ifndef TREENODE_H_INCLUDED
#define TREENODE_H_INCLUDED

#include <iostream>
#include <utility>

template <class T>
class TreeNode {
private:
    T info;
    int pairValue;
    TreeNode<T> * left = nullptr;
    TreeNode<T> * right = nullptr;
    TreeNode<T> *parent = nullptr;

public:
    /* Constructores */
    TreeNode() { };
    TreeNode(const T & _info) : info(_info) {}
    TreeNode(const TreeNode<T> & );
    TreeNode(T, int);

    /* Destructor */
    virtual ~TreeNode();

    /* Getter y Setter */
    T getInfo() const { return info; }
    void setInfo(T & value) { info = value; }

    int getPairValue() const { return pairValue; }
    void setPairValue(int & _pairValue) { pairValue = _pairValue; }

    TreeNode<T> * getLeft() const { return left; }
    void setLeft(TreeNode<T> * value) { left = value; }

    TreeNode<T> * getRight() const { return right; }
    void setRight(TreeNode<T> * value) { right = value; }

    TreeNode<T> * getParent() const { return parent; }
    void setParent(TreeNode<T> * value) { parent = value; }

    /* Sobrecarga operador == */
    bool operator ==(TreeNode<T> &);

    /* Sobrecarga operador << */
    template <typename Tn>
    friend std::ostream & operator << (std::ostream & os, const TreeNode<Tn> & node);
};

template <class T>
TreeNode<T>::TreeNode(const TreeNode<T> & other)
{
    info = other.info;
    left = other.left;
    right = other.right;
    parent = other.parent;
}

template <class T>
TreeNode<T>::TreeNode(T _key, int _value)
{
    info = _key;
    pairValue = _value;
}

template <class T>
TreeNode<T>::~TreeNode()
{
    info.~T();
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

template <class T>
bool TreeNode<T>::operator ==(TreeNode<T> & other)
{
    return (info == other.info) && (left == other.left) && (right == other.right);
}

template <class T>
std::ostream & operator << (std::ostream & os, const TreeNode<T> & node)
{
    os << node.info << ", ";
    os << node.pairValue;

    return os;
}

#endif // TREENODE_H_INCLUDED
