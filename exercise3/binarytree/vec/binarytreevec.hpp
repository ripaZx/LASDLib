
#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeVec : virtual public BinaryTree<Data> {

private:

protected:

  using BinaryTree<Data>::size;

  struct NodeVec : virtual public BinaryTree<Data>::Node {

  private:

  protected:

    Data Element;

    unsigned long index;
    Vector<NodeVec>* owningVec;
  
  public:

  NodeVec(const Data&);
  NodeVec(Data&&) noexcept;

  ~NodeVec();

  NodeVec& operator=(const NodeVec&);
  NodeVec& operator=(NodeVec&) noexcept;

  const Data& Element() const noexcept override;
  Data& Element() noexcept override;

  bool HasLeftChild() const noexcept override;
  bool HasRightChild() const noexcept override;

  NodeVec& LeftChild() override;
  NodeVec& RightChild() override;

  };

  Vector<NodeVec> btVec; 

public:

  // Default constructor
  BinaryTreeVec();

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeVec(const LinearContainer<Data>&); // A binary tree obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeVec(const BinaryTreeVec&);

  // Move constructor
  BinaryTreeVec(BinaryTreeVec&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BinaryTreeVec();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeVec& operator=(const BinaryTreeVec&);

  // Move assignment
  BinaryTreeVec& operator=(BinaryTreeVec&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeVec&) const noexcept;
  inline bool operator!=(const BinaryTreeVec&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  NodeVec& Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override; // Override Container member

};

/* ************************************************************************** */

}

#include "binarytreevec.cpp"

#endif
