
#ifndef MYTEST_HPP
#define MYTEST_HPP

#include "../list/list.hpp"
#include "../vector/vector.hpp"

/* ************************************************************************** */

void StructureSelection(char& sInput, char& tInput);

template <typename Data>
void RandPopulate(lasd::LinearContainer<Data> con);

template <typename Data>
void PrintElement(lasd::LinearContainer<Data> con);

void testMenu();

/* ************************************************************************** */

#endif
