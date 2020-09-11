#ifndef ROPE_ROPE_INL_H
#define ROPE_ROPE_INL_H

#include "Rope.h"

template<typename T>
Rope<T>::Rope()
    : impTreap() {}

template<typename T>
Rope<T>::Rope(const Rope<T>& otherRope)
    : impTreap(otherRope.impTreap) {}

template<typename T>
Rope<T>::Rope(Rope&& otherRope)
    : impTreap(std::move(otherRope.impTreap)) {}

template<typename T>
template<typename Container>
Rope<T>::Rope(const Container& values, size_t size)
    : impTreap(values, size) {}

template<typename T>
Rope<T>::Rope(const std::vector<T>& values)
    : impTreap(values) {}

template<typename T>
Rope<T>::Rope(std::vector<T>&& values)
    : impTreap(std::move(values)) {}

template<typename T>
Rope<T>::Rope(const std::string& s)
    : impTreap(s) {
    static_assert(std::is_same<T, char>::value, "!");
}

template<typename T>
Rope<T>::Rope(std::string&& s)
    : impTreap(std::move(s)) {
    static_assert(std::is_same<T, char>::value, "!");
}

template<typename T>
template<typename Container>
Rope<T>::Rope(Container&& values, size_t size)
    : impTreap(std::move(values), size) {}

template<typename T>
template<typename It>
Rope<T>::Rope(It first, It last)
    : impTreap(first, last) {}


template<typename T>
void Rope<T>::push_back(const T& value) {
    impTreap.insert(size(), value);
}


template<typename T>
void Rope<T>::pop_back() {
    impTreap.erase(size() - 1);
}

template<typename T>
void Rope<T>::concat(const Rope& otherRope) {
    size_t n = otherRope.size();
    for (size_t i = 0; i < n; i++) {
        this->push_back(otherRope[i]);
    }
}

template<typename T>
void Rope<T>::concat(Rope&& otherRope) {
    impTreap = ImplicitTreap<T>::merge(impTreap, otherRope.impTreap);
}

template<typename T>
std::pair<Rope<T>, Rope<T>> Rope<T>::split(size_t toCut) {
    auto p = (*this).impTreap.split(toCut);
    std::pair<Rope<T>, Rope<T>> result;
    result.first.impTreap = p.first;
    result.second.impTreap = p.second;
    return result;
}

template<typename T>
void Rope<T>::erase(size_t pos) {
    impTreap.erase(pos);
}

template<typename T>
void Rope<T>::erase(size_t pos, size_t cnt) {
    impTreap.erase(pos, cnt);
}

template<typename T>
void Rope<T>::insert(size_t pos, const T& value) {
    impTreap.insert(pos, value);
}

template<typename T>
template<typename It>
void Rope<T>::insert(size_t pos, It first, It last) {
    while (first != last) {
        impTreap.insert(pos++, *first++);
    }
}

template<typename T>
void Rope<T>::insert(size_t pos, const Rope& otherRope) {
    impTreap.insert(pos, otherRope.impTreap);
}

template<typename T>
void Rope<T>::insert(size_t pos, Rope&& otherRope) {
    auto p = split(pos);
    p.first.concat(std::move(otherRope));
    p.first.concat(std::move(p.second));
    *this = std::move(p.first);
}

template<typename T>
void Rope<T>::print(size_t from, size_t cnt, std::ostream& os, const std::string& delim) {
    if (from + cnt > size()) {
        throw std::out_of_range("Attempt to print a non-existent element");
    }

    auto p1 = split(from);
    auto p2 = p1.second.split(cnt);
    print(os, p2.first.impTreap.getRoot(), delim);
    p1.first.concat(std::move(p2.first));
    p1.first.concat(std::move(p2.second));
    *this = std::move(p1.first);
}

template<typename T>
size_t Rope<T>::size() const {
    return impTreap.size();
}

template<typename T>
T& Rope<T>::operator[](size_t pos) {
    return impTreap.getValue(pos);
}

template<typename T>
const T& Rope<T>::operator[](size_t pos) const {
    return impTreap.getValue(pos);
}

template<typename T>
bool Rope<T>::operator == (const Rope<T>& otherRope) const {
    if (otherRope.size() != size()) { return false; }
    std::vector<T> my_v = toVec(), other_v = otherRope.toVec();
    return my_v == other_v;
}

template<typename T>
bool Rope<T>::operator != (const Rope<T>& otherRope) const {
    return !((*this) == otherRope);
}

template<typename T>
bool Rope<T>::operator < (const Rope<T>& otherRope) const {
    std::vector<T> my_v = toVec(), other_v = otherRope.toVec();
    return my_v < other_v;
}

template<typename T>
bool Rope<T>::operator <= (const Rope<T>& otherRope) const {
    return (*this) == otherRope || (*this) < otherRope;
}

template<typename T>
bool Rope<T>::operator > (const Rope<T>& otherRope) const {
    return !((*this) <= otherRope);
}

template<typename T>
bool Rope<T>::operator >= (const Rope<T>& otherRope) const {
    return !((*this) < otherRope);
}

template<typename T>
Rope<T>& Rope<T>::operator = (const Rope<T>& otherRope) {
    impTreap = otherRope.impTreap;
    return *this;
}

template<typename T>
Rope<T>& Rope<T>::operator=(Rope<T>&& otherRope) {
    impTreap = std::move(otherRope.impTreap);
    return *this;
}

template<typename T>
std::vector<T> Rope<T>::toVec() const {
    std::vector<T> result;
    result.reserve(size());
    toVec(impTreap.getRoot(), result);
    return result;
}


template<typename T>
void Rope<T>::print(std::ostream& os, Node<T> curRoot, const std::string& delim) {
    if (!curRoot) { return; }
    print(os, curRoot->getLeft(), delim);
    os << curRoot->getValue() << delim;
    print(os, curRoot->getRight(), delim);
}

template<typename T>
void Rope<T>::toVec(Node<T> curNode, std::vector<T>& result) {
    if (!curNode) { return; }
    toVec(curNode->getLeft(), result);
    result.push_back(curNode->getValue());
    toVec(curNode->getRight(), result);
}


#endif // ROPE_ROPE_INL_H
