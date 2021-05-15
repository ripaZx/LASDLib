#include <iostream>
namespace lasd {

/* ************************************************************************** */

template <typename Data>
BST<Data>::BST(const LinearContainer<Data>& con) {
    for (unsigned long i=0; i<con.Size(); i++)
        Insert(con[i]);
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
        while (!itr.Terminated())
        {
            if (*itr != *bstItr)
                return false;

            ++itr;
            ++bstItr;
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
    NodeLnk*& nod = FindPointerTo(root, dat);
    if (nod == nullptr)
    {
        nod = new NodeLnk(dat);
        size++;
    }
}

template <typename Data>
void BST<Data>::Insert(Data&& dat) noexcept {
    NodeLnk*& nod = FindPointerTo(root, dat);
    if (nod == nullptr)
    {
        nod = new NodeLnk(std::move(dat));
        size++;
    }
}

template <typename Data>
void BST<Data>::Remove(const Data& dat) noexcept {
    delete Detach(FindPointerTo(root, dat));
}

template <typename Data>
const Data& BST<Data>::Min() const {
    if (root != nullptr)
        return FindPointerToMin(root)->Elem;
    
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
    NodeLnk* const& ptr = FindPointerToPredecessor(root, dat);
    if (ptr != nullptr)
        return ptr->Elem;
    
    else
        throw std::length_error("Access to a non existent NodeLnk.");
}

template <typename Data>
Data BST<Data>::PredecessorNRemove(const Data& dat) {
    NodeLnk*& ptr = FindPointerToPredecessor(root, dat);
    if (ptr != nullptr)
        return DataNDelete(Detach(ptr));
    else
        throw std::length_error("Access to a non existent NodeLnk.");
}

template <typename Data>
void BST<Data>::RemovePredecessor(const Data& dat) {
    NodeLnk*& ptr = FindPointerToPredecessor(root, dat);
    if (ptr != nullptr)
        delete Detach(ptr);
    else
        throw std::length_error("Access to a non existent NodeLnk.");
}

template <typename Data>
const Data& BST<Data>::Successor(const Data& dat) const {
    NodeLnk* const& ptr = FindPointerToSuccessor(root, dat);
    if (ptr != nullptr)
        return ptr->Elem;

    else
        throw std::length_error("Access to a non existent NodeLnk.");
}

template <typename Data>
Data BST<Data>::SuccessorNRemove(const Data& dat) {
    NodeLnk*& ptr = FindPointerToSuccessor(root, dat);
    if (ptr != nullptr)
        return DataNDelete(Detach(ptr));
    else
        throw std::length_error("Access to a non existent NodeLnk.");
}

template <typename Data>
void BST<Data>::RemoveSuccessor(const Data& dat) {
    NodeLnk*& ptr = FindPointerToSuccessor(root, dat);
    if (ptr != nullptr)
        delete Detach(ptr);
    else
        throw std::length_error("Access to a non existent NodeLnk.");
}

template <typename Data>
bool BST<Data>::Exists(const Data& dat) const noexcept {
    return (FindPointerTo(root, dat) != nullptr);
}

template <typename Data>
Data BST<Data>::DataNDelete(NodeLnk* nod) {
    Data dat = std::move(nod->Elem);
    delete nod;
    return dat;
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Detach(NodeLnk*& nod) noexcept {
    if (nod != nullptr)
    {
        if (nod->left == nullptr)
            return SkipOnRight(nod);
        
        else if (nod->right == nullptr)
            return SkipOnLeft(nod);
        
        else
        {
            NodeLnk* max = DetachMax(nod->left);
            std::swap(nod->Elem, max->Elem);
            return max;
        }
    }
    return nullptr;
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMin(NodeLnk*& nod) noexcept {
    return SkipOnRight(FindPointerToMin(nod));
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMax(NodeLnk*& nod) noexcept {
    return SkipOnLeft(FindPointerToMax(nod));
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::SkipOnLeft(NodeLnk*& nod) noexcept {
    NodeLnk* tmp = nullptr;
    if (nod != nullptr)
    {
        std::swap(tmp, nod->left);
        std::swap(tmp, nod);
        --size;
    }
    return tmp;
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::SkipOnRight(NodeLnk*& nod) noexcept {
    NodeLnk* tmp = nullptr;
    if (nod != nullptr)
    {
        std::swap(tmp, nod->right);
        std::swap(tmp, nod);
        --size;
    }
    return tmp;
}

template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMin(NodeLnk*& nod) noexcept {
    return const_cast<NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerToMin(nod));
}

template <typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMin(NodeLnk* const& nod) const noexcept {
    NodeLnk* const* ptr = &nod;
    NodeLnk* current = nod;
    if (current != nullptr)
    {
        while (current->left != nullptr)
        {
            ptr = &current->left;
            current = current->left;
        }
    }
    return *ptr;
}

template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMax(NodeLnk*& nod) noexcept {
    return const_cast<NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerToMax(nod));
}

template <typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMax(NodeLnk* const& nod) const noexcept {
    NodeLnk* const* ptr = &nod;
    NodeLnk* current = nod;
    if (current != nullptr)
    {
        while (current->right != nullptr)
        {
            ptr = &current->right;
            current = current->right;
        }
    }
    return *ptr;
}

template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerTo(NodeLnk*& nod, const Data& dat) noexcept {
    return const_cast<NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerTo(nod, dat));
}

template <typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerTo(NodeLnk* const& nod, const Data& dat) const noexcept {
    NodeLnk* const* ptr = &nod;
    NodeLnk* current = nod;
    while (current != nullptr)
    {
        if (current->Elem > dat)
        {
            ptr = &current->left;
            current = current->left;
        }
        else if (current->Elem < dat)
        {
            ptr = &current->right;
            current = current->right;
        }
        else
            return *ptr;
    }
    return *ptr;
}

template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToPredecessor(NodeLnk*& nod, const Data& dat) noexcept {
    return const_cast<NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerToPredecessor(nod, dat));
}

template <typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToPredecessor(NodeLnk* const& nod, const Data& dat) const noexcept {
    NodeLnk* const* pre = nullptr;
    NodeLnk* current = nod;
    while (current != nullptr)
    {
        if (current->Elem < dat)
        {
            pre = &current;
            if (current->HasRightChild())
                current = current->right;
            else
                return *pre;
        }
        else
        {
            if (current->HasLeftChild())
            {
                if (current->Elem > dat)
                    current = current->left;

                else
                {
                    pre = &FindPointerToMax(current->left);
                    return *pre;
                }
            }
            else
                return *pre;
            
        }
    }
    return *pre;
}

template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToSuccessor(NodeLnk*& nod, const Data& dat) noexcept {
    return const_cast<NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerToSuccessor(nod, dat));
}

template <typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToSuccessor(NodeLnk* const& nod, const Data& dat) const noexcept {
    NodeLnk* const* suc = nullptr;
    NodeLnk* current = nod;
    while (current != nullptr)
    {
        if (current->Elem > dat)
        {
            suc = &current;
            current = current->left;
        }
        else if (current->Elem < dat)
            current = current->right;

        else
        {
            if (current->right == nullptr)
                return *suc;
            
            else
            {
                suc = &FindPointerToMin(current->right);
                return *suc;
            }
        }
    }
    return *suc;
}

/* ************************************************************************** */

}
