#include "Partie.h"


///Constructeur par d�faut
Partie::Partie()
{
    m_snoopy = new PersoSnoopy();
    m_niveau = new Niveau();
}

///Destructeur
Partie::~Partie()
{
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

    ///Boucle de jeu tant que le compteur est != 0 ou ESC n'est pas pr�ss�e
    while((esc == 0) && (timeOut == 0))
    {
        if(partie->m_niveau->getTempsRestant() <= 0) /// Est-ce que le temps restant est inf�rieur � 0 ?
        {
            timeOut = 1;
            system("cls");
            m_niveau->pConsole->gotoLigCol(12, 30);
            std::cout << "Temps ecoule !";
        }
        else
        {
            system("cls");
            m_niveau->afficherPlateau(1);
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
