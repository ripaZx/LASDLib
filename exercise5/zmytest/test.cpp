
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
    std::uniform_int_distribution<Data> rowDist(0, static_cast<int>(n)-1);
    std::default_random_engine colGen(std::random_device{}());
    std::uniform_int_distribution<Data> colDist(0, static_cast<int>(m)-1);
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
    std::uniform_int_distribution<int> rowDist(0, static_cast<int>(n)-1);
    std::default_random_engine colGen(std::random_device{}());
    std::uniform_int_distribution<int> colDist(0, static_cast<int>(m)-1);
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
    if (m != 0 && n != 0)
    {
        std::default_random_engine rowGen(std::random_device{}());
        std::uniform_int_distribution<int> rowDist(0, static_cast<int>(n)-1);
        std::default_random_engine colGen(std::random_device{}());
        std::uniform_int_distribution<int> colDist(0, static_cast<int>(m)-1);
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
void ElemExists(const lasd::Matrix<Data>& mat) {
    Data elem;
    do
    {
        std::cout<< std::endl << "Verificare l'esistenza di quale elemento?" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin>>elem;
    } while (std::cin.fail());
        std::cout<< std::endl <<"L'elemento "<< elem << (mat.Exists(elem) ? "" : " non") << " è presente." << std::endl;
}

template <typename Data>
void AuxFoldProd(const Data& dat, const void* val, void* prod) {
    if (dat < *((int*)val))
        *((int*)prod) = *((int*)prod)*dat;
}

template <typename Data>
void SmallerThanNProd(const lasd::Matrix<Data>& con) {
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
void BiggerThanNSum(const lasd::Matrix<Data>& con) {
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
void ShorterThanNConcat(const lasd::Matrix<Data>& con) {
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
void MapDouble(Data& dat, void* _) {
  dat *= 2;
}

template <typename Data>
void MapInverseCube(Data& dat, void* _) {
    dat = -(dat)*(-dat)*(-dat);
}

template <typename Data>
void MapInsert(Data& dat, void* str) {
    dat.insert(0, *(std::string*)str);
}

template <typename Data>
void StringInsert(lasd::Matrix<Data>& con) {
    std::string str;
    std::cout<< std::endl << "Inserisci la stringa da inserire in testa ad ogni elemento:" << std::endl;
    std::cin.clear();
    std::cin>>str;
    con.MapPreOrder(&MapInsert<Data>, &str);
}

template <typename Data>
void MatrixOperations(lasd::Matrix<Data>& mat) {
    char choice;
    bool end = false;
    while (!end)
    {
        std::cout<< std::endl << "Selezionare l'azione da intraprendere: " << std::endl << "[A]ccesso    [R]idimensionamento    [E]sci" << std::endl;
        std::cin.clear();
        std::cin>>choice;
        choice = std::toupper(choice);
        while (choice != 'A' && choice != 'R' && choice != 'E')
        {
            std::cout << std::endl <<"Inserire uno tra A, R oppure E..."<< std::endl;
            std::cin.clear();
            std::cin>>choice;
            choice = std::toupper(choice);
        }
        if (choice == 'A')
        {
            int n, m;
            do
            {
                std::cout<< std::endl << "Inserire il numero di riga e di colonna (separate da invio) della cella su cui operare..."<< std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin>> n >> m;
            } while (std::cin.fail());
            std::cout<< std::endl << "Definire il tipo di accesso" << std::endl << "[R]ead    [W]rite    [E]xistence" << std::endl;
            std::cin.clear();
            std::cin>>choice;
            choice = std::toupper(choice);
            while (choice != 'R' && choice != 'W' && choice != 'E')
            {
                std::cout<< std::endl << "Inserire uno tra R, W oppure E..."<< std::endl;
                std::cin.clear();
                std::cin>>choice;
                choice = std::toupper(choice);
            }
            if (choice == 'R')
            {
                try
                {
                    std::cout<< std::endl << "L'elemento della cella a cui si ha effettuato accesso è: " << const_cast<const lasd::Matrix<Data>& >(mat)(n, m) << std::endl;
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << std::endl;
                }
            }
            else if (choice == 'W')
            {
                Data elem;
                do
                {
                    std::cout<< std::endl <<"Quale elemento inserire nella cella selezionata?"<< std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin>>elem;
                } while(std::cin.fail());
                try
                {
                    mat(n, m) = elem;
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }
            }
            else if (choice == 'E')
                std::cout << std::endl << "La cella (" + std::to_string(n) + "," + std::to_string(m) + ")" + (mat.ExistsCell(n,m) ? "" : " non") + " esiste!";
        }
        else if (choice == 'R')
        {
            unsigned long n;
            std::cout << std::endl << "Ridimensionare le righe o le colonne? " << std::endl << "    [R]ighe    [C]olonne" << std::endl;
            std::cin.clear();
            std::cin >> choice;
            choice = std::toupper(choice);
            while (choice != 'R' && choice != 'C')
            {
                std::cout << std::endl << "Inserire uno tra R e C..." << std::endl;
                std::cin.clear();
                std::cin >> choice;
                choice = std::toupper(choice);
            }
            do
            {
                std::cout << std::endl << "Inserire la nuova dimensione da assegnare..." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin>> n;
            } while (std::cin.fail());
            if (choice == 'R')
                mat.RowResize(n);

            else if (choice == 'C')
                mat.ColumnResize(n);
        }
        else if (choice == 'E')
            end = true;
    }
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
                    else if (choice == 'E')
                        ElemExists(mat);
                    else if (choice == 'F')
                        SmallerThanNProd(mat);
                    else if (choice == 'M')
                        mat.MapPreOrder(&MapDouble<int>, 0);
                    else if (choice == 'S')
                        MatrixOperations(mat);
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
                    else if (choice == 'E')
                        ElemExists(mat);
                    else if (choice == 'F')
                        BiggerThanNSum(mat);
                    else if (choice == 'M')
                        mat.MapPreOrder(&MapInverseCube<float>, 0);
                    else if (choice == 'S')
                        MatrixOperations(mat);
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
                    else if (choice == 'E')
                        ElemExists(mat);
                    else if (choice == 'F')
                        ShorterThanNConcat(mat);
                    else if (choice == 'M')
                        StringInsert(mat);
                    else if (choice == 'S')
                        MatrixOperations(mat);
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
                    else if (choice == 'E')
                        ElemExists(mat);
                    else if (choice == 'F')
                        SmallerThanNProd(mat);
                    else if (choice == 'M')
                        mat.MapPreOrder(&MapDouble<int>, 0);
                    else if (choice == 'S')
                        MatrixOperations(mat);
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
                    else if (choice == 'E')
                        ElemExists(mat);
                    else if (choice == 'F')
                        BiggerThanNSum(mat);
                    else if (choice == 'M')
                        mat.MapPreOrder(&MapInverseCube<float>, 0);
                    else if (choice == 'S')
                        MatrixOperations(mat);
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
                    else if (choice == 'E')
                        ElemExists(mat);
                    else if (choice == 'F')
                        ShorterThanNConcat(mat);
                    else if (choice == 'M')
                        StringInsert(mat);
                    else if (choice == 'S')
                        MatrixOperations(mat);
                    else if (choice == 'Q')
                        end = true;
                }
            }
        }
    }
    else
        std::cout << std::endl << "Goodbye!" << std::endl;
}