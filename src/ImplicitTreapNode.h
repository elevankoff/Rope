#ifndef ROPE_IMPLICITTREAPNODE_H
#define ROPE_IMPLICITTREAPNODE_H

#include <cstdio>
#include <random>
#include <chrono>

template<typename T>
class ImplicitTreapNode {
public:
    ImplicitTreapNode(int priority, const T& value);

    static size_t getSize(ImplicitTreapNode* node);

    size_t getPriority() const;

    const T& getValue() const;

    void setValue(const T& otherValue);

    size_t getSize() const; // returns size of subtree

    void updateSize(); // updates size of current node by "left" and "right"

private:
    T value;
    size_t size, priority;
    ImplicitTreapNode* left;
    ImplicitTreapNode* right;
};

#include "ImplicitTreapNode.cpp"

#endif //ROPE_IMPLICITTREAPNODE_H
