
#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

#include "../iterator/iterator.hpp"

// #include "..."

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTree : virtual public InOrderMappableContainer<Data>,
                   virtual public BreadthMappableContainer<Data>,
                   virtual public InOrderFoldableContainer<Data>,
                   virtual public BreadthFoldableContainer<Data> {

private:

protected:

  using BreadthMappableContainer<Data>::size;

  Node* root;

public:

  struct Node {

  private:

  protected:

    Data Element;
    Node* left = nullptr;
    Node* right = nullptr;

  public:

    friend class BinaryTree<Data>;

    /* ********************************************************************** */

    // Destructor
    virtual ~Node() = default;

    /* ********************************************************************** */

    // Copy assignment
    Node& operator=(const Node&) = delete;

    // Move assignment
    Node& operator=(Node&&) noexcept = delete;

    /* ********************************************************************** */

    // Comparison operators
    bool operator==(const Node&) const noexcept;
    inline bool operator!=(const Node&) const noexcept;

    /* ********************************************************************** */

    // Specific member functions

    virtual Data& Element() const noexcept = 0;
    virtual const Data& Element() const noexcept = 0;

    bool IsLeaf() const noexcept;
    virtual bool HasLeftChild() const noexcept = 0;
    virtual bool HasRightChild() const noexcept = 0;

    virtual Node& LeftChild() = 0;
    virtual Node& RightChild() = 0;

  };

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTree() = default;

  /* ************************************************************************ */

  // Copy assignment
  tBinaryTree& operator=(const BinaryTree&) = delete;

  // Move assignment
  BinaryTree& operator=(BinaryTree&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTree&) const noexcept;
  inline bool operator!=(const BinaryTree&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  virtual Node& Root() const; // (concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFunctor;

  void MapPreOrder(const MapFunctor, void*) override;
  void MapPostOrder(const MapFunctor, void*) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from FoldableContainer)

  using typename FoldableContainer<Data>::FoldFunctor;

  void FoldPreOrder(const FoldFunctor, const void*, void*) const override;
  void FoldPostOrder(const FoldFunctor, const void*, void*) const override;

  /* ************************************************************************ */

  // Specific member functions (inherited from InOrderMappableContainer)

  void MapInOrder(const MapFunctor, void*) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from InOrderFoldableContainer)

  void FoldInOrder(const FoldFunctor, const void*, void*) const override;

  /* ************************************************************************ */

  // Specific member functions (inherited from BreadthMappableContainer)

  void MapBreadth(const MapFunctor, void*) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from BreadthFoldableContainer)

  void FoldBreadth(const FoldFunctor, const void*, void*) const override;

protected:

  // Auxiliary member functions (for MappableContainer)

  void MapPreOrder(const MapFunctor, void*, Node*);
  void MapPostOrder(const MapFunctor, void*, Node*);

  /* ************************************************************************ */

  // Auxiliary member functions (for FoldableContainer)

  void FoldPreOrder(const FoldFunctor, const void*, void*, const Node*) const; // Accessory function executing from one node of the tree
  void FoldPostOrder(const FoldFunctor, const void*, void*, const Node*) const; // Accessory function executing from one node of the tree

  /* ************************************************************************ */

  // Auxiliary member functions (for InOrderMappableContainer)

  void MapInOrder(const MapFunctor, void*, Node*); // Accessory function executing from one node of the tree

  /* ************************************************************************ */

  // Auxiliary member functions (for InOrderFoldableContainer)

  void FoldInOrder(const FoldFunctor, const void*, void*, const Node*) const; // Accessory function executing from one node of the tree

  /* ************************************************************************ */

  // Auxiliary member functions (for BreadthMappableContainer)

  void MapBreadth(const MapFunctor, void*, Node*); // Accessory function executing from one node of the tree

  /* ************************************************************************ */

  // Auxiliary member functions (for BreadthFoldableContainer)

  void FoldBreadth(const FoldFunctor, const void*, void*, const Node*) const; // Accessory function executing from one node of the tree

};

/* ************************************************************************** */

template <typename Data>
class BTPreOrderIterator { // Must extend ForwardIterator<Data>

private:

  // ...

protected:

  // ...

public:

  // Specific constructors
  // BTPreOrderIterator(argument) specifiers; // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  // BTPreOrderIterator(argument) specifiers;

  // Move constructor
  // BTPreOrderIterator(argument) specifiers;

  /* ************************************************************************ */

  // Destructor
  // ~BTPreOrderIterator() specifiers;

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

  // Specific member functions (inherited from Iterator)

  // type operator*() specifiers; // (throw std::out_of_range when terminated)

  // type Terminated() specifiers; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  // type operator++() specifiers; // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class BTPostOrderIterator { // Must extend ForwardIterator<Data>

private:

  // ...

protected:

  // ...

public:

  // Specific constructors
  // BTPostOrderIterator(argument) specifiers; // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  // BTPostOrderIterator(argument) specifiers;

  // Move constructor
  // BTPostOrderIterator(argument) specifiers;

  /* ************************************************************************ */

  // Destructor
  // ~BTPostOrderIterator() specifiers;

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

  // Specific member functions (inherited from Iterator)

  // type operator*() specifiers; // (throw std::out_of_range when terminated)

  // type Terminated() specifiers; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  // type operator++() specifiers; // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class BTInOrderIterator { // Must extend ForwardIterator<Data>

private:

  // ...

protected:

  // ...

public:

  // Specific constructors
  // BTInOrderIterator(argument) specifiers; // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  // BTInOrderIterator(argument) specifiers;

  // Move constructor
  // BTInOrderIterator(argument) specifiers;

  /* ************************************************************************ */

  // Destructor
  // ~BTInOrderIterator() specifiers;

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

  // Specific member functions (inherited from Iterator)

  // type operator*() specifiers; // (throw std::out_of_range when terminated)

  // type Terminated() specifiers; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  // type operator++() specifiers; // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class BTBreadthIterator { // Must extend ForwardIterator<Data>

private:

  // ...

protected:

  // ...

public:

  // Specific constructors
  // BTBreadthIterator(argument) specifiers; // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  // BTBreadthIterator(argument) specifiers;

  // Move constructor
  // BTBreadthIterator(argument) specifiers;

  /* ************************************************************************ */

  // Destructor
  // ~BTBreadthIterator() specifiers;

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

  // Specific member functions (inherited from Iterator)

  // type operator*() specifiers; // (throw std::out_of_range when terminated)

  // type Terminated() specifiers; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  // type operator++() specifiers; // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */

}

#include "binarytree.cpp"

#endif
