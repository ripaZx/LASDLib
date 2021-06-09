
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
        Vector<Data>::Clear();

    else if (newRows != rows)
        Vector<Data>::Resize(newRows*columns);

    rows = newRows;
}

template <typename Data>
void MatrixVec<Data>::ColumnResize(const unsigned long newCols) {
    if (newCols == 0)
        Vector<Data>::Clear();

    else if (newCols != columns)
    {
        MatrixVec<Data>* tmpMat = new MatrixVec<Data>(*this);
        Vector<Data>::Resize(rows*newCols);
        unsigned long limit = (newCols > columns) ? columns : newCols; 
        for (unsigned long i=0; i<rows; i++)
            for (unsigned long j=0; j<limit; j++)
                (*this)(i, j) = (*tmpMat)(i, j);

        size = newCols*rows;
        delete tmpMat;
    }
    columns = newCols;
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
        throw std::out_of_range("Access at (row,column) ("+ std::to_string(row) + "," + std::to_string(col) + 
                                "); matrix size: " + std::to_string(rows) + "x" + std::to_string(columns) + ".");
}

template <typename Data>
void MatrixVec<Data>::Clear() {
    Vector<Data>::Clear();
    rows = 0;
    columns = 0;
}

/* ************************************************************************** */

}
