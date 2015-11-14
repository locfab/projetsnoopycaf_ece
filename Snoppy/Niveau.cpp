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
    pConsole->gotoLigCol(1, 50);
    std::cout << "Coord balle : " << m_balle->getX() << " " << m_balle->getY();
    pConsole->gotoLigCol(2, 50);
    std::cout << "Vect depX : " << m_balle->getDepX() << "  Vect depY : " << m_balle->getDepY();
    pConsole->gotoLigCol(3, 50);
    std::cout << "Position memoire du B : " << m_plateau[m_balle->getX()][m_balle->getY()];
    /*
    pConsole->gotoLigCol(9, 50);
    std::cout << "Coord Poussable 7 : " << m_tabBlocs[6]->Blocs::getX() << " " << m_tabBlocs[6]->getY();
    pConsole->gotoLigCol(10, 50);
    std::cout << "Coord Poussable 8 : " << m_tabBlocs[7]->Blocs::getX() << " " << m_tabBlocs[7]->getY();
    pConsole->gotoLigCol(11, 50);
    std::cout << "Coord Poussable 9 : " << m_tabBlocs[8]->Blocs::getX() << " " << m_tabBlocs[8]->getY();
    pConsole->gotoLigCol(12, 50);
    std::cout << "Coord Poussable 10 : " << m_tabBlocs[9]->Blocs::getX() << " " << m_tabBlocs[9]->getY();
    pConsole->gotoLigCol(13, 50);
    std::cout << "Coord Poussable 11 : " << m_tabBlocs[10]->Blocs::getX() << " " << m_tabBlocs[10]->getY();
    pConsole->gotoLigCol(14, 50);
    std::cout << "Coord Poussable 12 : " << m_tabBlocs[11]->Blocs::getX() << " " << m_tabBlocs[11]->getY();
    */
    pConsole->gotoLigCol(15, 50);
    std::cout << "Poussable ? : " << m_tabBlocs[9]->getPoussable();
    pConsole->gotoLigCol(16, 50);
    std::cout << "Lettre de la balle : " << m_balle->getLettre();

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
            }

            if(this->m_plateau[i][j]=='P')
            {
              p_Blocs = new BlocsPoussables(i, j, true);
              m_tabBlocs.push_back(p_Blocs);
              p_Blocs = NULL;
            }

            if(this->m_plateau[i][j]=='C')
            {
              p_Blocs = new BlocsCassables(i, j);
              m_tabBlocs.push_back(p_Blocs);
              p_Blocs = NULL;
            }

            if(this->m_plateau[i][j]=='T')
            {
              p_Blocs = new BlocsPieges(i, j);
              m_tabBlocs.push_back(p_Blocs);
              p_Blocs = NULL;
            }
        }
    }
}

void Niveau::initCoordSnoop(PersoSnoopy* snoopy)
{
     for (int i=0; i<20; i++)
    {
        for(int j=0; j<10; j++)
        {
            if(this->m_plateau[i][j]=='S')
            {
            snoopy->setCoordonnees(i,j);
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

/// Getter sur le déplacement de la balle
void Niveau::getDeplacementBalle(std::vector< std::vector<char> > plateau)
{
    return m_balle->deplacement(plateau);
}

/// Getter sur le plateau
std::vector< std::vector<char> > Niveau::getPlateau()
{
    return m_plateau;
}

/// Getter sur la balle
Balle* Niveau::getBalle()
{
    return m_balle;
}

/// Change le plateau
void Niveau::changerPlateau()
{
    if( !((m_balle->getX() == 0)&&(m_balle->getDepX() == -1)) && !((m_balle->getX() == 19)&&(m_balle->getDepX() == 1)) && !((m_balle->getY() == 0)&&(m_balle->getDepY() == -1)) && !((m_balle->getY() == 9)&&(m_balle->getDepY() == 1)) /*&& (m_plateau[m_balle->getX()+m_balle->getDepX()][m_balle->getY()+m_balle->getDepY()] != 'P')*/  )
    {
        char lettreIntermediaire;
        lettreIntermediaire = m_plateau[m_balle->getX()+m_balle->getDepX()][m_balle->getY()+m_balle->getDepY()];
        m_plateau[m_balle->getX()+m_balle->getDepX()][m_balle->getY()+m_balle->getDepY()] = m_balle->getLettre();
        m_plateau[m_balle->getX()][m_balle->getY()] = lettreIntermediaire;

        m_balle->setY();
        m_balle->setX();
    }
}

/// On regarde si la balle va rencontrer un obstacle (hors murs)
void Niveau::checkerPlateauPourBalle()
{
    if(m_plateau[m_balle->getX()+1][m_balle->getY()+1] == 'P')
    {
        m_balle->setDepX(-m_balle->getDepX());
        m_balle->setDepY(-m_balle->getDepY());
    }
}
