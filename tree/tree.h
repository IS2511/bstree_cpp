#ifndef TREE_H
#define TREE_H

#include <cstddef>
#include <cstdint>
#include <utility>

namespace Tree {
    // enum class TreeType : uint8_t {
    //     // Faster lookup, slower insertion and deletion compared to red-black.
    //     AVL = 0,
    //     // Faster insertion, slower lookup compared to AVL.
    //     RedBlack = 1
    // };


    // Node interface
    //
    // Implementations should inherit from this class.
    // They must implement the following functions:
    // - Default constructor. `Tree`s may allocate `std::array`s of nodes on creation.
    // - Move assignment operator.
    // - `K& _key()`
    // - `const K& _key() const`
    // - `T& _value()`
    // - `const T& _value() const`
    template <class T, class K, class NodeType>
    struct Node {
        using ValueType = T;
        using KeyType = K;

        // Require the derived implementation NodeType have a default constructor. (not sure it actually does)
        Node() = default;

        // Move constructor
        Node(Node&& other) {
            static_cast<NodeType*>(this)->operator=(std::move(static_cast<NodeType&>(other)));
        }

        // Move assignment operator
        Node& operator=(Node&& other) {
            static_cast<NodeType*>(this)->operator=(std::move(static_cast<NodeType&>(other)));
        }

        // Equality operator
        bool operator==(const Node& other) const {
            return key() == other.key() && value() == other.value();
        }
    
    protected:
        // Key getters (used for setting too)
        K& key() {
            return static_cast<NodeType*>(this)->_key();
        }
        const K& key() const {
            return static_cast<const NodeType*>(this)->_key();
        }

        // Value getters (used for setting too)
        T& value() {
            return static_cast<NodeType*>(this)->_value();
        }
        const T& value() const {
            return static_cast<const NodeType*>(this)->_value();
        }
    };


    // Tree interface
    // Self-balancing Binary Search Tree.
    // Each node has a value of type `T`. Keys are of type `K`.
    // Doesn't use dynamic memory allocation (uses std::array).
    // `K` has to be comparable (`operator<`, `operator==`).
    // `K` and `T` have to be moveable (have a move assignment operator).
    // TreeType is the type of the tree (AVL, RedBlack, etc.).
    // See `trees/avl/avl.h` for an example.
    // 
    // Implementations should inherit from this class.
    // They must implement the following functions:
    // - Copy and move assignment operators.
    // - `Node<T, K, NodeType>* _get(const K& key) const`
    // - `bool _insert(const K&& key, const T&& value)`
    // - `bool _remove(const K& key)`
    // - `size_t _size() const`
    // - `void _clear()`
    template <class T, class K, size_t Size, class TreeType>
    class Tree {

    protected:

        using ValueType = T;
        using KeyType = K;
        // using NodeType = typename TreeType<T, K, Size>::NodeType;

        // Internal get
        /// @returns `nullptr` if key doesn't exist
        // Node<T, K, NodeType>* _get(const K& key) const {
        //     return static_cast<TreeType*>(this)._get(key);
        // }

        // Internal insert
        /// @returns `true` if successful, `false` if tree is full
        /// @note Assumes key doesn't exist in the tree.
        // bool _insert(const K&& key, const T&& value) {
        //     return static_cast<TreeType*>(this)._insert(std::move(key), std::move(value));
        // }

        // Internal remove
        /// @returns `true` if successful, `false` if key doesn't exist
        // bool _remove(const K& key) {
        //     return static_cast<TreeType*>(this)._remove(key);
        // }

        // Internal size
        // Counts the number of nodes in the tree.
        // size_t _size() const {
        //     return static_cast<const TreeType*>(this)._size();
        // }

        // Recursively compare node trees (don't actually use recursion, please)
        // TODO: How should this work?
        //   Ideally, two HashMaps are created to compare the trees only by keys and values.
        //   This should eventually become a mandatory to implement function.
        // static bool compareNodeTrees(const Node<T, K, NodeType>* a, const Node<T, K, NodeType>* b) {
        //     return TreeType::compareNodeTrees(a, b);
        // };

    public:

        // Constructors
        Tree() = default;

        // Destructor
        ~Tree() = default;

        // Copy and move constructors
        Tree(const Tree& other) {
            static_cast<TreeType*>(this) = static_cast<const TreeType&>(other);
        }
        Tree(Tree&& other) {
            static_cast<TreeType*>(this) = std::move(static_cast<TreeType&>(other));
        }

        // Copy and move assignment operators
        Tree& operator=(const Tree& other) {
            static_cast<TreeType*>(this) = static_cast<const TreeType&>(other);
        }
        Tree& operator=(Tree&& other) {
            static_cast<TreeType*>(this) = std::move(static_cast<TreeType&>(other));
        }

        // Equality operators
        // bool operator==(const Tree& other) const {
        //     return TreeType::compareNodeTrees(
        //         static_cast<TreeType*>(this)._root(),
        //         static_cast<const TreeType&>(other)._root());
        // }

        // Index operators
        /// @throws std::out_of_range if key doesn't exist
        T& operator[](const K& key) {
            return get(key);
        }
        /// @throws std::out_of_range if key doesn't exist
        const T& operator[](const K& key) const {
            return get(key);
        }


        size_t capacity() const {
            return Size;
        }
        size_t size() const {
            return static_cast<const TreeType*>(this)->_size();
        }

        bool is_empty() const {
            return static_cast<const TreeType*>(this)->_size() == 0;
        }
        bool is_full() const {
            return static_cast<const TreeType*>(this)->_size() == Size;
        }


        // Contains
        /*[[nodiscard]]*/ bool contains_key(const K& key) const {
            return static_cast<const TreeType*>(this)->_get(key) != nullptr;
        }
        // /*[[nodiscard]]*/ bool contains_value(const T& value) const {
        //     // TODO: Implement
        // }

        // Get
        /// @throws std::out_of_range if key doesn't exist
        /*[[nodiscard]]*/ T& get(const K& key);
        /// @throws std::out_of_range if key doesn't exist
        /*[[nodiscard]]*/ const T& get(const K& key) const;

        // Try get
        // std::optional is C++17 and I don't want to have dependencies :(
        /// @p result is set to the value of the key if it exists.
        /// @returns true if the key exists in the tree, false otherwise.
        /*[[nodiscard]]*/ bool try_get(const K& key, T& result) const;

        // Insert
        /// @returns true if the key was inserted, false otherwise (tree full).
        /*[[nodiscard]]*/ bool insert(const K&& key, const T&& value) {
            return static_cast<TreeType*>(this)->_insert(std::move(key), std::move(value));
        }

        // Set
        /// @returns true if the key was set, false otherwise (key doesn't exist).
        /*[[nodiscard]]*/ bool set(const K& key, const T&& value);

        // Remove
        /// @returns true if the key was removed, false otherwise (key doesn't exist).
        bool remove(const K& key) {
            return static_cast<TreeType*>(this)->_remove(key);
        }

        // Clear
        void clear() {
            static_cast<TreeType*>(this)->_clear();
        }
    };
} // namespace Tree

#endif // TREE_H
