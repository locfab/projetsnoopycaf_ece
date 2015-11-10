#include <iostream>
#include "PersoSnoopy.h"
#include "BlocsPoussables.h"
#include "BlocsCassables.h"
#include "BlocsPieges.h"


int main()
{
    PersoSnoopy* snoopy = new PersoSnoopy();
    BlocsPoussables* blocsPoussables = new BlocsPoussables(2,2,true);
    BlocsPoussables* sblocsPoussables = new BlocsPoussables();
    BlocsCassables* blocsCassables = new BlocsCassables(3,3);
    BlocsCassables* sblocsCassables = new BlocsCassables();
    BlocsPieges* blocsPieges = new BlocsPieges(4,4);
    BlocsPieges* sblocsPieges = new BlocsPieges();
    std::cout << snoopy->getNbOiseauAttrap() << std::endl;
    snoopy->setPlusOiseau();
    snoopy->setPlusOiseau();
    std::cout << snoopy->getVivant() << std::endl;
    snoopy->setVivant(false);
    std::cout << snoopy->getNbOiseauAttrap() << std::endl;
    std::cout << snoopy->getVivant() << std::endl;
    return 0;
}
