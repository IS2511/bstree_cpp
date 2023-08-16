#include "tree.h"

#include <stdexcept>


namespace Tree {


template <class T, class K, size_t Size, class TreeType>
T& Tree<T, K, Size, TreeType>::get(const K& key) {
    auto* node = _get(key);

    if (node == nullptr)
        throw std::out_of_range("Key doesn't exist in tree");

    return node->value;
}

template <class T, class K, size_t Size, class TreeType>
const T& Tree<T, K, Size, TreeType>::get(const K& key) const {
    const auto* node = _get(key);

    if (node == nullptr)
        throw std::out_of_range("Key doesn't exist in tree");

    return node->value;
}


template <class T, class K, size_t Size, class TreeType>
bool Tree<T, K, Size, TreeType>::try_get(const K& key, T& result) const {
    const auto* node = _get(key);

    if (node == nullptr)
        return false;

    result = node->value;
    return true;
}

// Set
template <class T, class K, size_t Size, class TreeType>
bool Tree<T, K, Size, TreeType>::set(const K& key, const T&& value) {
    auto* node = static_cast<TreeType*>(this)->_get(key);

    if (node == nullptr)
        return false;
    
    node->value = std::move(value);
    return true;
}


} // namespace Tree
