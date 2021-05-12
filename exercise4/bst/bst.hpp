
#ifndef BST_HPP
#define BST_HPP

/* ************************************************************************** */

#include "../binarytree/lnk/binarytreelnk.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BST : protected BinaryTreeLnk<Data> {

private:

protected:

  using Node = typename BinaryTreeLnk<Data>::NodeLnk;
  using BinaryTreeLnk<Data>::size;
  using BinaryTreeLnk<Data>::root;

public:

  // Default constructor
  BST() = default;

  /* ************************************************************************ */

  // Specific constructors
  BST(const LinearContainer<Data>&); // A bst obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  BST(const BST&);

  // Move constructor
  BST(BST&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BST() = default;

  /* ************************************************************************ */

  // Copy assignment
  BST& operator=(const BST&);

  // Move assignment
  BST& operator=(BST&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BST&) const noexcept;
  inline bool operator!=(const BST&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  void Insert(const Data&) noexcept; // Copy of the value
  void Insert(Data&&) noexcept; // Move of the value
  void Remove(const Data&) noexcept;

  const Data& Min() const; // (concrete function must throw std::length_error when empty)
  Data MinNRemove(); // (concrete function must throw std::length_error when empty)
  void RemoveMin(); // (concrete function must throw std::length_error when empty)

  const Data& Max() const; // (concrete function must throw std::length_error when empty)
  Data MaxNRemove(); // (concrete function must throw std::length_error when empty)
  void RemoveMax(); // (concrete function must throw std::length_error when empty)

  const Data& Predecessor(const Data&) const; // (concrete function must throw std::length_error when not found)
  Data PredecessorNRemove(const Data&); // (concrete function must throw std::length_error when not found)
  void RemovePredecessor(const Data&); // (concrete function must throw std::length_error when not found)

  const Data& Successor(const Data&) const; // (concrete function must throw std::length_error when not found)
  Data SuccessorNRemove(const Data&); // (concrete function must throw std::length_error when not found)
  void RemoveSuccessor(const Data&); // (concrete function must throw std::length_error when not found)

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  bool Exists(const Data&) const noexcept; // Override TestableContainer member

protected:

  // Auxiliary member functions

  Data DataNDelete(Node*);

  Node* Detach(Node*&) noexcept;

  Node* DetachMin(Node*&) noexcept;
  Node* DetachMax(Node*&) noexcept;

  Node* SkipOnLeft(Node*&) noexcept;
  Node* SkipOnRight(Node*&) noexcept;

  Node*& FindPointerToMin(Node*&) noexcept;
  Node* const& FindPointerToMin(Node* const&) const noexcept;
  Node*& FindPointerToMax(Node*&) noexcept;
  Node* const& FindPointerToMax(Node* const&) const noexcept;

  Node*& FindPointerTo(Node*&, const Data&) noexcept;
  Node* const& FindPointerTo(Node* const&, const Data&) const noexcept;

  Node*& FindPointerToPredecessor(Node*&, const Data&) noexcept;
  Node* const& FindPointerToPredecessor(Node* const&, const Data&) const noexcept;
  Node*& FindPointerToSuccessor(Node*&, const Data&) noexcept;
  Node* const& FindPointerToSuccessor(Node* const&, const Data&) const noexcept;

};

/* ************************************************************************** */

}

#include "bst.cpp"

#endif
