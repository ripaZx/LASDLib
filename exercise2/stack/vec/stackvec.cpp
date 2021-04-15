
namespace lasd {

/* ************************************************************************** */

template <typename Data>
StackVec<Data>::StackVec() {
    size = basicOffset;
    Elements = new Data[size];
    top = 0;
}

template <typename Data>
StackVec<Data>::StackVec(const LinearContainer<Data>& con) {
    top = con.Size();
    size = top + basicOffset;
    Elements = new Data[size];
    for (unsigned long i=0; i<top; i++)
        Elements[i] = con[i];
}

template <typename Data>
StackVec<Data>::StackVec(const StackVec<Data>& sVec) {
    size = sVec.size;
    Elements = new Data[size];
    top = sVec.top;
    for (unsigned long i=0; i<top; i++)
        Elements[i] = sVec[i];
}

template <typename Data>
StackVec<Data>::StackVec(StackVec<Data>&& sVec) noexcept {
    std::swap(Elements, sVec.Elements);
    std::swap(size, sVec.size);
    std::swap(top, sVec.top);
}

template <typename Data>
StackVec<Data>& StackVec<Data>::operator=(const StackVec<Data>& sVec) {
    if(*this != sVec)
    {
        size = sVec.size;
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
        std::swap(top, sVec.top);
    }
    return *this;
}

template <typename Data>
bool StackVec<Data>::operator==(const StackVec<Data>& sVec) const noexcept {
    if (top == sVec.top)
    {
        for (unsigned long i=0; i<top; i++)
            if (Elements[i] != sVec.Elements[i])
                return false;
            
        return true;
    }
    else
        return false;
}

template <typename Data>
inline bool StackVec<Data>::operator!=(const StackVec<Data>& sVec) const noexcept {
    return !(*this==sVec);
}

template <typename Data>
void StackVec<Data>::Push(const Data& dat) {
    if(top == size)
        Expand();
    Elements[top] = dat;
    top++;
}

template <typename Data>
void StackVec<Data>::Push(Data&& dat) noexcept {
    if(top == size) 
        Expand();
    Elements[top] = std::move(dat);
    top++;
}

template <typename Data>
Data& StackVec<Data>::Top() const {
    if (top > 0)
        return Elements[top-1];
    else
        throw std::length_error("Access to an empty stack.");
}

template <typename Data>
void StackVec<Data>::Pop() {
    if (top > 0)
    {
        top--;
        if(top < size/4)
            Reduce();
    }
    else
        throw std::length_error("Access to an empty stack.");
}

template <typename Data>
Data StackVec<Data>::TopNPop() {
    if (top > 0)
    {
        top--;
        if(top < size/4)
            Reduce();
        return Elements[top];
    }
    else
        throw std::length_error("Access to an empty stack.");
}

template <typename Data>
inline bool StackVec<Data>::Empty() const noexcept {
    return (top == 0);
}

template <typename Data>
inline unsigned long StackVec<Data>::Size() const noexcept {
    return top;
}

template <typename Data>
void StackVec<Data>::Clear() {
    delete[] Elements;
    size = 9;
    Elements = new Data[size];
    top = 0;
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
