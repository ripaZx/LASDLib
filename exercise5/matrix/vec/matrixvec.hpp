
#ifndef MATRIXVEC_HPP
#define MATRIXVEC_HPP

/* ************************************************************************** */

#include "../matrix.hpp"

#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class MatrixVec : virtual public Matrix<Data>,
                  protected Vector<Data> {

private:

  // ...

protected:

  using Matrix<Data>::rows;
  using Matrix<Data>::columns;

  // ...

public:

  // Default constructor
  MatrixVec() = default;

  /* ************************************************************************ */

  // Specific constructors
  MatrixVec(const unsigned long, const unsigned long); // A matrix of some specified dimension

  /* ************************************************************************ */

  // Copy constructor
  MatrixVec(const MatrixVec&);

  // Move constructor
  MatrixVec(MatrixVec&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~MatrixVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  MatrixVec& operator=(const MatrixVec&);

  // Move assignment
  MatrixVec& operator=(MatrixVec&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const MatrixVec&) const noexcept;
  bool operator!=(const MatrixVec&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Matrix)

  // type RowResize() specifiers; // Override Matrix member
  // type ColumnResize() specifiers; // Override Matrix member

  // type ExistsCell() specifiers; // Override Matrix member (should not throw exceptions)

  // type operator()() specifiers; // Override Matrix member (mutable access to the element; throw out_of_range when out of range)
  // type operator()() specifiers; // Override Matrix member (immutable access to the element; throw out_of_range when out of range and length_error when not present)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  // type Clear() specifiers; // Override Container member

  /* ************************************************************************ */

  // Specific member functions (inherited from MappableContainer)

  // type MapPreOrder(arguments) specifiers; // Override MappableContainer member
  // type MapPostOrder(arguments) specifiers; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from FoldableContainer)

  // type FoldPreOrder(arguments) specifiers; // Override FoldableContainer member
  // type FoldPostOrder(arguments) specifiers; // Override FoldableContainer member

};

/* ************************************************************************** */

}

#include "matrixvec.cpp"

#endif
