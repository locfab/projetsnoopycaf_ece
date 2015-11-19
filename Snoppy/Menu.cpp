#include <iostream>
#include "Menu.h"
#include "Partie.h"



Menu::Menu(): m_choixMenu('0'), m_motDePasse("Snoop")
{

}

Menu::~Menu()
{

}

void Menu::afficherMenu()
{
    char choixMenu('0');
    setChoixMenu(choixMenu);


    while(this->getChoixMenu()<'1' || this->getChoixMenu()>'5')
     {
        this->setChoixMenu('0');

        system("cls");

        std::cout << "1- Jouer" << std::endl << std::endl;
        std::cout << "2- Charger partie" << std::endl << std::endl;
        std::cout << "3- Mot de passe" << std::endl << std::endl;
        std::cout << "4- Score" << std::endl << std::endl;
        std::cout << "5- Quitter" << std::endl << std::endl;

        std::cout << "Faites votre choix:  ";
        std::cin.clear();
        std::cin >> choixMenu;
        this->setChoixMenu(choixMenu);
     }

     this->choix(getChoixMenu());
}

void Menu::choix(char decisionJoueur)
{
    switch (decisionJoueur)
      {
         case '1':
            this->creerPartie(decisionJoueur);
            break;
         case '2':
            this->creerPartie(decisionJoueur);
            break;
         default:
            this->setChoixMenu('0');
            this->afficherMenu();
      }
}


void Menu::creerPartie(char decisionJoueur)
{
    std::string pseudoDonne;

    std::string const dossier("sauvegarde//");
    std::string nom;
    std::string const extention(".txt");
    std::string nomFichier;

    Partie *m_partie = new Partie();
    if(decisionJoueur == '2')
    {
        std::cout << "Entrer votre pseudo" << std::endl;
        std::cin >> pseudoDonne;
        nom = pseudoDonne;
        nomFichier = dossier + nom + extention;
        if(is_readable(nomFichier))
        {
         m_partie->jouer(m_partie, decisionJoueur, nom);
        }
    }
    if(decisionJoueur == '1')
    {
        std::cout << "Creer votre pseudo" << std::endl;
        std::cin >> pseudoDonne;
        nom = pseudoDonne;
        nomFichier = dossier + nom + extention;

        if(!is_readable(nomFichier))
        {
        m_partie->jouer(m_partie, decisionJoueur, nom);
        }
    }
    delete m_partie;
    system("cls");
    afficherMenu();
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

bool Menu::is_readable( const std::string & file )
{
    std::ifstream fichier( file.c_str() );
    return !fichier.fail();
}
