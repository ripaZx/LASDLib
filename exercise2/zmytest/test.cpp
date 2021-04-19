#include "test.hpp"

#include <iostream>
#include <random>

void StructureSelection(char& sInput, char& iInput, char& tInput) {
    std::cout<< std::endl <<"Selezionare l'implementazione su cui lavorare:"<< std::endl <<"    [S]tack    [Q]ueue..."<< std::endl;
    std::cin.clear();
    std::cin>>iInput;
    sInput = std::toupper(iInput);
    while(iInput != 'Q' && iInput != 'S')
    {
        std::cout<< std::endl <<"Inserire S oppure Q..."<< std::endl;
        std::cin.clear();
        std::cin>>iInput;
        iInput = std::toupper(iInput);
    }

    std::cout<< std::endl <<"Selezionare l'implementazione su cui lavorare:"<< std::endl <<"    [V]ettore    [L]ista..."<< std::endl;
    std::cin.clear();
    std::cin>>sInput;
    sInput = std::toupper(sInput);
    while(sInput != 'V' && sInput != 'L')
    {
        std::cout<< std::endl <<"Inserire V oppure L..."<< std::endl;
        std::cin.clear();
        std::cin>>sInput;
        sInput = std::toupper(sInput);
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
void RandPopulateQueueInt(lasd::Queue<Data>& que, const unsigned long& n) {
    std::default_random_engine gen(std::random_device{}());
    std::uniform_int_distribution<Data> dist(1, 100);
    for (unsigned long i=0; i<n; i++)
        que.Enqueue(dist(gen));
}

template <typename Data>
void RandPopulateStackInt(lasd::Stack<Data>& stk, const unsigned long& n) {
    std::default_random_engine gen(std::random_device{}());
    std::uniform_int_distribution<Data> dist(1, 100);
    for (unsigned long i=0; i<n; i++)
        stk.Push(dist(gen));
}

template <typename Data>
void RandPopulateQueueReal(lasd::Queue<Data>& que, const unsigned long& n) {
    std::default_random_engine gen(std::random_device{}());
    std::uniform_real_distribution<Data> dist(1, 99);
    for(unsigned long i=0; i<n; i++)
        que.Enqueue(dist(gen));
}

template <typename Data>
void RandPopulateStackReal(lasd::Stack<Data>& stk, const unsigned long& n) {
    std::default_random_engine gen(std::random_device{}());
    std::uniform_real_distribution<Data> dist(1, 99);
    for(unsigned long i=0; i<n; i++)
        stk.Push(dist(gen));
}

template <typename Data>
void RandPopulateQueueString(lasd::Queue<Data>& que, const unsigned long& n) {
    std::default_random_engine gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(97, 122);
    std::default_random_engine lenGen(std::random_device{}());
    std::uniform_int_distribution<int> lenDist(1, 16);
    for (unsigned long i=0; i<n; i++)
    {
        std::string randString;
        for (int j=0; j<(lenDist(lenGen)); j++)
            randString.append(1, static_cast<char>(dist(gen)));
        
        que.Enqueue(randString);
    }
}

template <typename Data>
void RandPopulateStackString(lasd::Stack<Data>& stk, const unsigned long& n) {
    std::default_random_engine gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(97, 122);
    std::default_random_engine lenGen(std::random_device{}());
    std::uniform_int_distribution<int> lenDist(1, 16);
    for (unsigned long i=0; i<n; i++)
    {
        std::string randString;
        for (int j=0; j<(lenDist(lenGen)); j++)
            randString.append(1, static_cast<char>(dist(gen)));
        
        stk.Push(randString);
    }
}

void testMenu() {
    char sInput, iInput, tInput;
    unsigned long n;
    std::cout<< std::endl << "Quale test si vuole eseguire?" << std::endl << "[L]asdTest    [M]yTest    [E]xit";
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
        StructureSelection(sInput, iInput, tInput);
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