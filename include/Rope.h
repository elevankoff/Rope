#ifndef ROPE_ROPE_H
#define ROPE_ROPE_H

#include "../src/ImplicitTreap.h"

template <typename T>
class Rope {
public:
    // Constructors
    Rope();

    Rope(const Rope& otherRope);

    Rope(Rope&& otherRope);

    template<typename Container>
    explicit Rope(const Container& values, size_t size);

    template<typename Container>
    explicit Rope(Container&& values, size_t size);

    explicit Rope(const std::vector<T>& values);

    explicit Rope(std::vector<T>&& values);

    explicit Rope(const std::string& s);

    explicit Rope(std::string&& s);

    template <typename It>
    Rope(It first, It last);

    void push_back(const T& value);

    void pop_back();

    //  Concatenate current rope with "other" ("other" rope becomes empty)
    void concat(const Rope& otherRope);

    void concat(Rope&& otherRope);

    // Splits current rope into two ropes, where first rope has size "toCut" and
    // other has size oldRopeSize - toCut
    [[ nodiscard ]] std::pair<Rope<T>, Rope<T>> split(size_t toCut);

    // Deletes element at position "pos"
    void erase(size_t pos);

    // Deletes elements in the interval [pos, pos + cnt)
    void erase(size_t pos, size_t cnt);

    // Inserts element at position "pos"
    void insert(size_t pos, const T& value);

    // Inserts elements by iterators before position "pos"
    template<typename It>
    void insert(size_t pos, It first, It last);

    // Inserts "otherRope" before position "pos" ("otherRope" is still usable)
    void insert(size_t pos, const Rope& otherRope);

    // Inserts "otherRope" before position "pos" ("otherRope" is not more usable)
    void insert(size_t pos, Rope&& otherRope);

    // prints "cnt" elements from position "from"
    void print(size_t from, size_t cnt, std::ostream& os = std::cout, const std::string& delim = " ");

    // Returns number of elements in the current rope
    size_t size() const;

    T& operator [](size_t pos);

    const T& operator[](size_t pos) const;

    bool operator == (const Rope<T>& otherRope) const;

    bool operator != (const Rope<T>& otherRope) const;

    bool operator < (const Rope<T>& otherRope) const;

    bool operator <= (const Rope<T>& otherRope) const;

    bool operator > (const Rope<T>& otherRope) const;

    bool operator >= (const Rope<T>& otherRope) const;

    Rope<T>& operator = (const Rope<T>& otherRope);

    Rope<T>& operator = (Rope<T>&& otherRope);

    std::vector<T> toVec() const;

private:
    static void print(std::ostream& os, Node<T> curRoot, const std::string& delim);

    static void toVec(Node<T> curNode, std::vector<T>& result);

private:
    ImplicitTreap<T> impTreap;
};

#include "Rope-inl.h"


#endif //ROPE_ROPE_H
