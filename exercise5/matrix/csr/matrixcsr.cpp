
namespace lasd {

/* ************************************************************************** */

template <typename Data>
MatrixCSR<Data>::MatrixCSR() {
    rowVec.Resize(1);
    rowVec[0] = &head;
}

template <typename Data>
MatrixCSR<Data>::MatrixCSR(const unsigned long row, const unsigned long col) {
    Vector<Node**>  tmpVec(row+1);
    for (unsigned long i=0; i<(row+1); i++)
        tmpVec[i] = &head;
    std::swap(tmpVec, rowVec);
    rows = row;
    columns = col;
}

template <typename Data>
MatrixCSR<Data>::MatrixCSR(const MatrixCSR& mat) {
    Node** current = &head;
    Node* currentMat = mat.head;
    Vector<Node**> tmpVec(mat.rowVec.Size());
    for (unsigned long i=0; i<tmpVec.Size(); i++)
    {
        tmpVec[i] = current;
        if (mat.rowVec[i] != mat.rowVec[i+1])
            while (currentMat != *(mat.rowVec[i+1]))
            {
                *current = new Node(*currentMat);
                current = &((*current)->next);
                currentMat = currentMat->next;
            }
    }
    std::swap(tmpVec, rowVec);
    rows = mat.rows;
    columns = mat.columns;
}

template <typename Data>
MatrixCSR<Data>::MatrixCSR(MatrixCSR&& mat) noexcept {
    std::swap(rows, mat.rows);
    std::swap(columns, mat.columns);
    std::swap(head, mat.head);
    std::swap(rowVec, mat.rowVec);
}

template <typename Data>
MatrixCSR<Data>& MatrixCSR<Data>::operator=(const MatrixCSR& mat) {
    if (*this != mat)
    {
        rows = mat.rows;
        columns = mat.columns;
        MatrixCSR<Data>* tmpMat = new MatrixCSR<Data>(mat);
        std::swap(*tmpMat, *this);
        delete tmpMat;
    }
    return *this;
}

template <typename Data>
MatrixCSR<Data>& MatrixCSR<Data>::operator=(MatrixCSR&& mat) noexcept {
    if (*this != mat)
    {
        std::swap(rows, mat.rows);
        std::swap(columns, mat.columns);
        std::swap(head, mat.head);
        std::swap(rowVec, mat.rowVec);
    }
    return *this;
}

template <typename Data>
bool MatrixCSR<Data>::operator==(const MatrixCSR& mat) const noexcept {
    Node* current = head;
    Node* currentMat = mat.head;
    while (current != nullptr)
    {
        if (current->Element.first != currentMat->Element.first || current->Element.second != currentMat->Element.second)
            return false;
        
        current = current->next;
        currentMat = currentMat->next;
    }
    return true;
}

template <typename Data>
inline bool MatrixCSR<Data>::operator!=(const MatrixCSR& mat) const noexcept {
    return !(*this == mat);
}

template <typename Data>
void MatrixCSR<Data>::RowResize(const unsigned long newRows) {

}

template <typename Data>
void MatrixCSR<Data>::ColumnResize(const unsigned long newCols) {

}

template <typename Data>
bool MatrixCSR<Data>::ExistsCell(const unsigned long row, const unsigned long col) const noexcept {
    if (row < rows && col < columns)
    {
        Node* nod = *(rowVec[row]);
        while (nod != *(rowVec[row+1]))
        {
            if (nod->Element.second == col)
                return true;
            else
                nod = nod->next;
        }
        return false;
    }
    else
        return false;
}

template <typename Data>
Data& MatrixCSR<Data>::operator()(const unsigned long row, const unsigned long col) {

} 

template <typename Data>
const Data& MatrixCSR<Data>::operator()(const unsigned long row, const unsigned long col) const {

}

template <typename Data>
void MatrixCSR<Data>::Clear() {
    List<std::pair<Data, unsigned long>>::Clear();
    rowVec.Resize(1);
    rowVec[0] = &head;
    rows = 0;
    columns = 0;
}

template <typename Data>
void MatrixCSR<Data>::MapPreOrder(const MapFunctor func, void* par) {
    List<std::pair<Data, unsigned long>>::MapPreOrder(
        [&func] (std::pair<Data, unsigned long>& dat, void* parx) { func(dat.first, parx); }
        , par);
}

template <typename Data>
void MatrixCSR<Data>::MapPostOrder(const MapFunctor func, void* par) {
    List<std::pair<Data, unsigned long>>::MapPostOrder(
        [&func] (std::pair<Data, unsigned long>& dat, void* parx) { func(dat.first, parx); }
        , par);
}

template <typename Data>
void MatrixCSR<Data>::FoldPreOrder(const FoldFunctor func, const void* par, void* acc) const {
    List<std::pair<Data, unsigned long>>::FoldPreOrder(
        [&func] (const std::pair<Data, unsigned long>& dat, const void* parx, void* accx) { func(dat.first, parx, accx); }
        , par, acc);
}

template <typename Data>
void MatrixCSR<Data>::FoldPostOrder(const FoldFunctor func, const void* par, void* acc) const {
    List<std::pair<Data, unsigned long>>::FoldPostOrder(
        [&func] (const std::pair<Data, unsigned long>& dat, const void* parx, void* accx) { func(dat.first, parx, accx); }
        , par, acc);
}

/* ************************************************************************** */

}
