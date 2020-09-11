#ifndef ROPE_IMPLICITTREAP_INL_H
#define ROPE_IMPLICITTREAP_INL_H

#include <exception>
#include <stdexcept>

#include "ImplicitTreap.h"

template<typename T>
template<typename Container>
ImplicitTreap<T>::ImplicitTreap(const Container& values) {
    for (const auto& value : values) {
        insert(size(), value);
    }
}

template<typename T>
template<typename Container>
ImplicitTreap<T>::ImplicitTreap(Container&& values) {
    for (auto&& value : values) {
        insert(size(), std::move(value));
    }
}

template<typename T>
ImplicitTreap<T>::ImplicitTreap(Node<T> otherRoot)
    : root(otherRoot) {}

template<typename T>
ImplicitTreap<T>::ImplicitTreap(const ImplicitTreap<T>& other)
    : root(copy(root, other.root)) {}


template<typename T>
ImplicitTreap<T>::ImplicitTreap(ImplicitTreap<T>&& other) {
    root = other.root;
    other.root = nullptr;
}

template<typename T>
template<typename It>
ImplicitTreap<T>::ImplicitTreap(It first, It last) {
    while (first != last) {
        insert(size(), *first++);
    }
}

template<typename T>
Node<T> ImplicitTreap<T>::createNode(const T& value) {
    size_t priority = ImplicitTreapRandom();
    auto result = new ImplicitTreapNode<T>(priority, value);
    return result;
}

template<typename T>
Node<T> ImplicitTreap<T>::createNode(T&& value) {
    size_t priority = ImplicitTreapRandom();
    auto result = new ImplicitTreapNode<T>(priority, std::move(value));
    return result;
}


template<typename T>
size_t ImplicitTreap<T>::size() const {
    return ImplicitTreapNode<T>::getSize(root);
}

template<typename T>
Node<T> ImplicitTreap<T>::getRoot() const {
    return root;
}

template<typename T>
void ImplicitTreap<T>::setRoot(Node<T> newRoot) {
    root = newRoot;
}

template<typename T>
void ImplicitTreap<T>::insert(size_t pos, const T& value) {
    if (pos > size()) {
        throw std::out_of_range("Attempt to insert into non-existent position");
    }

    root = insert(root, pos, value);
}

template<typename T>
void ImplicitTreap<T>::insert(size_t pos, T&& value) {
    if (pos > size()) {
        throw std::out_of_range("Attempt to insert into non-existent position");
    }

    root = insert(root, pos, std::move(value));
}

template<typename T>
void ImplicitTreap<T>::insert(size_t pos, const ImplicitTreap<T>& other) {
    if (pos > size()) {
        throw std::out_of_range("Attempt to insert into non-existent position");
    }
    size_t n = other.size();
    for (size_t i = 0; i < n; i++, pos++) {
        insert(pos, other.getValue(i));
    }
}

template<typename T>
void ImplicitTreap<T>::erase(size_t pos, size_t cnt) {
    if (pos + cnt > size())
        throw std::out_of_range("Incorrect range");

    auto p1 = split(root, pos + cnt);
    Node<T> left1 = p1.first;
    Node<T> right1 = p1.second;
    auto p2 = split(left1, pos);

    Node<T> left2 = p2.first;
    Node<T> right2 = p2.second;
    clear(right2);
    root = merge(left2, right1);
}


template<typename T>
void ImplicitTreap<T>::erase(size_t pos) {
    if (pos >= size())
        throw std::out_of_range("Attempt to erase non-existent element");

    erase(pos, 1);
}

template<typename T>
std::pair<Node<T>, Node<T>>
ImplicitTreap<T>::split(Node<T> curNode, size_t toCut) {
    if (!curNode) return {};
    size_t leftSize = ImplicitTreapNode<T>::getSize(curNode->getLeft());

    if (leftSize >= toCut) {
        auto p = split(curNode->getLeft(), toCut);
        curNode->setLeft(p.second);
        curNode->update();
        return {p.first, curNode};
    } else {
        auto p = split(curNode->getRight(), toCut - leftSize - 1);
        curNode->setRight(p.first);
        curNode->update();
        return {curNode, p.second};
    }
}

template<typename T>
Node<T> ImplicitTreap<T>::merge(Node<T> lhs, Node<T> rhs) {
    if (!lhs) { return rhs; }
    if (!rhs) { return lhs; }

    if (lhs->getPriority() > rhs->getPriority()) {
        lhs->setRight(merge(lhs->getRight(), rhs));
        lhs->update();
        return lhs;
    } else {
        rhs->setLeft(merge(lhs, rhs->getLeft()));
        rhs->update();
        return rhs;
    }
}

template<typename T>
Node<T> ImplicitTreap<T>::insert(Node<T> curRoot, size_t pos, const T& value) {
    auto p = split(curRoot, pos);
    Node<T> left = p.first;
    Node<T> right = p.second;
    auto newNode = createNode(value);
    auto leftMergeResult = merge(left, newNode);
    return merge(leftMergeResult, right);
}


template<typename T>
Node<T> ImplicitTreap<T>::insert(Node<T> curRoot, size_t pos, T&& value) {
    auto p = split(curRoot, pos);
    Node<T> left = p.first;
    Node<T> right = p.second;
    auto newNode = createNode(std::move(value));
    auto leftMergeResult = merge(left, newNode);
    return merge(leftMergeResult, right);
}


template<typename T>
T& ImplicitTreap<T>::getValue(Node<T> curRoot, size_t pos) {
    size_t leftSize = ImplicitTreapNode<T>::getSize(curRoot->getLeft());
    if (leftSize == pos) return curRoot->getValue();
    if (pos > leftSize) {
        return getValue(curRoot->getRight(), pos - leftSize - 1);
    } else {
        return getValue(curRoot->getLeft(), pos);
    }
}

template<typename T>
std::pair<ImplicitTreap<T>, ImplicitTreap<T>>
ImplicitTreap<T>::split(size_t x) {
    auto p = split(root, x);
    this->root = nullptr;

    return std::make_pair(ImplicitTreap(p.first), ImplicitTreap(p.second));
}

template<typename T>
ImplicitTreap<T> ImplicitTreap<T>::merge(ImplicitTreap<T>& lhs, ImplicitTreap<T>& rhs) {
    Node<T> newRoot = ImplicitTreap<T>::merge(lhs.getRoot(), rhs.getRoot());
    lhs.root = rhs.root = nullptr;
    return ImplicitTreap(newRoot);
}

template<typename T>
T& ImplicitTreap<T>::getValue(size_t pos) {
    if (pos >= size()) {
        throw std::out_of_range("Attempt to get value of non-existent element");
    }

    return getValue(root, pos);
}

template<typename T>
const T& ImplicitTreap<T>::getValue(size_t pos) const {
    if (pos >= size()) {
        throw std::out_of_range("Attempt to get value of non-existent element");
    }

    return getValue(root, pos);
}

template<typename T>
void ImplicitTreap<T>::clear(Node<T> curNode) {
    if (!curNode) { return; }
    clear(curNode->getLeft());
    clear(curNode->getRight());
    delete curNode;
}

template<typename T>
ImplicitTreap<T>::~ImplicitTreap() {
    clear(root);
}

template<typename T>
Node<T> ImplicitTreap<T>::copy(Node<T> to, Node<T> from) {
    if (!from) { return nullptr; }
    to = createNode(from->getValue());
    to->setLeft(copy(to->getLeft(), from->getLeft()));
    to->setRight(copy(to->getRight(), from->getRight()));
    to->update();
    return to;
}

template<typename T>
ImplicitTreap<T>& ImplicitTreap<T>::operator=(const ImplicitTreap<T>& other) {
    if (this != &other) {
        clear(root);
        root = copy(root, other.root);
    }
    return *this;
}

template<typename T>
ImplicitTreap<T>& ImplicitTreap<T>::operator=(ImplicitTreap<T>&& other) {
    this->root = other.root;
    other.root = nullptr;
    return *this;
}


#endif // ROPE_IMPLICITTREAP_INL_H
