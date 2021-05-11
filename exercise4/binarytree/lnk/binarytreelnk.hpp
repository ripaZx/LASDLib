
#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeLnk : virtual public BinaryTree<Data> {

private:

protected:

  using BinaryTree<Data>::size;

  struct NodeLnk : virtual public BinaryTree<Data>::Node {

  private:

  protected:

    Data Elem;
    NodeLnk* left = nullptr;
    NodeLnk* right = nullptr;

  public:

    friend class BinaryTreeLnk<Data>;

    // Specific constructors
    NodeLnk(const Data&);
    NodeLnk(Data&&) noexcept;

    // Copy Constructor
    NodeLnk(const NodeLnk&);

    //Move Constructor
    NodeLnk(NodeLnk&&) noexcept;

    // Destructor
    ~NodeLnk();

    /* ********************************************************************** */

    // Copy assignment
    NodeLnk& operator=(const NodeLnk&);

    // Move assignment
    NodeLnk& operator=(NodeLnk&&) noexcept;

    /* ********************************************************************** */

    // Specific member functions

    const Data& Element() const noexcept override;
    Data& Element() noexcept override;

    bool HasLeftChild() const noexcept override;
    bool HasRightChild() const noexcept override;

    NodeLnk& LeftChild() const override;
    NodeLnk& RightChild() const override;

  };

  NodeLnk* root = nullptr;

public:

  // Default constructor
  BinaryTreeLnk() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeLnk(const LinearContainer<Data>&);

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeLnk(const BinaryTreeLnk&);

  // Move constructor
  BinaryTreeLnk(BinaryTreeLnk&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BinaryTreeLnk();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeLnk& operator=(const BinaryTreeLnk&);

  // Move assignment
  BinaryTreeLnk& operator=(BinaryTreeLnk&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeLnk&) const noexcept;
  inline bool operator!=(const BinaryTreeLnk&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  NodeLnk& Root() const override;

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override;

};

/* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif
