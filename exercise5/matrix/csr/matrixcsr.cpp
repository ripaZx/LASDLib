
namespace lasd {

/* ************************************************************************** */

template <typename Data>
MatrixCSR<Data>::MatrixCSR() {
    rowVec.Resize(1);
    rowVec[0] = &head;
}

template <typename Data>
MatrixCSR<Data>::MatrixCSR(const unsigned long row, const unsigned long col) {
    rowVec.Resize(row+1);
}

/* ************************************************************************** */

}
