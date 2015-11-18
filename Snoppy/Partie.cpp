#include "Partie.h"
#include <string>



///Constructeur par défaut
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
    int nombre(0);

partie->m_niveau->setPlateau("3");
//partie->m_niveau->afficherPlateau(1);

    m_niveau->creerObjet();
    //m_niveau->creerObjet("nom");// a ne pas utiliser au hasard sinon ca plante
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
            m_niveau->setCordSnoopClav(m_snoopy, m_niveau);
            m_niveau->changerPlateau(m_snoopy);
            m_niveau->afficherPlateau(1);
            if(!m_snoopy->getVivant()){}
            std::cout << "coord de Snoopy : " << "(" << m_snoopy->getX() << ";" << m_snoopy->getY()<< ")";
            std::cout << "coord de tab9 : " << "(" << m_niveau->getTabBlocs()[9]->getX() << ";" << m_niveau->getTabBlocs()[9]->getY()<< ")";
            std::cout << "SnoopyVivant? : " << m_snoopy->getVivant();
        }
        partie->m_niveau->getAttendre(0.1);         /// Temporisation de 0.1 seconde
        esc = GetAsyncKeyState(VK_ESCAPE);
    }

    if(esc != 0)
    {
            std::string const nomFichier("Nom.txt");
            std::ofstream monFlux(nomFichier.c_str());

            if(monFlux)
            {
                monFlux << 'p' << ' ';
                    for(int j=0; j< 10; j++)
                    {
                        for(int i=0; i< 20; i++)
                        {
                         monFlux << m_niveau->getPlateau()[i][j];
                        }
                    }
                    monFlux << std::endl;

                monFlux << 'S' << ' ' << m_snoopy->getX() << ' ' << m_snoopy->getY() << ' ' << m_snoopy->getNbrVie() << ' ' << m_snoopy->getScore() << std::endl;

                monFlux << 'B' << ' ' << m_niveau->getBalle()->getX() << ' ' << m_niveau->getBalle()->getY() << ' ' << m_niveau->getBalle()->getDepX() << ' ' << m_niveau->getBalle()->getDepY() << std::endl;

                monFlux << 'P';

                    for(int i=0; i<m_niveau->getTabBlocs().size();i++)
                        {
                        if(m_niveau->getTabBlocs()[i]->getLettre()=='P')
                            {
                             nombre++;
                            }
                        }
                        monFlux << ' ' << nombre << ' ';
                        nombre = 0;

                    for(int i=0; i<m_niveau->getTabBlocs().size();i++)
                        {
                            if(m_niveau->getTabBlocs()[i]->getLettre()=='P')
                            {
                               monFlux << m_niveau->getTabBlocs()[i]->getX() << ' ' << m_niveau->getTabBlocs()[i]->getY() << ' ' << m_niveau->getTabBlocs()[i]->getPoussable() << ' ';
                            }
                        }
                    monFlux << std::endl;

                monFlux << 'C';

                    for(int i=0; i<m_niveau->getTabBlocs().size();i++)
                        {
                        if(m_niveau->getTabBlocs()[i]->getLettre()=='C')
                            {
                             nombre++;
                            }
                        }
                        monFlux << ' ' << nombre << ' ';
                        nombre = 0;

                    for(int i=0; i<m_niveau->getTabBlocs().size();i++)
                    {
                        if(m_niveau->getTabBlocs()[i]->getLettre()=='C')
                        {
                           monFlux << m_niveau->getTabBlocs()[i]->getX() << ' ' << m_niveau->getTabBlocs()[i]->getY() << ' ';
                        }
                    }
                     monFlux << std::endl;

                monFlux << 'T';

                    for(int i=0; i<m_niveau->getTabBlocs().size();i++)
                        {
                        if(m_niveau->getTabBlocs()[i]->getLettre()=='T')
                            {
                             nombre++;
                            }
                        }
                        monFlux << ' ' << nombre << ' ';
                        nombre = 0;

                    for(int i=0; i<m_niveau->getTabBlocs().size();i++)
                    {
                        if(m_niveau->getTabBlocs()[i]->getLettre()=='T')
                        {
                           monFlux << m_niveau->getTabBlocs()[i]->getX() << ' ' << m_niveau->getTabBlocs()[i]->getY() << ' ';
                        }
                    }
                  monFlux << std::endl;

                monFlux << 'O';

                    monFlux << ' ' << m_niveau->getTabOiseau().size() << ' ';

                    for(int i=0; i<m_niveau->getTabOiseau().size();i++)
                    {
                        monFlux << m_niveau->getTabOiseau()[i].getX() << ' ' << m_niveau->getTabOiseau()[i].getY() << ' ';
                    }
                  monFlux << std::endl;

                monFlux << 't';
                    monFlux << " " << m_niveau->getTempsRestant() << std::endl;

            }
            else
            {
                std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
            }

    }
/*
    if(esc != 0)
    {
        system("cls");
        m_niveau->pConsole->gotoLigCol(12, 30);
        std::cout << "Vous avez quitte la partie";
    }
*/


    m_niveau->pConsole->getInputKey();
}
