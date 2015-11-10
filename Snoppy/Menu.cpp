#include <iostream>
#include "Menu.h"
#include "PersoSnoopy.h"
#include "Niveau.h"



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

  std::cout << "Faites votre choix: " << std::endl; // A blinder ou ˆ faire autre part
	std::cin >> this->m_choixMenu;
	this->choix(m_choixMenu);
}

void Menu::choix(char decisionJoueur)
{
    switch (decisionJoueur)
      {
         case '2':
            this->creerPartie();
            break;
         case 'a':
            std::cout << "tu as tapŽ 'a'" << std::endl;
            break;
         default:
            this->m_choixMenu = 0;
            this->afficherMenu();
      }
}


void Menu::creerPartie()
{
    PersoSnoopy* m_snoopy = new PersoSnoopy();
    Niveau* m_niveau = new Niveau();


}
