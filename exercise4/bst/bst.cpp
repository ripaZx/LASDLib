
namespace lasd {

/* ************************************************************************** */

template <typename Data>
BST<Data>::BST(const LinearContainer<Data>& con) {

}

template <typename Data>
BST<Data>::BST(const BST<Data>& bst) : BinaryTreeLnk<Data>::BinaryTreeLnk(bst) { }

template <typename Data>
BST<Data>::BST(BST<Data>&& bst) noexcept : BinaryTreeLnk<Data>::BinaryTreeLnk(std::move(bst)) { }

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
        BTInOrderIterator<Data> itr(*this);
        BTInOrderIterator<Data> bstItr(bst);
        while (!itr.Terminated() && !bstItr.Terminated())
        {
            if (*itr != *bstItr)
                return false;
        }
        return true;
    }
    return false;
}

template <typename Data>
inline bool BST<Data>::operator!=(const BST<Data>& bst) const noexcept {
    return !(*this == bst);
}


template <typename Data>
void BST<Data>::Insert(const Data& dat) noexcept {
    Node*& nod = FindPointerTo(root, dat);
    if (nod == nullptr)
    {
        nod = new Node(dat);
        size++
    }
}

template <typename Data>
void BST<Data>::Insert(Data&& dat) noexcept {
    Node*& nod = FindPointerTo(root, dat);
    if (nod == nullptr)
    {
        nod = new Node(std::move(dat));
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
    Node* const* ptr = FindPointerToPredecessor(root, dat);
    if (ptr != nullptr)
        return (*ptr)->Elem;
    
    else
        throw std::length_error("Access to a non existent node.");
}

template <typename Data>
Data BST<Data>::PredecessorNRemove(const Data& dat) {
    Node** ptr = FindPointerToPredecessor(root, dat);
    if (ptr != nullptr)
        return DataNDelete(Detach(*ptr));
    else
        throw std::length_error("Access to a non existent node.");
}

template <typename Data>
void BST<Data>::RemovePredecessor(const Data& dat) {
    Node** ptr = FindPointerToPredecessor(root, dat);
    if (ptr != nullptr)
        delete Detach(*ptr);
    else
        throw std::length_error("Access to a non existent node.");
}

template <typename Data>
const Data& BST<Data>::Successor(const Data& dat) const {
    Node* const* ptr = FindPointerToSuccessor(root, dat);
    if (ptr != nullptr)
        return (*ptr)->Elem;

    else
        throw std::length_error("Access to a non existent node.");
}

template <typename Data>
Data BST<Data>::SuccessorNRemove(const Data& dat) {
    Node** ptr = FindPointerToSuccessor(root, dat);
    if (ptr != nullptr)
        return DataNDelete(Detach(*ptr));
    else
        throw std::length_error("Access to a non existent node.")
}

template <typename Data>
void BST<Data>::RemoveSuccessor(const Data& dat) {
    Node** ptr = FindPointerToSuccessor(root, dat);
    if (ptr != nullptr)
        delete Detach(*ptr);
    else
        throw std::length_error("Access to a non existent node.");
}

template <typename Data>
bool BST<Data>::Exists(const Data& dat) const noexcept {
    return (FindPointerTo(root, dat) != nullptr);
}

template <typename Data>
Data BST<Data>::DataNDelete(Node* nod) {
    Data dat = std::move(nod->Elem);
    delete nod;
    return dat;
}

template <typename Data>
BST<Data>::Node* BST<Data>::Detach(Node*& nod) noexcept {
    if (nod != nullptr)
    {
        if (nod->left == nullptr)
            return SkipOnRight(nod);
        
        else if (nod->right == nullptr)
            return SkipOnLeft(nod);
        
        else
        {
            Node* max = DetachMax(nod->left);
            std::swap(nod->Elem, max->Elem);
            return max;
        }
    }
}

template <typename Data>
BST<Data>::Node* BST<Data>::DetachMin(Node*& nod) noexcept {
    return SkipOnRight(FindPointerToMin(nod));
}

template <typename Data>
BST<Data>::Node* BST<Data>::DetachMax(Node*& nod) noexcept {
    return SkipOnLeft(FindPointerToMax(nod));
}

template <typename Data>
BST<Data>::Node* BST<Data>::SkipOnLeft(Node*& nod) noexcept {
    Node* lef = nullptr;
    if (nod != nullptr)
    {
        std::swap(lef, nod->left);
        std::swap(lef, nod);
        --size;
    }
    return lef;
}

template <typename Data>
BST<Data>::Node* BST<Data>::SkipOnRight(Node*& nod) noexcept {
    Node* rig = nullptr;
    if (nod != nullptr)
    {
        std::swap(rig, nod->right);
        std::swap(rig, nod);
        --size;
    }
    return rig;
}

template <typename Data>
BST<Data>::Node*& BST<Data>::FindPointerToMin(Node*& nod) noexcept {
    return const_cast<Node*&>(static_cast<const BST<Data> *>(*this)->FindPointerToMin(nod));
}

template <typename Data>
BST<Data>::Node* const& BST<Data>::FindPointerToMin(Node* const& nod) const noexcept {
    Node* const& ptr = &nod;
    Node* current = nod;
    if (current != nullptr)
    {
        while (current->left != nullptr)
        {
            ptr = &current->left;
            current = current->left;
        }
    }
}

template <typename Data>
BST<Data>::Node*& BST<Data>::FindPointerToMax(Node*& nod) noexcept {
    return const_cast<Node*&>(static_cast<const BST<Data> *>(*this)->FindPointerToMax(nod));
}

template <typename Data>
BST<Data>::Node* const& BST<Data>::FindPointerToMax(Node* const& nod) const noexcept {
    Node* const& ptr = &nod;
    Node* current = nod;
    if (current != nullptr)
    {
        while (current->right != nullptr)
        {
            ptr = &current->right;
            current = current->right;
        }
    }
}

/* ************************************************************************** */

}
