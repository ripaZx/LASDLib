
namespace lasd {

/* ************************************************************************** */

template <typename Data>
QueueLst<Data>::QueueLst(const LinearContainer<Data>& con) {
    for (unsigned long i=0; i<con.Size(); i++)
        this->InsertAtBack(con[i]);
}

template <typename Data>
QueueLst<Data>::QueueLst(const QueueLst<Data>& qList) {
    for(unsigned long i=0; i<qList.Size(); i++)
        this->InsertAtBack(qList[i]);
}

template <typename Data>
QueueLst<Data>::QueueLst(QueueLst<Data>&& qList) noexcept {
    std::swap(head, qList.head);
    std::swap(tail, qList.tail);
    std::swap(size, qList.size);
}

template <typename Data>
QueueLst<Data>& QueueLst<Data>::operator=(const QueueLst<Data>& qList) {
    if (*this != qList)
    {
        size = qList.Size();
        QueueLst<Data>* tmpQueue = new QueueLst<Data>(qList);
        std::swap(*tmpQueue, *this);
        delete tmpQueue;
    }
    return *this;
}

template <typename Data>
QueueLst<Data>& QueueLst<Data>::operator=(QueueLst<Data>&& qList) noexcept {
    if (*this != qList)
    {
        std::swap(head, qList.head);
        std::swap(tail, qList.tail);
        std::swap(size, qList.size);
    }
    return *this;
}

template <typename Data>
bool QueueLst<Data>::operator==(const QueueLst<Data>& qList) const noexcept {
    return List<Data>::operator==(qList);
}

template <typename Data>
inline bool QueueLst<Data>::operator!=(const QueueLst<Data>& qList) const noexcept {
    return !(*this==qList);
}

template <typename Data>
void QueueLst<Data>::Enqueue(const Data& dat) {
    this->InsertAtBack(dat);
}

template <typename Data>
void QueueLst<Data>::Enqueue(Data&& dat) noexcept {
    this->InsertAtBack(std::move(dat));
}

template <typename Data>
Data& QueueLst<Data>::Head() const {
    return this->Front();
}

template <typename Data>
void QueueLst<Data>::Dequeue() {
    this->RemoveFromFront();
}

template <typename Data>
Data QueueLst<Data>::HeadNDequeue() {
    return this->FrontNRemove();
}

template <typename Data>
void QueueLst<Data>::Clear() {
    for(unsigned long i=0; i<size; i++)
        this->RemoveFromFront();
    head = nullptr;
    tail = nullptr;
    size = 0;
}

/* ************************************************************************** */

}
