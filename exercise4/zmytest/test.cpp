
#include "test.hpp"

#include <iostream>
#include <random>
#include <iomanip>

void StructureSelection(char& tInput) {
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
void RandPopulateInt(lasd::BST<Data>& bst, const unsigned long& n) {
    std::default_random_engine gen(std::random_device{}());
    std::uniform_int_distribution<Data> dist(1, 100);
    for (unsigned long i=0; i<n; i++)
        bst.Insert(dist(gen));
}

template <typename Data>
void RandPopulateReal(lasd::BST<Data>& bst, const unsigned long& n) {
    std::default_random_engine gen(std::random_device{}());
    std::uniform_real_distribution<Data> dist(1, 99);
    for(unsigned long i=0; i<n; i++)
        bst.Insert(dist(gen));
}

template <typename Data>
void RandPopulateString(lasd::BST<Data>& bst, const unsigned long& n) {
    std::default_random_engine gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(97, 122);
    std::default_random_engine lenGen(std::random_device{}());
    std::uniform_int_distribution<int> lenDist(1, 16);
    for (unsigned long i=0; i<n; i++)
    {
        std::string newString { };
        for (int j=0; j<(lenDist(lenGen)); j++)
            newString.append(1, static_cast<char>(dist(gen)));
        
        bst.Insert(newString);
    }
}

template <typename Data>
void MapPrint(const Data& dat, void* _) {
  std::cout<< std::setprecision(7) << dat << " ";
}

template <typename Data>
void StructurePrint(lasd::BinaryTree<Data>& bt) {
    char choice;
    std::cout<< std::endl <<"Selezionare un ordine per la stampa degli elementi: " << std::endl << "P[R]eOrder    P[O]stOrder    [I]nOrder    [B]readth    " << std::endl;
    std::cin.clear();
    std::cin>>choice;
    choice = std::toupper(choice);
    while (choice != 'R' && choice != 'O' && choice != 'I' && choice != 'B')
    {
        std::cout<< std::endl <<"Inserire uno tra R, O, I oppure B..."<< std::endl;
        std::cin.clear();
        std::cin>>choice;
        choice = std::toupper(choice);
    }
    if (choice == 'R')
    {
        std::cout<< std::endl <<"Stampa degli elementi nella struttura in Pre Order"<< std::endl;
        bt.MapPreOrder(&MapPrint<Data>, 0);
    }
    else if (choice == 'O')
    {
        std::cout<< std::endl <<"Stampa degli elementi nella struttura in Post Order"<< std::endl;
        bt.MapPostOrder(&MapPrint<Data>, 0);
    }
    else if (choice == 'I')
    {
        std::cout<< std::endl <<"Stampa degli elementi nella struttura in In Order"<< std::endl;
        bt.MapInOrder(&MapPrint<Data>, 0);
    }
    else if (choice == 'B')
    {
        std::cout<< std::endl <<"Stampa degli elementi nella struttura in Ampiezza"<< std::endl;
        bt.MapBreadth(&MapPrint<Data>, 0);
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

template <typename Data>
void AuxFoldProd(const Data& dat, const void* val, void* prod) {
    if (dat < *((int*)val))
        *((int*)prod) = *((int*)prod)*dat;
}

template <typename Data>
void SmallerThanNProd(const lasd::FoldableContainer<Data>& con) {
    int n;
    int prod = 1;
    do
    {
        std::cout<< std::endl << "Moltiplicare gli elementi minori di quale numero?" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin>>n;
    } while (std::cin.fail());
    con.FoldPreOrder(&AuxFoldProd<Data>, &n, &prod);
    std::cout<< std::endl << "Il prodotto richiesto è: " << prod << std::endl;
}

template <typename Data>
void AuxFoldSum(const Data& dat, const void* val, void* sum) {
    if (dat > *((float*)val))
        *((float*)sum) += dat;
}

template <typename Data>
void BiggerThanNSum(const lasd::FoldableContainer<Data>& con) {
    float n;
    float sum = 0;
    do
    {
        std::cout<< std::endl << "Sommare gli elementi maggiori di quale numero?" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin>>n;
    } while (std::cin.fail());
    con.FoldPreOrder(&AuxFoldSum<Data>, &n, &sum);
    std::cout<< std::endl << "La somma richiesta è: " << sum << std::endl;
}

template <typename Data>
void AuxFoldConcat(const std::string& dat, const void* val, void* reString) {
    if(dat.length() <= *((int*)val))
        ((std::string*)reString)->append(dat);
}

template <typename Data>
void ShorterThanNConcat(const lasd::FoldableContainer<Data>& con) {
    int n;
    std::string reString{ };
    do
    {
        std::cout<< std::endl << "Concatenare le stringhe con lunghezza minore di quale numero?" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin>>n;
    } while (std::cin.fail());
    con.FoldPreOrder(&AuxFoldConcat<Data>, &n, &reString);
    std::cout<< std::endl << "La stringa ottenuta è: " << reString << std::endl;
}

void PrintMenu(char& choice) {
    std::cout<< std::endl <<"Selezionare una funzione:" << std::endl << "[V]isualizzazione    [E]sistenza    [F]old    [Q]uit    " << std::endl;
    std::cin.clear();
    std::cin>>choice;
    choice = std::toupper(choice);
    while(choice != 'V' && choice != 'E' && choice != 'F' && choice != 'M' && choice != 'O'  && choice != 'I' && choice != 'Q')
    {
        std::cout<< std::endl <<"Inserire uno tra V, E, F, oppure Q..."<< std::endl;
        std::cin.clear();
        std::cin>>choice;
        choice = std::toupper(choice);
    }
}

void testMenu() {
    char tInput;
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
        StructureSelection(tInput);
        do
        {
            std::cout<< std::endl << "Inserire il numero di elementi con cui popolare la struttura..."<< std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin>>n;
        } while (std::cin.fail());
        if (tInput == 'I')
        {
            lasd::BST<int> bst;
            RandPopulateInt(bst, n);
            while (!end)
            {
                PrintMenu(choice);
                if (choice == 'V')
                    StructurePrint(bst);
                else if (choice == 'E')
                    ElemExists(bst);
                else if (choice == 'F')
                    SmallerThanNProd(bst);
                else if (choice == 'Q')
                    end = true;
            }
        }
        else if (tInput == 'F')
        {
            lasd::BST<float> bst;
            RandPopulateReal(bst, n);
            while (!end)
            {
                PrintMenu(choice);
                if (choice == 'V')
                    StructurePrint(bst);
                else if (choice == 'E')
                    ElemExists(bst);
                else if (choice == 'F')
                    BiggerThanNSum(bst);
                else if (choice == 'Q')
                    end = true;
            }
        }
        else if (tInput == 'S')
        {
            lasd::BST<std::string> bst;
            RandPopulateString(bst, n);
            while (!end)
            {
                PrintMenu(choice);
                if (choice == 'V')
                    StructurePrint(bst);
                else if (choice == 'E')
                    ElemExists(bst);
                else if (choice == 'F')
                    ShorterThanNConcat(bst);
                else if (choice == 'Q')
                    end = true;
            }
        }
    }
}