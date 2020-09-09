#ifndef ROPE_IMPLICITTREAPNODE_INL_H
#define ROPE_IMPLICITTREAPNODE_INL_H

#include "ImplicitTreapNode.h"

template<typename T>
ImplicitTreapNode<T>::ImplicitTreapNode()
    : size_(1), left(nullptr), right(nullptr) {}

template<typename T>
ImplicitTreapNode<T>::ImplicitTreapNode(size_t priority, T&& value)
    : ImplicitTreapNode() {
    this->priority = priority;
    this->value = std::move(value);
}

template <typename T>
ImplicitTreapNode<T>::ImplicitTreapNode(size_t priority, const T& value)
        : ImplicitTreapNode() {
    this->priority = priority;
    this->value = value;
}

template <typename T>
size_t ImplicitTreapNode<T>::getSize(ImplicitTreapNode* node) {
    return node ? node->size_ : 0;
}

template<typename T>
size_t ImplicitTreapNode<T>::getPriority() const {
    return priority;
}

template<typename T>
void ImplicitTreapNode<T>::setPriority(size_t newPriority) {
    priority = newPriority;
}

template<typename T>
T& ImplicitTreapNode<T>::getValue() {
    return value;
}

template <typename T>
size_t ImplicitTreapNode<T>::size() const {
    return size_;
}

template <typename T>
void ImplicitTreapNode<T>::update() {
    size_ = getSize(left) + getSize(right) + 1;
}

template<typename T>
const T& ImplicitTreapNode<T>::getValue() const {
    return value;
}

template<typename T>
ImplicitTreapNode<T>& ImplicitTreapNode<T>::operator=(const T& otherValue) {
    value = otherValue;
    return *this;
}

template<typename T>
ImplicitTreapNode<T>& ImplicitTreapNode<T>::operator=(T&& otherValue) {
    value = std::move(otherValue);
    return *this;
}

template<typename T>
ImplicitTreapNode<T>* ImplicitTreapNode<T>::getLeft() const {
    return left;
}

template<typename T>
void ImplicitTreapNode<T>::setLeft(ImplicitTreapNode* other) {
    this->left = other;
}

template<typename T>
ImplicitTreapNode<T>* ImplicitTreapNode<T>::getRight() const {
    return right;
}

template<typename T>
void ImplicitTreapNode<T>::setRight(ImplicitTreapNode* other) {
    this->right = other;
}




#endif // ROPE_IMPLICITTREAPNODE_INL_H
