#ifndef ROPE_IMPLICITTREAP_CPP
#define ROPE_IMPLICITTREAP_CPP

#include <exception>
#include "ImplicitTreap.h"
#include <stdexcept>

template<typename T>
ImplicitTreap<T>::ImplicitTreap()
    : root(nullptr) {}


template<typename T>
ImplicitTreap<T>::ImplicitTreap(std::vector<T>&& values)
    : root(nullptr) {
    for (size_t i = 0; i < values.size(); i++) insert(i, values[i]);
}

template<typename T>
ImplicitTreap<T>::ImplicitTreap(const std::vector<T>& values)
    : root(nullptr){
    for (size_t i = 0; i < values.size(); i++) insert(i, values[i]);
}


template<typename T>
ImplicitTreap<T>::ImplicitTreap(ImplicitTreapNode<T>* otherRoot)
    : root(otherRoot) {}


template<typename T>
ImplicitTreap<T>::ImplicitTreap(const ImplicitTreap<T>& other)
    : root(nullptr) {
    root = copy(root, other.root);
}

template<typename T>
ImplicitTreap<T>::ImplicitTreap(ImplicitTreap<T>&& other)
    : root(other.root) { other.root = nullptr; }


template<typename T>
template<typename It>
ImplicitTreap<T>::ImplicitTreap(It first, It last)
    : root(nullptr) {
    while (first != last) insert(getSize(), *first++);
}

template<typename T>
ImplicitTreapNode<T>* ImplicitTreap<T>::createNode(const T& value) {
    std::mt19937 randomFunc = getRandFunc();
    int priority = randomFunc();
    auto result = new ImplicitTreapNode<T>(priority, value);
    return result;
}

template<typename T>
ImplicitTreapNode<T>* ImplicitTreap<T>::creatNode(T&& value) {
    std::mt19937 randomFunc = getRandFunc();
    int priority = randomFunc();
    auto result = new ImplicitTreapNode<T>(priority, std::move(value));
    return result;
}


template<typename T>
size_t ImplicitTreap<T>::getSize() const {
    return ImplicitTreapNode<T>::getSize(root);
}

template<typename T>
ImplicitTreapNode<T>* ImplicitTreap<T>::getRoot() const {
    return root;
}

template<typename T>
void ImplicitTreap<T>::insert(size_t pos, const T& value) {
    if (pos > getSize())
        throw std::out_of_range("Attempt to insert into non-existent position");

    root = insert(root, pos, value);
}

template<typename T>
void ImplicitTreap<T>::insert(size_t pos, T&& value) {
    if (pos > getSize())
        throw std::out_of_range("Attempt to insert into non-existent position");
    root = insert(root, pos, std::move(value));
}

template<typename T>
void ImplicitTreap<T>::insert(size_t pos, const ImplicitTreap<T>& other) {
    if (pos > getSize())
        throw std::out_of_range("Attempt to insert into non-existent position");
    size_t n = other.getSize();
    for (size_t i = 0; i < n; i++, pos++) {
        insert(pos, other.getValue(i));
    }
}

template<typename T>
void ImplicitTreap<T>::erase(size_t pos, size_t cnt) {
    if (pos + cnt > getSize())
        throw std::out_of_range("Incorrect range");

    auto p1 = split(root, pos + cnt);
    ImplicitTreapNode<T>* left1 = p1.first;
    ImplicitTreapNode<T>* right1 = p1.second;
    auto p2 = split(left1, pos);

    ImplicitTreapNode<T>* left2 = p2.first;
    ImplicitTreapNode<T>* right2 = p2.second;
    clear(right2);
    root = merge(left2, right1);
}


template<typename T>
void ImplicitTreap<T>::erase(size_t pos) {
    if (pos >= getSize())
        throw std::out_of_range("Attempt to erase non-existent element");

    erase(pos, 1);
}

template<typename T>
std::pair<ImplicitTreapNode<T>*, ImplicitTreapNode<T>*>
ImplicitTreap<T>::split(ImplicitTreapNode<T>* curNode, size_t toCut) {
    if (!curNode) return std::pair<ImplicitTreapNode<T>*, ImplicitTreapNode<T>*>();
    size_t leftSize = ImplicitTreapNode<T>::getSize(curNode->left);

    if (leftSize >= toCut) {
        auto p = split(curNode->left, toCut);
        curNode->left = p.second;
        curNode->updateSize();
        return {p.first, curNode};
    } else {
        auto p = split(curNode->right, toCut - leftSize - 1);
        curNode->right = p.first;
        curNode->updateSize();
        return {curNode, p.second};
    }
}

template<typename T>
ImplicitTreapNode<T>* ImplicitTreap<T>::merge(ImplicitTreapNode<T>* lhs, ImplicitTreapNode<T>* rhs) {
    if (!lhs) return rhs;
    if (!rhs) return lhs;
    if (lhs->getPriority() > rhs->getPriority()) {
        lhs->right = merge(lhs->right, rhs);
        lhs->updateSize();
        return lhs;
    } else {
        rhs->left = merge(lhs, rhs->left);
        rhs->updateSize();
        return rhs;
    }
}

template<typename T>
ImplicitTreapNode<T>* ImplicitTreap<T>::insert(ImplicitTreapNode<T>* curRoot, size_t pos, const T& value) {
    auto p = split(curRoot, pos);
    ImplicitTreapNode<T>* left = p.first;
    ImplicitTreapNode<T>* right = p.second;
    auto newNode = createNode(value);
    auto leftMergeResult = merge(left, newNode);
    return merge(leftMergeResult, right);
}


template<typename T>
ImplicitTreapNode<T>* ImplicitTreap<T>::insert(ImplicitTreapNode<T>* curRoot, size_t pos, T&& value) {
    auto p = split(curRoot, pos);
    ImplicitTreapNode<T>* left = p.first;
    ImplicitTreapNode<T>* right = p.second;
    auto newNode = createNode(std::move(value));
    auto leftMergeResult = merge(left, newNode);
    return merge(leftMergeResult, right);
}


template<typename T>
T& ImplicitTreap<T>::getValue(ImplicitTreapNode<T>* curRoot, size_t pos) {
    size_t leftSize = ImplicitTreapNode<T>::getSize(curRoot->left);
    if (leftSize == pos) return curRoot->getValue();
    if (pos > leftSize) {
        return getValue(curRoot->right, pos - leftSize - 1);
    } else {
        return getValue(curRoot->left, pos);
    }
}

template<typename T>
std::pair<ImplicitTreap<T>, ImplicitTreap<T>> ImplicitTreap<T>::split(size_t x) {
    auto p = split(root, x);
    this->root = nullptr;
    return std::make_pair(ImplicitTreap(p.first), ImplicitTreap(p.second));
}

template<typename T>
ImplicitTreap<T> ImplicitTreap<T>::merge(ImplicitTreap<T>& lhs, ImplicitTreap<T>& rhs) {
    ImplicitTreapNode<T>* newRoot = ImplicitTreap<T>::merge(lhs.getRoot(), rhs.getRoot());
    lhs.root = rhs.root = nullptr;
    return ImplicitTreap(newRoot);
}

template<typename T>
T& ImplicitTreap<T>::getValue(size_t pos) {
    if (pos >= getSize())
        throw std::out_of_range("Attempt to get value of non-existent element");

    return getValue(root, pos);
}

template<typename T>
const T& ImplicitTreap<T>::getValue(size_t pos) const {
    if (pos >= getSize())
        throw std::out_of_range("Attempt to get value of non-existent element");

    return getValue(root, pos);
}

template<typename T>
std::mt19937 ImplicitTreap<T>::getRandFunc() {
    std::mt19937 result(std::chrono::steady_clock::now().time_since_epoch().count());
    return result;
}

template<typename T>
void ImplicitTreap<T>::clear(ImplicitTreapNode<T>* curNode) {
    if (!curNode) return;
    clear(curNode->left);
    clear(curNode->right);
    delete curNode;
}

template<typename T>
ImplicitTreap<T>::~ImplicitTreap() {
    clear(root);
}

template<typename T>
ImplicitTreapNode<T>* ImplicitTreap<T>::copy(ImplicitTreapNode<T>* to, ImplicitTreapNode<T>* from) {
    if (!from) return nullptr;
    to = createNode(from->getValue());
    to->left = copy(to->left, from->left);
    to->right = copy(to->right, from->right);
    to->updateSize();
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

template<typename T>
void ImplicitTreap<T>::setRoot(ImplicitTreapNode<T>* newRoot) {
    root = newRoot;
}


#endif //ROPE_IMPLICITTREAP_CPP
