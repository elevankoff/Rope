# Rope

Rope is a data structure for fast manipulating with large strings. You can fast split rope into two ropes, concatenate two ropes into one, insert another rope or element, get and delete the element at a certain position. And all those operations have ***O(log(n))*** asymptotic.  
My implementation is based on Treap data structure with implicit key, so you can manipulate with sequences of any type you want.

More related information about these data structures you can find here:  
`Rope:`  
[[EN] Wikipedia](https://en.wikipedia.org/wiki/Rope_(data_structure))  
[[EN] Opengenus](https://iq.opengenus.org/rope-data-structure/)  
[[RU] Habr.com](https://habr.com/ru/post/144736/)  
[[RU] Qwe.wiki](https://ru.qwe.wiki/wiki/Rope_(data_structure))  
`Treap and Implicit Treap:`  
[[EN] Cp-algorithms](https://cp-algorithms.com/data_structures/treap.html)  
[[RU] Emaxx](https://e-maxx.ru/algo/treap)  
[[RU] Habr.com](https://habr.com/ru/post/102364/)

## Usage

```{C++}
#include "Rope.h"

int main() {
    Rope<char> rope1("Hello, ");
    Rope<char> rope2("World!!!");
    rope1.concat(std::move(rope2));
    rope1.print(std::cout, 0, rope1.getSize(), "");
    std::cout << '\n';
    /* Better don't touch moved elements, but in the current version
     * moved element becomes empty, so we can print it and get an empty string*/
    rope2.print(std::cout, 0, rope2.getSize(), "");
    std::cout << '\n';

    rope1.erase(0, 5);
    Rope<char> toAdd("I love you");
    rope1.insert(0, std::move(toAdd));
    rope1.print(std::cout, 0, rope1.getSize(), "");
    std::cout << '\n';
    auto p = rope1.split(10);
    p.first.print(std::cout, 0, p.first.getSize(), "");
    std::cout << '\n';
    p.second = Rope<char>("Lalita");
    p.second.print(std::cout, 0, p.second.getSize(), "");
    std::cout << '\n';
    return 0;
}

Output:
Hello, World!!!

I love you, World!!!
I love you
Lalita

```

## Comparison with Vector(or String)
| Operation| Vector(or String) | Rope |
|---- | ------------- | ------------- |
| `Build` | *O(n)* | *O(n log(n))* |
| `Insert (destructive (use std::move))` |  *O(n m)* | *O(log(n))* |
| `Insert (non-destructive)` |  *O(n m)* | *O(m log(n))* |
| `Erase` | *O(n)* | *O(log(n))* |
| `Concat` | *O(m)* | *O(log(n))* |
| `Split` |  *O(n)* | *O(log(n))* |
| `Push/pop back` | *O(1)* | *O(log(n))* |
| `Print` | *O(m)* | *O(m + log(n))* |
| `Get value` | *O(1)* | *O(log(n))* |
| `Get size` | *O(1)* | *O(1)* |
| `Comparison operators` | *O(n)* | *O(n)* |


## Future work
- Make "print"-function more user-friendly 
- Implement iterators 
- Add more tests
- Build can be improved up to *O(n)*
- ...

## Contributing
If you have any suggestions, here's my e-mail and Telegram: **e.levankoff@yandex.ru**  **@YegorLevankov**

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License
[MIT](https://choosealicense.com/licenses/mit/)
