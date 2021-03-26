
#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Vector : virtual public LinearContainer<Data>,
               virtual public MappableContainer<Data>,
               virtual public FoldableContainer<Data> { 

private:


protected:

using LinearContainer<Data>::size;

Data* Elements = nullptr;

public:

  // Default constructor
  Vector()  = default;

  /* ************************************************************************ */

  // Specific constructors
  Vector(const unsigned long); // A vector with a given initial dimension
  Vector(const LinearContainer<Data>&); // A vector obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  Vector(const Vector&);

  // Move constructor
  Vector(Vector&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  // ~Vector() specifiers;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;

  // Move assignment
  // type operator=(argument) specifiers;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  // type operator!=(argument) specifiers;

  /* ************************************************************************ */

  // Specific member functions

  // type Resize(argument) specifiers; // Resize the vector to a given size

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  // type Clear() specifiers; // Override Container member

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  // type Front() specifiers; // Override LinearContainer member (must throw std::length_error when empty)
  // type Back() specifiers; // Override LinearContainer member (must throw std::length_error when empty)

  // type operator[](argument) specifiers; // Override LinearContainer member (must throw std::out_of_range when out of range)

  /* ************************************************************************ */

  // Specific member functions (inherited from MappableContainer)

  // using typename MappableContainer<Data>::MapFunctor;

  // type MapPreOrder(arguments) specifiers; // Override MappableContainer member
  // type MapPostOrder(arguments) specifiers; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from FoldableContainer)

  // using typename FoldableContainer<Data>::FoldFunctor;

  // type FoldPreOrder(arguments) specifiers; // Override FoldableContainer member
  // type FoldPostOrder(arguments) specifiers; // Override FoldableContainer member

};

/* ************************************************************************** */

}

#include "vector.cpp"

#endif
