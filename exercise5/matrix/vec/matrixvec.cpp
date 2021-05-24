
namespace lasd {

/* ************************************************************************** */

template <typename Data>
MatrixVec<Data>::MatrixVec(const unsigned long row, const unsigned long col) : Vector<Data>::Vector(row*col) {
    rows = row;
    columns = col;
}

template <typename Data>
MatrixVec<Data>::MatrixVec(const MatrixVec& mat) : Vector<Data>::Vector(mat) {
    rows = mat.rows;
    columns = mat.columns;
}

template <typename Data>
MatrixVec<Data>::MatrixVec(MatrixVec&& mat) noexcept : Vector<Data>::Vector(std::move(mat)) {
    std::swap(rows, mat.rows);
    std::swap(columns, mat.columns);
}

template <typename Data>
MatrixVec<Data>& MatrixVec<Data>::operator=(const MatrixVec& mat) {
    Vector<Data>::operator=(mat);
    rows = mat.rows;
    columns = mat.columns;
    return *this;
}

template <typename Data>
MatrixVec<Data>& MatrixVec<Data>::operator=(MatrixVec&& mat) noexcept {
    Vector<Data>::operator=(std::move(mat));
    std::swap(rows, mat.rows);
    std::swap(columns, mat.columns);
    return *this;
}

template <typename Data>
bool MatrixVec<Data>::operator==(const MatrixVec<Data>& mat) const noexcept {
    return Vector<Data>::operator==(mat);
}

template <typename Data>
inline bool MatrixVec<Data>::operator!=(const MatrixVec<Data>& mat) const noexcept {
    return !(*this == mat);
}

template <typename Data>
void MatrixVec<Data>::RowResize(const unsigned long newRows) {
    if (newRows != rows)
    {
        Vector<Data>::Resize(newRows*columns);
        rows = newRows;
    }
}

template <typename Data>
void MatrixVec<Data>::ColumnResize(const unsigned long newCols) {
    if (newCols = 0)
        Clear();
    else if (newCols != columns)
    {
        unsigned long limit = (size < newCols*rows) ? size : newCols*rows;
        Data* tmpElements = new Data[newCols*rows] {};
        unsigned long i = 0, j = 0;
        while (i<limit)
        {
            if (j%newCols == i%columns)
            {
                std::swap(Vector<Data>::Elements[i], tmpElements[j]);
                i++;
            }
            j++;
        }
        std::swap(Vector<Data>::Elements, tmpElements);
        size = newCols*rows;
        columns = newCols;
        delete tmpElements;
    }
}

template <typename Data>
bool Matrix<Data>::ExistsCell(const unsigned long row, const unsigned long col) const noexcept {
    if (row < rows && col < columns)
        return true;
    
    else
        return false;
}

template <typename Data>
Data& MatrixVec<Data>::operator()(const unsigned long row, const unsigned long col) {
    return const_cast<Data&>(static_cast<const MatrixVec<Data> *>(this)->operator()(row, col));
}

template <typename Data>
const Data& MatrixVec<Data>::operator()(const unsigned long row, const unsigned long col) const {
    if (ExistsCell(row, col))
        return Vector<Data>::operator[]((row*columns)+col);

    else
        throw std::length_error("Out of range cell.");
}

template <typename Data>
void MatrixVec<Data>::Clear() {
    Vector<Data>::Clear();
    rows = 0;
    columns = 0;
}

// template <typename Data>
// void MatrixVec<Data>::MapPreOrder(const MapFunctor func, void* par) {
//     Vector<Data>::MapPreOrder(func, par);
// }

// template <typename Data>
// void MatrixVec<Data>::MapPostOrder(const MapFunctor func, void* par) {
//     Vector<Data>::MapPostOrder(func, par);
// }

// template <typename Data>
// void MatrixVec<Data>::FoldPreOrder(const FoldFunctor func, const void* par, void* acc) const {
//     Vector<Data>::FoldPreOrder(func, par, acc);
// }

// template <typename Data>
// void MatrixVec<Data>::FoldPostOrder(const FoldFunctor func, const void* par, void* acc) const {
//     Vector<Data>::FoldPostOrder(func, par, acc);
// }

/* ************************************************************************** */

}
