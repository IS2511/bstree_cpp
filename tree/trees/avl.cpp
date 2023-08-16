#include "avl.h"

#include <stdexcept>


namespace Tree {

template <class T, class K, size_t Size>
Node<T, K, typename AVLTree<T, K, Size>::NodeType>* AVLTree<T, K, Size>::_get(const K& key) const {
    auto* current = root;

    while (current != nullptr)
        if (key < current->key)
            current = current->left;
        else if (key > current->key)
            current = current->right;
        else
            return current;

    return nullptr;
}


template <class T, class K, size_t Size>
void rotateLeft(AVLNode<T, K>* node) {
    auto* right = node->right;
    node->right = right->left;
    right->left = node;
    node->height = std::max(node->left->height, node->right->height) + 1;
    right->height = std::max(right->left->height, right->right->height) + 1;
    node = right;
}

template <class T, class K, size_t Size>
void rotateRight(AVLNode<T, K>* node) {
    auto* left = node->left;
    node->left = left->right;
    left->right = node;
    node->height = std::max(node->left->height, node->right->height) + 1;
    left->height = std::max(left->left->height, left->right->height) + 1;
    node = left;
}

template <class T, class K, size_t Size>
void rotateLeftRight(AVLNode<T, K>* node) {
    rotateLeft(node->left);
    rotateRight(node);
}

template <class T, class K, size_t Size>
void rotateRightLeft(AVLNode<T, K>* node) {
    rotateRight(node->right);
    rotateLeft(node);
}

template <class T, class K, size_t Size>
void balance(AVLNode<T, K>* node) {
    // Height 1 means leafs
    // Height 0 means node doesn't exist

    if (node->left->height - node->right->height == 2) {
        if (node->left->left->height > node->left->right->height)
            rotateRight(node);
        else
            rotateLeftRight(node);
    } else if (node->right->height - node->left->height == 2) {
        if (node->right->right->height > node->right->left->height)
            rotateLeft(node);
        else
            rotateRightLeft(node);
    }
}


template <class T, class K, size_t Size>
bool AVLTree<T, K, Size>::_insert(const K&& key, const T&& value) {
    if (count == Size)
        return false;

    if (root == nullptr) {
        nodes[0] = Node<T, K, NodeType>(std::move(key), std::move(value));
        root = &nodes[0];
        count++;
        return true;
    }
    
    // Height 1 means leafs
    // Height 0 means node doesn't exist
    // All nodes in array are initialized with height 0 on tree creation
    // Don't allocate memory for new node, use array instead
    // Find an empty node in the array and replace it with a new one
    
    // First, find a place in the tree for a new node
    auto* current = root;
    auto* parrent = root;
    while (current != nullptr) {
        parrent = current;
        if (key < current->key)
            current = current->left;
        else
            current = current->right;
    }

    // Check if key already exists
    if (parrent->key == key)
        throw std::invalid_argument("Key already exists");

    // Second, find a place in the array to store a new node
    auto* node = &nodes[0];
    while (node->height != 0)
        node++;

    // Third, insert a new node
    *node = NodeType(std::move(key), std::move(value), 1);

    count++;
    return true;
}

template <class T, class K, size_t Size>
bool AVLTree<T, K, Size>::_remove(const K& key) {
    // Height 1 means leafs
    // Height 0 means node doesn't exist
    // All nodes in array are initialized with height 0 on tree creation
    // To delete a node in the array, just set its height
    // But first delete it from the tree

    // First, find the node to delete
    auto* current = root;
    auto* parrent = root;
    while (current != nullptr) {
        if (key < current->key) {
            parrent = current;
            current = current->left;
        } else if (key > current->key) {
            parrent = current;
            current = current->right;
        } else
            break;
    }

    // Check if key exists
    if (current == nullptr)
        return false;

    // Second, delete the node from the tree
    if (current->left == nullptr && current->right == nullptr) {
        // Node is a leaf
        if (current == root) {
            // Node is root
            root = nullptr;
        } else if (parrent->left == current) {
            // Node is left child
            parrent->left = nullptr;
        } else {
            // Node is right child
            parrent->right = nullptr;
        }
    } else if (current->left == nullptr) {
        // Node has only right child
        if (current == root) {
            // Node is root
            root = current->right;
        } else if (parrent->left == current) {
            // Node is left child
            parrent->left = current->right;
        } else {
            // Node is right child
            parrent->right = current->right;
        }
    } else if (current->right == nullptr) {
        // Node has only left child
        if (current == root) {
            // Node is root
            root = current->left;
        } else if (parrent->left == current) {
            // Node is left child
            parrent->left = current->left;
        } else {
            // Node is right child
            parrent->right = current->left;
        }
    } else {
        // Node has both children
        // Find the smallest node in the right subtree
        auto* smallest = current->right;
        auto* smallestParrent = current;
        while (smallest->left != nullptr) {
            smallestParrent = smallest;
            smallest = smallest->left;
        }

        // Replace the node with the smallest node
        if (current == root) {
            // Node is root
            root = smallest;
        } else if (parrent->left == current) {
            // Node is left child
            parrent->left = smallest;
        } else {
            // Node is right child
            parrent->right = smallest;
        }

        // Replace the smallest node with its right child
        if (smallestParrent->left == smallest) {
            // Smallest node is left child
            smallestParrent->left = smallest->right;
        } else {
            // Smallest node is right child
            smallestParrent->right = smallest->right;
        }

        // Replace the smallest
        smallest->left = current->left;
        smallest->right = current->right;

        // Balance the tree
        balance(smallest);
    }


    // Third, delete the node from the array
    current->height = 0;

    count--;
    return true;
}


}  // namespace Tree
