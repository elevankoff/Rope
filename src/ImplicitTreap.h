#ifndef ROPE_IMPLICITTREAP_H
#define ROPE_IMPLICITTREAP_H

#include <vector>

#include "ImplicitTreapNode.h"

template <typename T>
class ImplicitTreap {
public:
    // Constructors
    ImplicitTreap();

    explicit ImplicitTreap(std::vector<T>& values);

    explicit ImplicitTreap(ImplicitTreapNode<T>* otherRoot);

    // Creates node with the current "ImplicitTreap"'s random function
    ImplicitTreapNode<T>* createNode(const T& value);

    // Returns the number of elements in the current "ImplicitTreap"
    size_t getSize();

    // Returns root of the current "ImplicitTreap"
    ImplicitTreapNode<T>* getRoot() const;

    // Inserts an element in "pos" position
    void insert(size_t pos, const T& value);

    // Deletes an element in position "pos"
    void erase(size_t pos);

    // Returns two "ImplicitTreap"s: "left" with first x elements, "right" with others
    std::pair<ImplicitTreap<T>&, ImplicitTreap<T>&> split(size_t x);

    // Merges two "ImplicitTreap"s into one
    ImplicitTreap<T> merge(ImplicitTreap<T>& lhs, ImplicitTreap<T>& rhs);

    T& getValue(size_t pos);

    const T& getValue(size_t pos) const;

    // Returns random function of the current "ImplicitTreap"
    std::minstd_rand& getRandFunc();

private:
    std::pair<ImplicitTreapNode<T>*, ImplicitTreapNode<T>*> split(ImplicitTreapNode<T>* curNode, size_t toCut);

    ImplicitTreapNode<T>* merge(ImplicitTreapNode<T>* lhs, ImplicitTreapNode<T>* rhs);

    ImplicitTreapNode<T>* insert(ImplicitTreapNode<T>* curRoot, size_t pos, const T& value);

    void clear(ImplicitTreapNode<T>* curNode);

private:
    ImplicitTreapNode<T>* root;
    std::minstd_rand ImplicitTreapRandom;

public:
    ~ImplicitTreap();
};

#include "ImplicitTreap.cpp"

#endif //ROPE_IMPLICITTREAP_H
