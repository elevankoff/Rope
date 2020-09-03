#ifndef ROPE_ROPE_H
#define ROPE_ROPE_H

#include "ImplicitTreap.h"

template <typename T>
class Rope {
public:
    Rope();

    Rope(const Rope& otherRope);

    Rope(Rope&& otherRope);

    explicit Rope(const std::vector<T>& values);

    explicit Rope(std::vector<T>&& values);

    explicit Rope(const std::string& s);

    explicit Rope(std::string&& s);

    template <typename It>
    Rope(It first, It last);

    void concat(Rope& other);

    [[ nodiscard ]] std::pair<Rope<T>, Rope<T>> split(size_t toCut);

    void erase(size_t pos);

    void erase(size_t pos, size_t cnt);

    void insert(size_t pos, const T& value);

    template<typename It>
    void insert(size_t pos, It first, It last);

    void insert(size_t pos, Rope& otherRope);

    size_t getSize() const;

    T& operator [](int pos);

    const T& operator[](int pos) const;

    bool operator == (const Rope<T>& otherRope) const;

    bool operator != (const Rope<T>& otherRope) const;

    bool operator < (const Rope<T>& otherRope) const;

    bool operator <= (const Rope<T>& otherRope) const;

    bool operator > (const Rope<T>& otherRope) const;

    bool operator >= (const Rope<T>& otherRope) const;

private:
    ImplicitTreap<T> impTreap;
};

#include "Rope.cpp"


#endif //ROPE_ROPE_H
