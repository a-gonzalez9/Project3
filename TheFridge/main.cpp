#include <iostream>
#include "hashmap.cpp"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Hashmap hp = Hashmap(11);
    hp.insert("apple");
    hp.insert("banana");
    hp.insert("cherry");
    hp.insert("blueberry");
    hp.insert("mango");
    hp.insert("plum");
    hp.insert("watermelon");
    hp.insert("dragonfruit");
    hp.insert("kiwi");
    hp.insert("reallylongstring");
    hp.display();
    return 0;
}
