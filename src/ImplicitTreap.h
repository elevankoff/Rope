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
    int getSize();

    // Returns root of the current "ImplicitTreap"
    ImplicitTreapNode<T>* getRoot() const;

    // Inserts an element in "pos" position
    void insert(int pos, const T& value);

    // Deletes an element in position "pos"
    void erase(int pos);

    // Returns two "ImplicitTreap"s: "left" with first x elements, "right" with others
    std::pair<ImplicitTreap<T>&, ImplicitTreap<T>&> split(int x);

    // Merges two "ImplicitTreap"s into one
    void merge(ImplicitTreap<T>& lhs, ImplicitTreap<T>& rhs);

    // Returns random function of the current "ImplicitTreap"
    std::minstd_rand& getRandFunc();

private:
    std::pair<ImplicitTreapNode<T>*, ImplicitTreapNode<T>*> split(ImplicitTreapNode<T>* curNode, int toCut);

    ImplicitTreapNode<T>* merge(ImplicitTreapNode<T>* lhs, ImplicitTreapNode<T>* rhs);

    ImplicitTreap<T>* insert(ImplicitTreap<T>* curRoot, int pos, const T& value);

    void clear(ImplicitTreapNode<T>* curNode);

private:
    ImplicitTreapNode<T>* root;
    const std::minstd_rand ImplicitTreapRandom;

public:
    ~ImplicitTreap();
};

#include "ImplicitTreapNode.cpp"

#endif //ROPE_IMPLICITTREAP_H
