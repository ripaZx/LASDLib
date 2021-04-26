
// #include "..."

namespace lasd {

/* ************************************************************************** */

template <typename Data>
bool BinaryTree<Data>::Node::operator==(const Node& nod) const noexcept {
    // if (IsLeaf() && nod.IsLeaf())
    //     return Element == nod.Element;
    // else if (HasLeftChild() && nod.HasLeftChild())
    //     left == nod.left;
    // else if (HasRightChild() && nod.HasRightChild())
    //     right == nod.right;
}

template <typename Data>
inline bool BinaryTree<Data>::Node::operator!=(const Node& nod) const noexcept {
    return !(*this == nod);
}


template <typename Data>
bool BinaryTree<Data>::Node::IsLeaf() const noexcept {
    return !(HasRightChild() || HasLeftChild());
}

/* ************************************************************************** */

template <typename Data>
bool BinaryTree<Data>::operator==(const BinaryTree& tree) const noexcept {

}

template <typename Data>
inline bool BinaryTree<Data>::operator!=(const BinaryTree& tree) const noexcept {
    return !(*this == tree);
}

/* ************************************************************************** */

}
