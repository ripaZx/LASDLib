
namespace lasd {

/* ************************************************************************** */

template <typename Data>
QueueVec<Data>::QueueVec() {
    size = basicOffset;
    Elements = new Data[size];
    front = 0;
    back = 0;
}

template <typename Data>
QueueVec<Data>::QueueVec(const LinearContainer<Data>& con) {
    back = con.Size();
    front = 0;
    size = back + basicOffset;
    for(unsigned long i=0; i<back; i++)
        Elements[i] = con[i];
}

template <typename Data>
QueueVec<Data>::QueueVec(const QueueVec<Data>& qVec) {
    size = qVec.size;
    front = qVec.front;
    back = qVec.back;
    for (unsigned long i=0; i<size; i++)
        Elements[i] = qVec[i];
}

template <typename Data>
QueueVec<Data>::QueueVec(QueueVec<Data>&& qVec) noexcept {
    std::swap(Elements, qVec.Elements);
    std::swap(size, qVec.size);
    std::swap(front, qVec.front);
    std::swap(back, qVec.back);
}

template <typename Data>
QueueVec<Data>& QueueVec<Data>::operator=(const QueueVec<Data>& qVec) {
    if(*this != qVec)
    {
        size = qVec.size;
        QueueVec<Data>* tmpStack = new QueueVec<Data>(qVec);
        std::swap(*tmpStack, *this);
        delete tmpStack;
    }
    return *this;
}

template <typename Data>
QueueVec<Data>& QueueVec<Data>::operator=(QueueVec<Data>&& qVec) noexcept {
    if (*this != qVec)
    {
        std::swap(Elements, qVec.Elements);
        std::swap(size, qVec.size);
        std::swap(front, qVec.front);
        std::swap(back, qVec.back);
    }
    return *this;
}

template <typename Data>
bool QueueVec<Data>::operator==(const QueueVec<Data>& qVec) const noexcept {
    return true;
}

template <typename Data>
inline bool QueueVec<Data>::operator!=(const QueueVec<Data>& qVec) const noexcept {
    return !(*this==qVec);
}


/* ************************************************************************** */

}
