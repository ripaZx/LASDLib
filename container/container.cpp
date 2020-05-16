
// Specific member functions (Container)
inline bool Container::Empty() const noexcept
{
    return (size == 0);
}

inline unsigned long int Container::Size() const noexcept
{
    return size;
}

/* ************************************************************************** */

// Specific member functions (SearchableContainer)

template <typename Data>
void FoldExists(const Data& dat, const void* val, void* exists )
{
    if (dat == *((Data*) val))
    {
        *((bool*) exists) = true;
    }
}

template <typename Data>
bool SearchableContainer<Data>::Exists(const Data& dat) const noexcept
{
    bool exists = false;
    FoldPreOrder(&FoldExists<Data>, &dat, &exists);
    return exists;
}