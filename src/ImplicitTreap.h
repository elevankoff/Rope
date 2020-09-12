#ifndef ROPE_IMPLICITTREAP_H
#define ROPE_IMPLICITTREAP_H

#include <vector>
#include <iostream>
#include <stack>

#include "ImplicitTreapNode.h"

template<typename T>
using Node = ImplicitTreapNode<T>*;

template <typename T>
class ImplicitTreap {
public:
    // Constructors

    ImplicitTreap() = default;

    template<typename Container>
    explicit ImplicitTreap(const Container& values);

    template<typename Container>
    ImplicitTreap(Container&& values);

    ImplicitTreap(const ImplicitTreap<T>& other);

    ImplicitTreap(ImplicitTreap<T>&& other);

    template<typename It>
    ImplicitTreap(It first, It last);

    // Returns the number of elements in the current "ImplicitTreap"
    size_t size() const;

    // Returns root of the current "ImplicitTreap"
    Node<T> getRoot() const;

    void setRoot(Node<T> newRoot);

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

    // Creates node with the current "ImplicitTreap"'s random function
    [[ nodiscard ]] static Node<T> createNode(const T& value);

    [[ nodiscard ]] static Node<T> createNode(T&& value);

    T& getValue(size_t pos);

    const T& getValue(size_t pos) const;

    // Returns default random function, which is used in "createNode" method for generating "priority"
    static std::mt19937 getRandFunc();

    ImplicitTreap<T>& operator= (const ImplicitTreap<T>& other);

    ImplicitTreap<T>& operator= (ImplicitTreap<T>&& other);

    // "1" this > other
    // "0" this == other
    // "-1" this < other
    int lexCompare(const ImplicitTreap<T>& other) const;

private:

    explicit ImplicitTreap(Node<T> otherRoot);

    void fillStack(Node<T> node, std::stack<Node<T>>& st) const;

    static Node<T> copy(Node<T> to, Node<T> from);

    static std::pair<Node<T>, Node<T>> split(Node<T> curNode, size_t toCut);

    static Node<T> merge(Node<T> lhs, Node<T> rhs);

    static Node<T> insert(Node<T> curRoot, size_t pos, const T& value);

    static Node<T> insert(Node<T> curRoot, size_t pos, T&& value);

    static T& getValue(Node<T> curRoot, size_t pos);

    void clear(Node<T> curNode);

    Node<T> root = nullptr;

public:
    static std::mt19937 ImplicitTreapRandom;

    ~ImplicitTreap();
};

template<typename T>
std::mt19937 ImplicitTreap<T>::ImplicitTreapRandom(std::mt19937(std::chrono::steady_clock::now().time_since_epoch().count()));

#include "ImplicitTreap-inl.h"

#endif //ROPE_IMPLICITTREAP_H
