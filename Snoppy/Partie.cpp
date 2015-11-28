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
    bool accepter(true);
    bool partieEnCours(true);
    double tempsDePause = 0;
    int save = 0;
    char toucheUtilisateur('@');
    float vitesseMultiBoucle(1);

    if(decisionJoueurNiveau == "1" ) { vitesseMultiBoucle = 1.2; }// pour faire aller plus vite lea balle en fct des niveaux
    if(decisionJoueurNiveau == "2" ) { vitesseMultiBoucle = 0.9; }
    if(decisionJoueurNiveau == "3" ) { vitesseMultiBoucle = 0.6; }


    std::string const dossier("sauvegarde//");
    std::string nom(pseudo);
    std::string const extention(".txt");
    std::string nomFichier = dossier + nom + extention;
    system("cls");


    chargerPartieAvecMenu(pseudo, m_snoopy, m_niveau, decisionJoueurNiveau, decisionJoueurMenu);
    if(decisionJoueurMenu !='3' && atoi(decisionJoueurNiveau.c_str()) > m_snoopy->getNiveauDejaAtteint()) accepter = false;

    while(onContinu(m_snoopy, m_niveau, esc, timeOut, accepter, save, decisionJoueurMenu)) ///Boucle de jeu tant qui indique c'est tous les parametres pour continuer à jouer sont reunit
    {
            m_niveau->setDeplacementBalle();
            m_niveau->checkerPlateauPourBalle();
            m_niveau->changerPlateau(m_snoopy);
            m_niveau->setCordSnoopClav(m_snoopy, m_niveau, toucheUtilisateur);
            m_niveau->gererBonus(m_snoopy);
            m_niveau->afficherPlateau(m_snoopy, decisionJoueurMenu, decisionJoueurNiveau);
            m_niveau->getAttendre(0.09*vitesseMultiBoucle);         /// Temporisation de 0.1 seconde
            recupererEntresClav(m_niveau, m_snoopy, pause, save, esc, toucheUtilisateur);
            gestionDePause(m_niveau, pause, toucheUtilisateur, tempsDePause, esc);
    }

    if(decisionJoueurMenu != '3')// menu 1 et 2 sans mot de passe super Utilsateur
    {
        if(m_niveau->getTempsRestant() <= 0) { tempsEcoule(m_niveau, timeOut); } /// Est-ce que le temps restant est inférieur à 0 ?
        if(esc != 0) { quitterSansEnregister(m_niveau); }//si echap n'a pas ete apuiye
        if (!accepter) { niveauJamaisAtteintRetour(m_niveau, m_snoopy); }
        if(m_snoopy->getNbOiseauAttrap()==4){ prepaSauvPartieGagnee(m_niveau, m_snoopy, partieEnCours, save); }
        if (m_niveau->toucheBalle(m_snoopy, m_niveau)) { m_snoopy->setVivant(false);}
        if (!m_snoopy->getVivant()) { gestionDeMort(m_niveau, m_snoopy, pseudo, nomFichier); }
        if(m_snoopy->getNbrVie()<=0) { gestionPlusDeVie(m_snoopy, m_niveau, pseudo, nomFichier, save); }//si plus de vies
        if(m_niveau->is_readable(nomFichier)) { changerVie(pseudo, m_snoopy); }

        if(save != 0) { sauvegarde(pseudo, m_snoopy, m_niveau, partieEnCours); }
        if(!partieEnCours) {prepaEtLancerNivSuiv(m_snoopy, m_niveau, pseudo, decisionJoueurNiveau, partieEnCours);}

    }
    if(decisionJoueurMenu == '3')//menu 3 super Utilsateur
    {
        if(esc != 0) { quitterSansEnregister(m_niveau); }//si echap n'a pas ete apuiye
        if(m_snoopy->getNbOiseauAttrap()==4){ prepaSauvPartieGagnee(m_niveau, m_snoopy, partieEnCours, save); }
        if (m_niveau->toucheBalle(m_snoopy, m_niveau)) { m_snoopy->setVivant(false);}
        if (!m_snoopy->getVivant()) { gestionDeMort(m_niveau, m_snoopy, pseudo, nomFichier); }
    }
 setScoreMax(1);

}

void Partie::prepaEtLancerNivSuiv(PersoSnoopy* snoopy, Niveau*niveau, std::string pseudo, std::string decisionJoueurNiveau, bool partieEnCours)
{
    delete snoopy;
    delete niveau;

    m_snoopy = new PersoSnoopy();
    m_niveau = new Niveau();


    jouer(this, '2', pseudo, "0");
}

void Partie::recupererEntresClav(Niveau* niveau, PersoSnoopy* snoopy, int& pause, int& save, int& esc,char& toucheUtilisateur)
{
    toucheUtilisateur = '@';//ne represente probablement rien (mon equivalent à NULL avec les pointeur)

    if(m_niveau->pConsole->isKeyboardPressed())
    {
        toucheUtilisateur = niveau->pConsole->getInputKey();
        if((toucheUtilisateur == 'P')||(toucheUtilisateur == 'p')) pause = 1;
        if((toucheUtilisateur == 'S')||(toucheUtilisateur == 's')) save = 1;
        if((toucheUtilisateur == 'A')||(toucheUtilisateur == 'a')) snoopy->setModeDemolition(true);
    }

        esc = GetAsyncKeyState(VK_ESCAPE);
}

void Partie::gestionDePause(Niveau* niveau, int& pause, char& toucheUtilisateur, double& tempsDePause, int& esc)
{
         while (pause == 1)
         {
             system("cls");
             tempsDePause = clock() / CLOCKS_PER_SEC;
             std::cout << "Pause !";
             std::cout << "          " << tempsDePause;
             toucheUtilisateur = niveau->pConsole->getInputKey();
             if((toucheUtilisateur == 'P')||(toucheUtilisateur == 'p')) pause = 0;
             esc = GetAsyncKeyState(VK_ESCAPE);
             if(esc != 0) pause = 0;
             niveau->getAttendre(0.7);
             system("cls");
         }
}


void Partie::tempsEcoule(Niveau* niveau, int& timeOut)//faut les action necessaire quand le temps est ecoule
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

void Partie::niveauJamaisAtteintRetour(Niveau* niveau, PersoSnoopy* snoopy)
{
        system("cls");
        niveau->pConsole->gotoLigCol(12, 30);
        std::cout << "Niveau jamais atteint, votre meilleur niveau jamais atteint est:" << std::endl;
        std::cout << "   le: " << snoopy->getNiveauDejaAtteint() << std::endl;
        niveau->getAttendre(2);
}

void Partie::prepaSauvPartieGagnee(Niveau* niveau, PersoSnoopy* snoopy, bool& partieEnCours, int& save)//preparation de la sauvegarde quand le niveau a ete remporte
{
        niveau->getAttendre(0.75);
        system("cls");
        niveau->pConsole->gotoLigCol(12, 30);
        std::cout << "Vous avez attraper tous les oiseaux, vous pouvez aller au niveau suivant";
        niveau->getAttendre(2.3);
        snoopy->setNiveauActuel(snoopy->getNiveauActuel()+1);
        if(m_snoopy->getNiveauActuel() >= snoopy->getNiveauDejaAtteint())//on change la valeur du melleur niveau jamais atteint si c'est le cas
        {
            snoopy->setNiveauDejaAtteint(snoopy->getNiveauActuel());
            partieEnCours = false;
        }
        save = 1;
}

void Partie::changerVie(std::string nom, PersoSnoopy* snoopy)/// le but de cette fonction est de changer seulement la vie dans le fichier et non pas tout le fichier et donc de revir à l'endroit de la derniere sauvegarde avec seulement une vie en moins
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
            maSauvegarde.push_back(a);//on sauvegarde le fichier dans une chaine de caractere
        }
        fichier.close();
    }
    else
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier==" << std::endl;
    }

    while(maSauvegarde[i] != 's') i++;// permet d'aller au niveau de snoopy
    i++;
    while(maSauvegarde[i] != ' ') i++;//ces while avec ces ' ', permette de ce placer au niveau des vies
    i++;
    while(maSauvegarde[i] != ' ') i++;
    i++;
    while(maSauvegarde[i] != ' ') i++;
    i++;
    maSauvegarde[i]= (char)snoopy->getNbrVie()+'0';//Normalement les vie ne peuvvent etre qu'entre 0 et 9, donc tjs qu'un caractere


    std::ofstream monFlux(nomFichier.c_str());
    if(monFlux)
    {
        for(unsigned i(0); i< maSauvegarde.size(); i++)
        {
            monFlux << maSauvegarde[i];//on reecrit par dessu le fichier avec la vie qui a changée
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
        niveau->getAttendre(1.25);
        system("cls");
        niveau->pConsole->gotoLigCol(12, 30);
        std::cout << "Vous etes mort, touche par un piege";
    }
    if (niveau->toucheBalle(snoopy, niveau))
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

void Partie::gestionPlusDeVie(PersoSnoopy* snoopy, Niveau* niveau, std::string pseudo, std::string nomFichier, int& save)//si il n'y a plus de vie
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
    if(decisionJoueurMenu == '3') chargerPartieAvecMenu1(nom, snoopy, niveau, decisionJoueurNiveau);
}
void Partie::chargerPartieAvecMenu1(std::string nom, PersoSnoopy* snoopy, Niveau* niveau, std::string decisionJoueurNiveau)
{
    niveau->setPlateau(decisionJoueurNiveau);
    niveau->creerObjetDebut(snoopy, nom, decisionJoueurNiveau);//charger les obget par defaut
    niveau->initCoordSnoop(snoopy);
}
void Partie::chargerPartieAvecMenu2(std::string nom, PersoSnoopy* snoopy, Niveau* niveau, std::string decisionJoueurNiveau)
{
    //il faut voire si il a deja depasse ce niveau
        if(decisionJoueurNiveau == "0")
        {
            niveau->setPlateau("1");//juste une initialisation
            niveau->creerObjetSauv(nom, snoopy, niveau, decisionJoueurNiveau);//cahrger a partir de sauvegarde ou rappelera à l'interieur la creerObjetrDebut, si la partie ete terminee
        }
        else
        {
            niveau->setPlateau(decisionJoueurNiveau);
            niveau->creerObjetDebut(snoopy, nom, decisionJoueurNiveau);//creation par defaut
            niveau->initCoordSnoop(snoopy);

        }
}

bool Partie::onContinu(PersoSnoopy* snoopy, Niveau*niveau, int esc, int timeOut, bool accepter, int save, char decisionJoueurMenu)
{
    if(save != 0 && decisionJoueurMenu == '3'){ save = 0; }
    if((esc == 0) && (timeOut == 0) && (accepter) && (save==0))
    {
        if(snoopy->getVivant() && snoopy->getNbOiseauAttrap()<4 && snoopy->getNbrVie()>0)
        {
            if(!niveau->toucheBalle(snoopy, niveau) && (niveau->getTempsRestant()>0))
            {
                return true;
            }
        }
    }
    return false;
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

            monFlux << 'B';

                monFlux << ' ' << niveau->getVectBalle().size() << ' ';

                for(unsigned i=0; i<niveau->getVectBalle().size();i++)
                    {
                        monFlux << niveau->getVectBalle()[i].getX() << ' ' << niveau->getVectBalle()[i].getY() << ' ' << niveau->getVectBalle()[i].getDepX() << ' ' << niveau->getVectBalle()[i].getDepY()<< ' ';
                    }
                monFlux << std::endl;

            monFlux << 'P';
                for(unsigned short i=0; i<niveau->getTabBlocs().size();i++)
                    {
                    if(niveau->getTabBlocs()[i]->getLettre()=='P')
                        {
                         nombre++;
                        }
                    }
                    monFlux << ' ' << nombre << ' ';
                    nombre = 0;

                for(unsigned i=0; i<niveau->getTabBlocs().size();i++)
                    {
                        if(niveau->getTabBlocs()[i]->getLettre()=='P')
                        {
                           monFlux << niveau->getTabBlocs()[i]->getX() << ' ' << niveau->getTabBlocs()[i]->getY() << ' ' << niveau->getTabBlocs()[i]->getPoussable() << ' ';
                        }
                    }
                monFlux << std::endl;

            monFlux << 'C';

                for(unsigned i=0; i<niveau->getTabBlocs().size();i++)
                    {
                    if(niveau->getTabBlocs()[i]->getLettre()=='C')
                        {
                         nombre++;
                        }
                    }
                    monFlux << ' ' << nombre << ' ';
                    nombre = 0;

                for(unsigned i=0; i<niveau->getTabBlocs().size();i++)
                {
                    if(niveau->getTabBlocs()[i]->getLettre()=='C')
                    {
                       monFlux << niveau->getTabBlocs()[i]->getX() << ' ' << niveau->getTabBlocs()[i]->getY() << ' ';
                    }
                }
                 monFlux << std::endl;

            monFlux << 'T';

                for(unsigned i=0; i<niveau->getTabBlocs().size();i++)
                    {
                    if(niveau->getTabBlocs()[i]->getLettre()=='T')
                        {
                         nombre++;
                        }
                    }
                    monFlux << ' ' << nombre << ' ';
                    nombre = 0;

                for(unsigned i=0; i<niveau->getTabBlocs().size();i++)
                {
                    if(niveau->getTabBlocs()[i]->getLettre()=='T')
                    {
                       monFlux << niveau->getTabBlocs()[i]->getX() << ' ' << niveau->getTabBlocs()[i]->getY() << ' ';
                    }
                }
              monFlux << std::endl;

            monFlux << 'O';

                monFlux << ' ' << niveau->getTabOiseau().size() << ' ';

                for(unsigned i=0; i<niveau->getTabOiseau().size();i++)
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
bool Partie::is_readable( const std::string & file )//savoir si le ficheir existe
{
    std::ifstream fichier( file.c_str() );
    return !fichier.fail();
}

void Partie::setScoreMax(double newTempsRestant)
{
    double Sniveau;
    Sniveau=newTempsRestant*100;

        std::string const dossier("sauvegarde//");
        std::string nom("score");
        std::string const extention(".txt");
        std::string nomFichier = dossier + nom + extention;


        int meilleurScoreAct=0;

      if(is_readable(nomFichier))
        {



        std::ifstream fichier(nomFichier.c_str(), std::ios::in);  // on ouvre

        if(fichier)
        {
            fichier>>meilleurScoreAct;

        fichier.close();
    }
    else
    {
        std::cout << "Impossible d'ouvrir le fichier !!" << std::endl;
    }
        }


 if(Sniveau>meilleurScoreAct && Sniveau<60)
 {




      std::ofstream monFlux(nomFichier.c_str());
        int nombre(0);

        if(monFlux)
        {
            monFlux << Sniveau;
        }
        else
        {
            std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
        }



}}
