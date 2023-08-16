#ifndef TREE_REDBLACK_H
#define TREE_REDBLACK_H

#include "tree.h"

#include <array>
#include <bitset>


namespace Tree {

// Implementations should inherit from `Node` class.
// They must implement the following functions:
// - Default constructor. `Tree`s may allocate `std::array`s of nodes on creation.
// - Move assignment operators.
// - Equality operator. Only compares the node's key and value.
// - `K& _key()`
// - `const K& _key() const`
// - `T& _value()`
// - `const T& _value() const`

template<class T, class K>
class RedBlackNode : public Node<T, K, RedBlackNode<T, K>> {
    using NodeType = RedBlackNode;

    K key{};
    T value{};

    Node<T, K, NodeType>* left = nullptr;
    Node<T, K, NodeType>* right = nullptr;

    // First bit (LSB) is red (1) or black (0)
    // Second bit is exist (1) or not (0)
    std::bitset<2> bits{};

public:

    // Constructors
    RedBlackNode() = default;
    RedBlackNode(const K&& key, const T&& value, bool red = true) : key(key), value(value) {
        bits[0] = red;
        bits[1] = true;
    }

    bool operator==(const NodeType& other) const {
        return key == other.key && value == other.value;
    }

    // Assignment operators
    NodeType& operator=(NodeType&& other) = default;
};


 // Implementations should inherit from `Tree` class.
// They must implement the following functions:
// - Copy and move assignment operators.
// - `Node<T, K, NodeType>* _get(const K& key) const`
// - `bool _insert(const K&& key, const T&& value)`
// - `bool _remove(const K& key)`
// - `size_t _size() const`
// - `void _clear()`

template<class T, class K, size_t Size>
class RedBlackTree : public Tree<T, K, Size, RedBlackTree<T, K, Size>> {
public:
    using TreeType = RedBlackTree;
    using NodeType = RedBlackNode<T, K>;

    // Constructors
    RedBlackTree() = default;
    RedBlackTree(const RedBlackTree& other) = default;
    RedBlackTree(RedBlackTree&& other) = default;

    // Assignment operators
    RedBlackTree& operator=(const RedBlackTree& other) = default;
    RedBlackTree& operator=(RedBlackTree&& other) = default;

    // Destructor
    ~RedBlackTree() = default;

private:
    // The array of nodes.
    std::array<Node<T, K, NodeType>, Size> nodes{};
    // Root node of the tree.
    Node<T, K, NodeType>* root = nullptr;
    // Count of nodes in the tree.
    size_t count = 0;


    // RedBlack balancing functions
    void rotateLeft(Node<T, K, NodeType>* node);
    void rotateRight(Node<T, K, NodeType>* node);
    void balance(Node<T, K, NodeType>* node);
    void fixDoubleBlack(Node<T, K, NodeType>* node);

protected:
    Node<T, K, NodeType>* _get(const K& key) const;

    bool _insert(const K&& key, const T&& value);

    bool _remove(const K& key);

    size_t _size() const {
        return count;
    }

    void _clear();
};

}  // namespace Tree


#endif // TREE_REDBLACK_H
