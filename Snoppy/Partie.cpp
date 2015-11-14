#include "Partie.h"


///Constructeur par défaut
Partie::Partie()
{
    m_snoopy = new PersoSnoopy();
    m_niveau = new Niveau();
}

///Destructeur
Partie::~Partie()
{
    m_snoopy->~PersoSnoopy();
    m_niveau->~Niveau();
    delete m_snoopy;
    delete m_niveau;
}


/// Boucle de jeu
void Partie::jouer(Partie *partie)
{
    int timeOut = 0;
    int esc = 0;

partie->m_niveau->setPlateau('1');
//partie->m_niveau->afficherPlateau(1);

    m_niveau->creerObjet();
    m_niveau->initCoordSnoop(m_snoopy);

    ///Boucle de jeu tant que le compteur est != 0 ou ESC n'est pas préssée
    while((esc == 0) && (timeOut == 0))
    {
        if(partie->m_niveau->getTempsRestant() <= 0) /// Est-ce que le temps restant est inférieur à 0 ?
        {
            timeOut = 1;
            system("cls");
            m_niveau->pConsole->gotoLigCol(12, 30);
            std::cout << "Temps ecoule !";
        }
        else
        {
            system("cls");
            m_niveau->getDeplacementBalle(m_niveau->getPlateau());
            m_niveau->checkerPlateauPourBalle();
            m_niveau->changerPlateau();
            m_niveau->afficherPlateau(1);
            std::cout << "coord de Snoopy : " << "(" << m_snoopy->getX() << ";" << m_snoopy->getY()<< ")";
            //m_niveau->getTabBlocs()[9]->deplacement(1,0,m_niveau->getTabBlocs()[9]);/// TEST IMPORTANT POUR COMPRENDRE
            std::cout << "coord de tab9 : " << "(" << m_niveau->getTabBlocs()[9]->getX() << ";" << m_niveau->getTabBlocs()[9]->getY()<< ")";

        }
        partie->m_niveau->getAttendre(0.1);         /// Temporisation de 0.1 seconde
        esc = GetAsyncKeyState(VK_ESCAPE);
    }

    if(esc != 0)
    {
        system("cls");
        m_niveau->pConsole->gotoLigCol(12, 30);
        std::cout << "Vous avez quitte la partie";
    }



    m_niveau->pConsole->getInputKey();
}
