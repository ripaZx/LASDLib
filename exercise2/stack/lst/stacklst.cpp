
namespace lasd {

/* ************************************************************************** */

template <typename Data>
StackLst<Data>::StackLst(const LinearContainer<Data>& con) : List<Data>::List(con) { }

template <typename Data>
StackLst<Data>::StackLst(const StackLst<Data>& sList) : List<Data>::List(sList) { }

template <typename Data>
StackLst<Data>::StackLst(StackLst<Data>&& sList) noexcept : List<Data>::List(std::move(sList)) { }

template <typename Data>
StackLst<Data>& StackLst<Data>::operator=(const StackLst<Data>& sList) {
    if (*this != sList)
    {
        size = sList.Size();
        StackLst<Data>* tmpStack = new StackLst<Data>(sList);
        std::swap(*tmpStack, *this);
        delete tmpStack;
    }
    return *this;
}

template <typename Data>
StackLst<Data>& StackLst<Data>::operator=(StackLst<Data>&& sList) noexcept {
    if (*this != sList)
    {
        std::swap(head, sList.head);
        std::swap(size, sList.size);
    }
    return *this;
}

template <typename Data>
bool StackLst<Data>::operator==(const StackLst<Data>& sList) const noexcept {
    return List<Data>::operator==(sList);
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

template <typename Data>
void StackLst<Data>::Clear() {
    for(unsigned long i=0; i<size; i++)
        this->RemoveFromFront();
    head = nullptr;
    size = 0;
}

/* ************************************************************************** */

}
