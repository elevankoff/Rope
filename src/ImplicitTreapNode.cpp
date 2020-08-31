#ifndef ROPE_IMPLICITTREAPNODE_CPP
#define ROPE_IMPLICITTREAPNODE_CPP

#include "ImplicitTreapNode.h"

template <typename T>
ImplicitTreapNode<T>::ImplicitTreapNode(int priority, const T& value)
        : size(1), priority(priority), left(nullptr), right(nullptr), value(value) {}

template <typename T>
static size_t ImplicitTreapNode<T>::getSize(ImplicitTreapNode* node) {
    return node ? node->size : 0;
}

template<typename T>
size_t ImplicitTreapNode<T>::getPriority() const {
    return priority;
}

template <typename T>
size_t ImplicitTreapNode<T>::getSize() const {
    return size;
}

template <typename T>
void ImplicitTreapNode<T>::updateSize() {
    return getSize(left) + getSize(right) + 1;
}

template<typename T>
const T& ImplicitTreapNode<T>::getValue() const {
    return value;
}

template<typename T>
void ImplicitTreapNode<T>::setValue(const T& otherValue) {
    value(otherValue);
}

#endif
