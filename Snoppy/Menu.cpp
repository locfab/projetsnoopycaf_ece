#include <iostream>
#include "Menu.h"




Menu::Menu(): m_motDePasse("Snoop"), m_choixMenu('0')
{

}

Menu::~Menu()
{

}

void Menu::afficherMenu()
{
    std::string choixMenu("0");
    setChoixMenu(choixMenu[0]);
    char position('1');
    char valeurEntree;
    int a(0);

        std::cout << "\n\n\n\t\t\t\tLa Revanche de Snoopy \n\n\n" << std::endl << std::endl;
        std::cout << "=>";
        std::cout << "\t\t\t\t1- Jouer" << std::endl << std::endl;
        std::cout << "\t\t\t\t2- Charger partie" << std::endl << std::endl;
        std::cout << "\t\t\t\t3- Mot de passe" << std::endl << std::endl;
        std::cout << "\t\t\t\t4- Score" << std::endl << std::endl;
        std::cout << "\t\t\t\t5- Quitter" << std::endl << std::endl;
        std::cout << "1" << std::endl << std::endl << std::endl << "     Defilement avec 'i' , 'j' et 'e' ou 'espace' pour Entrer" << std::endl ;
    while(this->getChoixMenu()<'1' || this->getChoixMenu()>'5')
     {
        this->setChoixMenu('0');

        if(kbhit())
        {
        valeurEntree = getch();
        system("cls");


        if(valeurEntree == 'i' && position > '1')
        position -= 1;
        if(valeurEntree == 'k' && position < '5')
        position += 1;

        std::cout << "\n\n\n\t\t\t\tLa Revanche de Snoopy \n\n\n" << std::endl << std::endl;
        if(position == '1') std::cout << "=>";
        std::cout << "\t\t\t\t1- Jouer" << std::endl << std::endl;
        if(position == '2') std::cout << "=>";
        std::cout << "\t\t\t\t2- Charger partie" << std::endl << std::endl;
        if(position == '3') std::cout << "=>";
        std::cout << "\t\t\t\t3- Mot de passe" << std::endl << std::endl;
        if(position == '4') std::cout << "=>";
        std::cout << "\t\t\t\t4- Score" << std::endl << std::endl;
        if(position == '5') std::cout << "=>";
        std::cout << "\t\t\t\t5- Quitter" << std::endl << std::endl;
        std::cout << position << std::endl << std::endl << std::endl << "     Defilement avec 'i' , 'j' et 'e' ou 'espace' pour Entrer" << std::endl ;
        }

        if(valeurEntree=='e' || valeurEntree == 'E' || valeurEntree == 32)
        {
            choixMenu[0] = position;
            if(choixMenu.size()== 1)
            this->setChoixMenu(choixMenu[0]);
            else
            choixMenu = "0";
        }

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



    if(decisionJoueurMenu == '1')
    {
        system("cls");
        std::cout << "\n\n\n\n\n Creez votre pseudo ou appuyez sur 'r' pour revenir en arriere : ";
        std::cin >> pseudoDonne;
        nom = pseudoDonne;
        nomFichier = dossier + nom + extention;

         if(!is_readable(nomFichier) && nom != "r")
            {
            Partie *m_partie = new Partie(decisionJoueurMenu, "1", nom);
            m_partie->jouer(m_partie, decisionJoueurMenu, nom, "1");
            delete m_partie;
            }
    }

    if(decisionJoueurMenu == '2')
    {
        system("cls");

        std::cout << "\n\n\n\n\n\tEntrer votre pseudo ou 'r' pour revenir : ";
        std::cin >> pseudoDonne;
        nom = pseudoDonne;
        nomFichier = dossier + nom + extention;
        if(is_readable(nomFichier) && nom != "r")
        {
            while((decisionJoueurNiveau<"0" || decisionJoueurNiveau>"3") && decisionJoueurNiveau != "r")
                {
                std::cout << "\n\n\nAller au niveau deja atteint avec '1', '2' ou '3'\nRevenir a la derniere sauvegarde avec '0'\nRevenir en arriere avec 'r'" << std::endl;
                std::cin >> decisionJoueurNiveau;
                }

            if(decisionJoueurNiveau != "r" )
               {
                Partie *m_partie = new Partie(decisionJoueurMenu, decisionJoueurNiveau, nom);
                m_partie->jouer(m_partie, decisionJoueurMenu, nom, decisionJoueurNiveau);
                delete m_partie;
               }

        }
    }

    if(decisionJoueurMenu == '3')
    {
        system("cls");
        std::cout << "\n\n\n\n\n Appuyez sur 'r' pour revenir en arriere." << std::endl << std::endl;
        std::cout << " Entrez le mot de passe : ";
        std::cin >> motDePasse;
        if(motDePasse == m_motDePasse && nom != "r")
        {
            while((decisionJoueurNiveau<"1" || decisionJoueurNiveau>"3") && decisionJoueurNiveau != "r")
                {
                std::cout << "\n\n Choisissez le niveau souhaite parmi (1), (2) et (3) : ";
                std::cin >> decisionJoueurNiveau;
                }

            if(decisionJoueurNiveau != "r" )
               {
                Partie *m_partie = new Partie(decisionJoueurMenu, decisionJoueurNiveau, "rien");
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
            if(fichier.eof()){
            std::cout << "\n\n\n\n Pas encore de record... " << std::endl;}
            fichier>> meilleurScoreAct;
            fichier>> pseudo;
            if(meilleurScoreAct > 0){
            std::cout << "\n\n\n Le meilleur score jamais atteint est de " << meilleurScoreAct << " points, obtenu par " << pseudo << std::endl;}
            if(meilleurScoreAct == 0){
            std::cout << "\n\n\n Pas encore de record... " << std::endl;}
            if(meilleurScoreAct <0){
            std::cout << "Probleme score negatif... " << std::endl;}

            fichier.close();
        }
        else
        {
            std::cout << "Impossible d'ouvrir le fichier !!" << std::endl;
        }
    }

    if(!is_readable(nomFichier))
    {
    std::cout << "\n\n\n Pas encore de record... ";
    }

    std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;
    std::cout << " Appuyer sur 'r' pour revenir au menu principal" << std::endl;
    while(caracRetour != 'r')
    {
        if(kbhit())
        {
        caracRetour = getch();
        }
    }

    afficherMenu();

 }

