
// #include "..."

namespace lasd {

/* ************************************************************************** */

template <typename Data>
bool BinaryTree<Data>::Node::operator==(const Node& nod) const noexcept {
    if (Element != nod.Element)
        return false;
    
    if (isLeaf() && nod.IsLeaf())
        return true;
    
    else if (HasLeftChild() && HasRightChild())
        nod.HasLeftChild() && nod.HasRightChild() ?
         return LeftChild() == nod.LeftChild() && RightChild() == nod.RightChild() :
         return false;

    else if (HasLeftChild())
        nod.HasLeftChild() ?
         return LeftChild() == nod.LeftChild() :
         return false;

    else if (HasRightChild())
        nod.HasRightChild() ?
         return RightChild() == nod.RightChild() :
         return false;
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
    return Root() == tree.Root();
}

template <typename Data>
inline bool BinaryTree<Data>::operator!=(const BinaryTree& tree) const noexcept {
    return !(*this == tree);
}

template <typename Data>
void BinaryTree<Data>::MapPreOrder(const MapFunctor func, void* par) {
    MapPreOrder(func, par, Root());
}

template <typename Data>
void BinaryTree<Data>::MapPostOrder(const MapFunctor func, void* par) {
    MapPostOrder(func, par, Root());
}

template <typename Data>
void BinaryTree<Data>::FoldPreOrder(const FoldFunctor func, const void* par, void* acc) const {
    FoldPreOrder(func, par, Root());
}

template <typename Data>
void BinaryTree<Data>::FoldPostOrder(const FoldFunctor func, const void* par, void* acc) const {
    FoldPostOrder(func, par, Root());
}

template <typename Data>
void BinaryTree<Data>::MapInOrder(const MapFunctor func, void* par) {
    MapInOrder(func, par, Root());
}

template <typename Data>
void BinaryTree<Data>::FoldInOrder(const FoldFunctor func, const void* par, void* acc) const {
    FoldInOrder(func, par, acc, Root());
}

template <typename Data>
void BinaryTree<Data>::MapBreadth(const MapFunctor func, void* par) {
    MapBreadth(func, par, Root());
}

template <typename Data>
void BinaryTree<Data>::FoldBreadth(const FoldFunctor func, const void* par, void* acc) const {
    FoldBreadth(func, par, Root());
}

template <typename Data>
void BinaryTree<Data>::MapPreOrder(const MapFunctor func, void* par, Node* nod) {
    if (nod != nullptr)
    {
        func(nod->Element, par);
        if (!nod.IsLeaf())
        {
            if (nod.HasLeftChild() && nod.HasRightChild())
            {
                func(nod.LeftChild(), par);
                func(nod.RightChild(), par);
            }
            else if (nod.HasLeftChild())
                func(nod.LeftChild(), par);

            else if(nod.HasRightChild())
                func(nod.RightChild(), par);
        }          
    }
}

template <typename Data>
void BinaryTree<Data>::MapPostOrder(const MapFunctor func, void* par, Node* nod) {
    if (nod != nullptr)
    {
        if (!nod.IsLeaf())
        {
            if (nod.HasLeftChild() && nod.HasRightChild())
            {
                func(nod.LeftChild(), par);
                func(nod.RightChild(), par);
            }
            else if (nod.HasLeftChild())
                func(nod.LeftChild(), par);

            else if(nod.HasRightChild())
                func(nod.RightChild(), par);
        }
        func(nod->Element, par);
    }
}

template <typename Data>
void BinaryTree<Data>::FoldPreOrder(const FoldFunctor func, const void* par, void* acc, const Node* nod) const {
    if (nod != nullptr)
    {
        func(nod->Element, par, acc);
        if (!nod.IsLeaf())
        {
            if (nod.HasLeftChild() && nod.HasRightChild())
            {
                FoldPreOrder(func, par, acc, nod->LeftChild);
                FoldPreOrder(func, par, acc, nod->RightChild);
            }
            else if (nod.HasLeftChild())
                FoldPreOrder(func, par, acc, nod->LeftChild);

            else if(nod.HasRightChild())
                FoldPreOrder(func, par, acc, nod->RightChild);
        }   
    }
}

template <typename Data>
void BinaryTree<Data>::FoldPostOrder(const FoldFunctor func, const void* par, void* acc, const Node* nod) const {
    if (nod != nullptr)
    {
        if (!nod.IsLeaf())
        {
            if (nod.HasLeftChild() && nod.HasRightChild())
            {
                FoldPostOrder(func, par, acc, nod->LeftChild);
                FoldPostOrder(func, par, acc, nod->RightChild);
            }
            else if (nod.HasLeftChild())
                FoldPostOrder(func, par, acc, nod->LeftChild);

            else if(nod.HasRightChild())
                 FoldPostOrder(func, par, acc, nod->RightChild);
        }
        func(nod->Element, par, acc);
    }
}

template <typename Data>
void BinaryTree<Data>::MapInOrder(const MapFunctor func, void* par) {
    if (nod != nullptr)
    {
        
    }
}

/* ************************************************************************** */

}
