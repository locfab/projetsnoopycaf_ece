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

    std::cout << "Temps restant : " << getTempsRestant();
    setTempsRestant(getTempsRestant()); /// Calcul du nouveau temps restant

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
void Niveau::creerObjet()
{
    Balle* balle = new Balle(6,6,1,-1);
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
