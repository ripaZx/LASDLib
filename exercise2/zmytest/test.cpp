#include "test.hpp"

#include <iostream>
#include <random>

void StructureSelection(char& sInput, char& iInput, char& tInput) {
    std::cout<< std::endl <<"Selezionare la struttura su cui lavorare:"<< std::endl <<"    [S]tack    [Q]ueue..."<< std::endl;
    std::cin.clear();
    std::cin>>sInput;
    sInput = std::toupper(sInput);
    while(sInput != 'Q' && sInput != 'S')
    {
        std::cout<< std::endl <<"Inserire S oppure Q..."<< std::endl;
        std::cin.clear();
        std::cin>>sInput;
        sInput = std::toupper(sInput);
    }

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

template <typename Data>
void queueInsertion(lasd::Queue<Data>& que) {
    Data elem;
    do
    {
        std::cout<< std::endl <<"Quale elemento inserire nella coda?"<< std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin>>elem;
    } while(std::cin.fail());
    que.Enqueue(elem);
}

template <typename Data>
void stackInsertion(lasd::Stack<Data>& stk) {
    Data elem;
    do
    {
        std::cout<< std::endl <<"Quale elemento inserire nella pila?"<< std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin>>elem;
    } while(std::cin.fail());
    stk.Push(elem);
}

template <typename Data>
void queueRemoval(lasd::Queue<Data>& que) {
    char choice;
    std::cout<< std::endl <<"Si desidera rimuovere semplicemente o con visualizzazione?" << std::endl << "[R]imozione    [L]ettura e Rimozione" << std::endl;
    std::cin.clear();
    std::cin>>choice;
    choice = std::toupper(choice);
    while(choice != 'R' && choice != 'L')
    {
        std::cout << std::endl << "Inserire R oppure L..." << std::endl;
        std::cin.clear();
        std::cin>>choice;
        choice = toupper(choice);
    }
    if (choice == 'R')
    {
        try
        {
            que.Dequeue();
        }
        catch(const std::length_error& e)
        {
            std::cerr << e.what() << std::endl;
        }
        std::cout<< std::endl << "Rimozione effettuata" << std::endl;
    }
    else if (choice == 'L')
    {
        try
        {
            std::cout<< "Rimozione dell'elemento... " << que.HeadNDequeue() << " effettuata";
        }
        catch(const std::length_error& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
}

template <typename Data>
void stackRemoval(lasd::Stack<Data>& stk) {
    char choice;
    std::cout<< std::endl <<"Si desidera rimuovere semplicemente o con visualizzazione?" << std::endl << "[R]imozione    [L]ettura e Rimozione" << std::endl;
    std::cin.clear();
    std::cin>>choice;
    choice = std::toupper(choice);
    while(choice != 'R' && choice != 'L')
    {
        std::cout << std::endl << "Inserire R oppure L..." << std::endl;
        std::cin.clear();
        std::cin>>choice;
        choice = toupper(choice);
    }
    if (choice == 'R')
    {
        try
        {
            stk.Pop();
        }
        catch(const std::length_error& e)
        {
            std::cerr << e.what() << std::endl;
        }
        std::cout<< std::endl << "Rimozione effettuata" << std::endl;
    }
    else if (choice == 'L')
    {
        try
        {
            std::cout<< "Rimozione dell'elemento... " << stk.TopNPop() << " effettuata";
        }
        catch(const std::length_error& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
}

template <typename Data>
void queueHead(const lasd::Queue<Data>& que) {
    try
    {
        std::cout<< std::endl << "L'elemento in testa alla coda è: "<< que.Head() << std::endl;;
    }
    catch(const std::length_error& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

template <typename Data>
void stackHead(const lasd::Stack<Data>& stk) {
    try
    {
        std::cout<< std::endl << "L'elemento in testa allo stack è: "<< stk.Top() << std::endl;
    }
    catch(const std::length_error& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void PrintMenu(char& choice) {
    std::cout<< std::endl <<"Selezionare una funzione:" << std::endl << "[I]nserimento    [R]imozione    [H]ead    [V]uotezza    [D]imensione    [S]vuotamento    [Q]uit    " << std::endl;
    std::cin.clear();
    std::cin>>choice;
    choice = std::toupper(choice);
    while(choice != 'I' && choice != 'R' && choice != 'H' && choice != 'V' && choice != 'D' && choice != 'S' && choice != 'Q')
    {
        std::cout<< std::endl <<"Inserire uno tra I, R, H, V, D, S oppure Q..."<< std::endl;
        std::cin.clear();
        std::cin>>choice;
        choice = std::toupper(choice);
    }
}

void testMenu() {
    char sInput, iInput, tInput;
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
        StructureSelection(sInput, iInput, tInput);
        do
        {
            std::cout<< std::endl << "Inserire il numero di elementi con cui popolare la struttura..."<< std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin>>n;
        } while (std::cin.fail());
        if (sInput == 'S')
        {
            if (iInput == 'V')
            {
                if (tInput == 'I')
                {
                    lasd::StackVec<int> stkVec;
                    RandPopulateStackInt(stkVec, n);
                    while (!end)
                    {
                        PrintMenu(choice);
                        if (choice == 'I')
                            stackInsertion(stkVec);
                        else if (choice == 'R')
                            stackRemoval(stkVec);
                        else if (choice == 'H')
                            stackHead(stkVec);
                        else if (choice == 'V')
                            std::cout<< std::endl << "Lo stack" << (stkVec.Empty() ? "" : " non") << " è vuoto." << std::endl;
                        else if (choice == 'D')
                            std::cout<< std::endl << "Lo stack ha dimensione: " << stkVec.Size()<< std::endl;
                        else if (choice == 'S')
                        {
                            stkVec.Clear();
                            std::cout<< std::endl << "Lo stack è stato svuotato." << std::endl;
                        }
                        else if (choice == 'Q')
                            end = true;
                    }
                }
                else if (tInput == 'D')
                {
                    lasd::StackVec<double> stkVec;
                    RandPopulateStackReal(stkVec, n);
                    while (!end)
                    {
                        PrintMenu(choice);
                        if (choice == 'I')
                            stackInsertion(stkVec);
                        else if (choice == 'R')
                            stackRemoval(stkVec);
                        else if (choice == 'H')
                            stackHead(stkVec);
                        else if (choice == 'V')
                            std::cout<< std::endl << "Lo stack" << (stkVec.Empty() ? "" : " non") << " è vuoto." << std::endl;
                        else if (choice == 'D')
                            std::cout<< std::endl << "Lo stack ha dimensione: " << stkVec.Size()<< std::endl;
                        else if (choice == 'S')
                        {
                            stkVec.Clear();
                            std::cout<< std::endl << "Lo stack è stato svuotato." << std::endl;
                        }
                        else if (choice == 'Q')
                            end = true;
                    }
                }
                else if (tInput == 'S')
                {
                    lasd::StackVec<std::string> stkVec;
                    RandPopulateStackString(stkVec, n);
                    while (!end)
                    {
                        PrintMenu(choice);
                        if (choice == 'I')
                            stackInsertion(stkVec);
                        else if (choice == 'R')
                            stackRemoval(stkVec);
                        else if (choice == 'H')
                            stackHead(stkVec);
                        else if (choice == 'V')
                            std::cout<< std::endl << "Lo stack" << (stkVec.Empty() ? "" : " non") << " è vuoto." << std::endl;
                        else if (choice == 'D')
                            std::cout<< std::endl << "Lo stack ha dimensione: " << stkVec.Size()<< std::endl;
                        else if (choice == 'S')
                        {
                            stkVec.Clear();
                            std::cout<< std::endl << "Lo stack è stato svuotato." << std::endl;
                        }
                        else if (choice == 'Q')
                            end = true;
                    }
                }
            }
            else if (iInput == 'L')
            {
                if (tInput == 'I')
                {
                    lasd::StackLst<int> stkLst;
                    RandPopulateStackInt(stkLst, n);
                    while (!end)
                    {
                        PrintMenu(choice);
                        if (choice == 'I')
                            stackInsertion(stkLst);
                        else if (choice == 'R')
                            stackRemoval(stkLst);
                        else if (choice == 'H')
                            stackHead(stkLst);
                        else if (choice == 'V')
                            std::cout<< std::endl << "Lo stack" << (stkLst.Empty() ? "" : " non") << " è vuoto." << std::endl;
                        else if (choice == 'D')
                            std::cout<< std::endl << "Lo stack ha dimensione: " << stkLst.Size()<< std::endl;
                        else if (choice == 'S')
                        {
                            stkLst.Clear();
                            std::cout<< std::endl << "Lo stack è stato svuotato." << std::endl;
                        }
                        else if (choice == 'Q')
                            end = true;
                    }
                }
                else if (tInput == 'D')
                {
                    lasd::StackLst<double> stkLst;
                    RandPopulateStackReal(stkLst, n);
                    while (!end)
                    {
                        PrintMenu(choice);
                        if (choice == 'I')
                            stackInsertion(stkLst);
                        else if (choice == 'R')
                            stackRemoval(stkLst);
                        else if (choice == 'H')
                            stackHead(stkLst);
                        else if (choice == 'V')
                            std::cout<< std::endl << "Lo stack" << (stkLst.Empty() ? "" : " non") << " è vuoto." << std::endl;
                        else if (choice == 'D')
                            std::cout<< std::endl << "Lo stack ha dimensione: " << stkLst.Size()<< std::endl;
                        else if (choice == 'S')
                        {
                            stkLst.Clear();
                            std::cout<< std::endl << "Lo stack è stato svuotato." << std::endl;
                        }
                        else if (choice == 'Q')
                            end = true;
                    }
                }
                else if (tInput == 'S')
                {
                    lasd::StackLst<std::string> stkLst;
                    RandPopulateStackString(stkLst, n);
                    while (!end)
                    {
                        PrintMenu(choice);
                        if (choice == 'I')
                            stackInsertion(stkLst);
                        else if (choice == 'R')
                            stackRemoval(stkLst);
                        else if (choice == 'H')
                            stackHead(stkLst);
                        else if (choice == 'V')
                            std::cout<< std::endl << "Lo stack" << (stkLst.Empty() ? "" : " non") << " è vuoto." << std::endl;
                        else if (choice == 'D')
                            std::cout<< std::endl << "Lo stack ha dimensione: " << stkLst.Size()<< std::endl;
                        else if (choice == 'S')
                        {
                            stkLst.Clear();
                            std::cout<< std::endl << "Lo stack è stato svuotato." << std::endl;
                        }
                        else if (choice == 'Q')
                            end = true;
                    }
                }
            }
        }
        else if (sInput == 'Q')
        {
            if (iInput == 'V')
            {
                if (tInput == 'I')
                {
                    lasd::QueueVec<int> queVec;
                    RandPopulateQueueInt(queVec, n);
                    while (!end)
                    {
                        PrintMenu(choice);
                        if (choice == 'I')
                            queueInsertion(queVec);
                        else if (choice == 'R')
                            queueRemoval(queVec);
                        else if (choice == 'H')
                            queueHead(queVec);
                        else if (choice == 'V')
                            std::cout<< std::endl << "La queue" << (queVec.Empty() ? "" : " non") << " è vuota." << std::endl;
                        else if (choice == 'D')
                            std::cout<< std::endl << "La queue ha dimensione: " << queVec.Size()<< std::endl;
                        else if (choice == 'S')
                        {
                            queVec.Clear();
                            std::cout<< std::endl << "La queue è stata svuotata." << std::endl;
                        }
                        else if (choice == 'Q')
                            end = true;
                    }
                }
                else if (tInput == 'D')
                {
                    lasd::QueueVec<double> queVec;
                    RandPopulateQueueReal(queVec, n);
                    while (!end)
                    {
                        PrintMenu(choice);
                        if (choice == 'I')
                            queueInsertion(queVec);
                        else if (choice == 'R')
                            queueRemoval(queVec);
                        else if (choice == 'H')
                            queueHead(queVec);
                        else if (choice == 'V')
                            std::cout<< std::endl << "La queue" << (queVec.Empty() ? "" : " non") << " è vuota." << std::endl;
                        else if (choice == 'D')
                            std::cout<< std::endl << "La queue ha dimensione: " << queVec.Size()<< std::endl;
                        else if (choice == 'S')
                        {
                            queVec.Clear();
                            std::cout<< std::endl << "La queue è stata svuotata." << std::endl;
                        }
                        else if (choice == 'Q')
                            end = true;
                    }
                }
                else if (tInput == 'S')
                {
                    lasd::QueueVec<std::string> queVec;
                    RandPopulateQueueString(queVec, n);
                    while (!end)
                    {
                        PrintMenu(choice);
                        if (choice == 'I')
                            queueInsertion(queVec);
                        else if (choice == 'R')
                            queueRemoval(queVec);
                        else if (choice == 'H')
                            queueHead(queVec);
                        else if (choice == 'V')
                            std::cout<< std::endl << "La queue" << (queVec.Empty() ? "" : " non") << " è vuota." << std::endl;
                        else if (choice == 'D')
                            std::cout<< std::endl << "La queue ha dimensione: " << queVec.Size()<< std::endl;
                        else if (choice == 'S')
                        {
                            queVec.Clear();
                            std::cout<< std::endl << "La queue è stata svuotata." << std::endl;
                        }
                        else if (choice == 'Q')
                            end = true;
                    }
                }
            }
            else if (iInput == 'L')
            {
                if (tInput == 'I')
                {
                    lasd::QueueLst<int> queLst;
                    RandPopulateQueueInt(queLst, n);
                    while (!end)
                    {
                        PrintMenu(choice);
                        if (choice == 'I')
                            queueInsertion(queLst);
                        else if (choice == 'R')
                            queueRemoval(queLst);
                        else if (choice == 'H')
                            queueHead(queLst);
                        else if (choice == 'V')
                            std::cout<< std::endl << "La queue" << (queLst.Empty() ? "" : " non") << " è vuota." << std::endl;
                        else if (choice == 'D')
                            std::cout<< std::endl << "La queue ha dimensione: " << queLst.Size()<< std::endl;
                        else if (choice == 'S')
                        {
                            queLst.Clear();
                            std::cout<< std::endl << "La queue è stata svuotata." << std::endl;
                        }
                        else if (choice == 'Q')
                            end = true;
                    }
                }
                else if (tInput == 'D')
                {
                    lasd::QueueLst<double> queLst;
                    RandPopulateQueueReal(queLst, n);
                    while (!end)
                    {
                        PrintMenu(choice);
                        if (choice == 'I')
                            queueInsertion(queLst);
                        else if (choice == 'R')
                            queueRemoval(queLst);
                        else if (choice == 'H')
                            queueHead(queLst);
                        else if (choice == 'V')
                            std::cout<< std::endl << "La queue" << (queLst.Empty() ? "" : " non") << " è vuota." << std::endl;
                        else if (choice == 'D')
                            std::cout<< std::endl << "La queue ha dimensione: " << queLst.Size()<< std::endl;
                        else if (choice == 'S')
                        {
                            queLst.Clear();
                            std::cout<< std::endl << "La queue è stata svuotata." << std::endl;
                        }
                        else if (choice == 'Q')
                            end = true;
                    }
                }
                else if (tInput == 'S')
                {
                    lasd::QueueLst<std::string> queLst;
                    RandPopulateQueueString(queLst, n);
                    while (!end)
                    {
                        PrintMenu(choice);
                        if (choice == 'I')
                            queueInsertion(queLst);
                        else if (choice == 'R')
                            queueRemoval(queLst);
                        else if (choice == 'H')
                            queueHead(queLst);
                        else if (choice == 'V')
                            std::cout<< std::endl << "La queue" << (queLst.Empty() ? "" : " non") << " è vuota." << std::endl;
                        else if (choice == 'D')
                            std::cout<< std::endl << "La queue ha dimensione: " << queLst.Size()<< std::endl;
                        else if (choice == 'S')
                        {
                            queLst.Clear();
                            std::cout<< std::endl << "La queue è stata svuotata." << std::endl;
                        }
                        else if (choice == 'Q')
                            end = true;
                    }
                }
            }
        }
    }
    else
        std::cout << std::endl << "Goodbye!" << std::endl;
}