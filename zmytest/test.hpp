
#ifndef ZMYTEST_HPP
#define ZMYTEST_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../vector/vector.hpp"
#include "../list/list.hpp"

/* ************************************************************************** */

void PrintMenu();
void StructureChoice(char&, char&);
template <typename Data>
void RandPopulate(lasd::Vector<Data>);
template <typename Data>
void RandPopulate(lasd::List<Data>);
template <typename Data>
void PrintElement(lasd::Vector<Data>);
template <typename Data>
void PrintElement(lasd::List<Data>);

#endif
