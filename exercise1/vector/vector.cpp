
namespace lasd {

/* ************************************************************************** */

template <typename Data>
Vector<Data>::Vector(const unsigned long newSize) {
    Elements = new Data[newSize];
    size = newSize;
}

template <typename Data>
Vector<Data>::Vector(const LinearContainer<Data>& con) {
    size = con.Size();
    Elements = new Data[size];

    for (unsigned long i=0; i<size; i++)
        Elements[i] = con[i];
}

template <typename Data>
Vector<Data>::Vector(const Vector<Data>& vec) {
    Elements = new Data[vec.size];
    std::copy(vec.Elements, vec.Elements + vec.size, Elements);
    size = vec.size;
}

template <typename Data>
Vector<Data>::Vector(Vector<Data>&& vec) noexcept {
    std::swap(Elements, vec.Elements);
    std::swap(size, vec.size);
}

template <typename Data>
Vector<Data>::~Vector() {
    delete[] Elements;
}

template <typename Data>
Vector<Data>& Vector<Data>::operator=(const Vector<Data>& vec) {
    Vector<Data>* tmpvec = new Vector<Data>(vec);
    std::swap(*tmpvec, *this);
    delete tmpvec;
    return *this;
}

template <typename Data>
Vector<Data>& Vector<Data>::operator=(Vector<Data>&& vec) noexcept {
    std::swap(Elements, vec.Elements);
    std::swap(size, vec.size);
    return *this;
}

template <typename Data>
bool Vector<Data>::operator==(const Vector<Data>& vec) const noexcept {
    if (size == vec.size)
    {
        for (unsigned long i=0; i<size; i++)
            if (Elements[i]!= vec.Elements[i])
                return false;
        
        return true;
    }
    else
        return false;
}

template <typename Data>
inline bool Vector<Data>::operator!=(const Vector<Data>& vec) const noexcept {
    return !(*this==vec);
}

template <typename Data>
void Vector<Data>::Resize(const unsigned long newSize) {
    if (newSize == 0)
        Clear();
    else if (size != newSize)
    {
        unsigned long limit = (size < newSize) ? size : newSize;
        Data* TmpElements = new Data[newSize] {};
        for (unsigned long i = 0; i<limit; i++)
            std::swap(Elements[i], TmpElements[i]);
        std::swap(Elements, TmpElements);
        size = newSize;
        delete[] TmpElements;
    }
}

template <typename Data>
void Vector<Data>::Clear() {
    delete[] Elements;
    Elements = nullptr;
    size = 0;
}

template <typename Data>
Data& Vector<Data>::Front() const {
    if (size != 0)
        return Elements[0];
    else
        throw std::length_error("Access to an empty vector.");
}

template <typename Data>
Data& Vector<Data>::Back() const {
    if (size != 0)
        return Elements[size-1];
    else 
        throw std::length_error("Access to an empty vector.");
}

template <typename Data>
Data& Vector<Data>::operator[](const unsigned long index) const {
    if (index < size)
        return Elements[index];
    else
        throw std::out_of_range("Access at index " + std::to_string(index) + "; vector size " + std::to_string(size) + ".");
}

template <typename Data>
void Vector<Data>::MapPreOrder(const MapFunctor func, void* par) {
    for (unsigned long i=0; i<size; i++)
        func(Elements[i], par);
}

template <typename Data>
void Vector<Data>::MapPostOrder(const MapFunctor func, void* par) {
    unsigned long i = size;
    while (i>0)
        func(Elements[--i], par);
}


template <typename Data>
void Vector<Data>::FoldPreOrder(const FoldFunctor func, const void* par, void* acc) const {
    for (unsigned long i=0; i<size; i++)
        func(Elements[i], par, acc);
}

template <typename Data>
void Vector<Data>::FoldPostOrder(const FoldFunctor func, const void* par, void* acc) const {
    unsigned long i = size;
    while (i>0)
        func(Elements[--i], par, acc);
}

/* ************************************************************************** */

}
