#ifndef ROPE_IMPLICITTREAPNODE_H
#define ROPE_IMPLICITTREAPNODE_H

#include <cstdio>
#include <random>
#include <chrono>

template<typename T>
class ImplicitTreapNode {
public:
    // Constructors
    ImplicitTreapNode();

    ImplicitTreapNode(size_t priority, T&& value);

    ImplicitTreapNode(size_t priority, const T& value);

    // Returns current node's priority
    size_t getPriority() const;

    // Return current node's value ref
    T& getValue();

    const T& getValue() const;

    // Returns size of subtree
    size_t size() const;

    // Updates size of current node by "left" and "right"
    void update();

    ImplicitTreapNode<T>* getLeft() const;

    void setLeft(ImplicitTreapNode* other);

    ImplicitTreapNode<T>* getRight() const;

    void setRight(ImplicitTreapNode* other);

    // Sets new value
    ImplicitTreapNode<T>& operator = (const T& otherValue);

    ImplicitTreapNode<T>& operator = (T&& otherValue);

    // Returns "node"'s subtree size
    static size_t getSize(ImplicitTreapNode* node);

private:
    T value;
    // Size of subtree and randomly generated "priority"
    size_t size_, priority;
    ImplicitTreapNode* left;
    ImplicitTreapNode* right;
};

#include "ImplicitTreapNode-inl.h"

#endif //ROPE_IMPLICITTREAPNODE_H
