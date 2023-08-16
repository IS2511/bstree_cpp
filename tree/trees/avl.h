#ifndef TREE_AVL_H
#define TREE_AVL_H

#include "tree.h"

#include <array>


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
class AVLNode : public Node<T, K, AVLNode<T, K>> {
    using NodeType = AVLNode;

    K key{};
    T value{};

    Node<T, K, NodeType>* left = nullptr;
    Node<T, K, NodeType>* right = nullptr;

    // Height of the subtree with this node as root.
    // 1 means leaf. 0 means doesn't exist.
    size_t height = 0;

public:

    // Constructors
    AVLNode() = default;
    AVLNode(const K&& key, const T&& value, size_t height) :
        key(std::move(key)), value(std::move(value)), height(height)
    {};

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
class AVLTree : public Tree<T, K, Size, AVLTree<T, K, Size>> {
public:
    using TreeType = AVLTree;
    using NodeType = AVLNode<T, K>;

    // Constructors
    AVLTree() = default;
    // AVLTree(const AVLTree& other) = default;
    // AVLTree(AVLTree&& other) = default;

    // Assignment operators
    AVLTree& operator=(const AVLTree& other) = default;
    AVLTree& operator=(AVLTree&& other) = default;

    // Destructor
    ~AVLTree() = default;

private:
    // The array of nodes.
    std::array<NodeType, Size> nodes{};
    // Root node of the tree.
    NodeType* root = nullptr;
    // Count of nodes in the tree.
    size_t count = 0;


    // AVL balancing functions
    void rotateLeft(NodeType* node);
    void rotateRight(NodeType* node);
    void rotateLeftRight(NodeType* node);
    void rotateRightLeft(NodeType* node);
    void balance(NodeType* node);

public:
    Node<T, K, NodeType>* _get(const K& key) const;

    bool _insert(const K&& key, const T&& value);

    bool _remove(const K& key);

    size_t _size() const {
        return count;
    }

    void _clear();
};

}  // namespace Tree

#endif // TREE_AVL_H
