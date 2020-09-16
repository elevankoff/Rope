#include <iostream>
#include <cassert>
#include "../include/Rope.h"

template <typename T>
void toVec(Node<T> curNode, std::vector<T>& result) {
    if (!curNode) { return; }
    toVec(curNode->getLeft(), result);
    result.push_back(curNode->getValue());
    toVec(curNode->getRight(), result);
}

template <typename T>
std::vector<T> toVec(const ImplicitTreap<T>& t) {
    std::vector<T> result;
    toVec(t.getRoot(), result);
    return result;
}

void TestImplicitTreapNode() {
    std::cout << "-----------------\n";
    std::cout << "ImplicitTreapNode testing: \n";
    int a = 1;
    ImplicitTreapNode<int> t1(1001, 5),
        t2(1000, a), t3(999, a);
    assert(t1.getPriority() == 1001);
    assert(t1.size() == 1);
    assert(t1.getValue() == 5);
    t1.setLeft(&t2);
    t1.setRight(&t3);
    t1.update();
    assert(t1.getPriority() == 1001);
    assert(t1.size() == 3);
    assert(t1.getLeft() == &t2);
    assert(t1.getRight() == &t3);
    assert(t1.getLeft()->getPriority() == 1000);
    assert(t1.getRight()->getPriority() == 999);
    ImplicitTreapNode<int> t4(998, 1), t5(997, 2);
    t3.setLeft(&t4);
    t3.setRight(&t5);
    t3.update();
    t1.update();
    assert(t1.getRight()->getLeft()->getPriority() == 998);
    assert(t1.getRight()->getRight()->getPriority() == 997);
    assert(t1.size() == 5);
    assert(t3.size() == 3);
    assert(t3.getValue() == 1);
    assert(t3.getPriority() == 999);
    t3 = 1337;
    assert(t3.getValue() == 1337);
    t3 = std::move(a);
    int& x = t3.getValue();
    assert(x == 1);
    x = 1000;
    assert(t3.getValue() == 1000);
    const ImplicitTreapNode<int> t6(2000, 1);
    assert(t6.size() == 1);
    std::cout << "ImplicitTreapNode is OK\n";
    std::cout << "-----------------\n \n";

}


void TestImplicitTreap1() {
    std::cout << "-----------------\n";
    std::cout << "ImplicitTreap1 testing: \n";
    std::vector<int> v = {1, 2, 3, 4, 5, 6};
    ImplicitTreap<int> t(v);

    assert(t.size() == 6);
    for (size_t i = 0; i < v.size(); i++) {
        assert(t.getValue(i) == v[i]);
    }
    assert(toVec(t) == std::vector<int>({1, 2, 3, 4, 5, 6}));

    t.erase(0);
    assert(toVec(t) == std::vector<int>({2, 3, 4, 5, 6}));
    assert(t.size() == 5);
    t.erase(2);
    assert(toVec(t) == std::vector<int>({2, 3, 5, 6}));
    assert(t.size() == 4);
    t.insert(3, 7);
    assert(t.size() == 5);
    assert(toVec(t) == std::vector<int>({2, 3, 5, 7, 6}));

    auto p = t.split(2);
    assert(toVec(p.first) == std::vector<int>({2, 3}));
    assert(toVec(p.second) == std::vector<int>({5, 7, 6}));

    assert(p.first.size() == 2);
    assert(p.second.size() == 3);

    t = ImplicitTreap<int>::merge(p.first, p.second);
    assert(t.size() == 5);
    assert(toVec(t) == std::vector<int>({2, 3, 5, 7, 6}));
    t = ImplicitTreap<int>(std::vector<int>({1, 2, 3, 4}));
    assert(t.getValue(2) == 3);
    assert(t.size() == 4);
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
    assert(t1.size() == 2);
    assert(toVec(t1) == std::vector<int>({1, 2}));
    t = t1;
    assert(t1.size() == 2);
    assert(toVec(t1) == std::vector<int>({1, 2}));
    assert(t.size() == 2);
    assert(toVec(t) == std::vector<int>({1, 2}));
    t1 = ImplicitTreap<int>::merge(t, t1);
    assert(t1.size() == 4);
    assert(toVec(t1) == std::vector<int>({1, 2, 1, 2}));

    v = {1, 2, 5};
    ImplicitTreap<int> t2(v.begin(), v.end());
    t2.insert(1, t1);
    assert(toVec(t2) == std::vector<int>({1, 1, 2, 1, 2, 2, 5}));
    std::cout << "ImplicitTreap1 is OK \n";
    std::cout << "-----------------\n \n";
}

void TestImplicitTreap2() {
    std::cout << "--------------\n";
    std::cout << "ImplicitTreap2 testing: \n";

    std::vector<int> v1;
    ImplicitTreap<int> t;
    for (size_t i = 0; i < 100; i++) {
        size_t type = rand()%3;
        if (type == 0) {
            assert(t.size() == v1.size());
            size_t pos;
            if (t.size() == 0) {
                pos = 0;
            } else {
                pos = rand() % t.size();
            }
            int val = rand() % 100 - 50;
            t.insert(pos, val);
            v1.insert(v1.begin() + pos, val);
            assert(toVec(t) == v1);
        } else if (type == 1 && t.size()) {
            size_t pos = rand() % t.size();
            t.erase(pos);
            v1.erase(v1.begin() + pos);
            assert(t.size() == v1.size());
            assert(toVec(t) == v1);
        } else if (t.size()) {
            size_t pos = rand() % t.size();
            assert(t.getValue(pos) == v1[pos]);
        }
    }

    std::vector<int> v = {1, 3, 2, 5};
    ImplicitTreap<int> t1(v.begin(), v.end()), t2(v);
    const ImplicitTreap<int> t3(std::move(v));

    assert(toVec(t1) == toVec(t2));
    assert(toVec(t2) == toVec(t3));
    assert(t1.size() == t2.size());
    assert(t1.size() == t3.size());
    assert(t1.size() == 4);

    auto p = t1.split(2);
    assert(toVec(t1) == std::vector<int>());
    assert(toVec(p.first) == std::vector<int>({1, 3}));
    assert(toVec(p.second) == std::vector<int>({2, 5}));
    assert(t1.size() == 0);
    assert(t1.getRoot() == nullptr);

    ImplicitTreap<int> t4 = ImplicitTreap<int>::merge(p.first, p.second);
    assert(p.first.size() == 0);
    assert(p.second.size() == 0);
    assert(toVec(t4) == v);
    t4 = ImplicitTreap<int>::merge(t2, t4);
    assert(t4.size() == 8);
    assert(t2.size() == 0);
    assert(toVec(t4) == std::vector<int>({1, 3, 2, 5, 1, 3, 2, 5}));
    t4.insert(0, 10);
    t4.insert(1, 100);
    assert(toVec(t4) == std::vector<int>({10, 100, 1, 3, 2, 5, 1, 3, 2, 5}));
    assert(t4.size() == 10);
    t4.insert(1, t3);
    assert(toVec(t4) == std::vector<int>({10, 1, 3, 2, 5, 100, 1, 3, 2, 5, 1, 3, 2, 5}));

    std::vector<int> toCheck({10, 1, 3, 2, 5, 100, 1, 3, 2, 5, 1, 3, 2, 5});

    assert(t4.size() == toCheck.size());
    for (size_t i = 0; i < t4.size(); i++) {
        assert(t4.getValue(i) == toCheck[i]);
    }

    t4.erase(0);
    t4.erase(t4.size() - 1);
    t4.erase(2);
    assert(toVec(t4) == std::vector<int>({1, 3, 5, 100, 1, 3, 2, 5, 1, 3, 2}));


    ImplicitTreap<int> t5(v);

    t4 = t5;
    assert(toVec(t4) == v);
    assert(t4.size() == 4);
    t4 = std::move(t5);
    assert(t5.size() == 0);
    assert(toVec(t4) == v);

    std::cout << "ImplicitTreap2 is OK \n";
    std::cout << "--------------\n\n";
}

void TestRope1() {
    std::cout << "--------------\n";
    std::cout << "Rope1 testing: \n";
    Rope<char> s1(std::string("123"));
    assert(s1.size() == 3);
    assert(s1[0] == '1');
    assert(s1[1] == '2');
    assert(s1[2] == '3');

    Rope<char> s2(std::string("456"));
    assert(s2.size() == 3);
    assert(s2[0] == '4');
    assert(s2[1] == '5');
    assert(s2[2] == '6');

    Rope<char> s3(std::move(s1));
    s3.concat(s2);
    assert(s3.size() == 6);
    assert(s3[0] == '1');
    assert(s3[1] == '2');
    assert(s3[2] == '3');
    assert(s3[3] == '4');
    assert(s3[4] == '5');
    assert(s3[5] == '6');

    s3.concat(Rope<char>(std::string("789")));
    assert(s3.size() == 9);
    assert(s3[0] == '1');
    assert(s3[3] == '4');
    assert(s3[6] == '7');
    assert(s3[7] == '8');
    assert(s3[8] == '9');

    Rope<char> s4(std::string("a"));


    s4.concat(Rope<char>(std::string("bcdefgh")));
    assert(s4.size() == 8);
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
    assert(s5 == Rope<char>(std::string("aa")));
    s5.push_back('c');
    s5.push_back('w');
    assert(s5 == Rope<char>(std::string("aacw")));

    std::string s6_str;
    Rope<char> const s6(Rope<char>(std::string("abcd")));
    Rope<char> empty(std::string(""));
    assert(empty.size() == 0);
    s5.concat(s6);
    assert(s5 == Rope<char>(std::string("aacwabcd")));
    s5.insert(0, 'A');
    s5.insert(1, 'B');
    assert(s5 == Rope<char>(std::string("ABaacwabcd")));
    auto p = s5.split(5);
    assert(p.first == Rope<char>(std::string("ABaac")));
    assert(p.second == Rope<char>(std::string("wabcd")));
    p.first.concat(std::move(p.second));
    assert(p.first == Rope<char>(std::string("ABaacwabcd")));
    p.first.concat(p.first);
    assert(p.first == Rope<char>(std::string("ABaacwabcdABaacwabcd")));
    Rope<char> a(p.first);
    a.erase(2, 2);
    assert(a == Rope<char>(std::string("ABcwabcdABaacwabcd")));
    a.pop_back();
    a.pop_back();
    assert(a == Rope<char>(std::string("ABcwabcdABaacwab")));
    Rope<char> b(std::string("asdads"));
    Rope<char> c(std::string("basdas"));
    assert(b < c);
    assert(b <= c);
    assert(c > b);
    assert(c >= b);
    assert(!(c == b));
    assert(c != b);
    std::cout << "Rope1 is OK \n";
    std::cout << "--------------\n";
}

void TestRope2() {
    std::cout << "-----------------\n";
    std::cout << "Rope2 testing: \n";

    const std::string s1 = "Hi, Pedro!";
    Rope<char> r1(s1);
    assert(r1[0] == s1[0]);
    assert(r1[2] == s1[2]);
    assert(r1[4] == s1[4]);
    assert(r1[r1.size() - 1] == s1[s1.size() - 1]);
    assert(r1.toVec() == std::vector<char>(s1.begin(), s1.end()));
    assert(r1.size() == s1.size());

    std::string s2 = " I want to tell you a story...",
        s3 = s1 + s2;

    Rope<char> r2(s2.begin(), s2.end());
    r1.concat(r2);
    assert(r1.toVec() == std::vector<char>(s3.begin(), s3.end()));
    r1.concat(std::move(r2));
    assert(r2.size() == 0);
    s3 += s2;
    assert(r1.toVec() == std::vector<char>(s3.begin(), s3.end()));
    assert(r1.size() == s3.size());
    r1.pop_back(); s3.pop_back();
    r1.pop_back(); s3.pop_back();
    assert(r1.toVec() == std::vector<char>(s3.begin(), s3.end()));
    assert(r1.size() == s3.size());
    char& x = r1[0];
    s3[0] = 'U';
    x = 'U';
    r1.print(0, r1.size(), std::cout, "");
    std::cout << '\n';

    try {
        r1.print(10, r1.size(), std::cout, "");
        assert(false);
    } catch(...) {}

    assert(r1.toVec() == std::vector<char>(s3.begin(), s3.end()));

    r1.push_back('!'); s3.push_back('!');
    r1.push_back('!'); s3.push_back('!');
    assert(r1.toVec() == std::vector<char>(s3.begin(), s3.end()));
    Rope<char> r3(s3.begin(), s3.end());
    assert(r3 == r1);
    r1[0] = r3[0] = 'K';
    assert(r3 == r1);
    r1.erase(0);
    r3.erase(0);
    s3.erase(s3.begin());
    assert(r3.size() == s3.size());
    assert(r3.toVec() == std::vector<char>(s3.begin(), s3.end()));
    r1.insert(1, std::move(r3));
    std::string s4 = s3;
    s3.insert(1, s4);
    assert(r1.toVec() == std::vector<char>(s3.begin(), s3.end()));
    assert(r1.size() == s3.size());
    s3.insert(3, s4);
    Rope<char> r4(s4.begin(), s4.end());
    r1.insert(3, r4);
    assert(r1.toVec() == std::vector<char>(s3.begin(), s3.end()));
    r1 = r4;
    assert(r1.size() == s4.size());
    assert(r1.toVec() == std::vector<char>(s4.begin(), s4.end()));

    std::cout << "Rope2 is OK \n";
    std::cout << "--------------\n\n";
}

void TestAll() {
    TestImplicitTreapNode();
    TestImplicitTreap1();
    TestImplicitTreap2();
    TestRope1();
    TestRope2();
}

using namespace __gnu_cxx;
#include <ext/rope>
#include <set>

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

template<typename T>
void curTime(T& timer) {
    timer = std::chrono::high_resolution_clock::now();
}

template<typename T>
void printDuration(const T& start, const T& stop) {
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << duration.count() / 1'000'000.0 << " (sec)\n";
}

void CompareTime() {
    auto start = std::chrono::high_resolution_clock::now(),
    stop = std::chrono::high_resolution_clock::now();

    std::vector<char> lines[1000];
    for (size_t i = 0; i < 1000; i++) {
        size_t size = 1000;
        for (size_t j = 0; j < size; j++) {
            lines[i].push_back(char('a' + rng()%26));
        }
    }


    std::cout << "Random insertions: \n";
    curTime(start);
    rope<char> sr[1000];

    for (size_t i = 0; i < 1000; i++) {
        for (size_t j = 0; j < 1000; j++) {
            if (j == 0) {
                sr[i].push_back(lines[i][j]);
            } else {
                sr[i].insert(rng() % sr[i].size(), lines[i][j]);
            }
        }
    }

    curTime(stop);
    std::cout << "__gnu_cxx rope: ";
    printDuration(start, stop);

    curTime(start);
    Rope<char> mr[1000];
    for (size_t i = 0; i < 1000; i++) {
        for (size_t j = 0; j < 1000; j++) {
            if (j == 0) {
                mr[i].push_back(lines[i][j]);
            } else {
                mr[i].insert(rng() % mr[i].size(), lines[i][j]);
            }
        }
    }
    curTime(stop);

    std::cout << "My rope: ";
    printDuration(start, stop);

    std::cout << "Random deletions: \n";

    curTime(start);
    for (size_t i = 0; i < 1000; i++) {
        for (size_t j = 0; j < 1000; j++) {
            size_t pos = rng() % sr[i].size();
            sr[i].erase(pos, 1);
        }
    }
    curTime(stop);

    std::cout << "__gnu_cxx rope: ";
    printDuration(start, stop);

    curTime(start);
    for (auto & i : mr) {
        for (size_t j = 0; j < 1000; j++) {
            size_t pos = rng() % i.size();
            i.erase(pos);
        }
    }
    curTime(stop);

    std::cout << "My rope: ";
    printDuration(start, stop);

    for (size_t i = 0; i < 1000; i++) {
        for (size_t j = 0; j < 1000; j++) {
            mr[i].push_back(lines[i][j]);
            sr[i].push_back(lines[i][j]);
        }
    }

    std::cout << "Appending ropes (with copying): \n";
    curTime(start);
    for (size_t i = 1; i < 1000; i++) {
        sr[0].append(sr[i]);
    }
    curTime(stop);
    std::cout << "__gnu_cxx rope: ";
    printDuration(start, stop);

    curTime(start);
    for (size_t i = 1; i < 1000; i++) {
        mr[0].concat(mr[i]);
    }
    curTime(stop);
    std::cout << "My rope: ";
    printDuration(start, stop);

    std::cout << "Clearing: \n";
    curTime(start);
    for (size_t i = 0; i < 1000; i++) {
        sr[i].clear();
    }
    curTime(stop);
    std::cout << "__gnu_cxx rope: ";
    printDuration(start, stop);

    curTime(start);
    for (size_t i = 0; i < 1000; i++) {
        mr[i].clear();
    }
    curTime(stop);
    std::cout << "My rope: ";
    printDuration(start, stop);

    std::cout << "Push back: \n";
    curTime(start);
    for (size_t i = 0; i < 1000; i++) {
        for (auto& c : lines[i]) {
            sr[i].push_back(c);
        }
    }
    curTime(stop);
    std::cout << "__gnu_cxx rope: ";
    printDuration(start, stop);

    curTime(start);
    for (size_t i = 0; i < 1000; i++) {
        for (auto& c : lines[i]) {
            mr[i].push_back(c);
        }
    }
    curTime(stop);
    std::cout << "My rope: ";
    printDuration(start, stop);

    std::cout << "Appending ropes (without copying): \n";
    std::cout << "__gnu_cxx rope: N/A \n";

    curTime(start);
    for (size_t i = 1; i < 1000; i++) {
        mr[0].concat(std::move(mr[i]));
    }
    curTime(stop);
    std::cout << "My rope: ";
    printDuration(start, stop);
}

int main() {
    srand(time(0));
    CompareTime();
    std::cout << "\n\n";
    TestAll();

    return 0;

}
