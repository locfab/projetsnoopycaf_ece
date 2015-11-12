#include <iostream>
#include "Niveau.h"
#include <fstream>

/// Constructeur par défaut
Niveau::Niveau()
            :   m_niveauCourant(0)
{
    // Alloue la mémoire du pointeur
    pConsole = Console::getInstance();
    m_temps = new Temps();
    m_tempsRestant = m_temps->getTempsMax();
    m_balle = NULL;

}

/// Destructeur
Niveau::~Niveau()
{
    delete m_temps;
}

void Niveau::setPlateau(char niveau)
{
    switch(niveau)
    {
        case '1':
            std::ifstream fichier("matriceNiveau1UtilisableSansEspace.txt", std::ios::in);  // on ouvre

            std::vector< std::vector<char> > grille(20);
            for(int i(0); i < 20; ++i)
            {
                grille[i] = std::vector<char>(10);
            }

            if(fichier)
            {
                char caractere;  // notre variable o sera stockŽ le caractre

                for (int j=0; j<10; j++)
                {
                    for (int i=0; i<20; i++)
                    {
                        fichier.get(caractere);  // on lit un caractre et on le stocke dans caractere
                        grille[i][j]=caractere;
                    }
                }

                fichier.close();
            }
            else
                std::cout << "Impossible d'ouvrir le fichier !" << std::endl;

            this->m_plateau = grille;// peut etre mettre un getter

    }
}

void Niveau::afficherPlateau(char niveau)
{
    system("cls");

    pConsole->gotoLigCol(5, 50);

    std::cout << "Temps restant : " << (int)getTempsRestant();
    setTempsRestant(getTempsRestant()); /// Calcul du nouveau temps restant

    ///Test d'affichage des coordonnées des différents objets du plateau
    pConsole->gotoLigCol(7, 50);
    std::cout << "Coord balle : " << m_balle->getX() << " " << m_balle->getY();
    pConsole->gotoLigCol(8, 50);
    std::cout << "Coord Oiseau 1 : " << m_tabOiseau[0].getX() << " " << m_tabOiseau[0].getY();
    pConsole->gotoLigCol(9, 50);
    std::cout << "Coord Oiseau 2 : " << m_tabOiseau[1].getX() << " " << m_tabOiseau[1].getY();
    pConsole->gotoLigCol(10, 50);
    std::cout << "Coord Oiseau 3 : " << m_tabOiseau[2].getX() << " " << m_tabOiseau[2].getY();
    pConsole->gotoLigCol(11, 50);
    std::cout << "Coord Oiseau 4 : " << m_tabOiseau[3].getX() << " " << m_tabOiseau[3].getY();


    pConsole->gotoLigCol(0, 0);

    for (int j=0; j<10; j++)
    {
        for (int i=0; i<20; i++)
        {
            std::cout << this->m_plateau[i][j] << " ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
}


/// Creer un objet
void Niveau::creerObjet()
{
    Oiseau *p_Oiseau;
    Blocs* p_Blocs;

    for (int i=0; i<20; i++)
    {
        for(int j=0; j<10; j++)
        {
            if(this->m_plateau[i][j]=='B')
            {
            m_balle = new Balle(i,j,1,1);
            }

            if(this->m_plateau[i][j]=='O')
            {
            p_Oiseau = new Oiseau(i, j);
            std::cout << p_Oiseau->getX();
            m_tabOiseau.push_back(*p_Oiseau);
            p_Oiseau = NULL;
            //m_tabOiseau.[m_tabOiseau.size()+1];
            }

            if(this->m_plateau[i][j]=='P')
            {
              p_Blocs = new BlocsPoussables(i, j, true);
              m_tabBlocs.push_back(*p_Blocs);
              p_Blocs = NULL;
            }

            if(this->m_plateau[i][j]=='C')
            {
              p_Blocs = new BlocsCassables(i, j);
              m_tabBlocs.push_back(*p_Blocs);
              p_Blocs = NULL;
            }

            if(this->m_plateau[i][j]=='T')
            {
              p_Blocs = new BlocsPieges(i, j);
              m_tabBlocs.push_back(*p_Blocs);
              p_Blocs = NULL;
            }
        }
    }
}


/// Getter de la fonction de temporisation de la classe Temps
void Niveau::getAttendre(double secondes)
{
    return m_temps->attendre(secondes);
}

/// Getter sur le temps maximum de la partie de la classe Temps
double Niveau::getTemps()
{
    return m_temps->getTempsMax();
}

/// Getter du temps restant
double Niveau::getTempsRestant()
{
    return m_tempsRestant;
}

/// Setter du nouveau temps restant
void Niveau::setTempsRestant(double newTempsRestant)
{
    if(newTempsRestant >= 0)
    {
        m_tempsRestant = m_temps->getTempsMax() - (double)clock() / CLOCKS_PER_SEC;
    }
}

/// Getter sur le nombre de balles en jeu
/*char Niveau::getNombreBalles()
{
    return m_nombreBalles;
}

/// Setter sur le nombre de balles en jeu
void Niveau::setNombreBalles(char nombreBalles)
{
    if((nombreBalles >= 0) && nombreBalles <= 2)
    {
        m_nombreBalles += nombreBalles;
    }
}

/// Augmente le nombre de balles sur le terrain
void Niveau::ajouterBalle()
{
    setNombreBalles(1);
}*/
