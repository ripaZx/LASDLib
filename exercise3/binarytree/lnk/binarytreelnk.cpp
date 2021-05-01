
namespace lasd {

/* ************************************************************************** */

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const Data& dat) {
    Elem = dat;
}

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(Data&& dat) noexcept {
    std::swap(Elem, dat);
}

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::~NodeLnk() {
    delete left;
    delete right;
}

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::operator=(const NodeLnk& nod) {
    Elem = nod.Elem;
}

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::operator=(NodeLnk&& nod) noexcept {
    std::swap(Elem, nod.Elem);
}

template <typename Data>
const Data& BinaryTreeLnk<Data>::NodeLnk::Element() const noexcept {
    return Elem;
}

template <typename Data>
Data& BinaryTreeLnk<Data>::NodeLnk::Element() noexcept {
    return Elem;
}

template <typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::HasLeftChild() const noexcept {
    return !(left == nullptr);
}

template <typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::HasRightChild() const noexcept {
    return !(right == nullptr);
}

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::LeftChild() const {
    return *left;
}

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::RightChild() const {
    return *right;
}

/* ************************************************************************** */

template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const LinearContainer<Data>& con) {

}

template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk& bt) {

}

template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk&& bt) noexcept {

}

template <typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk& bt) {

}

template <typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(BinaryTreeLnk&& bt) noexcept {

}

template <typename Data>
bool BinaryTreeLnk<Data>::operator==(const BinaryTreeLnk& bt) const noexcept {

}

template <typename Data>
inline bool BinaryTreeLnk<Data>::operator!=(const BinaryTreeLnk& bt) const noexcept {

}

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::Root() const {

}

template <typename Data>
void BinaryTreeLnk<Data>::Clear() {

}


/* ************************************************************************** */

}
