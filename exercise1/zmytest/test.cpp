#include "test.hpp"

#include <iostream>
#include <random>

void StructureSelection(char& sInput, char& tInput) {
    std::cout<< std::endl <<"Selezionare la struttura su cui lavorare:"<< std::endl <<"\t[V]ettore\t[L]ista..."<< std::endl;
    std::cin>>sInput;
    sInput = toupper(sInput);
    while(sInput != 'V' && sInput != 'L')
    {
        std::cout<< std::endl <<"Inserire V oppure L..."<< std::endl;
        std::cin.clear();
        std::cin>>sInput;
        sInput = toupper(sInput);
    }

    std::cout<< std::endl <<"Selezionare il tipo di dato da trattare:"<< std::endl <<"\t[I]nt\t[F]loat\t[D]ouble\t[C]har..."<< std::endl;
    std::cin>>tInput;
    tInput = toupper(tInput);
    while(tInput != 'I' && tInput != 'F' && tInput != 'D' && tInput != 'C')
    {
        std::cout<< std::endl <<"Inserire uno tra: I, F, D, C..."<< std::endl;
        std::cin.clear();
        std::cin>>tInput;
        tInput = toupper(tInput);
    }
}

template <typename Data>
void RandPopulate(lasd::LinearContainer<Data> con) {
    unsigned long n;
    std::default_random_engine gen(std::random_device{}());
    std::uniform_int_distribution<Data> dist(1, 100);
    std::cout<< std::endl << "Inserire il numero di elementi con cui popolare la struttura..."<< std::endl;
    std::cin>>n;
    for (unsigned long i=0; i<n; i++)
    {
        con[i] = (dist(gen));
    }
}

template <typename Data>
void PrintElement(lasd::LinearContainer<Data> con) {
    char input;
    std::cout<< std::endl << "Seleziona se stampare il primo, l'ultimo o un indice:";
    std::cout<< std::endl << "\t[P]rimo\t[U]ltimo\t[I]ndice";
    input = toupper(input);
    while(input != 'P' && input != 'U' && input != 'I')
    {
        std::cout<<"Inserire uno tra: P, U, I..."<< std::endl;
        std::cin.clear();
        std::cin>>input;
        input = toupper(input);
    }
    if (input == 'P')
        con.Front();
    else if (input == 'U')
        con.Back();
    else if (input == 'I')
    {
        unsigned long i;
        do 
        {
            std::cout<< std::endl << "Inserire l'indice da visualizzare...";
            std::cin>>i;
            if (cin.fail())
                std::cout<< std::endl << "Inserire un numero...";
        }
        while (!cin.fail());
        std::cout<< std::endl << con[i];
    }
}
