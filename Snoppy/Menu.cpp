#include <iostream>
#include "Menu.h"
#include "PersoSnoopy.h"
#include "Niveau.h"



Menu::Menu()
{
}

void Menu::afficherMenu()
{
    char choixMenu('0');

    while(this->getChoixMenu()<'1' || this->getChoixMenu()>'5')
     {
        this->setChoixMenu('0');

        std::cout << "1- Jouer" << std::endl;
        std::cout << "2- Charger partie" << std::endl;
        std::cout << "3- Mot de passe" << std::endl;
        std::cout << "4- Score" << std::endl;
        std::cout << "5- Quitter" << std::endl;

        std::cout << "Faites votre choix: " << std::endl;
        std::cin >> choixMenu;
        this->setChoixMenu(choixMenu);
     }

     this->choix(getChoixMenu());
}

void Menu::choix(char decisionJoueur)
{
    switch (decisionJoueur)
      {
         case '2':
            this->creerPartie();
            break;
         case 'a':
            std::cout << "il reste a faire" << std::endl;
            break;
         default:
            this->setChoixMenu('0');
            this->afficherMenu();
      }
}


void Menu::creerPartie()
{
    PersoSnoopy* m_snoopy = new PersoSnoopy();
    Niveau* m_niveau = new Niveau();
    m_niveau->setPlateau("ChaineDeCaractere");
    m_niveau->afficherPlateau();
}

char Menu::getChoixMenu() const
{
  return m_choixMenu;
}
void Menu::setChoixMenu(char choixMenu)
{
    if(this->getChoixMenu()<'1' || this->getChoixMenu()>'5')
    this->m_choixMenu = choixMenu;
    else
    this->m_choixMenu ='0';
}
