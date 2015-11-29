#include <iostream>
#include "Menu.h"




Menu::Menu(): m_choixMenu('0'), m_motDePasse("Snoop")
{

}

Menu::~Menu()
{

}

void Menu::afficherMenu()
{
    std::string choixMenu("0");
    setChoixMenu(choixMenu[0]);


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
        if(choixMenu.size()== 1)
        this->setChoixMenu(choixMenu[0]);
        else
        choixMenu = "0";
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
         case '3':
            this->creerPartie(decisionJoueur);
            break;
         case '4':
           highscore(10,0);
            break;
         case '5':
            system("cls");
            for(int i(0); i<7; i++)std::cout << std::endl;
            std::cout << "      Appuyez sur echap pour fermer la fenetre" << std::endl;
            for(int i(0); i<7; i++)std::cout << std::endl;
            break;
         default:
            this->setChoixMenu('0');
            this->afficherMenu();
      }
}


void Menu::creerPartie(char decisionJoueurMenu)
{
    std::string pseudoDonne;
    std::string decisionJoueurNiveau;
    std::string motDePasse;

    std::string const dossier("sauvegarde//");
    std::string nom;
    std::string const extention(".txt");
    std::string nomFichier;

    Partie *m_partie = new Partie();

    if(decisionJoueurMenu == '1')
    {
        std::cout << "Creer votre pseudo ou 'r' pour revenir" << std::endl;
        std::cin >> pseudoDonne;
        nom = pseudoDonne;
        nomFichier = dossier + nom + extention;

         if(!is_readable(nomFichier) && nom != "r")
            {
            m_partie->jouer(m_partie, decisionJoueurMenu, nom, "1");
            delete m_partie;
            }
    }

    if(decisionJoueurMenu == '2')
    {
        std::cout << "Entrer votre pseudo ou 'r' pour revenir" << std::endl;
        std::cin >> pseudoDonne;
        nom = pseudoDonne;
        nomFichier = dossier + nom + extention;
        if(is_readable(nomFichier) && nom != "r")
        {
            while((decisionJoueurNiveau<"0" || decisionJoueurNiveau>"3") && decisionJoueurNiveau != "r")
                {
                std::cout << "Aller au niveau deja atteint avec '1', '2' ou '3' ou revenir a la derniere sauvegarde en avec '0', 'r' pour revenir" << std::endl;
                std::cin >> decisionJoueurNiveau;
                }

            if(decisionJoueurNiveau != "r" )
               {
                m_partie->jouer(m_partie, decisionJoueurMenu, nom, decisionJoueurNiveau);
                delete m_partie;
               }

        }
    }

    if(decisionJoueurMenu == '3')
    {
        std::cout << "Entrer le mot de passe ou 'r' pour revenir" << std::endl;
        std::cin >> motDePasse;
        if(motDePasse == m_motDePasse && nom != "r")
        {
            while((decisionJoueurNiveau<"1" || decisionJoueurNiveau>"3") && decisionJoueurNiveau != "r")
                {
                std::cout << "Aller au niveau deja atteint avec '1', '2' ou '3' ou 'r' pour revenir" << std::endl;
                std::cin >> decisionJoueurNiveau;
                }

            if(decisionJoueurNiveau != "r" )
               {
                m_partie->jouer(m_partie, decisionJoueurMenu, "rien", decisionJoueurNiveau);
                delete m_partie;
               }

        }
    }



    system("cls");
    afficherMenu();
}


char Menu::getChoixMenu() const
{
  return m_choixMenu;
}

///Choix du Menu
void Menu::setChoixMenu(char choixMenu)
{
    if(this->getChoixMenu()<'1' || this->getChoixMenu()>'5')
    this->m_choixMenu = choixMenu;
    else
    this->m_choixMenu ='0';
}

/// Fonction qui renvoie erreure si le fichier n'est pas lisible
bool Menu::is_readable( const std::string & file )
{
    std::ifstream fichier( file.c_str() );
    return !fichier.fail();
}

///Highscore
void Menu::highscore( int TempsRestant, int score)

 {
        std::string const dossier("sauvegarde//");
        std::string nom("score");
        std::string const extention(".txt");
        std::string nomFichier = dossier + nom + extention;

        char caracRetour('@');

    int meilleurScoreAct=0;
    std::string pseudo;

    if(score> meilleurScoreAct)
    {
        meilleurScoreAct=score;
    }

    system("cls");

    if(is_readable(nomFichier))
    {
        std::ifstream fichier(nomFichier.c_str(), std::ios::in);  // on ouvre

        if(fichier)
        {
            fichier>> meilleurScoreAct;
            fichier>> pseudo;
            if(meilleurScoreAct > 0){
            std::cout << "Le meilleur score jamais atteint est : " << meilleurScoreAct << ", obtenu par " << pseudo << std::endl;}
            if(meilleurScoreAct == 0){
            std::cout << "Pas encore de record... " << std::endl;}
            if(meilleurScoreAct <0){
            std::cout << "Probleme score negatif... " << std::endl;}
            if(meilleurScoreAct == 'EOF'){
            std::cout << "Pas encore de record... " << std::endl;}

            
            

            fichier.close();
        }
        else
        {
            std::cout << "Impossible d'ouvrir le fichier !!" << std::endl;
        }
    }

    if(!is_readable(nomFichier))
    {
    std::cout << "Pas encore de record... ";
    }

    std::cout << std::endl;
    std::cout << "appuyer sur 'r' pour revenir au menu " << std::endl;
    while(caracRetour != 'r')
    {
        if(kbhit())
        {
        caracRetour = getch();
        }
    }

    afficherMenu();

 }

