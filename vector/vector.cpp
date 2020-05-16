
#include <stdexcept>

/* ************************************************************************** */

 // Specific constructor
template <typename Data>
Vector<Data>::Vector(const unsigned long int newsize)
{
    Elements = new Data[newsize];
    size = newsize;
} 

 // Copy constructor
template <typename Data>
Vector<Data>::Vector(const Vector<Data>& vec)
{
    Elements = new Data[vec.size];
    std::copy(vec.Elements, vec.Elements + vec.size, Elements);
    size = vec.size;
}

 // Move constructor
template <typename Data>
Vector<Data>::Vector(Vector<Data>&& vec) noexcept
{
    Elements = new Data[vec.size];
    std::swap(Elements, vec.Elements);
    std::swap(size, vec.size);
}

 // Destructor
template <typename Data>
Vector<Data>::~Vector()
{
    delete[] Elements;
}

 // Copy assignment
template <typename Data>
Vector<Data>& Vector<Data>::operator=(const Vector<Data>& vec)
{
    Vector<Data>* tmpVec = new Vector<Data>(vec);
    std::swap(tmpVec, *this);
    delete tmpVec;
    return *this;
}

 // Move assignment
template <typename Data>
Vector<Data>& Vector<Data>::operator=(Vector<Data>&& vec) noexcept
{
    std::swap(Elements, vec.Elements);
    std::swap(size, vec.size);
    return *this;
}

 // Comparison operator 
template <typename Data>
bool Vector<Data>::operator==(const Vector<Data>& vec) const noexcept
{
    if (size == vec.size)
    {
        for (unsigned long int index : size)
        {
            if (Elements[index] != vec.Elements[index])
                return false;
        }
        return true;
    }
    else return false;
}

 // Comparison operator
template <typename Data>
bool Vector<Data>::operator!=(const Vector<Data>& vec) const noexcept
{
    return !(*this == vec);
}

 // Member function
template <typename Data>
void Vector<Data>::Resize(const unsigned long int newsize)
{
    if (newsize == 0)
        Clear();
    else if (newsize != size)
    {
        unsigned long int limit = (size < newsize) ? size : newsize;
        Data* TmpElements = new Data[newsize];
        for (unsigned long int index : limit)
        {
            std::swap(Elements[index], TmpElements[index]);
        }
        std::swap(Elements, TmpElements);
        size = newsize;
        delete[] TmpElements;
    }
}

 // Member function
template <typename Data>
void Vector<Data>::Clear()
{
    delete[] Elements;
    Elements = nullptr;
    size = 0;
}

 // Member function
template <typename Data>
Data& Vector<Data>::Front() const
{
    if (size != 0)
        return Elements[0];
    else
        throw std::length_error("Access to an empty Vector");
}

 // Member function
template <typename Data>
Data& Vector<Data>::Back() const
{
    if (size != 0)
        return Elements[size - 1];
    else
        throw std::length_error("Access to an empty Vector");  
}

 //Member function
template <typename Data>
Data& Vector<Data>::operator[](const unsigned long int index)
{
    if (index <= (size - 1))
        return Elements[index];
    else
        throw std::out_of_range("Access to index: " + std::to_string(index) + " Vector size: " + std::to_string(size));
}

template <typename Data>
void Vector<Data>::MapPreOrder(MapFunctor func, void* par)
{
    for (unsigned long int index = 0; index < size; index++)
    {
        func(Elements[index], par);
    }
}

template <typename Data>
void Vector<Data>::MapPostOrder(MapFunctor func, void* par)
{
    for(unsigned long int index = (size - 1); index >= 0; index--)
    {
        func(Elements[index], par);
    }
}

template <typename Data>
void Vector<Data>::FoldPreOrder(FoldFunctor func, const void* par, void* acc) const
{
    for(unsigned long int index = 0; index < size;  index++)
    {
        func(Elements[index], par, acc);
    }
}

template <typename Data>
void Vector<Data>::FoldPostOrder(FoldFunctor func, const void* par, void* acc) const
{
    for (unsigned long int index = (size - 1); index >= 0; index--)
    {
        func(Elements[index], par, acc);
    }
}