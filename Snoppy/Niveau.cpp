#include <iostream>
#include "Niveau.h"
#include <fstream>


Niveau::Niveau()
{
}

void Niveau::setPlateau(std::string niveau)
{
    std::ifstream fichier("matriceNiveau1UtilisableSansEspace.txt", std::ios::in);  // on ouvre

    //char tab[20][10];

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

    this->m_plateau = grille;
}

void Niveau::afficherPlateau() const
{
    for (int j=0; j<10; j++)
    {
        for (int i=0; i<20; i++)
        {
            std::cout << this->m_plateau[i][j];
        }
        std::cout << std::endl;
    }
}

