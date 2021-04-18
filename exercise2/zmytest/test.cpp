#include "test.hpp"

#include <iostream>

void testMenu() {
    char lasdInput;
    std::cout<< std::endl << "Si vuole eseguire il test LASD? [Y/N]" << std::endl;
    std::cin>> lasdInput;
    lasdInput = std::toupper(lasdInput);
    while (lasdInput != 'Y' && lasdInput != 'N')
    {
        std::cout<< std::endl <<"Inserire Y oppure N..."<< std::endl;
        std::cin.clear();
        std::cin>>lasdInput;
        lasdInput = std::toupper(lasdInput);
    }
    if (lasdInput == 'Y')
        lasdtest();
    else
        std::cout<< std::endl << "Goodbye!" << std::endl;
}