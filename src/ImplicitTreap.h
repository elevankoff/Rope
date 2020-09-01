#ifndef ROPE_IMPLICITTREAP_H
#define ROPE_IMPLICITTREAP_H

#include <vector>

#include "ImplicitTreapNode.h"

template <typename T>
class ImplicitTreap {
public:
    // Constructors
    ImplicitTreap();

    explicit ImplicitTreap(std::vector<T>&& values);

    explicit ImplicitTreap(const std::vector<T>& values);

    explicit ImplicitTreap(ImplicitTreapNode<T>* otherRoot);

    explicit ImplicitTreap(const ImplicitTreap& other);

    explicit ImplicitTreap(ImplicitTreap&& other);

    // Creates node with the current "ImplicitTreap"'s random function
    [[ nodiscard ]] static ImplicitTreapNode<T>* createNode(const T& value);

    // Returns the number of elements in the current "ImplicitTreap"
    size_t getSize();

    // Returns root of the current "ImplicitTreap"
    ImplicitTreapNode<T>* getRoot() const;

    // Inserts an element in "pos" position
    void insert(size_t pos, const T& value);

    // Deletes an element in position "pos"
    void erase(size_t pos);

    // Returns two "ImplicitTreap"s: "left" with first x elements, "right" with others
    [[ nodiscard ]] std::pair<ImplicitTreap<T>, ImplicitTreap<T>> split(size_t x);

    // Merges two "ImplicitTreap"s into one
    [[ nodiscard ]] static ImplicitTreap<T> merge(ImplicitTreap<T>& lhs, ImplicitTreap<T>& rhs);

    T& getValue(size_t pos);

    const T& getValue(size_t pos) const;

    // Returns default random function, which is used in "createNode" method for generating "priority"
    static std::mt19937 getRandFunc();

    ImplicitTreap<T>& operator = (const ImplicitTreap<T>& other);

    ImplicitTreap<T>& operator = (ImplicitTreap<T>&& other);

private:
    static void copy(ImplicitTreapNode<T>* to, ImplicitTreapNode<T>* from);

    static std::pair<ImplicitTreapNode<T>*, ImplicitTreapNode<T>*> split(ImplicitTreapNode<T>* curNode, size_t toCut);

    static ImplicitTreapNode<T>* merge(ImplicitTreapNode<T>* lhs, ImplicitTreapNode<T>* rhs);

    static ImplicitTreapNode<T>* insert(ImplicitTreapNode<T>* curRoot, size_t pos, const T& value);

    void clear(ImplicitTreapNode<T>* curNode);

private:
    ImplicitTreapNode<T>* root;
    static std::mt19937 ImplicitTreapRandom;

public:
    ~ImplicitTreap();
};
#include "ImplicitTreap.cpp"

#endif //ROPE_IMPLICITTREAP_H
