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
    int pause = 0;
    int nombre(0);
    double tempsDePause = 0;
    int save = 0;
    char toucheUtilisateur(0);

    partie->m_niveau->setPlateau("3");
    m_niveau->creerObjet();
    //m_niveau->creerObjet("nom");// a ne pas utiliser au hasard sinon ca plante
    m_niveau->initCoordSnoop(m_snoopy);

    ///Boucle de jeu tant que le compteur est != 0 ou ESC n'est pas préssée
    while((esc == 0) && (timeOut == 0) && (save==0) && m_snoopy->getVivant() && !m_snoopy->toucheBalle(m_snoopy, m_niveau->getBalle()))
    {
        if (pause == 0)
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
                m_niveau->getDeplacementBalle(m_niveau->getPlateau());
                m_niveau->checkerPlateauPourBalle();
                m_niveau->setCordSnoopClav(m_snoopy, m_niveau, toucheUtilisateur);
                m_niveau->changerPlateau(m_snoopy);
                m_niveau->afficherPlateau();

                m_niveau->pConsole->gotoLigCol(6, 50);
                std::cout << "Nombre d'oiseaux attrapes : " << m_snoopy->getNbOiseauAttrap() << "  ";
            }

            partie->m_niveau->getAttendre(0.1);         /// Temporisation de 0.1 seconde
            esc = GetAsyncKeyState(VK_ESCAPE);
            toucheUtilisateur = '@';//ne represente probablement rien (equivalent à NULL avec les pointeur)

            if(m_niveau->pConsole->isKeyboardPressed())
            {
                toucheUtilisateur = m_niveau->pConsole->getInputKey();
                if((toucheUtilisateur == 'P')||(toucheUtilisateur == 'p')) pause = 1;
                if((toucheUtilisateur == 'S')||(toucheUtilisateur == 's')) save = 1;
                if((toucheUtilisateur == 'A')||(toucheUtilisateur == 'a')) m_snoopy->setModeDemolition(true);
            }
        }

        if((pause == 1 ))
        {
             system("cls");
             tempsDePause = clock() / CLOCKS_PER_SEC;
             std::cout << "Pause !";
             std::cout << "          " << tempsDePause;
             char attente = m_niveau->pConsole->getInputKey();
             if((attente == 'P')||(attente == 'p')) pause = 0;
        }
    }

    if(save != 0)
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
    if(esc != 0)
    {
        system("cls");
        m_niveau->pConsole->gotoLigCol(12, 30);
        std::cout << "Vous avez quitte la partie";
        m_niveau->pConsole->getInputKey();
    }

    if (!m_snoopy->getVivant())
    {
        partie->m_niveau->getAttendre(0.75);
        system("cls");
        m_niveau->pConsole->gotoLigCol(12, 30);
        std::cout << "Vous etes mort, touche par un piege";
        partie->m_niveau->getAttendre(2.3);
    }
    if (m_snoopy->toucheBalle(m_snoopy, m_niveau->getBalle()))
    {
        m_niveau->pConsole->gotoLigCol(m_snoopy->getY()*2, m_snoopy->getX()*2);
        std::cout <<'B';
        partie->m_niveau->getAttendre(0.75);
        system("cls");
        m_niveau->pConsole->gotoLigCol(12, 30);
        std::cout << "Vous etes mort, touche par la balle";
        partie->m_niveau->getAttendre(2.3);
    }
}
