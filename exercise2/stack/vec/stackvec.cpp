
namespace lasd {

/* ************************************************************************** */

template <typename Data>
StackVec<Data>::StackVec() {
    size = 9;
    Elements = new Data[size];
    head = 0;
}

template <typename Data>
StackVec<Data>::StackVec(const LinearContainer<Data>& con) {
    size = con.Size();
    Elements = new Data[size+9];
    head = size-1;
    for (unsigned long i=0, j=head; i<size; i++, j--)
        Elements[i] = con[j];
}

template <typename Data>
StackVec<Data>::StackVec(const StackVec<Data>& sVec) {
    size = sVec.Size();
    Elements = new Data[size];
    head = sVec.head;
    for (unsigned long i=0; i<size; i++)
        Elements[i] = sVec[i];
}

template <typename Data>
StackVec<Data>::StackVec(StackVec<Data>&& sVec) noexcept {
    std::swap(Elements, sVec.Elements);
    std::swap(size, sVec.size);
    std::swap(head, sVec.head);
}

template <typename Data>
StackVec<Data>::~StackVec() {
    delete[] Elements;
}

template <typename Data>
StackVec<Data>& StackVec<Data>::operator=(const StackVec<Data>& sVec) {
    if(*this != sVec)
    {
        size = sVec.Size();
        StackVec<Data>* tmpStack = new StackVec<Data>(sVec);
        std::swap(*tmpStack, *this);
        delete tmpStack;
    }
    return *this;
}

template <typename Data>
StackVec<Data>& StackVec<Data>::operator=(StackVec<Data>&& sVec) noexcept {
    if (*this != sVec)
    {
        std::swap(Elements, sVec.Elements);
        std::swap(size, sVec.size);
        std::swap(head, sVec.head);
    }
    return *this;
}

template <typename Data>
bool StackVec<Data>::operator==(const StackVec<Data>& sVec) const noexcept {
    return Vector<Data>::operator==(sVec);
}

template <typename Data>
inline bool StackVec<Data>::operator!=(const StackVec<Data>& sVec) const noexcept {
    return !(*this==sVec);
}

template <typename Data>
void StackVec<Data>::Push(const Data& dat) {
    if(head == size)
        Expand();
    Elements[head] = dat;
    head++;
}

template <typename Data>
void StackVec<Data>::Push(Data&& dat) noexcept {
    if(head == size) 
        Expand();
    Elements[head] = std::move(dat);
    head++;
}

template <typename Data>
Data& StackVec<Data>::Top() const {
    return Elements[head];
}

template <typename Data>
void StackVec<Data>::Pop() {
    head--;
    if(head < size/4)
        Reduce();
}

template <typename Data>
Data StackVec<Data>::TopNPop() {
    head--;
    if(head < size/4)
        Reduce();
    return Elements[head];
}

template <typename Data>
inline bool StackVec<Data>::Empty() {
    return (head == 0);
}

template <typename Data>
inline unsigned long StackVec<Data>::Size() {
    return head;
}

template <typename Data>
void StackVec<Data>::Clear() {
    delete[] Elements;
    size = 9;
    Elements = new Data[size];
    head = 0;
}

template <typename Data>
void StackVec<Data>::Expand() {
    this->Resize(2*size);
}

template <typename Data>
void StackVec<Data>::Reduce() {
    this->Resize(size/2);
}
/* ************************************************************************** */

}
