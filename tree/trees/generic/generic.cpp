#include "generic.h"

template<class T, class K, size_t Size>
bool GenericTree::Node<T, K>::treeEquals(const BSTree::Node<T, K>* other) const {
    if (this == nullptr && other == nullptr)
        return true;
    if (this == nullptr || other == nullptr)
        return false;

    std::array<const Node*, SIZE> stack1;
    std::array<const Node*, SIZE> stack2;
    size_t stackSize1 = 0;
    size_t stackSize2 = 0;

    stack1[stackSize1] = this;
    stackSize1++;
    stack2[stackSize2] = other;
    stackSize2++;

    while (stackSize1 > 0 && stackSize2 > 0) {
        stackSize1--;
        const Node* node1 = stack1[stackSize1];
        stackSize2--;
        const Node* node2 = stack2[stackSize2];

        if (node1->key != node2->key || node1->value != node2->value
            || node1->height != node2->height)
            return false;

        if (node1->left != nullptr && node2->left != nullptr) {
            stackSize1++;
            stack1[stackSize1] = node1->left;
            stackSize2++;
            stack2[stackSize2] = node2->left;
        } else if (node1->left != nullptr || node2->left != nullptr)
            return false;

        if (node1->right != nullptr && node2->right != nullptr) {
            stack1[stackSize1++] = node1->right;
            stack2[stackSize2++] = node2->right;
        } else if (node1->right != nullptr || node2->right != nullptr)
            return false;
    }

    return stackSize1 == stackSize2;
}
