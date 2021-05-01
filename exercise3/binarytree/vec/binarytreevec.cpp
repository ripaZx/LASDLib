
namespace lasd {

/* ************************************************************************** */

template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(const Data& dat) {

}

template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(Data&& dat) noexcept {

}

/* ************************************************************************** */

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec() {

}

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const LinearContainer<Data>& con) {

}

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data>& btV) {
    size = btV.size;
    btVec = btV.btVec;
}

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec&& btV) noexcept {
    std::swap(size, btV.size);
    std::swap(btVec, btV.btVec);
}

template <typename Data>
BinaryTreeVec<Data>::~BinaryTreeVec() {

}

template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data>& btV) {
    if (*this != btV)
    {
        btVec = btV.btVec;
        size = btV.size;
    }
    return *this;
}

template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(BinaryTreeVec<Data>&& btV) noexcept {
    if (*this != btV)
    {
        std::swap(btVec, btV.btVec);
        std::swap(size, btV.size);
    }
    return *this;
}

template <typename Data>
bool BinaryTreeVec<Data>::operator==(const BinaryTreeVec<Data>& btV) const noexcept {
    return size == btV.size && btVec == btV.btVec;
}

template <typename Data>
inline bool BinaryTreeVec<Data>::operator!=(const BinaryTreeVec<Data>& btV) const noexcept {
    return !(*this == btV);
}

template <typename Data>
BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() const {
    return btVec[0];
}

template <typename Data>
void BinaryTreeVec<Data>::Clear() {
    btVec.Clear();
    size = 0;
}


/* ************************************************************************** */

}
