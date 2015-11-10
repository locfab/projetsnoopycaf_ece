#include <iostream>
#include "Menu.h"


Menu::Menu()
{
}

void Menu::afficherMenu()
{

	std::cout << "1- Jouer" << std::endl;
	std::cout << "2- Charger partie" << std::endl;
	std::cout << "3- Mot de passe" << std::endl;
	std::cout << "4- Score" << std::endl;
	std::cout << "5- Quitter" << std::endl;

	std::cin >> this->m_choixMenu;
}
