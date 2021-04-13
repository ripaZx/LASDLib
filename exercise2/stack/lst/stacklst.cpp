
namespace lasd {

/* ************************************************************************** */

template <typename Data>
StackLst<Data>::StackLst(const LinearContainer<Data>& con) {
    for (unsigned long i=con.Size(); i>0; i--)
        this->InsertAtFront(con[i]);
}

template <typename Data>
StackLst<Data>::StackLst(const StackLst<Data>& sList) {
    
}

template <typename Data>
StackLst<Data>::StackLst(StackLst<Data>&& sList) noexcept {
}

template <typename Data>
StackLst<Data>::~StackLst() {

}

template <typename Data>
StackLst<Data>& StackLst<Data>::operator=(const StackLst<Data>& sList) {
}

template <typename Data>
StackLst<Data>& StackLst<Data>::operator=(StackLst<Data>&& sList) noexcept {
}

template <typename Data>
bool StackLst<Data>::operator==(const StackLst<Data>& sList) const noexcept {
}

template <typename Data>
inline bool StackLst<Data>::operator!=(const StackLst<Data>& sList) const noexcept {
    return !(*this==sList);
}

template <typename Data>
void StackLst<Data>::Push(const Data& dat) {
    this->InsertAtFront(dat);
}

template <typename Data>
void StackLst<Data>::Push(Data&& dat) noexcept {
    this->InsertAtFront(std::move(dat));
}

template <typename Data>
Data& StackLst<Data>::Top() const {
    return this->Front();
}

template <typename Data>
void StackLst<Data>::Pop() {
    this->RemoveFromFront();
}

template <typename Data>
Data StackLst<Data>::TopNPop() {
    return this->FrontNRemove();
}
/* ************************************************************************** */

}
