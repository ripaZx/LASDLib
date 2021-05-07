
namespace lasd {

/* ************************************************************************** */

template <typename Data>
bool BinaryTree<Data>::Node::CompareSubTrees(const Node& nod) const noexcept {
    if (*this != nod)
        return false;
    else
    {
        if (HasLeftChild() && HasRightChild())
        {
            if (nod.HasLeftChild() && nod.HasRightChild())
                return LeftChild().CompareSubTrees(nod.LeftChild()) && RightChild().CompareSubTrees(nod.RightChild());
            else
                return false;
        }
        else if (HasLeftChild())
        {
            if (nod.HasLeftChild())
                return LeftChild().CompareSubTrees(nod.LeftChild());
            else
                return false;
        }
        else if (HasRightChild())
        {
            if (nod.HasRightChild()) 
                return RightChild().CompareSubTrees(nod.RightChild());
            else
                return false;
        }
        else
            return true;
    }
}

template <typename Data>
bool BinaryTree<Data>::Node::operator==(const Node& nod) const noexcept {
    if (Element() == nod.Element())
        return true;
    else
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
bool BinaryTree<Data>::operator==(const BinaryTree<Data>& tree) const noexcept {
    if (size == 0 && tree.size == 0)
        return true;
    else if (size == tree.size)
        return Root().CompareSubTrees(tree.Root());
    else 
        return false;
}

template <typename Data>
inline bool BinaryTree<Data>::operator!=(const BinaryTree<Data>& tree) const noexcept {
    return !(*this == tree);
}

template <typename Data>
inline void BinaryTree<Data>::MapPreOrder(const MapFunctor func, void* par) {
    if (size != 0)
        MapPreOrder(func, par, &Root());
}

template <typename Data>
inline void BinaryTree<Data>::MapPostOrder(const MapFunctor func, void* par) {
    if (size != 0)
        MapPostOrder(func, par, &Root());
}

template <typename Data>
inline void BinaryTree<Data>::FoldPreOrder(const FoldFunctor func, const void* par, void* acc) const {
    if (size != 0)
        FoldPreOrder(func, par, acc, &Root());
}

template <typename Data>
inline void BinaryTree<Data>::FoldPostOrder(const FoldFunctor func, const void* par, void* acc) const {
    if (size != 0)
        FoldPostOrder(func, par, acc, &Root());
}

template <typename Data>
inline void BinaryTree<Data>::MapInOrder(const MapFunctor func, void* par) {
    if (size != 0)
        MapInOrder(func, par, &Root());
}

template <typename Data>
inline void BinaryTree<Data>::FoldInOrder(const FoldFunctor func, const void* par, void* acc) const {
    if (size != 0)
        FoldInOrder(func, par, acc, &Root());
}

template <typename Data>
void BinaryTree<Data>::MapBreadth(const MapFunctor func, void* par) {
    QueueLst<Node*> que;
    que.Enqueue(&Root());
    MapBreadth(func, par, &que);
}

template <typename Data>
void BinaryTree<Data>::FoldBreadth(const FoldFunctor func, const void* par, void* acc) const {
    QueueLst<Node*> que;
    que.Enqueue(&Root());
    FoldBreadth(func, par, acc, &que);
}

template <typename Data>
void BinaryTree<Data>::MapPreOrder(const MapFunctor func, void* par, Node* nod) {
    if (nod != nullptr)
    {
        func(nod->Element(), par);
        if (!nod->IsLeaf())
        {
            if (nod->HasLeftChild())
                MapPreOrder(func, par, &nod->LeftChild());

            if(nod->HasRightChild())
                MapPreOrder(func, par, &nod->RightChild());
        }         
    }
}

template <typename Data>
void BinaryTree<Data>::MapPostOrder(const MapFunctor func, void* par, Node* nod) {
    if (nod != nullptr)
    {
        if (!nod->IsLeaf())
        {
            if (nod->HasLeftChild())
                MapPostOrder(func, par, &nod->LeftChild());

            if(nod->HasRightChild())
                MapPostOrder(func, par, &nod->RightChild());
        }
        func(nod->Element(), par);
    }
}

template <typename Data>
void BinaryTree<Data>::FoldPreOrder(const FoldFunctor func, const void* par, void* acc, const Node* nod) const {
    if (nod != nullptr)
    {
        func(nod->Element(), par, acc);
        if (!nod->IsLeaf())
        {
            if (nod->HasLeftChild())
                FoldPreOrder(func, par, acc, &nod->LeftChild());

            if(nod->HasRightChild())
                FoldPreOrder(func, par, acc, &nod->RightChild());
        }   
    }
}

template <typename Data>
void BinaryTree<Data>::FoldPostOrder(const FoldFunctor func, const void* par, void* acc, const Node* nod) const {
    if (nod != nullptr)
    {
        if (!nod->IsLeaf())
        {
            if (nod->HasLeftChild())
                FoldPostOrder(func, par, acc, &nod->LeftChild());

            if(nod->HasRightChild())
                FoldPostOrder(func, par, acc, &nod->RightChild());
        }
        func(nod->Element(), par, acc);
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
                MapInOrder(func, par, &nod->LeftChild());
                func(nod->Element(), par);
                MapInOrder(func, par, &nod->RightChild());
            }
            else if (nod->HasLeftChild())
            {
                MapInOrder(func, par, &nod->LeftChild());
                func(nod->Element(), par);
            }
            else if (nod->HasRightChild())
            {
                func(nod->Element(), par);
                MapInOrder(func, par, &nod->RightChild());
            }
        }
        else
            func(nod->Element(), par);
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
                FoldInOrder(func, par, acc, &nod->LeftChild());
                func(nod->Element(), par, acc);
                FoldInOrder(func, par, acc, &nod->RightChild());
            }
            else if (nod->HasLeftChild())
            {
                FoldInOrder(func, par, acc, &nod->LeftChild());
                func(nod->Element(), par, acc);
            }
            else if (nod->HasRightChild())
            {
                func(nod->Element(), par, acc);
                FoldInOrder(func, par, acc, &nod->RightChild());
            }
        }
        else
            func(nod->Element(), par, acc);
    }
}

template <typename Data>
void BinaryTree<Data>::MapBreadth(const MapFunctor func, void* par, Queue<Node*>* que) {
    while (!que->Empty())
    {
        Node* nod = que->Head();
        func(nod->Element(), par);
        que->Dequeue();

        if(nod->HasLeftChild())
            que->Enqueue(&nod->LeftChild());
        
        if (nod->HasRightChild())
            que->Enqueue(&nod->RightChild());
    }
}

template <typename Data>
void BinaryTree<Data>::FoldBreadth(const FoldFunctor func, const void* par, void* acc, Queue<Node*>* que) const {
    while (!que->Empty())
    {
        Node* nod = que->Head();
        func(nod->Element(), par, acc);
        que->Dequeue();

        if(nod->HasLeftChild())
            que->Enqueue(&nod->LeftChild());
        
        if (nod->HasRightChild())
            que->Enqueue(&nod->RightChild());
    }
}

/* ************************************************************************** */

template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data>& bt) {
    current = &bt.Root();
}

template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator<Data>& itr) {
    current = itr.current;
    stk = itr.stk;
}

template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator<Data>&& itr) noexcept {
    std::swap(current, itr.current);
    std::swap(stk, itr.stk);
}

template <typename Data>
BTPreOrderIterator<Data>::~BTPreOrderIterator() {
    current = nullptr;
}

template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator<Data>& itr) {
    if (*this != itr)
    {
        BTPreOrderIterator<Data>* tmpItr = new BTPreOrderIterator<Data>(itr);
        std::swap(*this, tmpItr);
        delete tmpItr;
    }
    return *this;
}

template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(BTPreOrderIterator<Data>&& itr) noexcept {
    if (*this != itr)
    {
        std::swap(current, itr.current);
        std::swap(stk, itr.stk);
    }
    return *this;
}

template <typename Data>
bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator<Data>& itr) const noexcept {
    return *current == *itr.current && stk == itr.stk;
}

template <typename Data>
inline bool BTPreOrderIterator<Data>::operator!=(const BTPreOrderIterator<Data>& itr) const noexcept {
    return !(*this==itr);
}

template <typename Data>
Data& BTPreOrderIterator<Data>::operator*() const {
    if (!Terminated())
        return current->Element();
    else
        throw std::out_of_range("Access to a terminated iterator.");
}

template <typename Data>
bool BTPreOrderIterator<Data>::Terminated() const noexcept {
    return (current == nullptr);
}

template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator++() {
    if (current != nullptr)
    {
        if (current->HasRightChild())
            stk.Push(&current->RightChild());
        if (current->HasLeftChild())
            stk.Push(&current->LeftChild());

        current = stk.Empty() ?
        nullptr :
        stk.TopNPop();
        
        return *this;
    }
    else
        throw std::out_of_range("Access to a terminated iterator.");
}

/* ************************************************************************** */

template <typename Data>
typename BinaryTree<Data>::Node& BTPostOrderIterator<Data>::LeftMostLeaf(Node& nod) {
    if (nod.HasLeftChild())
    {
        stk.Push(&nod);
        return LeftMostLeaf(nod.LeftChild());
    }
    else if (nod.HasRightChild())
    {
        stk.Push(&nod);
        return LeftMostLeaf(nod.RightChild());
    }
    else
        return nod;
}

template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data>& bt) {
    current = &LeftMostLeaf(bt.Root());
}

template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator<Data>& itr) {
    current = itr.current;
    stk = itr.stk;
}

template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator<Data>&& itr) noexcept {
    std::swap(current, itr.current);
    std::swap(stk, itr.stk);
}

template <typename Data>
BTPostOrderIterator<Data>::~BTPostOrderIterator() {
    current = nullptr;
}

template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator<Data>& itr) {
    if (*this != itr)
    {
        BTPostOrderIterator<Data>* tmpItr = new BTPostOrderIterator<Data>(itr);
        std::swap(*this, tmpItr);
        delete tmpItr;
    }
    return *this;
}

template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(BTPostOrderIterator<Data>&& itr) noexcept {
    if (*this != itr)
    {
        std::swap(current, itr.current);
        std::swap(stk, itr.stk);
    }
    return *this;
}

template <typename Data>
bool BTPostOrderIterator<Data>::operator==(const BTPostOrderIterator<Data>& itr) const noexcept {
    return *current == *itr.current && stk == itr.stk;
}

template <typename Data>
inline bool BTPostOrderIterator<Data>::operator!=(const BTPostOrderIterator<Data>& itr) const noexcept {
    return !(*this==itr);
}

template <typename Data>
Data& BTPostOrderIterator<Data>::operator*() const {
    if (!Terminated())
        return current->Element();
    else
        throw std::out_of_range("Access to a terminated iterator.");
}

template <typename Data>
bool BTPostOrderIterator<Data>::Terminated() const noexcept {
    return (current == nullptr);
}

template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator++() {
    if (current != nullptr)
    {
        if (stk.Empty())
            current = nullptr;

        else if (current == &stk.Top()->LeftChild() && stk.Top()->HasRightChild())
            current = &LeftMostLeaf(stk.Top()->RightChild());
    
        else
            current = stk.TopNPop();

        return *this;
    }
    else
        throw std::out_of_range("Access to a terminated iterator.");
}

/* ************************************************************************** */

template <typename Data>
typename BinaryTree<Data>::Node& BTInOrderIterator<Data>::LeftMostNode(Node& nod) {
    if (nod.HasLeftChild())
    {
        stk.Push(&nod);
        return LeftMostNode(nod.LeftChild());
    }
    else
        return nod;
}

template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data>& bt) {
    current = &LeftMostNode(bt.Root());
}

template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BTInOrderIterator<Data>& itr) {
    current = itr.current;
    stk = itr.stk;
}

template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(BTInOrderIterator<Data>&& itr) noexcept {
    std::swap(current, itr.current);
    std::swap(stk, itr.stk);
}

template <typename Data>
BTInOrderIterator<Data>::~BTInOrderIterator() {
    current = nullptr;
}

template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(const BTInOrderIterator<Data>& itr) {
    if (*this != itr)
    {
        BTInOrderIterator<Data>* tmpItr = new BTInOrderIterator<Data>(itr);
        std::swap(*this, tmpItr);
        delete tmpItr;
    }
    return *this;
}

template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(BTInOrderIterator<Data>&& itr) noexcept {
    if (*this != itr)
    {
        std::swap(current, itr.current);
        std::swap(stk, itr.stk);
    }
    return *this;
}

template <typename Data>
bool BTInOrderIterator<Data>::operator==(const BTInOrderIterator<Data>& itr) const noexcept {
    return *current == *itr.current && stk == itr.stk;
}

template <typename Data>
inline bool BTInOrderIterator<Data>::operator!=(const BTInOrderIterator<Data>& itr) const noexcept {
    return !(*this==itr);
}

template <typename Data>
Data& BTInOrderIterator<Data>::operator*() const {
    if (!Terminated())
        return current->Element();
    else
        throw std::out_of_range("Access to a terminated iterator.");
}

template <typename Data>
bool BTInOrderIterator<Data>::Terminated() const noexcept {
    return (current == nullptr);
}

template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator++() {
    if (current != nullptr)
    {
        if (current->HasRightChild())
            current = &LeftMostNode(current->RightChild());

        else
            current = stk.Empty() ?
            nullptr :
            stk.TopNPop();

        return *this;
    }
    else
        throw std::out_of_range("Access to a terminated iterator.");
}

/* ************************************************************************** */

template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data>& bt) {
    current = &bt.Root();
}

template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BTBreadthIterator<Data>& itr) {
    current = itr.current;
    que = itr.que;
}

template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(BTBreadthIterator<Data>&& itr) noexcept {
    std::swap(current, itr.current);
    std::swap(que, itr.que);
}

template <typename Data>
BTBreadthIterator<Data>::~BTBreadthIterator() {
    current = nullptr;
}

template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(const BTBreadthIterator<Data>& itr) {
    if (*this != itr)
    {
        BTBreadthIterator<Data>* tmpItr = new BTBreadthIterator<Data>(itr);
        std::swap(*this, tmpItr);
        delete tmpItr;
    }
    return *this;
}

template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(BTBreadthIterator<Data>&& itr) noexcept {
    if (*this != itr)
    {
        std::swap(current, itr.current);
        std::swap(que, itr.que);
    }
    return *this;
}

template <typename Data>
bool BTBreadthIterator<Data>::operator==(const BTBreadthIterator<Data>& itr) const noexcept {
    return *current == *itr.current && que == itr.que;
}

template <typename Data>
inline bool BTBreadthIterator<Data>::operator!=(const BTBreadthIterator<Data>& itr) const noexcept {
    return !(*this==itr);
}

template <typename Data>
Data& BTBreadthIterator<Data>::operator*() const {
    if (!Terminated())
        return current->Element();
    else
        throw std::out_of_range("Access to a terminated iterator.");
}

template <typename Data>
bool BTBreadthIterator<Data>::Terminated() const noexcept {
    return (current == nullptr);
}

template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator++() {
    if (current != nullptr)
    {
        if (current->HasLeftChild())
            que.Enqueue(&current->LeftChild());
        if (current->HasRightChild())
            que.Enqueue(&current->RightChild());
        
        current = que.Empty() ?
        nullptr :
        que.HeadNDequeue();
        
        return *this;
    }
    else
        throw std::out_of_range("Access to a terminated iterator.");
}

/* ************************************************************************** */


}
