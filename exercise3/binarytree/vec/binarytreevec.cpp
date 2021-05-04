
namespace lasd {

/* ************************************************************************** */

template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(const NodeVec& nod) {
    Elem = nod.Elem;
    index = nod.index;
}

template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(NodeVec&& nod) noexcept {
    std::swap(Elem, nod.Elem);
    std::swap(index, nod.index);
}

template <typename Data>
BinaryTreeVec<Data>::NodeVec::~NodeVec() {
    owner = nullptr;
}

template <typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::operator=(const NodeVec& nod) {
    if (*this != nod)
    {
        Elem = nod.Elem;
        index = nod.index;
    }
    return *this;
}

template <typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::operator=(NodeVec&& nod) noexcept {
    if (*this != nod)
    {
        std::swap(Elem, nod.Elem);
        std::swap(index, nod.index);
    }
    return *this;
}

template <typename Data>
const Data& BinaryTreeVec<Data>::NodeVec::Element() const noexcept {
    return Elem;
}

template <typename Data>
Data& BinaryTreeVec<Data>::NodeVec::Element() noexcept {
    return Elem;
}

template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept {
    return owner->Size() > (index*2)+1;
}

template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept {
    return owner->Size() > (index*2)+2;
}

template <typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::LeftChild() const {
    return (*owner)[(index*2)+1];
}

template <typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::RightChild() const {
    return (*owner)[(index*2)+2];
}

/* ************************************************************************** */

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const LinearContainer<Data>& con) {
    size = con.Size();
    btVec.Resize(size);
    for (unsigned long i=0; i<size; i++)
    {
        btVec[i].Element() = con[i];
        btVec[i].index = i;
        btVec[i].owner = &btVec;
    }
}

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data>& bt) {
    size = bt.size;
    btVec.Resize(size);
    for (unsigned long i=0; i<size; i++)
    {
        btVec[i] = bt.btVec[i];
        btVec[i].owner = &btVec;
    }
}

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data>&& bt) noexcept {
    std::swap(size, bt.size);
    std::swap(btVec, bt.btVec);
}

template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data>& bt) {
    if (*this != bt)
    {
        size = bt.size;
        btVec.Resize(size);
        for (unsigned long i=0; i<size; i++)
        {
            btVec[i] = bt.btVec[i];
            btVec[i].owner = &btVec;
        }
    }
    return *this;
}

template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(BinaryTreeVec<Data>&& bt) noexcept {
    if (*this != bt)
    {
        std::swap(size, bt.size);
        std::swap(btVec, bt.btVec);
    }
    return *this;
}

template <typename Data>
bool BinaryTreeVec<Data>::operator==(const BinaryTreeVec<Data>& bt) const noexcept {
    if (size == bt.size)
        return btVec == bt.btVec;
    else 
        return false;
}

template <typename Data>
inline bool BinaryTreeVec<Data>::operator!=(const BinaryTreeVec<Data>& bt) const noexcept {
    return !(*this == bt);
}

template <typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() const {
    if (size != 0)
        return btVec[0];
    else
        throw std::length_error("Access to an empty tree (vector).");
}

template <typename Data>
void BinaryTreeVec<Data>::Clear() {
    btVec.Clear();
    size = 0;
}

template <typename Data>
void BinaryTreeVec<Data>::MapBreadth(const MapFunctor func, void* par) {
    for (unsigned long i=0; i<size; i++)
        func(btVec[i].Element(), par);
}

template <typename Data>
void BinaryTreeVec<Data>::FoldBreadth(const FoldFunctor func, const void* par, void* acc) const {
    for (unsigned long i=0; i<size; i++)
        func(btVec[i].Element(), par, acc);
}

/* ************************************************************************** */

}
