
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
    Elements = new Data[size];
    for(unsigned long i=0; i<back; i++)
        Elements[i] = con[i];
}

template <typename Data>
QueueVec<Data>::QueueVec(const QueueVec<Data>& qVec) {
    size = qVec.size;
    front = qVec.front;
    back = qVec.back;
    Elements = new Data[size];
    for (unsigned long i=front; i!=back; i=(i+1)%size)
        Elements[i] = qVec.Elements[i];
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
        QueueVec<Data>* tmpQueue = new QueueVec<Data>(qVec);
        std::swap(*tmpQueue, *this);
        delete tmpQueue;
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
    if (Size() == qVec.Size())
    {
        for (unsigned long i=front, j=qVec.front; i!=back; i=(i+1)%size, j=(j+1)%qVec.size)
            if (Elements[i] != qVec.Elements[j])
                return false;
        
        return true;
    }
    else
        return false;
}

template <typename Data>
inline bool QueueVec<Data>::operator!=(const QueueVec<Data>& qVec) const noexcept {
    return !(*this==qVec);
}

template <typename Data>
void QueueVec<Data>::Enqueue(const Data& dat) {
    if (front == (back+1)%size)
    {
        Expand();
    }
    Elements[back] = dat;
    back = (back+1)%size;
}

template <typename Data>
void QueueVec<Data>::Enqueue(Data&& dat) noexcept {
    if (front == (back+1)%size)
    {
        Expand();
    }
    Elements[back] = std::move(dat);
    back = (back+1)%size;
}

template <typename Data>
Data& QueueVec<Data>::Head() const {
    if (front != back)
        return Elements[front];
    else
        throw std::length_error("Access to an empty queue.");
}

template <typename Data>
void QueueVec<Data>::Dequeue() {
    if (front != back)
    {
        front = (front+1)%size;
        if (Size() < size/4)
            Reduce();
    }
    else
        throw std::length_error("Access to an empty queue.");
}

template <typename Data>
Data QueueVec<Data>::HeadNDequeue() {
    if(front != back)
    {
        Data element = Elements[front];
        front = (front+1)%size;
        if (Size() < size/4)
            Reduce();
        return element;
    }
    else
        throw std::length_error("Access to an empty queue.");

}

template <typename Data>
inline bool QueueVec<Data>::Empty() const noexcept {
    return (front == back);
}

template <typename Data>
inline unsigned long QueueVec<Data>::Size() const noexcept {
    if (back >= front)
        return back - front;
    else
        return (size + back) - front;
}

template <typename Data>
void QueueVec<Data>::Clear() {
    delete[] Elements;
    size = basicOffset;
    Elements = new Data[size];
    front = 0;
    back = 0;
}

template <typename Data>
void QueueVec<Data>::Expand() {
    if (front < back)
        this->Resize(2*size);
    else
    {
        SwapVectors();
        this->Resize(2*size);
    }
}

template <typename Data>
void QueueVec<Data>::Reduce() {
    SwapVectors();
    this->Resize(size/2);
}

template <typename Data>
void QueueVec<Data>::SwapVectors() {
    QueueVec<Data>* tmpVec = new QueueVec<Data>(*this);
    for (unsigned long i=front, j=0; i!=back; i=(i+1)%size, j++)
        tmpVec->Elements[j] = Elements[i];
    tmpVec->back = Size();
    tmpVec->front = 0;
    std::swap(*this, *tmpVec);
    delete tmpVec;
}

/* ************************************************************************** */

}
