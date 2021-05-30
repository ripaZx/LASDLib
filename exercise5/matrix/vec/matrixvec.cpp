
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
    if (newRows == 0)
        Clear();
    else if (newRows != rows)
    {
        Vector<Data>::Resize(newRows*columns);
        rows = newRows;
    }
}

template <typename Data>
void MatrixVec<Data>::ColumnResize(const unsigned long newCols) {
    if (newCols == 0)
        Clear();
    else if (newCols != columns)
    {
        Data* tmpElements = new Data[newCols*rows] {};
        unsigned long i = 0, j = 0;
        while (i < size)
        {
            if (j%newCols == i%columns)
            {
                std::swap(Vector<Data>::Elements[i], tmpElements[j]);
                (newCols > columns) ? i++ : j++;
            }
            (newCols > columns) ? j++ : i++;
        }
        std::swap(Vector<Data>::Elements, tmpElements);
        size = newCols*rows;
        columns = newCols;
        delete tmpElements;
    }
}

template <typename Data>
bool MatrixVec<Data>::ExistsCell(const unsigned long row, const unsigned long col) const noexcept {
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
        throw std::out_of_range("Out of range cell.");
}

template <typename Data>
void MatrixVec<Data>::Clear() {
    Vector<Data>::Clear();
    rows = 0;
    columns = 0;
}

/* ************************************************************************** */

}
