#ifndef ROPE_ROPECONSTITERATOR_INL_H
#define ROPE_ROPECONSTITERATOR_INL_H

#include "../include/Rope-inl.h"

// Const iterator implementation

template<typename T>
Rope<T>::const_iterator::const_iterator(const T* elem, size_t pos, const Rope<T>* rope)
        : elem(elem)
        , pos(pos)
        , rope(rope)
{}

template<typename T>
typename Rope<T>::const_iterator
Rope<T>::const_iterator::operator+ (int n) {
    return const_iterator(&(*rope)[pos + n], pos + n, rope);
}

template<typename T>
typename Rope<T>::const_iterator
Rope<T>::const_iterator::operator- (int n) {
    return const_terator(&(*rope)[pos - n], pos - n, rope);
}

template<typename T>
typename Rope<T>::const_iterator
Rope<T>::const_iterator::operator++ (int) {
   const_iterator res(elem, pos, rope);
    if (pos + 1 == rope->size()) {
        pos++;
    } else {
        elem = &(*rope)[++pos];
    }
    return res;
}

template<typename T>
typename Rope<T>::const_iterator
Rope<T>::const_iterator::operator-- (int) {
   const_iterator res(elem, pos, rope);
    elem = &(*rope)[--pos];
    return res;
}

template<typename T>
typename Rope<T>::const_iterator
Rope<T>::const_iterator::operator++ () {
    if (pos + 1 == rope->size()) {
        pos++;
    } else {
        elem = &(*rope)[++pos];
    }
    return *this;
}

template<typename T>
typename Rope<T>::const_iterator
Rope<T>::const_iterator::operator-- () {
    elem = &(*rope)[--pos];
    return *this;
}

template<typename T>
bool Rope<T>::const_iterator::operator!= (const const_iterator& it) { return pos != it.pos; }

template<typename T>
bool Rope<T>::const_iterator::operator== (const const_iterator& it) { return pos == it.pos; }

template<typename T>
const T& Rope<T>::const_iterator::operator* () { return *elem; }

#endif //ROPE_ROPECONSTITERATOR_INL_H
