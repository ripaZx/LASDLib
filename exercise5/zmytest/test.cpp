
#include "test.hpp"

#include <iostream>
#include <iomanip>
#include <random>

void StructureSelection(char& iInput, char& tInput) {
    std::cout<< std::endl <<"Selezionare l'implementazione su cui lavorare:"<< std::endl <<"    [S]erializzazione    [C]ompressed_Sparse_Row..."<< std::endl;
    std::cin.clear();
    std::cin>>iInput;
    iInput = std::toupper(iInput);
    while(iInput != 'S' && iInput != 'C')
    {
        std::cout<< std::endl <<"Inserire S oppure C..."<< std::endl;
        std::cin.clear();
        std::cin>>iInput;
        iInput = std::toupper(iInput);
    }

    std::cout<< std::endl <<"Selezionare il tipo di dato da trattare:"<< std::endl <<"    [I]nt    [F]loat    [S]tring..."<< std::endl;
    std::cin>>tInput;
    tInput = std::toupper(tInput);
    while(tInput != 'I' && tInput != 'F' && tInput != 'S')
    {
        std::cout<< std::endl <<"Inserire uno tra: I, F, S..."<< std::endl;
        std::cin.clear();
        std::cin>>tInput;
        tInput = std::toupper(tInput);
    }
}

template <typename Data>
void RandPopulateInt(lasd::Matrix<Data>& mat, const unsigned long& n, const unsigned long& m) {
    std::default_random_engine gen(std::random_device{}());
    std::uniform_int_distribution<Data> dist(1, 100);
    for (unsigned long i=0; i<n; i++)
        for (unsigned long j=0; j<m; j++)
            mat(i, j) = (dist(gen)); 
}

template <typename Data>
void RandSparsePopulateInt(lasd::Matrix<Data>& mat, const unsigned long& n, const unsigned long& m) {
    std::default_random_engine rowGen(std::random_device{}());
    std::uniform_int_distribution<Data> rowDist(0, static_cast<int>(n));
    std::default_random_engine colGen(std::random_device{}());
    std::uniform_int_distribution<Data> colDist(0, static_cast<int>(m));
    std::default_random_engine elemNumGen(std::random_device{}());
    std::uniform_int_distribution<Data> elemNumDist(1, static_cast<int>(n*m));
    std::default_random_engine gen(std::random_device{}());
    std::uniform_int_distribution<Data> dist(1, 100);
    for (unsigned long i=0; i<elemNumDist(elemNumGen); i++)
        mat(rowDist(rowGen), colDist(colGen)) = (dist(gen)); 
}

template <typename Data>
void RandPopulateReal(lasd::Matrix<Data>& mat, const unsigned long& n, const unsigned long& m) {
    std::default_random_engine gen(std::random_device{}());
    std::uniform_real_distribution<Data> dist(1, 99);
    for(unsigned long i=0; i<n; i++)
        for (unsigned long j=0; j<m; j++)
            mat(i, j) = (dist(gen));
}

template <typename Data>
void RandSparsePopulateReal(lasd::Matrix<Data>& mat, const unsigned long& n, const unsigned long& m) {
    std::default_random_engine rowGen(std::random_device{}());
    std::uniform_int_distribution<int> rowDist(0, static_cast<int>(n));
    std::default_random_engine colGen(std::random_device{}());
    std::uniform_int_distribution<int> colDist(0, static_cast<int>(m));
    std::default_random_engine elemNumGen(std::random_device{}());
    std::uniform_int_distribution<int> elemNumDist(1, static_cast<int>(n*m));
    std::default_random_engine gen(std::random_device{}());
    std::uniform_real_distribution<Data> dist(1, 99);
    for (unsigned long i=0; i<elemNumDist(elemNumGen); i++)
        mat(rowDist(rowGen), colDist(colGen)) = (dist(gen)); 
}

template <typename Data>
void RandPopulateString(lasd::Matrix<Data>& mat, const unsigned long& n, const unsigned long& m) {
    std::default_random_engine gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(97, 122);
    std::default_random_engine lenGen(std::random_device{}());
    std::uniform_int_distribution<int> lenDist(1, 16);
    for (unsigned long i=0; i<n; i++)
        for (unsigned long j=0; j<m; j++)
        {
            std::string newString { };
            for (int k=0; k<(lenDist(lenGen)); k++)
                newString.append(1, static_cast<char>(dist(gen)));
            
            mat(i, j) = newString;
        }
}

template <typename Data>
void RandSparsePopulateString(lasd::Matrix<Data>& mat, const unsigned long& n, const unsigned long& m) {
    std::default_random_engine rowGen(std::random_device{}());
    std::uniform_int_distribution<int> rowDist(0, static_cast<int>(n));
    std::default_random_engine colGen(std::random_device{}());
    std::uniform_int_distribution<int> colDist(0, static_cast<int>(m));
    std::default_random_engine elemNumGen(std::random_device{}());
    std::uniform_int_distribution<int> elemNumDist(1, static_cast<int>(n*m));
    std::default_random_engine gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(97, 122);
    std::default_random_engine lenGen(std::random_device{}());
    std::uniform_int_distribution<int> lenDist(1, 16);
    for (unsigned long i=0; i<elemNumDist(elemNumGen); i++)
    {
        std::string newString {};
        for (int j=0; j<(lenDist(lenGen)); j++)
            newString.append(1, static_cast<char>(dist(gen)));

        mat(rowDist(rowGen), colDist(colGen)) = newString;
    }
}

template <typename Data>
void MapPrint(const Data& dat, void* _) {
    std::cout<< std::setprecision(7) << dat << " ";
}

template <typename Data>
void StructurePrint(lasd::Matrix<Data>& mat) {
    char choice;
    std::cout << std::endl << "Selezionare un ordine per la stampa degli elementi: " << std::endl << "P[R]eOrder    P[O]stOrder" << std::endl;
    std::cin.clear();
    std::cin>>choice;
    choice = std::toupper(choice);
    while (choice != 'R' && choice != 'O')
    {
        std::cout << std::endl << "Inserire uno tra R oppure O..." << std::endl;
        std::cin.clear();
        std::cin>>choice;
        choice = std::toupper(choice);
    }
    if (choice == 'R')
    {
        std::cout << std::endl << "Stampa degli elementi della struttura in PreOrder" << std::endl;
        mat.MapPreOrder(&MapPrint<Data>, 0);
    }
    else if (choice == 'O')
    {
        std::cout << std::endl << "Stampa degli elementi della struttura in PostOrder" << std::endl;
        mat.MapPostOrder(&MapPrint<Data>, 0);
    }
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

void PrintMenu(char& choice) {
    std::cout<< std::endl <<"Selezionare una funzione:" << std::endl << "[V]isualizzazione    [E]sistenza    [F]old    [M]ap    [S]tructureSpecific    [Q]uit    " << std::endl;
    std::cin.clear();
    std::cin>>choice;
    choice = std::toupper(choice);
    while(choice != 'V' && choice != 'E' && choice != 'F' && choice != 'M' && choice != 'S' && choice != 'Q')
    {
        std::cout<< std::endl <<"Inserire uno tra V, E, F, M, S oppure Q..."<< std::endl;
        std::cin.clear();
        std::cin>>choice;
        choice = std::toupper(choice);
    }
}

void testMenu() {
    char iInput, tInput;
    unsigned long n, m;
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
            std::cout<< std::endl << "Inserire il numero di righe e colonne (separate da invio) con cui popolare la struttura..."<< std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin>> n >> m;
        } while (std::cin.fail());
        if (iInput == 'S')
        {
            if (tInput == 'I')
            {
                lasd::MatrixVec<int> mat(n, m);
                RandPopulateInt(mat, n, m);
                while (!end)
                {
                    PrintMenu(choice);
                    if (choice == 'V')
                        StructurePrint(mat);
                    else if (choice == 'Q')
                        end = true;
                }
            }
            else if (tInput == 'F')
            {
                lasd::MatrixVec<float> mat(n, m);
                RandPopulateReal(mat, n, m);
                while (!end)
                {
                    PrintMenu(choice);
                    if (choice == 'V')
                        StructurePrint(mat);
                    else if (choice == 'Q')
                        end = true;
                }
            }
            else if (tInput == 'S')
            {
                lasd::MatrixVec<std::string> mat(n, m);
                RandPopulateString(mat, n, m);
                while (!end)
                {
                    PrintMenu(choice);
                    if (choice == 'V')
                        StructurePrint(mat);
                    else if (choice == 'Q')
                        end = true;
                }
            }
        }
        else if (iInput == 'C')
        {
            if (tInput == 'I')
            {
                lasd::MatrixCSR<int> mat(n, m);
                RandSparsePopulateInt(mat, n, m);
                while (!end)
                {
                    PrintMenu(choice);
                    if (choice == 'V')
                        StructurePrint(mat);
                    else if (choice == 'Q')
                        end = true;
                }
            }
            else if (tInput == 'F')
            {
                lasd::MatrixCSR<float> mat(n, m);
                RandSparsePopulateReal(mat, n, m);
                while (!end)
                {
                    PrintMenu(choice);
                    if (choice == 'V')
                        StructurePrint(mat);
                    else if (choice == 'Q')
                        end = true;
                }
            }
            else if (tInput == 'S')
            {
                lasd::MatrixCSR<std::string> mat(n, m); 
                RandSparsePopulateString(mat, n, m);
                while (!end)
                {
                    PrintMenu(choice);
                    if (choice == 'V')
                        StructurePrint(mat);
                    else if (choice == 'Q')
                        end = true;
                }
            }
        }
        
    }
    else
        std::cout << std::endl << "Goodbye!" << std::endl;
}