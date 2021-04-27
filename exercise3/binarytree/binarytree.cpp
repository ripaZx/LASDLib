
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
    QueueLst<Node> que = new QueueLst<Node>();
    que.Enqueue(Root());
    MapBreadth(func, par, que);
}

template <typename Data>
void BinaryTree<Data>::FoldBreadth(const FoldFunctor func, const void* par, void* acc) const {
    QueueLst<Node> que = new QueueLst<Node>();
    que.Enqueue(Root());
    FoldBreadth(func, par, acc, que);
}

template <typename Data>
void BinaryTree<Data>::MapPreOrder(const MapFunctor func, void* par, Node* nod) {
    if (nod != nullptr)
    {
        func(nod->Element, par);
        if (!nod->IsLeaf())
        {
            if (nod->HasLeftChild() && nod->HasRightChild())
            {
                MapPreOrder(func, par, nod->LeftChild();
                MapPreOrder(func, par, nod->RightChild());
            }
            else if (nod->HasLeftChild())
                MapPreOrder(func, par, nod->LeftChild());

            else if(nod->HasRightChild())
                MapPreOrder(func, par, nod->RightChild());
        }          
    }
}

template <typename Data>
void BinaryTree<Data>::MapPostOrder(const MapFunctor func, void* par, Node* nod) {
    if (nod != nullptr)
    {
        if (!nod->IsLeaf())
        {
            if (nod->HasLeftChild() && nod->HasRightChild())
            {
                MapPostOrder(func, par, nod->LeftChild();
                MapPostOrder(func, par, nod->RightChild());
            }
            else if (nod->HasLeftChild())
                MapPostOrder(func, par, nod->LeftChild();

            else if(nod->HasRightChild())
                MapPostOrder(func, par, nod->RightChild());
        }
        func(nod->Element, par);
    }
}

template <typename Data>
void BinaryTree<Data>::FoldPreOrder(const FoldFunctor func, const void* par, void* acc, const Node* nod) const {
    if (nod != nullptr)
    {
        func(nod->Element, par, acc);
        if (!nod->IsLeaf())
        {
            if (nod->HasLeftChild() && nod->HasRightChild())
            {
                FoldPreOrder(func, par, acc, nod->LeftChild());
                FoldPreOrder(func, par, acc, nod->RightChild());
            }
            else if (nod->HasLeftChild())
                FoldPreOrder(func, par, acc, nod->LeftChild());

            else if(nod->HasRightChild())
                FoldPreOrder(func, par, acc, nod->RightChild());
        }   
    }
}

template <typename Data>
void BinaryTree<Data>::FoldPostOrder(const FoldFunctor func, const void* par, void* acc, const Node* nod) const {
    if (nod != nullptr)
    {
        if (!nod->IsLeaf())
        {
            if (nod->HasLeftChild() && nod->HasRightChild())
            {
                FoldPostOrder(func, par, acc, nod->LeftChild());
                FoldPostOrder(func, par, acc, nod->RightChild());
            }
            else if (nod->HasLeftChild())
                FoldPostOrder(func, par, acc, nod->LeftChild());

            else if(nod->HasRightChild())
                 FoldPostOrder(func, par, acc, nod->RightChild());
        }
        func(nod->Element, par, acc);
    }
}

template <typename Data>
void BinaryTree<Data>::MapInOrder(const MapFunctor func, void* par, Node* nod) {
    if (nod != nullptr)
    {
        if (!nod->IsLeaf())
        {
            if (nod->HasLeftChild() && nod->HasRightChild())
            {
                MapInOrder(func, par, nod->LeftChild());
                func(nod->Element, par);
                MapInOrder(func, par, nod->RightChild());
            }
            else if (nod->HasLeftChild())
            {
                MapInOrder(func, par, nod->LeftChild());
                func(nod->Element, par);
            }
            else if (nod->HasRightChild())
            {
                func(nod->Element, par);
                MapInOrder(func, par, nod->RightChild());
            }
        }
        else
            func(nod->Element, par);
    }
}

template <typename Data>
void BinaryTree<Data>::FoldInOrder(const FoldFunctor func, const void* par, void* acc, const Node* nod) const {
    if (nod != nullptr)
    {
        if (!nod->IsLeaf())
        {
            if (nod->HasLeftChild() && nod->HasRightChild())
            {
                FoldInOrder(func, par, acc, nod->LeftChild());
                func(nod->Element, par, acc);
                FoldInOrder(func, par, acc, nod->RightChild())
            }
            else if (nod->HasLeftChild())
            {
                FoldInOrder(func, par, acc, nod->LeftChild());
                func(nod->Element, par, acc);
            }
            else if (nod->HasRightChild())
            {
                func(nod->Element, par, acc);
                FoldInOrder(func, par, acc, nod->RightChild());
            }
        }
        else
            func(nod->Element, par, acc);
    }
}

template <typename Data>
void BinaryTree<Data>::MapBreadth(const MapFunctor func, void* par, Queue<Node>& que) {
    while (!que.Empty())
    {
        Node* nod = que.Head();
        func(nod->Element, par);
        que.Dequeue();

        if(nod->HasLeftChild())
            que.Enqueue(nod->LeftChild());
        
        if (nod->HasRightChild())
            que.Enqueue(nod->RightChild());
    }
}

template <typename Data>
void BinaryTree<Data>::FoldBreadth(const FoldFunctor func, const void* par, void* acc, Queue<Node>& que) const {
    while (!que.Empty())
    {
        Node* nod = que.Head();
        func(nod->Element, par, acc);
        que.Dequeue();

        if(nod->HasLeftChild())
            que.Enqueue(nod->LeftChild());
        
        if (nod->HasRightChild())
            que.Enqueue(nod->RightChild());
    }
}

/* ************************************************************************** */

}
