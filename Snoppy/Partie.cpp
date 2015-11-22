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
    std::string const dossier("sauvegarde//");
    std::string nom(pseudo);
    std::string const extention(".txt");
    std::string nomFichier = dossier + nom + extention;
    system("cls");


    chargerPartieAvecMenu(pseudo, m_snoopy, m_niveau, decisionJoueurNiveau, decisionJoueurMenu);
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

    if(partie->m_niveau->getTempsRestant() <= 0) { tempsEcoule(m_niveau, timeOut); } /// Est-ce que le temps restant est inférieur à 0 ?
    if(esc != 0) { quitterSansEnregister(m_niveau); }
    if (!accepter) { niveauPasAtteintRetour(m_niveau, m_snoopy); }
    if(m_snoopy->getNbOiseauAttrap()==4){ prepaSauvPartieGagnee(m_niveau, m_snoopy, partieEnCours, save); }
    if (m_snoopy->toucheBalle(m_snoopy, m_niveau->getBalle())) { m_snoopy->setVivant(false);}
    if (!m_snoopy->getVivant()) { gestionDeMort(m_niveau, m_snoopy, pseudo, nomFichier); }
    if(m_snoopy->getNbrVie()==0) { gestionPlusDeVie(m_snoopy, m_niveau, pseudo, nomFichier); }

    if(save != 0) { sauvegarde(pseudo, m_snoopy, m_niveau, partieEnCours); }



}



void Partie::tempsEcoule(Niveau* niveau, int& timeOut)
{
        timeOut = 1;
        system("cls");
        niveau->pConsole->gotoLigCol(12, 30);
        std::cout << "Temps ecoule !";
        niveau->getAttendre(0.75);
}

void Partie::quitterSansEnregister(Niveau* niveau)
{
        system("cls");
        niveau->pConsole->gotoLigCol(12, 30);
        std::cout << "Vous avez quitte la partie";
        niveau->getAttendre(0.75);
}

void Partie::niveauPasAtteintRetour(Niveau* niveau, PersoSnoopy* snoopy)
{
        system("cls");
        niveau->pConsole->gotoLigCol(12, 30);
        std::cout << "Niveau jamais atteint, votre meilleur niveau jamais atteint est:" << std::endl;
        std::cout << std::endl;
        std::cout << "   " << snoopy->getNiveauDejaAtteint() << std::endl;
        niveau->getAttendre(2.0);
}

void Partie::prepaSauvPartieGagnee(Niveau* niveau, PersoSnoopy* snoopy, bool& partieEnCours, int& save)
{
        niveau->getAttendre(0.75);
        system("cls");
        niveau->pConsole->gotoLigCol(12, 30);
        std::cout << "Vous avez attraper tous les oiseaux, vous pouvez aller au niveau suivant";
        niveau->getAttendre(2.3);
        snoopy->setNiveauActuel(snoopy->getNiveauActuel()+1);
        if(m_snoopy->getNiveauActuel() >= snoopy->getNiveauDejaAtteint())
        {
            snoopy->setNiveauDejaAtteint(snoopy->getNiveauActuel());
            partieEnCours = false;
        }
        save = 1;
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

void Partie::gestionDeMort(Niveau* niveau, PersoSnoopy* snoopy, std::string pseudo, std::string nomFichier)
{
    if(snoopy->getToucheParPiege())
    {
        niveau->getAttendre(0.75);
        system("cls");
        niveau->pConsole->gotoLigCol(12, 30);
        std::cout << "Vous etes mort, touche par un piege";
    }
    if (snoopy->toucheBalle(snoopy, niveau->getBalle()))
    {
        niveau->pConsole->gotoLigCol(snoopy->getY()*2, snoopy->getX()*2);
        std::cout <<'B';
        niveau->getAttendre(0.75);
        system("cls");
        niveau->pConsole->gotoLigCol(12, 30);
        std::cout << "Vous etes mort, touche par la balle";
    }
    niveau->getAttendre(2.3);
    snoopy->setNbrVie(snoopy->getNbrVie()-1);
    if(niveau->is_readable(nomFichier))//pour ne pas modifier un fichier qui n'existe pas
    {
      changerVie(pseudo, snoopy);
    }
}

void Partie::gestionPlusDeVie(PersoSnoopy* snoopy, Niveau* niveau, std::string pseudo, std::string nomFichier)
{
        niveau->getAttendre(0.75);
        system("cls");
        niveau->pConsole->gotoLigCol(12, 12);
        std::cout << "Game Over, Vous avez toujours acces au niveau que vous avez atteint mais votre score est nul";
        niveau->getAttendre(2.3);
        snoopy->setNiveauActuel(1);
        snoopy->setNbrVie(3);
        snoopy->setScore(0);
        if(niveau->is_readable(nomFichier))//pour ne pas modifier un fichier qui n'existe pas
        {
            changerVie(pseudo, snoopy);
        }

}




void Partie::chargerPartieAvecMenu(std::string nom, PersoSnoopy* snoopy, Niveau* niveau, std::string decisionJoueurNiveau, char decisionJoueurMenu)
{
        if(decisionJoueurMenu == '1') chargerPartieAvecMenu1(nom, snoopy, niveau, decisionJoueurNiveau);
        if(decisionJoueurMenu == '2') chargerPartieAvecMenu2(nom, snoopy, niveau, decisionJoueurNiveau);
}

void Partie::chargerPartieAvecMenu1(std::string nom, PersoSnoopy* snoopy, Niveau* niveau, std::string decisionJoueurNiveau)
{
    niveau->setPlateau(decisionJoueurNiveau);
    niveau->creerObjetDebut(snoopy, nom, decisionJoueurNiveau);
    niveau->initCoordSnoop(snoopy);
}
void Partie::chargerPartieAvecMenu2(std::string nom, PersoSnoopy* snoopy, Niveau* niveau, std::string decisionJoueurNiveau)
{
    //il faut voire si il a deja depasse ce niveau
        if(decisionJoueurNiveau == "0")
        {
            niveau->setPlateau("1");//juste une initialisation
            niveau->creerObjetSauv(nom, snoopy, niveau, decisionJoueurNiveau);
        }
        else
        {
            niveau->setPlateau(decisionJoueurNiveau);
            niveau->creerObjetDebut(snoopy, nom, decisionJoueurNiveau);
            niveau->initCoordSnoop(snoopy);

        }
}
void Partie::sauvegarde(std::string pseudo, PersoSnoopy* snoopy, Niveau* niveau, bool partieEnCours)
{
            std::string const dossier("sauvegarde//");
            std::string nom(pseudo);
            std::string const extention(".txt");
            std::string nomFichier = dossier + nom + extention;
            std::ofstream monFlux(nomFichier.c_str());
            int nombre(0);

            if(monFlux)
            {
                monFlux << partieEnCours << ' ' << snoopy->getNiveauActuel() << ' ' << snoopy->getNiveauDejaAtteint() << std::endl;;

                monFlux << 'p' << ' ';
                    for(int j=0; j< 10; j++)
                    {
                        for(int i=0; i< 20; i++)
                        {
                         monFlux << niveau->getPlateau()[i][j];
                        }
                    }
                    monFlux << std::endl;

                monFlux << 's' << ' ' << snoopy->getX() << ' ' << snoopy->getY() << ' ' << snoopy->getNbrVie() << ' ' << snoopy->getScore() << std::endl;

                monFlux << 'B' << ' ' << niveau->getBalle()->getX() << ' ' << niveau->getBalle()->getY() << ' ' << niveau->getBalle()->getDepX() << ' ' << niveau->getBalle()->getDepY() << std::endl;

                monFlux << 'P';
                    for(int i=0; i<niveau->getTabBlocs().size();i++)
                        {
                        if(niveau->getTabBlocs()[i]->getLettre()=='P')
                            {
                             nombre++;
                            }
                        }
                        monFlux << ' ' << nombre << ' ';
                        nombre = 0;

                    for(int i=0; i<niveau->getTabBlocs().size();i++)
                        {
                            if(niveau->getTabBlocs()[i]->getLettre()=='P')
                            {
                               monFlux << niveau->getTabBlocs()[i]->getX() << ' ' << niveau->getTabBlocs()[i]->getY() << ' ' << niveau->getTabBlocs()[i]->getPoussable() << ' ';
                            }
                        }
                    monFlux << std::endl;

                monFlux << 'C';

                    for(int i=0; i<niveau->getTabBlocs().size();i++)
                        {
                        if(niveau->getTabBlocs()[i]->getLettre()=='C')
                            {
                             nombre++;
                            }
                        }
                        monFlux << ' ' << nombre << ' ';
                        nombre = 0;

                    for(int i=0; i<niveau->getTabBlocs().size();i++)
                    {
                        if(niveau->getTabBlocs()[i]->getLettre()=='C')
                        {
                           monFlux << niveau->getTabBlocs()[i]->getX() << ' ' << niveau->getTabBlocs()[i]->getY() << ' ';
                        }
                    }
                     monFlux << std::endl;

                monFlux << 'T';

                    for(int i=0; i<niveau->getTabBlocs().size();i++)
                        {
                        if(niveau->getTabBlocs()[i]->getLettre()=='T')
                            {
                             nombre++;
                            }
                        }
                        monFlux << ' ' << nombre << ' ';
                        nombre = 0;

                    for(int i=0; i<niveau->getTabBlocs().size();i++)
                    {
                        if(niveau->getTabBlocs()[i]->getLettre()=='T')
                        {
                           monFlux << niveau->getTabBlocs()[i]->getX() << ' ' << niveau->getTabBlocs()[i]->getY() << ' ';
                        }
                    }
                  monFlux << std::endl;

                monFlux << 'O';

                    monFlux << ' ' << niveau->getTabOiseau().size() << ' ';

                    for(int i=0; i<niveau->getTabOiseau().size();i++)
                    {
                        monFlux << niveau->getTabOiseau()[i].getX() << ' ' << niveau->getTabOiseau()[i].getY() << ' ';
                    }
                  monFlux << std::endl;

                monFlux << 't';
                    monFlux << " " << niveau->getTempsRestant() << std::endl;

            }
            else
            {
                std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
            }
}
