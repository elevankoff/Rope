#ifndef ROPE_IMPLICITTREAPNODE_H
#define ROPE_IMPLICITTREAPNODE_H

#include <cstdio>
#include <random>
#include <chrono>

template<typename T>
class ImplicitTreapNode {
public:
    // Constructors
    ImplicitTreapNode(int priority, T&& value);

    ImplicitTreapNode(int priority, const T& value);

    // Returns "node"'s subtree size
    static size_t getSize(ImplicitTreapNode* node);

    // Returns current node's priority
    size_t getPriority() const;

    // Return current node's value ref
    T& getValue();

    const T& getValue() const;

    // Sets new value
    void setValue(const T& otherValue);

    // Returns size of subtree
    size_t getSize() const;

    // Updates size of current node by "left" and "right"
    void updateSize();

public:
    ImplicitTreapNode* left;
    ImplicitTreapNode* right;

private:
    T value;
    // Size of subtree and randomly generated "priority"
    size_t size, priority;
};

#include "ImplicitTreapNode.cpp"

#endif //ROPE_IMPLICITTREAPNODE_H
