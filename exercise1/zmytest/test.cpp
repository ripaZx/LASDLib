#include "test.hpp"

#include <iostream>
#include <random>
#include <iomanip>
#include <algorithm>

void StructureSelection(char& sInput, char& tInput) {
    std::cout<< std::endl <<"Selezionare la struttura su cui lavorare:"<< std::endl <<"    [V]ettore    [L]ista..."<< std::endl;
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
void RandPopulateVecInt(lasd::Vector<Data>& vec, const unsigned long& n) {
    std::default_random_engine gen(std::random_device{}());
    std::uniform_int_distribution<Data> dist(1, 100);
    for (unsigned long i=0; i<n; i++)
        vec[i] = (dist(gen));
}

template <typename Data>
void RandPopulateLisInt(lasd::List<Data>& lis, const unsigned long& n) {
    std::default_random_engine gen(std::random_device{}());
    std::uniform_int_distribution<Data> dist(1, 100);
    for (unsigned long i=0; i<n; i++)
        lis.InsertAtBack(dist(gen));
}

template <typename Data>
void RandPopulateVecReal(lasd::Vector<Data>& vec, const unsigned long& n) {
    std::default_random_engine gen(std::random_device{}());
    std::uniform_real_distribution<Data> dist(1, 99);
    for(unsigned long i=0; i<n; i++)
        vec[i] = (dist(gen));
}

template <typename Data>
void RandPopulateLisReal(lasd::List<Data>& lis, const unsigned long& n) {
    std::default_random_engine gen(std::random_device{}());
    std::uniform_real_distribution<Data> dist(1, 30);
    for (unsigned long i=0; i<n; i++)
        lis.InsertAtBack(dist(gen));
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

template <typename Data>
void RandPopulateLisString(lasd::List<Data>& lis, const unsigned long& n) {
    std::default_random_engine gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(97, 122);
    std::default_random_engine lenGen(std::random_device{}());
    std::uniform_int_distribution<int> lenDist(1, 16);
    for (unsigned long i=0; i<n; i++)
    {
        std::string randString;
        for (int j=0; j<(lenDist(lenGen)); j++)
            randString.append(1, static_cast<char>(dist(gen)));
        
        lis.InsertAtBack(randString);
    }
}

template <typename Data>
void PrintElement(const lasd::LinearContainer<Data>& con) {
    char input;
    std::cout<< std::endl << "Selezionare quale elemento stampare:"<< std::endl << "    [P]rimo    [U]ltimo    [I]ndice" << std::endl;
    std::cin>>input;
    input = std::toupper(input);
    while(input != 'P' && input != 'U' && input != 'I')
    {
        std::cout<< std::endl <<"Inserire uno tra: P, U, I..."<< std::endl;
        std::cin.clear();
        std::cin>>input;
        input = std::toupper(input);
    }
    if (input == 'P')
    {
        try
        {
            std::cout<< "Il primo elemento della struttura è: " << std::setprecision(17) << con.Front() << std::endl;
        }
        catch(const std::length_error& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
    else if (input == 'U')
    {
        try
        {
            std::cout<< "L'ultimo elemento della struttura è: " << std::setprecision(17) << con.Back() << std::endl;
        }
        catch(const std::length_error& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
    else if (input == 'I')
    {
        unsigned long i;
        do 
        {
            std::cout<< std::endl << "Inserire l'indice da visualizzare..." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin>>i;
        } while (std::cin.fail());
        try
        {
            std::cout<< std::endl << "Elemento all'indice " << i << ": " << std::setprecision(17) << con[i] << std::endl;
        }
        catch(const std::out_of_range& e)
        {
            std::cerr << std::endl << e.what() << std::endl;
        }
    }
}

template <typename Data>
void MapPrint(const Data& dat, void* _) {
  std::cout<< std::setprecision(17) << dat << " ";
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
void AuxFoldSum(const Data& dat, const void* val, void* sum) {
    if (dat < *((int*)val))
        *((int*)sum) += dat;
}

template <typename Data>
void SmallerThanNSum(const lasd::FoldableContainer<Data>& con) {
    int n;
    int sum = 0;
    do
    {
        std::cout<< std::endl << "Sommare gli elementi minori di quale numero?" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin>>n;
    } while (std::cin.fail());
    con.FoldPreOrder(&AuxFoldSum<Data>, &n, &sum);
    std::cout<< std::endl << "La somma richiesta è: " << sum << std::endl;
}

template <typename Data>
void AuxFoldProd(const Data& dat, const void* val, void* prod) {
    if (dat > *((float*)val))
        *((float*)prod) = *((float*)prod)*dat;
}

template <typename Data>
void BiggerThanNProd(const lasd::FoldableContainer<Data>& con) {
    float n;
    float prod = 1;
    do
    {
        std::cout<< std::endl << "Moltiplicare gli elementi maggiori di quale numero?" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin>>n;
    } while (std::cin.fail());
    con.FoldPreOrder(&AuxFoldProd<Data>, &n, &prod);
    std::cout<< std::endl << "Il prodotto richiesto è: " << prod << std::endl;
}

template <typename Data>
void AuxFoldConcat(const std::string& dat, const void* val, void* reString) {
    if(dat.length() <= *((int*)val))
        ((std::string*)reString)->append(dat);
}

template <typename Data>
void ShorterThanNConcat(const lasd::FoldableContainer<Data>& con) {
    int n;
    std::string reString{};
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
void MapSquare(Data& dat, void* _) {
    dat *= dat;
}

template <typename Data>
void MapUppercase(Data& dat, void* _) {
    std::transform(dat.begin(), dat.end(), dat.begin(), [](unsigned char c){ return std::toupper(c); });
}

template <typename Data>
void VecResize(lasd::Vector<Data>& vec) {
    unsigned long n;
    std::cout<< std::endl <<"Ridimensionamento vettore" << std::endl;
    do
    {
        std::cout<< std::endl << "Inserire la nuova dimensione del vettore: " << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin>>n;
    } while (std::cin.fail());
    vec.Resize(n);
}

template <typename Data>
void LisInsOrRem(lasd::List<Data>& lis) {
    char choice;
    std::cout<< std::endl << "Inserimento o rimozione di un elemento dalla lista" << std::endl << "[I]nserimento    [R]imozione" << std::endl;
    std::cin.clear();
    std::cin>>choice;
    choice = std::toupper(choice);
    while(choice != 'I' && choice != 'R')
    {
        std::cout<< std::endl <<"Inserire I oppure R..."<< std::endl;
        std::cin.clear();
        std::cin>>choice;
        choice = std::toupper(choice);
    }
    if (choice == 'I')
    {
        Data elem;
        do
        {
            std::cout<< std::endl <<"Quale elemento inserire nella lista?"<< std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin>>elem;
        } while(std::cin.fail());
        std::cout<< std::endl <<"Si desidera inserire in testa o in coda alla lista?" << std::endl << "[T]esta    [C]oda" << std::endl;
        std::cin.clear();
        std::cin>>choice;
        choice = std::toupper(choice);
        while (choice != 'T' && choice != 'C')
        {
            std::cout << std::endl << "Inserire T oppure C..." << std::endl;
            std::cin.clear();
            std::cin>>choice;
            choice = toupper(choice);
        }
        if (choice == 'T')
            lis.InsertAtFront(std::move(elem));
        else if (choice == 'C')
            lis.InsertAtBack(std::move(elem));
    }
    else if(choice == 'R')
    {
        std::cout<< std::endl <<"Si desidera rimuovere semplicemente o con visualizzazione?" << std::endl << "[R]emove    [F]rontNRemove" << std::endl;
        std::cin.clear();
        std::cin>>choice;
        choice = std::toupper(choice);
        while(choice != 'R' && choice != 'F')
        {
            std::cout << std::endl << "Inserire R oppure F..." << std::endl;
            std::cin.clear();
            std::cin>>choice;
            choice = toupper(choice);
        }
        if (choice == 'R')
        {
            try
            {
                lis.RemoveFromFront();
            }
            catch(const std::length_error& e)
            {
                std::cerr << e.what() << std::endl;
            }
            std::cout<< std::endl << "Rimozione effettuata" << std::endl;
        }
        else if (choice == 'F')
        {
            try
            {
                std::cout<< "Rimozione dell'elemento... " << lis.FrontNRemove() << " effettuata";
            }
            catch(const std::length_error& e)
            {
                std::cerr << e.what() << std::endl;
            }
        }
    }
}

void PrintMenu(char& choice) {
    std::cout<< std::endl <<"Selezionare una funzione:" << std::endl << "[E]lement_Print    [P]rint_Structure    [C]heck_Existence    [F]old_Operation    [M]ap_Operation    [S]tructure_Specific_Operation    [Q]uit    " << std::endl;
    std::cin.clear();
    std::cin>>choice;
    choice = std::toupper(choice);
    while(choice != 'E' && choice != 'P' && choice != 'C' && choice != 'F' && choice != 'M' && choice != 'S' && choice != 'Q')
    {
        std::cout<< std::endl <<"Inserire uno tra E, P, C, F, M, S oppure Q..."<< std::endl;
        std::cin.clear();
        std::cin>>choice;
        choice = std::toupper(choice);
    }
}

void testMenu() {
    char tInput, sInput, mInput;
    unsigned long n;
    bool end = false;
    char choice;
    StructureSelection(sInput, tInput);
    do
    {
        std::cout<< std::endl << "Inserire il numero di elementi con cui popolare la struttura..."<< std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin>>n;
    } while (std::cin.fail());
    if (sInput == 'V')
    {
        if(tInput == 'I')
        {
            lasd::Vector<int> vec(n);
            RandPopulateVecInt(vec, n);
            while (!end)
            {
                PrintMenu(choice);
                if (choice == 'E')
                    PrintElement(vec);
                else if (choice == 'P')
                {
                    std::cout<< "Procedo alla stampa di tutti gli elementi della struttura: " << std::endl;
                    vec.MapPreOrder(&MapPrint<int>, 0);
                }
                else if (choice == 'C')
                    ElemExists(vec);
                else if (choice == 'F')
                    SmallerThanNSum(vec);
                else if (choice == 'M')
                {
                    std::cout<< std::endl <<"Raddoppio tutti i valori della struttura" << std::endl;
                    vec.MapPreOrder(&MapDouble<int>, 0);
                }
                else if (choice == 'S')
                    VecResize(vec);
                else if (choice == 'Q')
                    end = true;
            }
        }
        else if (tInput == 'D')
        {
            lasd::Vector<double> vec(n);
            RandPopulateVecReal(vec, n);
            while (!end)
            {
                PrintMenu(choice);
                if (choice == 'E')
                    PrintElement(vec);
                else if (choice == 'P')
                {
                    std::cout<< "Procedo alla stampa di tutti gli elementi della struttura: " << std::endl;
                    vec.MapPreOrder(&MapPrint<double>, 0);
                }
                else if (choice == 'C')
                    ElemExists(vec);
                else if (choice == 'F')
                    BiggerThanNProd(vec);
                else if (choice == 'M')
                {
                    std::cout<< std::endl <<"Eseguo il quadrato di tutti i valori della struttura" << std::endl;
                    vec.MapPreOrder(&MapSquare<double>, 0);
                }
                else if (choice == 'S')
                    VecResize(vec);
                else if (choice == 'Q')
                    end = true;
            }
        }
        else if (tInput == 'S')
        {
            lasd::Vector<std::string> vec(n);
            RandPopulateVecString(vec, n);
            while (!end)
            {
                PrintMenu(choice);
                if (choice == 'E')
                    PrintElement(vec);
                else if (choice == 'P')
                {
                    std::cout<< "Procedo alla stampa di tutti gli elementi della struttura: " << std::endl;
                    vec.MapPreOrder(&MapPrint<std::string>, 0);
                }
                else if (choice == 'C')
                    ElemExists(vec);
                else if (choice == 'F')
                    ShorterThanNConcat(vec);
                else if (choice == 'M')
                {
                    std::cout<< std::endl <<"Trasformo le stringhe da lowercase ad uppercase..." << std::endl;
                    vec.MapPreOrder(&MapUppercase<std::string>, 0);
                }
                else if (choice == 'S')
                    VecResize(vec);
                else if (choice == 'Q')
                    end = true;
            }
        }
    }
    else if (sInput == 'L')
    {
        if(tInput == 'I')
        {
            lasd::List<int> lis;
            RandPopulateLisInt(lis, n);
            while (!end)
            {
                PrintMenu(choice);
                if (choice == 'E')
                    PrintElement(lis);
                else if (choice == 'P')
                {
                    std::cout<< "Procedo alla stampa di tutti gli elementi della struttura: " << std::endl;
                    lis.MapPreOrder(&MapPrint<int>, 0);
                }
                else if (choice == 'C')
                    ElemExists(lis);
                else if (choice == 'F')
                    SmallerThanNSum(lis);
                else if (choice == 'M')
                {
                    std::cout<< std::endl <<"Raddoppio tutti i valori della struttura" << std::endl;
                    lis.MapPreOrder(&MapDouble<int>, 0);
                }
                else if (choice == 'S')
                    LisInsOrRem(lis);
                else if (choice == 'Q')
                    end = true;
            }
        }
        else if (tInput == 'D')
        {
            lasd::List<double> lis;
            RandPopulateLisReal(lis, n);
            while (!end)
            {
                PrintMenu(choice);
                if (choice == 'E')
                    PrintElement(lis);
                else if (choice == 'P')
                {
                    std::cout<< "Procedo alla stampa di tutti gli elementi della struttura: " << std::endl;
                    lis.MapPreOrder(&MapPrint<double>, 0);
                }
                else if (choice == 'C')
                    ElemExists(lis);
                else if (choice == 'F')
                    BiggerThanNProd(lis);
                else if (choice == 'M')
                {
                    std::cout<< std::endl <<"Eseguo il quadrato di tutti i valori della struttura" << std::endl;
                    lis.MapPreOrder(&MapSquare<double>, 0);
                }
                else if (choice == 'S')
                    LisInsOrRem(lis);
                else if (choice == 'Q')
                    end = true;
            }
        }
        else if (tInput == 'S')
        {
            lasd::List<std::string> lis;
            RandPopulateLisString(lis, n);
            while (!end)
            {
                PrintMenu(choice);
                if (choice == 'E')
                    PrintElement(lis);
                else if (choice == 'P')
                {
                    std::cout<< "Procedo alla stampa di tutti gli elementi della struttura: " << std::endl;
                    lis.MapPreOrder(&MapPrint<std::string>, 0);
                }
                else if (choice == 'C')
                    ElemExists(lis);
                else if (choice == 'F')
                    ShorterThanNConcat(lis);
                else if (choice == 'M')
                {
                    std::cout<< std::endl <<"Trasformo le stringhe da lowercase ad uppercase..." << std::endl;
                    lis.MapPreOrder(&MapUppercase<std::string>, 0);
                }
                else if (choice == 'S')
                    LisInsOrRem(lis);
                else if (choice == 'Q')
                    end = true;
            }
        }
    }
    std::cout<< std::endl << "Si vuole passare al test LASD? [Y/N]" << std::endl;
    std::cin>> mInput;
    mInput = std::toupper(mInput);
    while (mInput != 'Y' && mInput != 'N')
    {
        std::cout<< std::endl <<"Inserire Y oppure N..."<< std::endl;
        std::cin.clear();
        std::cin>>mInput;
        mInput = std::toupper(mInput);
    }
    if (mInput == 'Y')
        lasdtest();
    else
        std::cout<< std::endl << "Goodbye!" << std::endl;
}