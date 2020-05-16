
#include <iostream>

#include "zmytest/test.hpp"
#include "zlasdtest/test.hpp"

int main()
{
  int input = 0;
  lasd::List<int>* list = new lasd::List<int>();

  for (int i = 0; i < 5; i++)
  {
    std::cout<<"Inserisci in cima: \n";
    std::cin>>input;
    list->InsertAtFront(input);
  }

  for (int i = 0; i < 5; i++)
  {
    std::cout<<"Inserisci in coda: \n";
    std::cin>>input;
    list->InsertAtBack(input);
  }

  std::cout<<"Stampa del valore in coda: \n";
  std::cout<< list->Back() << "\n";
  
  for (int i = 0; i < 10; i++)
  {
    std::cout<<"Stampa del valore in testa con eliminazione: \n";
    std::cout<< list->FrontNRemove() << "\n";
  }

  delete list;

  return 0;
}