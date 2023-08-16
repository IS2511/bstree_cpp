#include <iostream>
#include <string>

#include "tree-all.h"

int main() {
    Tree::AVLTree<std::string, int, 3> tree;

    std::cout << "Tree capacity: " << tree.capacity() << std::endl;
    std::cout << "Tree size: " << tree.size() << std::endl;
    std::cout << std::endl;

    std::cout << "Insertion [1] = \"b\": "
        << tree.insert(1, "b") << std::endl;
    std::cout << "Insertion [123123] = \"example value\": "
        << tree.insert(123123, "example value") << std::endl;
    std::cout << "Insertion [80085] = \"pair\": "
        << tree.insert(80085, "pair") << std::endl;
    std::cout << std::endl;

    std::cout << "Insertion to a full tree [111] = \"will fail\": "
        << tree.insert(111, "will fail") << std::endl;
    std::cout << std::endl;

    std::cout << "Tree capacity: " << tree.capacity() << std::endl;
    std::cout << "Tree size: " << tree.size() << std::endl;
    std::cout << std::endl;

    std::cout << "Tree contains key 1: " << tree.contains_key(1) << std::endl;
    std::cout << "Tree contains key 0: " << tree.contains_key(0) << std::endl;
    std::cout << "Tree contains key 999: " << tree.contains_key(999) << std::endl;
    std::cout << std::endl;

    // std::cout << "Tree contains value \"b\": " << tree.contains_value("b") << std::endl;
    // std::cout << "Tree contains value \"will fail\": " << tree.contains_value("will fail") << std::endl;
    // std::cout << "Tree contains value \"doesn't exist\": " << tree.contains_value("doesn't exist") << std::endl;
    // std::cout << std::endl;

    std::cout << "Tree[1] = " << tree[1] << std::endl;

    // Remove
    std::cout << "Remove [1]: " << tree.remove(1) << std::endl;
    std::cout << std::endl;

    std::cout << "Tree capacity: " << tree.capacity() << std::endl;
    std::cout << "Tree size: " << tree.size() << std::endl;
    std::cout << std::endl;

    std::cout << "Tree contains key 1: " << tree.contains_key(1) << std::endl;

    return 0;
}
