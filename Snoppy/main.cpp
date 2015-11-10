#include <iostream>
#include "Menu.h"



int main()
{

    Menu* menu = new Menu;
    menu->afficherMenu();
    return 0;
}


    /*
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
    std::cout << snoopy->getVivant() << std::endl;*/
