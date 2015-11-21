#include "Partie.h"
#include <string>
#include <vector>



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
void Partie::jouer(Partie *partie, char decisionJoueurMenu, std::string pseudo, std::string decisionJoueurNiveau)
{
    int timeOut = 0;
    int esc = 0;
    int pause = 0;
    int nombre(0);
    double tempsDePause = 0;
    int save = 0;
    char toucheUtilisateur('@');
    bool NiveauDejaAtteint;
    bool accepter(true);
    bool partieEnCours(true);
    system("cls");

    if(decisionJoueurMenu == '1')
    {
    partie->m_niveau->setPlateau(decisionJoueurNiveau);
    m_niveau->creerObjetDebut(m_snoopy, pseudo, decisionJoueurNiveau);
    m_niveau->initCoordSnoop(m_snoopy);
    }
    if(decisionJoueurMenu == '2')
    {
        //il faut voire si il a deja depasse ce niveau
        if(decisionJoueurNiveau == "0")
        {
            partie->m_niveau->setPlateau("1");//juste une initialisation
            m_niveau->creerObjetSauv(pseudo, m_snoopy, m_niveau, decisionJoueurNiveau);
        }
        else
        {
            m_niveau->setPlateau(decisionJoueurNiveau);
            m_niveau->creerObjetDebut(m_snoopy, pseudo, decisionJoueurNiveau);
            m_niveau->initCoordSnoop(m_snoopy);

        }
    }
    if(atoi(decisionJoueurNiveau.c_str()) > m_snoopy->getNiveauDejaAtteint()) accepter = false;

    ///Boucle de jeu tant que le compteur est != 0 ou ESC n'est pas préssée
    while((esc == 0) && (timeOut == 0) && (save==0) && accepter && m_snoopy->getVivant() && !m_snoopy->toucheBalle(m_snoopy, m_niveau->getBalle()) && (partie->m_niveau->getTempsRestant()>0) && m_snoopy->getNbOiseauAttrap()<4 && m_snoopy->getNbrVie()>0)
    {
        if (pause == 0)
        {
            m_niveau->getDeplacementBalle(m_niveau->getPlateau());
            m_niveau->checkerPlateauPourBalle();
            m_niveau->setCordSnoopClav(m_snoopy, m_niveau, toucheUtilisateur);
            m_niveau->changerPlateau(m_snoopy);
            m_niveau->afficherPlateau(m_snoopy);
            partie->m_niveau->getAttendre(0.07);         /// Temporisation de 0.1 seconde

            toucheUtilisateur = '@';//ne represente probablement rien (equivalent à NULL avec les pointeur)

            if(m_niveau->pConsole->isKeyboardPressed())
            {
                toucheUtilisateur = m_niveau->pConsole->getInputKey();
                if((toucheUtilisateur == 'P')||(toucheUtilisateur == 'p')) pause = 1;
                if((toucheUtilisateur == 'S')||(toucheUtilisateur == 's')) save = 1;
                if((toucheUtilisateur == 'A')||(toucheUtilisateur == 'a')) m_snoopy->setModeDemolition(true);
            }

            esc = GetAsyncKeyState(VK_ESCAPE);

        }

        if((pause == 1 ))
        {
             system("cls");
             tempsDePause = clock() / CLOCKS_PER_SEC;
             std::cout << "Pause !";
             std::cout << "          " << tempsDePause;
             char attente = m_niveau->pConsole->getInputKey();
             if((attente == 'P')||(attente == 'p')||(GetAsyncKeyState(VK_ESCAPE))) pause = 0;
        }
    }

    if(partie->m_niveau->getTempsRestant() <= 0) /// Est-ce que le temps restant est inférieur à 0 ?
    {
        timeOut = 1;
        system("cls");
        m_niveau->pConsole->gotoLigCol(12, 30);
        std::cout << "Temps ecoule !";
        partie->m_niveau->getAttendre(0.75);
    }

    if(esc != 0)
    {
        system("cls");
        m_niveau->pConsole->gotoLigCol(12, 30);
        std::cout << "Vous avez quitte la partie";
        m_niveau->pConsole->getInputKey();
    }

    if (!accepter)
    {
        system("cls");
        m_niveau->pConsole->gotoLigCol(12, 30);
        std::cout << "Niveau jamais atteint, votre meilleur niveau jamais atteint est:" << std::endl;
        std::cout << std::endl;
        std::cout << "   " << m_snoopy->getNiveauDejaAtteint() << std::endl;
        partie->m_niveau->getAttendre(2.0);
    }

    if(m_snoopy->getNbOiseauAttrap()==4)
    {
        partie->m_niveau->getAttendre(0.75);
        system("cls");
        m_niveau->pConsole->gotoLigCol(12, 30);
        std::cout << "Vous avez attraper tous les oiseaux, vous pouvez aller au niveau suivant";
        partie->m_niveau->getAttendre(2.3);
        m_snoopy->setNiveauActuel(m_snoopy->getNiveauActuel()+1);
        if(m_snoopy->getNiveauActuel() >= m_snoopy->getNiveauDejaAtteint())
        {
            m_snoopy->setNiveauDejaAtteint(m_snoopy->getNiveauActuel());
            partieEnCours = false;
        }
        save = 1;
    }


    if(save != 0)
    {
            std::string const dossier("sauvegarde//");
            std::string nom(pseudo);
            std::string const extention(".txt");
            std::string nomFichier = dossier + nom + extention;
            std::ofstream monFlux(nomFichier.c_str());

            if(monFlux)
            {
                monFlux << partieEnCours << ' ' << m_snoopy->getNiveauActuel() << ' ' << m_snoopy->getNiveauDejaAtteint() << std::endl;;

                monFlux << 'p' << ' ';
                    for(int j=0; j< 10; j++)
                    {
                        for(int i=0; i< 20; i++)
                        {
                         monFlux << m_niveau->getPlateau()[i][j];
                        }
                    }
                    monFlux << std::endl;

                monFlux << 's' << ' ' << m_snoopy->getX() << ' ' << m_snoopy->getY() << ' ' << m_snoopy->getNbrVie() << ' ' << m_snoopy->getScore() << std::endl;

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



    if (!m_snoopy->getVivant())
    {
        partie->m_niveau->getAttendre(0.75);
        system("cls");
        m_niveau->pConsole->gotoLigCol(12, 30);
        std::cout << "Vous etes mort, touche par un piege";
        partie->m_niveau->getAttendre(2.3);
        m_snoopy->setNbrVie(m_snoopy->getNbrVie()-1);
        partie->changerVie(pseudo, m_snoopy);
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
        m_snoopy->setNbrVie(m_snoopy->getNbrVie()-1);
        partie->changerVie(pseudo, m_snoopy);
    }
        if(m_snoopy->getNbrVie()==0)
    {
        partie->m_niveau->getAttendre(0.75);
        system("cls");
        m_niveau->pConsole->gotoLigCol(12, 12);
        std::cout << "Game Over, Vous avez toujours acces au niveau que vous avez atteint mais votre score est nul";
        partie->m_niveau->getAttendre(2.3);
        m_snoopy->setNiveauActuel(1);
        m_snoopy->setNbrVie(3);
        m_snoopy->setScore(0);
        partie->changerVie(pseudo,m_snoopy);

    }


}


void Partie::changerVie(std::string nom, PersoSnoopy* snoopy)
{
    std::string const dossier("sauvegarde//");
    std::string const extention(".txt");
    std::string nomFichier = dossier + nom + extention;
    std::vector <char> maSauvegarde;
    char a;
    int i=0;
    std::ifstream fichier(nomFichier.c_str(), std::ios::in);  // on ouvre

    if(fichier)
    {
        while(fichier.get(a))
        {
            maSauvegarde.push_back(a);
        }
        fichier.close();
    }
    else
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier==" << std::endl;
    }

        while(maSauvegarde[i]!= 's') i++;
        maSauvegarde[i+6]= (char)snoopy->getNbrVie()+'0';
        std::cout<< std::endl;
        std::cout<< maSauvegarde[i+7]<< std::endl;
        std::cout<< std::endl;


    std::ofstream monFlux(nomFichier.c_str());
    if(monFlux)
    {
        for(int i(0); i< maSauvegarde.size(); i++)
        {
            monFlux << maSauvegarde[i];
        }
    }
    else
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier:/." << std::endl;
    }

}
