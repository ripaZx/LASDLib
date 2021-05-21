
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

/* ************************************************************************** */

}
