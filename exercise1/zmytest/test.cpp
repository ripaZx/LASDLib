#include "test.hpp"

#include <iostream>
#include <string>
#include <random>
#include <limits>
#include <iomanip>

void StructureSelection(char& sInput, char& tInput) {
    std::cout<< std::endl <<"Selezionare la struttura su cui lavorare:"<< std::endl <<"    [V]ettore    [L]ista..."<< std::endl;
    std::cin>>sInput;
    sInput = toupper(sInput);
    while(sInput != 'V' && sInput != 'L')
    {
        std::cout<< std::endl <<"Inserire V oppure L..."<< std::endl;
        std::cin.clear();
        std::cin>>sInput;
        sInput = toupper(sInput);
    }

    std::cout<< std::endl <<"Selezionare il tipo di dato da trattare:"<< std::endl <<"    [I]nt    [F]loat    [D]ouble    [C]har    [S]tring..."<< std::endl;
    std::cin>>tInput;
    tInput = toupper(tInput);
    while(tInput != 'I' && tInput != 'F' && tInput != 'D' && tInput != 'C' && tInput != 'S')
    {
        std::cout<< std::endl <<"Inserire uno tra: I, F, D, C, S..."<< std::endl;
        std::cin.clear();
        std::cin>>tInput;
        tInput = toupper(tInput);
    }
}

template <typename Data>
void RandPopulateVecInt(lasd::LinearContainer<Data>& con, const unsigned long& n) {
    std::default_random_engine gen(std::random_device{}());
    std::uniform_int_distribution<Data> dist(1, 100);
    for (unsigned long i=0; i<n; i++)
        con[i] = (dist(gen));
}

template <typename Data>
void RandPopulateVecReal(lasd::LinearContainer<Data>& con, const unsigned long& n) {
    std::default_random_engine gen(std::random_device{}());
    std::uniform_real_distribution<Data> dist(1, 100);
    for(unsigned long i=0; i<n; i++)
        con[i] = (dist(gen));
}

template <typename Data>
void RandPopulateVecChar(lasd::LinearContainer<Data>& con, const unsigned long& n) {
    std::default_random_engine gen(std::random_device{}());
    std::uniform_int_distribution<Data> dist(33, 126);
    for(unsigned long i=0; i<n; i++)
        con[i] = static_cast<char>(dist(gen));
}

template <typename Data>
void RandPopulateVecString(lasd::LinearContainer<Data>& con, const unsigned long& n) {
    std::default_random_engine gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(33, 127);
    std::default_random_engine lenGen(std::random_device{}());
    std::uniform_int_distribution<int> lenDist(1, 16);
    for (unsigned long i=0; i<n; i++)
    {
        for (int j=0; j<(lenDist(lenGen)); j++)
            con[i].append(1, static_cast<char>(dist(gen)));
    }
}

template <typename Data>
void PrintElement(const lasd::LinearContainer<Data>& con) {
    char input;
    bool end = false;
    while (!end)
    {
        std::cout<< std::endl << "Selezionare quale elemento stampare:"<< std::endl << "    [P]rimo    [U]ltimo    [I]ndice    [E] per uscire" << std::endl;
        std::cin>>input;
        input = toupper(input);
        while(input != 'P' && input != 'U' && input != 'I' && input != 'E')
        {
            std::cout<< std::endl <<"Inserire uno tra: P, U, I, E..."<< std::endl;
            std::cin.clear();
            std::cin>>input;
            input = toupper(input);
        }
        if (input == 'E')
            end = true;
        else if (input == 'P')
            std::cout<< "Il primo elemento della struttura è: " << std::setprecision(21) << con.Front() << std::endl;
        else if (input == 'U')
            std::cout<< "L'ultimo elemento della struttura è: " << std::setprecision(21) << con.Back() << std::endl;
        else if (input == 'I')
        {
            unsigned long i;
            do 
            {
                std::cout<< std::endl << "Inserire l'indice da visualizzare..." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin>>i;
            }
            while (std::cin.fail());
            std::cout<< std::endl << "Elemento all'indice " << i << ": " << std::setprecision(21) << con[i] << std::endl;
        }
    }
}


template <typename Data>
void MapPrint(const Data& dat, void* _) {
  std::cout<< std::setprecision(21) << dat << " ";
}

template <typename Data>
void ElemExists(const lasd::FoldableContainer<Data>& con) {
    Data elem;
    do
    {
        std::cout<< std::endl << "Verificare l'esistenza di quale elemento?" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin>>elem;
    } while (std::cin.fail());
        std::cout<< std::endl <<"L'elemento "<< elem << (con.Exists(elem) ? "" : " non") << " è presente." << std::endl;
}


void testMenu() {
    char tInput, sInput;
    unsigned long n;
    StructureSelection(sInput, tInput);
    std::cout<< std::endl << "Inserire il numero di elementi con cui popolare la struttura..."<< std::endl;
    std::cin>>n;
    std::cin.clear();
    if (sInput == 'V')
    {
        if(tInput == 'I')
        {
            lasd::Vector<int> vec(n);
            RandPopulateVecInt(vec, n);
            PrintElement(vec);
            std::cout<< "Procedo alla stampa di tutti gli elementi della struttura: " << std::endl;
            vec.MapPreOrder(&MapPrint<int>, 0);
            ElemExists(vec);
        }
        else if (tInput == 'F')
        {
            lasd::Vector<float> vec(n);
            RandPopulateVecReal(vec, n);
            PrintElement(vec);
            std::cout<< "Procedo alla stampa di tutti gli elementi della struttura: " << std::endl;
            vec.MapPreOrder(&MapPrint<float>, 0);
            ElemExists(vec);
        }
        else if (tInput == 'D')
        {
            lasd::Vector<double> vec(n);
            RandPopulateVecReal(vec, n);
            PrintElement(vec);
            std::cout<< "Procedo alla stampa di tutti gli elementi della struttura: " << std::endl;
            vec.MapPreOrder(&MapPrint<double>, 0);
            ElemExists(vec);
        }
        else if (tInput == 'C')
        {
            lasd::Vector<char> vec(n);
            RandPopulateVecChar(vec, n);
            PrintElement(vec);
            std::cout<< "Procedo alla stampa di tutti gli elementi della struttura: " << std::endl;
            vec.MapPreOrder(&MapPrint<char>, 0);
            ElemExists(vec);
        }
        else if (tInput == 'S')
        {
            lasd::Vector<std::string> vec(n);
            RandPopulateVecString(vec, n);
            PrintElement(vec);
            std::cout<< "Procedo alla stampa di tutti gli elementi della struttura: " << std::endl;
            vec.MapPreOrder(&MapPrint<std::string>, 0);
            ElemExists(vec);
        }
    }
    // else if (sInput == 'V')
    // {
    //     if(tInput == 'I')
    //     {
    //         lasd::List<int> lis;
    //         RandPopulateInt(lis, n);
    //         PrintElement(lis);
    //     }
    //     else if (tInput == 'F')
    //     {
    //         lasd::Vector<float> vec(n);
    //         RandPopulateReal(vec, n);
    //         PrintElement(vec);
    //     }
    //     else if (tInput == 'D')
    //     {
    //         lasd::Vector<double> vec(n);
    //         RandPopulateReal(vec, n);
    //         PrintElement(vec);
    //     }
    //     else if (tInput == 'C')
    //     {
    //         lasd::Vector<char> vec(n);
    //         RandPopulateInt(vec, n);
    //         PrintElement(vec);
    //     }
    // }
    else
        std::cout << "Roba ancora da implementare" << std::endl;
}