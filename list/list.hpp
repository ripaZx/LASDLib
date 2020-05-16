
#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class List : public LinearContainer<Data>, public SearchableContainer<Data> { // Should extend LinearContainer<Data> and SearchableContainer<Data>

private:

protected:

  using LinearContainer<Data>::size;

  struct Node
  {

    Data Element = 0;
    Node* next = nullptr;

    /* ********************************************************************** */

    // Specific constructors
    Node(const Data&);

    Node(const Data&, const Node&);

    // Copy constructor
    Node(const Node&);

    // Move constructor
    Node(Node&&) noexcept;

    /* ********************************************************************** */

    // Destructor
    ~Node();

    /* ********************************************************************** */

    // Comparison operators
    bool operator==(const Node&) const noexcept;
    bool operator!=(const Node&) const noexcept;

    /* ********************************************************************** */

    // Specific member functions

    // ...

  };

  Node* head = nullptr;

public:

  // Default constructor
  List();

  // Copy constructor
  List(const List&);

  // Move constructor
  List(List&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~List();

  /* ************************************************************************ */

  // Copy assignment
  List& operator=(const List&);

  // Move assignment
  List& operator=(List&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const List&) const noexcept;
  bool operator!=(const List&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  void RemoveFromFront(); // (might throw std::length_error)
  Data& FrontNRemove(); // (might throw std::length_error)
  void InsertAtFront(const Data&) noexcept; // Copy of the value
  void InsertAtFront(Data&&) noexcept; // Move of the value

  void InsertAtBack(const Data&) noexcept; // Copy of the value
  void InsertAtBack(Data&&) noexcept; // Move of the value

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override; // Override Container member

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  Data& Front() const override; // Override LinearContainer member (might throw std::length_error)
  Data& Back() const override; // Override LinearContainer member (might throw std::length_error)

  Data& operator[](const unsigned long int) override; // Override LinearContainer member (might throw std::out_of_range)

  /* ************************************************************************ */

  // Specific member functions (inherited from SearchableContainer)

  using typename SearchableContainer<Data>::MapFunctor;
  void MapPreOrder(MapFunctor, void*) override; // Override SearchableContainer member
  void MapPostOrder(MapFunctor, void*) override; // Override SearchableContainer member

  using typename SearchableContainer<Data>::FoldFunctor;
  void FoldPreOrder(FoldFunctor, const void*, void*) const override; // Override SearchableContainer member
  void FoldPostOrder(FoldFunctor, const void*, void*) const override; // Override SearchableContainer member

protected:

  void MapPreOrder(MapFunctor, void*, Node*); // Accessory function executing from one point of the list onwards
  void MapPostOrder(MapFunctor, void*, const Node*, Node*); // Accessory function executing from one point of the list onwards

  void FoldPreOrder(FoldFunctor, const void*, void*, Node*) const; // Accessory function executing from one point of the list onwards
  void FoldPostOrder(FoldFunctor, const void*, void*, const Node*, Node*) const; // Accessory function executing from one point of the list onwards

};

/* ************************************************************************** */

#include "list.cpp"

}

#endif
