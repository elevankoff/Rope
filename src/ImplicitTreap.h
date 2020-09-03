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

    ImplicitTreap(const ImplicitTreap<T>& other);

    ImplicitTreap(ImplicitTreap<T>&& other);

    template<typename It>
    ImplicitTreap(It first, It last);

    // Creates node with the current "ImplicitTreap"'s random function
    [[ nodiscard ]] static ImplicitTreapNode<T>* createNode(const T& value);

    [[ nodiscard ]] static ImplicitTreapNode<T>* creatNode(T&& value);

    // Returns the number of elements in the current "ImplicitTreap"
    size_t getSize() const;

    // Returns root of the current "ImplicitTreap"
    ImplicitTreapNode<T>* getRoot() const;

    // Inserts an element in "pos" position
    void insert(size_t pos, const T& value);

    void insert(size_t pos, T&& value);

    void insert(size_t pos, const ImplicitTreap<T>& other);

    // Deletes elements in the interval [pos, pos + cnt)
    void erase(size_t pos, size_t cnt);

    // Deletes an element at position "pos"
    void erase(size_t pos);

    // Returns two "ImplicitTreap"s: "left" with first x elements, "right" with others
    // Current "ImplicitTreap" is becoming empty
    [[ nodiscard ]] std::pair<ImplicitTreap<T>, ImplicitTreap<T>> split(size_t x);

    // Merges two "ImplicitTreap"s into one
    // lhs and rhs are becoming empty
    [[ nodiscard ]] static ImplicitTreap<T> merge(ImplicitTreap<T>& lhs, ImplicitTreap<T>& rhs);

    T& getValue(size_t pos);

    const T& getValue(size_t pos) const;

    // Returns default random function, which is used in "createNode" method for generating "priority"
    static std::mt19937 getRandFunc();

    ImplicitTreap<T>& operator = (const ImplicitTreap<T>& other);

    ImplicitTreap<T>& operator = (ImplicitTreap<T>&& other);

private:
    explicit ImplicitTreap(ImplicitTreapNode<T>* otherRoot);

    static ImplicitTreapNode<T>* copy(ImplicitTreapNode<T>* to, ImplicitTreapNode<T>* from);

    static std::pair<ImplicitTreapNode<T>*, ImplicitTreapNode<T>*> split(ImplicitTreapNode<T>* curNode, size_t toCut);

    static ImplicitTreapNode<T>* merge(ImplicitTreapNode<T>* lhs, ImplicitTreapNode<T>* rhs);

    static ImplicitTreapNode<T>* insert(ImplicitTreapNode<T>* curRoot, size_t pos, const T& value);

    static ImplicitTreapNode<T>* insert(ImplicitTreapNode<T>* curRoot, size_t pos, T&& value);

    static T& getValue(ImplicitTreapNode<T>* curRoot, size_t pos);

    void clear(ImplicitTreapNode<T>* curNode);

private:
    ImplicitTreapNode<T>* root;
    static std::mt19937 ImplicitTreapRandom;

public:
    ~ImplicitTreap();
};
#include "ImplicitTreap.cpp"

#endif //ROPE_IMPLICITTREAP_H
