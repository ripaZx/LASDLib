
#include "test.hpp"

#include <iostream>
#include <random>

void StructureSelection(char& iInput, char& tInput) {
    std::cout<< std::endl <<"Selezionare l'implementazione su cui lavorare:"<< std::endl <<"    [V]ettore    [L]ista..."<< std::endl;
    std::cin.clear();
    std::cin>>iInput;
    iInput = std::toupper(iInput);
    while(iInput != 'V' && iInput != 'L')
    {
        std::cout<< std::endl <<"Inserire V oppure L..."<< std::endl;
        std::cin.clear();
        std::cin>>iInput;
        iInput = std::toupper(iInput);
    }

    std::cout<< std::endl <<"Selezionare il tipo di dato da trattare:"<< std::endl <<"    [I]nt    [D]ouble    [S]tring..."<< std::endl;
    std::cin>>tInput;
    tInput = std::toupper(tInput);
    while(tInput != 'I' && tInput != 'D' && tInput != 'S')
    {
        std::cout<< std::endl <<"Inserire uno tra: I, D, S..."<< std::endl;
        std::cin.clear();
        std::cin>>tInput;
        tInput = std::toupper(tInput);
    }
}

template <typename Data>
void RandPopulateVecInt(lasd::Vector<Data>& vec, const unsigned long& n) {
    std::default_random_engine gen(std::random_device{}());
    std::uniform_int_distribution<Data> dist(1, 100);
    for (unsigned long i=0; i<n; i++)
        vec[i] = (dist(gen));
}

template <typename Data>
void RandPopulateVecReal(lasd::Vector<Data>& vec, const unsigned long& n) {
    std::default_random_engine gen(std::random_device{}());
    std::uniform_real_distribution<Data> dist(1, 99);
    for(unsigned long i=0; i<n; i++)
        vec[i] = (dist(gen));
}

template <typename Data>
void RandPopulateVecString(lasd::Vector<Data>& vec, const unsigned long& n) {
    std::default_random_engine gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(97, 122);
    std::default_random_engine lenGen(std::random_device{}());
    std::uniform_int_distribution<int> lenDist(1, 16);
    for (unsigned long i=0; i<n; i++)
    {
        for (int j=0; j<(lenDist(lenGen)); j++)
            vec[i].append(1, static_cast<char>(dist(gen)));
    }
}

void PrintMenu(char& choice) {
    std::cout<< std::endl <<"Selezionare una funzione:" << std::endl << "[V]isualizzazione    [E]sistenza    [F]old    [M]ap    [Q]uit    " << std::endl;
    std::cin.clear();
    std::cin>>choice;
    choice = std::toupper(choice);
    while(choice != 'V' && choice != 'E' && choice != 'F' && choice != 'M' && choice != 'Q')
    {
        std::cout<< std::endl <<"Inserire uno tra V, E, F, M oppure Q..."<< std::endl;
        std::cin.clear();
        std::cin>>choice;
        choice = std::toupper(choice);
    }
}

void testMenu() {
    char iInput, tInput;
    unsigned long n;
    bool end = false;
    char choice;
    std::cout<< std::endl << "Quale test si vuole eseguire?" << std::endl << "[L]asdTest    [M]yTest    [E]xit" << std::endl;
    std::cin>> tInput;
    tInput = std::toupper(tInput);
    while (tInput != 'L' && tInput != 'M' && tInput != 'E')
    {
        std::cout<< std::endl <<"Inserire L, M oppure E..."<< std::endl;
        std::cin.clear();
        std::cin>>tInput;
        tInput = std::toupper(tInput);
    }
    if (tInput == 'L')
        lasdtest();
    else if (tInput == 'M')
    {
        StructureSelection(iInput, tInput);
        do
        {
            std::cout<< std::endl << "Inserire il numero di elementi con cui popolare la struttura..."<< std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin>>n;
        } while (std::cin.fail());
        
    }
    else
        std::cout << std::endl << "Goodbye!" << std::endl;
}