
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
    for (unsigned long i=0; i<=row; i++)
        tmpVec[i] = &head;
    std::swap(tmpVec, rowVec);
    rows = row;
    columns = col;
}

template <typename Data>
MatrixCSR<Data>::MatrixCSR(const MatrixCSR& mat) {
    Node** current = &head;
    Node* currentMat = mat.head;
    Vector<Node**> tmpVec(mat.rows+1);
    for (unsigned long i=0; i<mat.rows; i++)
    {
        tmpVec[i] = current;
        if (mat.rowVec[i] != mat.rowVec[i+1])
            while (currentMat != *(mat.rowVec[i+1]) && currentMat != nullptr)
            {
                *current = new Node(*currentMat);
                current = &((*current)->next);
                currentMat = currentMat->next;
            }
    }
    tmpVec[mat.rows] = current;
    std::swap(tmpVec, rowVec);
    rows = mat.rows;
    columns = mat.columns;
    size = mat.size;
}

template <typename Data>
MatrixCSR<Data>::MatrixCSR(MatrixCSR&& mat) noexcept : MatrixCSR() {
    std::swap(rows, mat.rows);
    std::swap(columns, mat.columns);
    std::swap(size, mat.size);
    std::swap(head, mat.head);
    std::swap(rowVec, mat.rowVec);
    mat.rowVec[0] = &mat.head;
    for (unsigned long i=0; i<=rows && *rowVec[i] == mat.head; i++)
        rowVec[i] = &head;
}

template <typename Data>
MatrixCSR<Data>& MatrixCSR<Data>::operator=(const MatrixCSR& mat) {
    if (*this != mat)
    {
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
        std::swap(size, mat.size);
        std::swap(head, mat.head);
        std::swap(rowVec, mat.rowVec);
        for (unsigned long i=0; i<=rows && *rowVec[i] == mat.head; i++)
            rowVec[i] = &head;
        for (unsigned long i=0; i<=mat.rows && *mat.rowVec[i] == head; i++)
            mat.rowVec[i] = &mat.head;
    }
    return *this;
}

template <typename Data>
bool MatrixCSR<Data>::operator==(const MatrixCSR& mat) const noexcept {
    if (size == mat.size)
    {
        unsigned long i = 0;
        if (rowVec.Size() != mat.rowVec.Size())
            return false;
        else
            while (*rowVec[i] != nullptr)
            {
                if (rowVec[i] != rowVec[i+1])
                {
                    if (mat.rowVec[i] == mat.rowVec[i+1])
                        return false;
                }
                else
                    if (mat.rowVec[i] != mat.rowVec[i+1])
                        return false;
                
                i++;
            }
        return List<std::pair<Data, unsigned long>>::operator==(mat);
    }
    else
        return false;
}

template <typename Data>
inline bool MatrixCSR<Data>::operator!=(const MatrixCSR& mat) const noexcept {
    return !(*this == mat);
}

template <typename Data>
void MatrixCSR<Data>::RowResize(const unsigned long newRows) {
    if (newRows == 0)
    {
        List<std::pair<Data, unsigned long>>::Clear();
        rowVec.Resize(1);
    }
    else if (newRows < rows)
    {
        Node* nextNode;
        Node* toDel = *rowVec[newRows];
        while (toDel != nullptr)
        {
            nextNode = toDel->next;
            delete toDel;
            toDel = nextNode;
        }
        rowVec.Resize(newRows+1);
        *rowVec[newRows] = nullptr;
    }
    else if (newRows > rows)
    {
        rowVec.Resize(newRows+1);
        for (unsigned long i=(rows+1); i<=newRows; i++)
            rowVec[i] = rowVec[rows];
    }
    rows = newRows;
}

template <typename Data>
void MatrixCSR<Data>::ColumnResize(const unsigned long newCols) {
    if (newCols == 0)
    {
        List<std::pair<Data, unsigned long>>::Clear();
        for (unsigned long i=1; i<=rows; i++)
            rowVec[i] = rowVec[0];
    }
    else if (newCols < columns)
    {
        for (unsigned long i=0; i<rows; i++)
        {
            Node** current = rowVec[i];
            while (current != rowVec[i+1] && (*current)->Element.second < newCols)
                current = &((*current)->next);

            if (current != rowVec[i+1])
            {
                Node* nextNode;
                Node* nod = *current;
                while (nod != *rowVec[i+1])
                {
                    nextNode = nod->next;
                    delete nod;
                    nod = nextNode;
                }
                *current = nod;
            }
        }
    }
    columns = newCols;
}

template <typename Data>
bool MatrixCSR<Data>::ExistsCell(const unsigned long row, const unsigned long col) const noexcept {
    if (row < rows && col < columns)
    {
        Node* nod = *(rowVec[row]);
        while (nod != *(rowVec[row+1]) && nod->Element.second <= col)
        {
            if (nod->Element.second == col)
                return true;

            nod = nod->next;
        }
        return false;
    }
    else
        return false;
}

template <typename Data>
Data& MatrixCSR<Data>::operator()(const unsigned long row, const unsigned long col) {
    if (row < rows && col < columns)
    {

    }
    else
        throw std::out_of_range("Access at (row,column) ("+ std::to_string(row) + "," + std::to_string(col) + 
                                "); matrix size: " + std::to_string(rows) + "x" + std::to_string(columns) + ".");
} 

template <typename Data>
const Data& MatrixCSR<Data>::operator()(const unsigned long row, const unsigned long col) const {
    if (row < rows && col < columns)
    {
        Node* nod = *(rowVec[row]);
        while (nod != *(rowVec[row+1]) && nod->Element.second <= col)
        {
            if (nod->Element.second == col)
                return nod->Element.first;

            nod = nod->next;
        }
        throw std::length_error("The cell is empty");
    }
    else
        throw std::out_of_range("Access at (row,column) ("+ std::to_string(row) + "," + std::to_string(col) + 
                                "); matrix size: " + std::to_string(rows) + "x" + std::to_string(columns) + ".");
}

template <typename Data>
void MatrixCSR<Data>::Clear() {
    List<std::pair<Data, unsigned long>>::Clear();
    rowVec.Resize(1);
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
