
namespace lasd {

/* ************************************************************************** */

template <typename Data>
BST<Data>::BST(const LinearContainer<Data>& con) {

}

template <typename Data>
BST<Data>::BST(const BST<Data>& bst) {

}

template <typename Data>
BST<Data>::BST(BST<Data>&& bst) noexcept {
    
}

template <typename Data>
BST<Data>& BST<Data>::operator=(const BST<Data>& bst) {
    if (*this != bst)
        BinaryTreeLnk<Data>::operator=(bst);
    return *this;
}

template <typename Data>
BST<Data>& BST<Data>::operator=(BST<Data>&& bst) noexcept {
    if (*this != bst)
        BinaryTreeLnk<Data>::operator=(std::move(bst));
    return *this;
}

template <typename Data>
bool BST<Data>::operator==(const BST<Data>& bst) const noexcept {
    if (size == bst.size)
    {

    }
}

template <typename Data>
inline bool BST<Data>::operator!=(const BST<Data>& bst) const noexcept {
    return !(*this == bst);
}


template <typename Data>
void BST<Data>::Insert(const Data& dat) noexcept {
    NodeLnk*& nod = FindPointerTo(root, dat);
    if (nod == nullptr)
    {
        nod = new NodeLnk(dat);
        size++
    }
}

template <typename Data>
void BST<Data>::Insert(Data&& dat) noexcept {
    NodeLnk*& nod = FindPointerTo(root, dat);
    if (nod == nullptr)
    {
        nod = new NodeLnk(std::move(dat));
        size++
    }
}

template <typename Data>
void BST<Data>::Remove(const Data& dat) noexcept {
    delete Detach(FindPointerTo(root, dat));
}

template <typename Data>
const Data& BST<Data>::Min() const {
    if (root != nullptr)
        return FindPointerTo(root)->Elem;
    
    else
        throw std::length_error("Access to an empty tree.");
}

template <typename Data>
Data BST<Data>::MinNRemove() {
    if (root != nullptr)
        return DataNDelete(DetachMin(root));

    else
        throw std::length_error("Access to an empty tree.");
}

template <typename Data>
void BST<Data>::RemoveMin() {
    if (root != nullptr)
        delete DetachMin(root);
    
    else
        throw std::length_error("Access to an empty tree.");
}

template <typename Data>
const Data& BST<Data>::Max() const {
    if (root != nullptr)
        return FindPointerToMax(root)->Elem;
    
    else
        throw std::length_error("Access to an empty tree.");
}

template <typename Data>
Data BST<Data>::MaxNRemove() {
    if (root != nullptr)
        return DataNDelete(DetachMax(root));

    else
        throw std::length_error("Access to an empty tree.");
}

template <typename Data>
void BST<Data>::RemoveMax() {
    if (root != nullptr)
        delete DetachMax(root);

    else
        throw std::length_error("Access to an empty tree.");
}

template <typename Data>
const Data& BST<Data>::Predecessor(const Data& dat) const {

}

template <typename Data>
Data BST<Data>::PredecessorNRemove(const Data& dat) {

}

template <typename Data>
void BST<Data>::RemovePredecessor(const Data& dat) {

}

template <typename Data>
const Data& BST<Data>::Successor(const Data& dat) const {

}

template <typename Data>
Data BST<Data>::SuccessorNRemove(const Data& dat) {

}

template <typename Data>
void BST<Data>::RemoveSuccessor(const Data& dat) {

}

template <typename Data>
bool BST<Data>::Exists(const Data& dat) const noexcept {
    return (FindPointerTo(root, dat) != nullptr);
}


/* ************************************************************************** */

}
