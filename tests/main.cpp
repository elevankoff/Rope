#include <iostream>
#include <cassert>
#include "../src/Rope.h"

template <typename T>
void toVec(ImplicitTreapNode<T>* curNode, std::vector<T>& result) {
    if (!curNode) return;
    toVec(curNode->left, result);
    result.push_back(curNode->getValue());
    toVec(curNode->right, result);
}

template <typename T>
std::vector<T> toVec(ImplicitTreap<T>& t) {
    std::vector<T> result;
    toVec(t.getRoot(), result);
    return result;
}

void TestImplicitTreapNode() {
    std::cout << "-----------------\n";
    std::cout << "ImplicitTreapNode testing: \n";
    ImplicitTreapNode<int> tn(10, 42), tnl(1, 2), tnr(2, 3);
    tn.left = &tnl;
    tn.right = &tnr;
    tn.updateSize();
    assert(tn.getPriority() == 10);
    assert(tn.left->getPriority() == tnl.getPriority());
    assert(tn.right->getPriority() == tnr.getPriority());
    std::cout << "Priority is OK \n";

    int& x = tn.getValue();
    x = 15;
    assert(tn.getValue() == 15);
    tn.setValue(30);
    assert(tn.getValue() == 30);
    std::cout << "Value is OK \n";

    assert(tn.getSize() == 3);
    assert(tnl.getSize() == 1);
    assert(tnr.getSize() == 1);
    ImplicitTreapNode<int> tn1(tn);
    assert(tn1.getSize() == 3);
    assert(tn.getSize() == 3);

    std::cout << "Size is OK \n";
    std::cout << "ImplicitTreapNode is OK\n";
    std::cout << "-----------------\n \n";
}

void TestImplicitTreap() {
    std::cout << "-----------------\n";
    std::cout << "ImplicitTreap testing: \n";
    std::vector<int> v = {1, 2, 3, 4, 5, 6};
    ImplicitTreap<int> t(v);

    assert(t.getSize() == 6);
    for (size_t i = 0; i < v.size(); i++) {
        assert(t.getValue(i) == v[i]);
    }

    t.erase(0);
    assert(toVec(t) == std::vector<int>({2, 3, 4, 5, 6}));
    assert(t.getSize() == 5);
    t.erase(2);
    assert(toVec(t) == std::vector<int>({2, 3, 5, 6}));
    assert(t.getSize() == 4);
    t.insert(3, 7);
    assert(t.getSize() == 5);
    assert(toVec(t) == std::vector<int>({2, 3, 5, 7, 6}));

    auto p = t.split(2);
    assert(toVec(p.first) == std::vector<int>({2, 3}));
    assert(toVec(p.second) == std::vector<int>({5, 7, 6}));

    assert(p.first.getSize() == 2);
    assert(p.second.getSize() == 3);

    t = ImplicitTreap<int>::merge(p.first, p.second);
    assert(t.getSize() == 5);
    assert(toVec(t) == std::vector<int>({2, 3, 5, 7, 6}));
    t = ImplicitTreap<int>(std::vector<int>({1, 2, 3, 4}));
    assert(t.getValue(2) == 3);
    assert(t.getSize() == 4);
    t.erase(2);
    assert(toVec(t) == std::vector<int>({1, 2, 4}));
    ImplicitTreap<int> g(std::vector<int>({5, 6, 1}));
    t = ImplicitTreap<int>::merge(t, g);
    assert(toVec(t) == std::vector<int>({1, 2, 4, 5, 6, 1}));
    t = t;
    assert(toVec(t) == std::vector<int>({1, 2, 4, 5, 6, 1}));

    t.insert(6, 10);
    assert(toVec(t) == std::vector<int>({1, 2, 4, 5, 6, 1, 10}));

    ImplicitTreap<int> t1;
    t1.insert(0, 1);
    t1.insert(1, 2);
    assert(t1.getSize() == 2);
    assert(toVec(t1) == std::vector<int>({1, 2}));
    t = t1;
    assert(t1.getSize() == 2);
    assert(toVec(t1) == std::vector<int>({1, 2}));
    assert(t.getSize() == 2);
    assert(toVec(t) == std::vector<int>({1, 2}));
    t1 = ImplicitTreap<int>::merge(t, t1);
    assert(t1.getSize() == 4);
    assert(toVec(t1) == std::vector<int>({1, 2, 1, 2}));

    v = {1, 2, 5};
    ImplicitTreap<int> t2(v.begin(), v.end());
    t2.insert(1, t1);
    assert(toVec(t2) == std::vector<int>({1, 1, 2, 1, 2, 2, 5}));
    std::cout << "ImplicitTreap is OK \n";
    std::cout << "-----------------\n \n";
}

void TestRope() {
    std::cout << "--------------\n";
    std::cout << "Rope testing: \n";
    Rope<char> s1(std::string("123"));
    assert(s1.getSize() == 3);
    assert(s1[0] == '1');
    assert(s1[1] == '2');
    assert(s1[2] == '3');

    Rope<char> s2(std::string("456"));
    assert(s2.getSize() == 3);
    assert(s2[0] == '4');
    assert(s2[1] == '5');
    assert(s2[2] == '6');

    Rope<char> s3(std::move(s1));
    s3.concat(s2);
    assert(s3.getSize() == 6);
    assert(s3[0] == '1');
    assert(s3[1] == '2');
    assert(s3[2] == '3');
    assert(s3[3] == '4');
    assert(s3[4] == '5');
    assert(s3[5] == '6');


    s3.concat(Rope<char>("789"));
    assert(s3.getSize() == 9);
    assert(s3[0] == '1');
    assert(s3[3] == '4');
    assert(s3[6] == '7');
    assert(s3[7] == '8');
    assert(s3[8] == '9');

    Rope<char> s4(std::string("a"));


    s4.concat(Rope<char>("bcdefgh"));
    assert(s4.getSize() == 8);
    assert(s4[0] == 'a');
    assert(s4[1] == 'b');
    assert(s4[2] == 'c');
    assert(s4[3] == 'd');
    assert(s4[4] == 'e');
    assert(s4[5] == 'f');
    assert(s4[6] == 'g');
    assert(s4[7] == 'h');


    Rope<char> s5(std::string("ab"));
    s5[1] = 'a';
    assert('a' == s5[1]);
    assert(s5 == Rope<char>("aa"));
    s5.push_back('c');
    s5.push_back('w');
    assert(s5 == Rope<char>("aacw"));

    std::string s6_str;
    Rope<char> const s6(Rope<char>(std::string("abcd")));
    Rope<char> empty("");
    assert(empty.getSize() == 0);
    s5.concat(s6);
    assert(s5 == Rope<char>("aacwabcd"));
    s5.insert(0, 'A');
    s5.insert(1, 'B');
    assert(s5 == Rope<char>("ABaacwabcd"));
    auto p = s5.split(5);
    assert(p.first == Rope<char>("ABaac"));
    assert(p.second == Rope<char>("wabcd"));
    p.first.concat(std::move(p.second));
    assert(p.first == Rope<char>("ABaacwabcd"));
    p.first.concat(p.first);
    assert(p.first == Rope<char>("ABaacwabcdABaacwabcd"));
    Rope<char> a(p.first);
    a.erase(2, 2);
    assert(a == Rope<char>("ABcwabcdABaacwabcd"));
    a.pop_back();
    a.pop_back();
    assert(a == Rope<char>("ABcwabcdABaacwab"));
    std::cout << "Rope is OK \n";
    std::cout << "--------------\n";
}

int main() {
    TestImplicitTreapNode();
    TestImplicitTreap();
    TestRope();
    return 0;
}