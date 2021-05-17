
#include "test.hpp"

#include <iostream>
#include <iomanip>
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
void RandPopulateInt(lasd::Vector<Data>& vec, const unsigned long& n) {
    std::default_random_engine gen(std::random_device{}());
    std::uniform_int_distribution<Data> dist(1, 100);
    for (unsigned long i=0; i<n; i++)
        vec[i] = (dist(gen));
}

template <typename Data>
void RandPopulateReal(lasd::Vector<Data>& vec, const unsigned long& n) {
    std::default_random_engine gen(std::random_device{}());
    std::uniform_real_distribution<Data> dist(1, 99);
    for(unsigned long i=0; i<n; i++)
        vec[i] = (dist(gen));
}

template <typename Data>
void RandPopulateString(lasd::Vector<Data>& vec, const unsigned long& n) {
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

template <typename Data>
void MapTriple(Data& dat, void* _) {
  dat *= 3;
}

template <typename Data>
void MapCube(Data& dat, void* _) {
    dat = dat*dat*dat;
}

template <typename Data>
void MapInsert(Data& dat, void* str) {
    dat.insert(0, *(std::string*)str);
}

template <typename Data>
void StringInsert(lasd::MappableContainer<Data>& con) {
    std::string str;
    std::cout<< std::endl << "Inserisci la stringa da inserire in testa ad ogni elemento:" << std::endl;
    std::cin.clear();
    std::cin>>str;
    con.MapPreOrder(&MapInsert<Data>, &str);
}

template <typename Data>
void ExploreTree(lasd::BinaryTree<Data>& bt) {
    char choice;
    bool end = false;
    typename lasd::BinaryTree<Data>::Node* nod = &bt.Root();
    while (!end)
    {
        std::cout<< std::endl << "Selezionare l'azione da intraprendere: " << std::endl << "[A]ccesso    [S]postamento    [E]sci" << std::endl;
        std::cin.clear();
        std::cin>>choice;
        choice = std::toupper(choice);
        while (choice != 'A' && choice != 'S' && choice != 'E')
        {
            std::cout << std::endl <<"Inserire uno tra A, S oppure E..."<< std::endl;
            std::cin.clear();
            std::cin>>choice;
            choice = std::toupper(choice);
        }
        if (choice == 'A')
        {
            std::cout<< std::endl << "Definire il tipo di accesso" << std::endl << "[R]ead    [W]rite" << std::endl;
            std::cin.clear();
            std::cin>>choice;
            choice = std::toupper(choice);
            while (choice != 'R' && choice != 'W')
            {
                std::cout<< std::endl << "Inserire uno tra R e W..."<< std::endl;
                std::cin.clear();
                std::cin>>choice;
                choice = std::toupper(choice);
            }
            if (choice == 'R')
                std::cout<< std::endl << "L'elemento del nodo a cui si ha effettuato accesso è: " << nod->Element() << std::endl;
            else if (choice == 'W')
            {
                Data elem;
                do
                {
                    std::cout<< std::endl <<"Quale elemento inserire nella posizione corrente dell'albero?"<< std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin>>elem;
                } while(std::cin.fail());
                nod->Element() = elem;
            }
        }
        else if (choice == 'S')
        {
            std::cout<< std::endl << "Selezionare quale figlio esplorare: " << std::endl << "[D]estro    [S]inistro" << std::endl;
            std::cin.clear();
            std::cin>>choice;
            choice = std::toupper(choice);
            while (choice != 'D' && choice != 'S')
            {
                std::cout<< std::endl << "Inserire uno tra D e S..." << std::endl;
                std::cin.clear();
                std::cin>>choice;
                choice = std::toupper(choice);
            }
            if (choice == 'D')
            {
                if (nod->HasRightChild())
                    nod = &nod->RightChild();
                else
                    std::cout<< std::endl << "Il nodo corrente non ha figlio destro." << std::endl;
            }
            else if (choice == 'S')
            {
                if (nod->HasLeftChild())
                    nod = &nod->LeftChild();
                else
                    std::cout<< std::endl << "Il nodo corrente non ha figlio sinistro." << std::endl;
            }
        }
        else if (choice == 'E')
            end = true;
    }
}

template <typename Data>
void IteratorNavigation(lasd::ForwardIterator<Data>& itr) {
    char choice;
    bool end = false;
    while (!end)
    {
        std::cout<< "Il dato puntato dall'iteratore è: " << *itr << std::endl;
        std::cout<< "Passare al prossimo dato oppure terminare la visita? " << std::endl << "[N]ext    [Q]uit"<< std::endl;
        std::cin.clear();
        std::cin>>choice;
        choice = std::toupper(choice);
        while (choice != 'N' && choice != 'Q')
        {
            std::cout<< std::endl <<"Inserire uno tra N e Q..." << std::endl;
            std::cin.clear();
            std::cin>>choice;
            choice = std::toupper(choice);
        }
        if (choice == 'N')
        {
            ++itr;
            if (itr.Terminated())
            {
                std::cout<< "L'iteratore è arrivato alla fine della struttura." << std::endl;
                end = true;
            }
        }
        else if (choice == 'Q')
            end = true;
    }
}

template <typename Data>
void IteratorSelection(lasd::BinaryTree<Data>& bt) {
    char choice;
    std::cout<< std::endl << "Selezionare il tipo di iteratore da usare: " << std::endl << "P[R]eOrder    P[O]stOrder    [I]nOrder    [B]readth    "<< std::endl;
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
        lasd::BTPreOrderIterator<Data>* itr = new lasd::BTPreOrderIterator<Data>(bt);
        IteratorNavigation(*itr);
    }
    else if (choice == 'O')
    {
        lasd::BTPostOrderIterator<Data>* itr = new lasd::BTPostOrderIterator<Data>(bt);
        IteratorNavigation(*itr);
    }
    else if (choice == 'I')
    {
        lasd::BTInOrderIterator<Data>* itr = new lasd::BTInOrderIterator<Data>(bt);
        IteratorNavigation(*itr);
    }
    else if (choice == 'B')
    {
        lasd::BTBreadthIterator<Data>* itr = new lasd::BTBreadthIterator<Data>(bt);
        IteratorNavigation(*itr);
    }
}

void PrintMenu(char& choice) {
    std::cout<< std::endl <<"Selezionare una funzione:" << std::endl << "[V]isualizzazione    [E]sistenza    [F]old    [M]ap    [O]perazioni sui nodi    [I]teratori    [Q]uit    " << std::endl;
    std::cin.clear();
    std::cin>>choice;
    choice = std::toupper(choice);
    while(choice != 'V' && choice != 'E' && choice != 'F' && choice != 'M' && choice != 'O'  && choice != 'I' && choice != 'Q')
    {
        std::cout<< std::endl <<"Inserire uno tra V, E, F, M, O, I oppure Q..."<< std::endl;
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
        if (iInput == 'V')
        {
            if (tInput == 'I')
            {
                lasd::Vector<int> vec(n);
                RandPopulateInt(vec, n);
                lasd::BinaryTreeVec<int> btV(vec);
                while (!end)
                {
                    PrintMenu(choice);
                    if (choice == 'V')
                        StructurePrint(btV);
                    else if (choice == 'E')
                        ElemExists(btV);
                    else if (choice == 'F')
                        SmallerThanNProd(btV);
                    else if (choice == 'M')
                        btV.MapPreOrder(&MapTriple<int>, 0);
                    else if (choice == 'O')
                        ExploreTree(btV);
                    else if (choice == 'I')
                        IteratorSelection(btV);
                    else if (choice == 'Q')
                        end = true;
                }
            }
            else if (tInput == 'F')
            {
                lasd::Vector<float> vec(n);
                RandPopulateReal(vec, n);
                lasd::BinaryTreeVec<float> btV(vec);
                while (!end)
                {
                    PrintMenu(choice);
                    if (choice == 'V')
                        StructurePrint(btV);
                    else if (choice == 'E')
                        ElemExists(btV);
                    else if (choice == 'F')
                        BiggerThanNSum(btV);
                    else if (choice == 'M')
                        btV.MapPostOrder(&MapCube<float>, 0);
                    else if (choice == 'O')
                        ExploreTree(btV);
                    else if (choice == 'I')
                        IteratorSelection(btV);
                    else if (choice == 'Q')
                        end = true;
                }
            }
            else if (tInput == 'S')
            {
                lasd::Vector<std::string> vec(n);
                RandPopulateString(vec, n);
                lasd::BinaryTreeVec<std::string> btV(vec);
                while (!end)
                {
                    PrintMenu(choice);
                    if (choice == 'V')
                        StructurePrint(btV);
                    else if (choice == 'E')
                        ElemExists(btV);
                    else if (choice == 'F')
                        ShorterThanNConcat(btV);
                    else if (choice == 'M')
                        StringInsert(btV);
                    else if (choice == 'O')
                        ExploreTree(btV);
                    else if (choice == 'I')
                        IteratorSelection(btV);
                    else if (choice == 'Q')
                        end = true;
                }
            }
        }
        else if (iInput == 'L')
        {
            if (tInput == 'I')
            {
                lasd::Vector<int> vec(n);
                RandPopulateInt(vec, n);
                lasd::BinaryTreeLnk<int> btL(vec);
                while (!end)
                {
                    PrintMenu(choice);
                    if (choice == 'V')
                        StructurePrint(btL);
                    else if (choice == 'E')
                        ElemExists(btL);
                    else if (choice == 'F')
                        SmallerThanNProd(btL);
                    else if (choice == 'M')
                        btL.MapPreOrder(&MapTriple<int>, 0);
                    else if (choice == 'O')
                        ExploreTree(btL);
                    else if (choice == 'I')
                        IteratorSelection(btL);
                    else if (choice == 'Q')
                        end = true;
                }
            }
            else if (tInput == 'F')
            {
                lasd::Vector<float> vec(n);
                RandPopulateReal(vec, n);
                lasd::BinaryTreeLnk<float> btL(vec);
                while (!end)
                {
                    PrintMenu(choice);
                    if (choice == 'V')
                        StructurePrint(btL);
                    else if (choice == 'E')
                        ElemExists(btL);
                    else if (choice == 'F')
                        BiggerThanNSum(btL);
                    else if (choice == 'M')
                        btL.MapPostOrder(&MapCube<float>, 0);
                    else if (choice == 'O')
                        ExploreTree(btL);
                    else if (choice == 'I')
                        IteratorSelection(btL);
                    else if (choice == 'Q')
                        end = true;
                }
            }
            else if (tInput == 'S')
            {
                lasd::Vector<std::string> vec(n);
                RandPopulateString(vec, n);
                lasd::BinaryTreeLnk<std::string> btL(vec);
                while (!end)
                {
                    PrintMenu(choice);
                    if (choice == 'V')
                        StructurePrint(btL);
                    else if (choice == 'E')
                        ElemExists(btL);
                    else if (choice == 'F')
                        ShorterThanNConcat(btL);
                    else if (choice == 'M')
                        StringInsert(btL);
                    else if (choice == 'O')
                        ExploreTree(btL);
                    else if (choice == 'I')
                        IteratorSelection(btL);
                    else if (choice == 'Q')
                        end = true;
                }
            }
        }
    }
    else
        std::cout << std::endl << "Goodbye!" << std::endl;
}