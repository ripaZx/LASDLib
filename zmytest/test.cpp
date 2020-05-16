#include <iostream>
#include <random>

#include "test.hpp"


/* ************************************************************************** */
void PrintMenu()
{
  std::cout<<"1) Visualizzazione di un elemento dalla struttura\n";
  std::cout<<"2) Visualizzazione di tutta la struttura\n";
  std::cout<<"3) Controllo di esistenza di un valore\n";
  std::cout<<"4) LASD test\n";
}

void StructureChoice(char& sInput, char& tInput)
{
    std::cout<<"\nSelezionare la struttura su cui lavorare:\n\t[V]ettore\t[L]ista...\n";
    std::cin>>sInput;
    sInput = toupper(sInput);
    while(sInput != 'V' && sInput != 'L')
    {
        std::cout<<"\nInserire V oppure L...\n";
        std::cin.clear();
        std::cin>>sInput;
        sInput = toupper(sInput);
    }


    std::cout<<"\nSelezionare il tipo di dato da trattare:\n\t[I]nt\t[F]loat\t[D]ouble\t[C]har...\n";
    std::cin>>tInput;
    tInput = toupper(tInput);
    while(tInput != 'I' && tInput != 'F' && tInput != 'D' && tInput != 'C')
    {
        std::cout<<"\nInserire uno tra: I, F, D, C...\n";
        std::cin.clear();
        std::cin>>tInput;
        tInput = toupper(tInput);
    }
}

template <typename Data>
void RandPopulate(lasd::Vector<Data> vec)
{
    unsigned long int n;
    std::default_random_engine gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(1, 100);
    std::cout<<"\nInserire il numero di elementi con cui popolare la struttura...\n";
    std::cin>>n;
    for (int i = 0; i < n; i++)
    {
         Data elem = static_cast<Data>(dist(gen));
        vec[i] = elem;
    }
}

template <typename Data>
void RandPopulate(lasd::List<Data> lis)
{
    unsigned long int n;
    std::default_random_engine gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(1, 100);
    std::cout<<"\nInserire il numero di elementi con cui popolare la struttura...\n";
    std::cin>>n;
    for (int i = 0; i < n; i++)
    {
        Data elem = static_cast<Data>(dist(gen));
        lis[i] = elem;
    }
}

template <typename Data>
void PrintElement(lasd::Vector<Data> vec)
{    
    unsigned long int index;
    std::cout<<"Inserire l'indice da stampare a schermo...\n";
    std::cin>>index;
    std::cout<<"L'elemento all'indice: " << index << " è: " << vec[index - 1];
}

template <typename Data>
void PrintElement(lasd::List<Data> lis)
{
    unsigned long int index;
    std::cout<<"Inserire l'indice da stampare a schermo...\n";
    std::cin>>index;
    std::cout<<"L'elemento all'indice: " << index << " è: " << lis[index - 1];
}

template void RandPopulate<int>(lasd::Vector<int>);
template void RandPopulate<float>(lasd::Vector<float>);
template void RandPopulate<double>(lasd::Vector<double>);
template void RandPopulate<char>(lasd::Vector<char>);

template void RandPopulate<int>(lasd::List<int>);
template void RandPopulate<float>(lasd::List<float>);
template void RandPopulate<double>(lasd::List<double>);
template void RandPopulate<char>(lasd::List<char>);

template void PrintElement<int>(lasd::Vector<int>);
template void PrintElement<float>(lasd::Vector<float>);
template void PrintElement<double>(lasd::Vector<double>);
template void PrintElement<char>(lasd::Vector<char>);

template void PrintElement<int>(lasd::List<int>);
template void PrintElement<float>(lasd::List<float>);
template void PrintElement<double>(lasd::List<double>);
template void PrintElement<char>(lasd::List<char>);
