#ifndef ROPE_ROPEITERATOR_INL_H
#define ROPE_ROPEITERATOR_INL_H

#include "../include/Rope.h"

// Iterator implementation

template<typename T>
Rope<T>::iterator::iterator(T* elem, size_t pos, Rope<T>* rope)
        : elem(elem)
        , pos(pos)
        , rope(rope)
{}

template<typename T>
typename Rope<T>::iterator
Rope<T>::iterator::operator+ (int n) {
    return iterator(&(*rope)[pos + n], pos + n, rope);
}

template<typename T>
typename Rope<T>::iterator
Rope<T>::iterator::operator- (int n) {
    return iterator(&(*rope)[pos - n], pos - n, rope);
}

template<typename T>
typename Rope<T>::iterator
Rope<T>::iterator::operator++ (int) {
    iterator res(elem, pos, rope);
    if (pos + 1 == rope->size()) {
        pos++;
    } else {
        elem = &(*rope)[++pos];
    }
    return res;
}

template<typename T>
typename Rope<T>::iterator
Rope<T>::iterator::operator-- (int) {
    iterator res(elem, pos, rope);
    elem = &(*rope)[--pos];
    return res;
}

template<typename T>
typename Rope<T>::iterator
Rope<T>::iterator::operator++ () {
    if (pos + 1 == rope->size()) {
        pos++;
    } else {
        elem = &(*rope)[++pos];
    }
    return *this;
}

template<typename T>
typename Rope<T>::iterator
Rope<T>::iterator::operator-- () {
    elem = &(*rope)[--pos];
    return *this;
}

template<typename T>
bool Rope<T>::iterator::operator!= (const iterator& it) { return pos != it.pos; }

template<typename T>
bool Rope<T>::iterator::operator== (const iterator& it) { return pos == it.pos; }

template<typename T>
T& Rope<T>::iterator::operator* () { return *elem; }

#endif //ROPE_ROPEITERATOR_INL_H
