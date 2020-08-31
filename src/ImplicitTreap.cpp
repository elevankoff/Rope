#ifndef ROPE_IMPLICITTREAP_CPP
#define ROPE_IMPLICITTREAP_CPP

#include <stdexcept>
#include "ImplicitTreap.h"

template<typename T>
ImplicitTreap<T>::ImplicitTreap()
    : ImplicitTreapRandom(std::chrono::steady_clock::now().time_since_epoch().count())
    , root(nullptr) {}


template<typename T>
ImplicitTreap<T>::ImplicitTreap(std::vector<T>& values)
    : ImplicitTreapRandom(std::chrono::steady_clock::now().time_since_epoch().count())
    , root(nullptr){
    for (int i = 0; i < values.size(); i++) insert(i, values[i]);
}


template<typename T>
ImplicitTreap<T>::ImplicitTreap(ImplicitTreapNode<T>* otherRoot)
    : root(otherRoot) {}

template<typename T>
int ImplicitTreap<T>::getSize() {
    return getSize(root);
}

template<typename T>
ImplicitTreapNode<T>* ImplicitTreap<T>::getRoot() const {
    return root;
}


template<typename T>
void ImplicitTreap<T>::insert(int pos, const T& value) {
    if (pos < 0 || pos > getSize())
        throw std::out_of_range("Attempt to insert into non-existent position");

    root = insert(root, pos, value);
}


template<typename T>
void ImplicitTreap<T>::erase(int pos) {
    if (pos < 0 || pos >= getSize())
        throw std::out_of_range("Attempt to erase non-existent element");

    auto p1 = split(root, pos + 1);
    ImplicitTreapNode<T>* left1 = p1.first, right1 = p1.second;
    auto p2 = split(left1, pos);
    ImplicitTreapNode<T>* left2 = p1.first, right2 = p1.second;
    delete right2;
    root = merge(left2, right1);
}

template<typename T>
std::pair<ImplicitTreapNode<T>*, ImplicitTreapNode<T>*>
ImplicitTreap<T>::split(ImplicitTreapNode<T>* curNode, int toCut) {
    if (!curNode) return std::pair<ImplicitTreapNode<T>*, ImplicitTreapNode<T>*>();
    if (getSize(curNode->left) >= toCut) {
        auto p = split(curNode->left, toCut);
        curNode->left = p.second;
        curNode->updateSize();
        return {p.first, curNode};
    } else {
        auto p = split(curNode->right, toCut - getSize(curNode->left) - 1);
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
ImplicitTreapNode<T>* ImplicitTreap<T>::createNode(const T& value) {
    auto result = new ImplicitTreapNode<T>(ImplicitTreapRandom(), value);
    return result;
}

template<typename T>
ImplicitTreap<T>* ImplicitTreap<T>::insert(ImplicitTreap<T>* curRoot, int pos, const T& value) {
    auto p = split(curRoot, pos);
    ImplicitTreapNode<T>* left = p.first, right = p.second;
    auto newNode = createNode(value);
    auto leftMergeResult = merge(left, newNode);
    return merge(leftMergeResult, right);
}

template<typename T>
std::pair<ImplicitTreap<T>&, ImplicitTreap<T>&> ImplicitTreap<T>::split(int x) {
    auto p = split(root, x);
    return std::make_pair(ImplicitTreap(p.first), ImplicitTreap(p.second));
}

template<typename T>
void ImplicitTreap<T>::merge(ImplicitTreap<T>& lhs, ImplicitTreap<T>& rhs) {
    ImplicitTreapNode<T>* newRoot = merge(lhs.getRoot(), rhs.getRoot());
    return ImplicitTreap(newRoot);
}

template<typename T>
std::minstd_rand& ImplicitTreap<T>::getRandFunc() {
    return ImplicitTreapRandom;
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

#endif
