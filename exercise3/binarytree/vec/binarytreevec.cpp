
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
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::operator=(const NodeVec& nod) {
    this->Elem = nod.Elem;
}

template <typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::operator=(NodeVec&& nod) noexcept {
    std::swap(this->Elem, nod.Elem);
}

template <typename Data>
const Data& BinaryTreeVec<Data>::NodeVec::Element() const noexcept {
    return this->Elem;
}

template <typename Data>
Data& BinaryTreeVec<Data>::NodeVec::Element() noexcept {
    return this->Elem;
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
    btVec = bt.btVec;
}

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec&& bt) noexcept {
    std::swap(size, bt.size);
    std::swap(btVec, bt.btVec);
}

template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data>& bt) {
    if (*this != bt)
    {
        btVec = bt.btVec;
        size = bt.size;
    }
    return *this;
}

template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(BinaryTreeVec<Data>&& bt) noexcept {
    if (*this != bt)
    {
        std::swap(btVec, bt.btVec);
        std::swap(size, bt.size);
    }
    return *this;
}

template <typename Data>
bool BinaryTreeVec<Data>::operator==(const BinaryTreeVec<Data>& bt) const noexcept {
    return size == bt.size && btVec == bt.btVec;
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
        throw std::length_error("Access to an empty tree (vector)");
}

template <typename Data>
void BinaryTreeVec<Data>::Clear() {
    btVec.Clear();
    size = 0;
}

/* ************************************************************************** */

}
