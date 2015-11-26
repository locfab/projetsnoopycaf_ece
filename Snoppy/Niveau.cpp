#include <iostream>
#include <sstream>
#include "Niveau.h"
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <string>

/// Constructeur par défaut
Niveau::Niveau()
            :   m_niveauCourant(0), m_lig(10), m_col(20)
{
    // Alloue la mémoire du pointeur
    pConsole = Console::getInstance();
    m_temps = new Temps();
    m_tempsRestant = m_temps->getTempsMax();
    m_balle=NULL;
    m_bonusAttrap=NULL;


}

/// Destructeur
Niveau::~Niveau()
{
    int nb = m_tabBlocs.size();

    for(int i(0); i<nb; i++){
    delete m_tabBlocs[i];}

    for(int i(0); i<nb; i++){
    m_tabBlocs.pop_back();}

    delete m_temps;
    delete m_balle;
    delete m_bonusAttrap;
}

void Niveau::setPlateau(std::string niveau)
{

    std::string nb = niveau; //choisir quel fichier on ouvre 1, 2 ,3
    std::string debut("matriceNiveau");
    std::string fin("UtilisableSansEspace.txt");
    std::string nomFichier = debut + nb + fin;

        std::ifstream fichier(nomFichier.c_str(), std::ios::in);  // on ouvre

        std::vector< std::vector<char> > grille(m_col);
        for(int i(0); i < m_col; ++i)
        {
            grille[i] = std::vector<char>(m_lig);
        }

        if(fichier)
        {
            char caractere;  // notre variable o sera stockŽ le caractre

            for (int j=0; j< m_lig; j++)
            {
                for (int i=0; i< m_col; i++)
                {
                    fichier.get(caractere);  // on lit un caractre et on le stocke dans caractere
                    grille[i][j]=caractere;
                }
            }

            fichier.close();
        }
        else
            std::cout << "Impossible d'ouvrir le fichier !!!" << std::endl;

        this->m_plateau = grille;// peut etre mettre un getter

}

void Niveau::afficherPlateau(PersoSnoopy* snoopy, char decisionJoueurMenu, std::string decisionJoueurNiveau)
{
    pConsole->gotoLigCol(5, 50);
    std::cout << "Temps restant : " << (int)getTempsRestant() << "  ";
    setTempsRestant(getTempsRestant()); /// Calcul du nouveau temps restant
    pConsole->gotoLigCol(0, 0);

    for (int j=0; j< m_lig; j++)
    {
        for (int i=0; i< m_col; i++)
        {
            std::cout << this->m_plateau[i][j] << " ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }


    if(decisionJoueurMenu != '3')//si pas menu mot de passe
    {
        pConsole->gotoLigCol(4, 50);
        std::cout << "Niveau actuel : " << snoopy->getNiveauActuel() << "  " << std::endl;
        pConsole->gotoLigCol(6, 50);
        std::cout << "Nombre d'oiseaux attrapes : " << snoopy->getNbOiseauAttrap() << "  " << std::endl;
        pConsole->gotoLigCol(7, 50);
        std::cout << "Nombre de vie : " << snoopy->getNbrVie() << "  " << std::endl;
        pConsole->gotoLigCol(8, 50);
        std::cout << "Score : " << snoopy->getScore() << "  " << std::endl;
        pConsole->gotoLigCol(11, 50);
        std::cout << "Meilleur niveau atteint : " << snoopy->getNiveauDejaAtteint() << "  " << std::endl;
    }
    if(decisionJoueurMenu == '3')
    {
        pConsole->gotoLigCol(6, 50);
        std::cout << "Niveau actuel : " << decisionJoueurNiveau << "  " << std::endl;
        pConsole->gotoLigCol(7, 50);
        std::cout << "Nombre d'oiseaux attrapes : " << snoopy->getNbOiseauAttrap() << "  " << std::endl;
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
void Niveau::changerPlateau(PersoSnoopy* snoopy)// regenerer un plateau avec les nouvelles modication à partir des objet existant
{
    int diffTemps;
    if(m_bonusAttrap != NULL){diffTemps = m_bonusAttrap->getTempsALaCreation()-getTempsRestant();}

    for (int j=0; j< m_lig; j++)
    {
        for (int i=0; i< m_col; i++)
        {
            this->m_plateau[i][j] = '.';// on initialise avec des points
        }
    }

    if(verificationBalle_Bords() == 1)//on met la balle à partir de nouvelle coordonnes
    {
        char lettreIntermediaire;
        lettreIntermediaire = m_plateau[m_balle->getX()+m_balle->getDepX()][m_balle->getY()+m_balle->getDepY()];
        m_plateau[m_balle->getX()+m_balle->getDepX()][m_balle->getY()+m_balle->getDepY()] = m_balle->getLettre();
        m_plateau[m_balle->getX()][m_balle->getY()] = lettreIntermediaire;

        m_balle->setY();
        m_balle->setX();
    }

    m_plateau[snoopy->getX()][snoopy->getY()] = 'S';//on place snoopy
    if(m_bonusAttrap != NULL) {m_plateau[m_bonusAttrap->getX()][m_bonusAttrap->getY()] = 3-(char)diffTemps + '0';}

    for(unsigned i=0; i<m_tabBlocs.size();++i)
    {
       m_plateau[m_tabBlocs[i]->getX()][m_tabBlocs[i]->getY()] = m_tabBlocs[i]->getLettre(); //on place tous les blocs à partir de leurs lettes
    }

    for(unsigned i=0; i<m_tabOiseau.size();++i)
    {
       m_plateau[m_tabOiseau[i].getX()][m_tabOiseau[i].getY()] = 'O' ;// on place les oiseaus
    }
}

/// On appelle la vérification de tous les blocs
void Niveau::checkerPlateauPourBalle()
{
    verificationBalle_BlocsPoussables();
    verificationBalle_BlocsCassables();
    verificationBalle_BlocsPieges();
}



std::vector<Blocs*> Niveau::getTabBlocs()
{
    return m_tabBlocs;
}

std::vector<Oiseau> Niveau::getTabOiseau()
{
    return m_tabOiseau;
}


Blocs* Niveau::getBlocsAuCord(std::vector<Blocs*> tabBlocs, int x, int y)//retourne un pointeur sur le bloc qui se trouve au niveau des coordonnes indiquées
{

    for(unsigned i(0); i< tabBlocs.size(); i++)
    {
        if((tabBlocs[i]->getX() == x) && (tabBlocs[i]->getY() == y))
        {
        return tabBlocs[i];
        }
    }
}

int Niveau::getPositionBlocs(Niveau* niveau,Blocs* blocs)//avoir la position au sein du vector du bloc demande
{
    for(unsigned i(0); i<niveau->getTabBlocs().size(); i++)
    {
        if(niveau->getTabBlocs()[i]== blocs)
        {
            return i;
        }
    }
}

int Niveau::getPosiOiseauAuNivTab(std::vector<Oiseau> const tabOiseau, int x, int y)//avoir la position au sein du vector de l'oiseau demande
{

    for(unsigned i(0); i< tabOiseau.size(); i++)
    {
        if((tabOiseau[i].getX() == x) && (tabOiseau[i].getY() == y))
        {
        return i;
        }
    }
}

void Niveau::gererBonus(PersoSnoopy* snoopy)
{

    int i,j;
    if(m_bonusAttrap == NULL)
    {
       i= rand()%20;
       j= rand()%10;
        if(rand()%30 == 0 && m_plateau[i][j] == '.')
        {
           m_bonusAttrap = new BonusAttrap(i,j,this->getTempsRestant());
        }

    }
    else if(m_bonusAttrap->getTempsALaCreation()-getTempsRestant()>3)
    {
        delete m_bonusAttrap;
        m_bonusAttrap = NULL;
    }
    else if (m_bonusAttrap->getTempsALaCreation()-getTempsRestant()<3)
    {
        if(snoopy->getX() == m_bonusAttrap->getX() && snoopy->getY() == m_bonusAttrap->getY())
        {
            snoopy->setNbrVie(snoopy->getNbrVie()+1);
            delete m_bonusAttrap;
            m_bonusAttrap = NULL;

        }
    }


}


/// Creer un objet
void Niveau::creerObjetDebut(PersoSnoopy* snoopy, std::string nom, std::string decisionJoueurNiveau)//l'objectif de creer les objet à partir de la matrice fournit avec le jeu
{
    std::string const dossier("sauvegarde//");
    std::string const pseudo(nom);
    std::string const extention(".txt");
    std::string nomFichier = dossier + nom + extention;

    int a;

    Oiseau *p_Oiseau;
    Blocs* p_Blocs;

    for(int j=0; j< m_lig; j++)
    {
        for (int i=0; i< m_col; i++)
        {
            if(this->m_plateau[i][j]=='B')
            {
            m_balle = new Balle(i,j,-1,-1);
            }

            if(this->m_plateau[i][j]=='O')
            {
            p_Oiseau = new Oiseau(i, j);
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



            if(is_readable(nomFichier))//si le fichier existe, (cette fonction est appelé quand le ficheir existe si le niveau avez ete gagner)
            {
               std::ifstream fichier(nomFichier.c_str(), std::ios::in);  // on ouvre
                if(fichier)
                {
                    fichier >> a;//on passe les caratere
                    fichier >> a;//on passe les caratere
                    fichier >> a;//ON recupere le deja atteint par le joueur dans le passe
                    snoopy->setNiveauDejaAtteint(a);
                    snoopy->setNiveauActuel(atoi(decisionJoueurNiveau.c_str()));//on lui met le niveau actuelle dans lequel on va jouer

                }
            }
        }
    }
}



void Niveau::creerObjetSauv(std::string nom, PersoSnoopy* snoopy, Niveau* niveau, std::string decisionJoueurNiveau)// permet de creer les objet à partir des sauvegardes
{
    std::string const dossier("sauvegarde//");
    std::string const pseudo(nom);
    std::string const extention(".txt");
    std::string nomFichier = dossier + nom + extention;

    int a, b, c, d;
    Oiseau *p_Oiseau;
    Blocs* p_Blocs;
    std::string mot;
    char caractere;  // notre variable o sera stockŽ le caractre
    int valeur(0);
    int nb(0);
    int niveauActuel;
    int niveauDejaAtteint;
    bool partieEnCours;
    int tailleTableau;
    std::ostringstream nivSuiv;


        std::ifstream fichier(nomFichier.c_str(), std::ios::in);  // on ouvre

        if(fichier)
        {
            fichier >> partieEnCours;
            fichier >> niveauActuel;
            fichier >> niveauDejaAtteint;
            fichier.get(caractere);

            fichier >> mot;
            fichier.get(caractere);


            for (int j=0; j< m_lig; j++)// recuperation de la table
            {
                for (int i=0; i< m_col; i++)
                {
                    fichier.get(caractere);  // on lit un caractre et on le stocke dans caractere
                    getPlateau()[i][j]=caractere;
                }
            }

            fichier.get(caractere);//on va aux prochain caractere interressant
            fichier.get(caractere);
            fichier.get(caractere);

            //recuperation des infos de snoop, cord, vie score

            fichier >> nb;
            a = nb;
            fichier >> nb;
            b = nb;
            fichier >> nb;
            c = nb;
            fichier >> nb;
            d = nb;


            snoopy->setX(a);
            snoopy->setY(b);
            snoopy->setNbrVie(c);
            snoopy->setScore(d);
            snoopy->setNiveauActuel(niveauActuel);//recuper en haut de la methode
            snoopy->setNiveauDejaAtteint(niveauDejaAtteint);//recuper en haut de la methode


            fichier.get(caractere);//on va aux prochain caractere interressant
            fichier.get(caractere);
            fichier.get(caractere);

            //recuperation des donnees de la balle, coord et direction
            fichier >> nb;
            a = nb;
            fichier >> nb;
            b = nb;
            fichier >> nb;
            c = nb;
            fichier >> nb;
            d = nb;

            m_balle = new Balle(a,b,c,d);


            fichier.get(caractere);//on va aux prochain caractere interressant
            fichier.get(caractere);
            fichier.get(caractere);

            //recuperation des P
            fichier >> nb;
            valeur = nb;
            for (int i(0); i<valeur; i++)
            {
                fichier >> nb;
                a = nb;
                fichier >> nb;
                b = nb;
                fichier >> nb;
                c = (bool)nb;

                p_Blocs = new BlocsPoussables(a, b, c);
                m_tabBlocs.push_back(p_Blocs);
                p_Blocs = NULL;
            }

            fichier.get(caractere);//on va aux prochain caractere interressant
            fichier.get(caractere);
            fichier.get(caractere);
            fichier.get(caractere);

            //recuperation des C

            fichier >> nb;
            valeur = nb;
            for (int i(0); i<valeur; i++)
            {
                fichier >> nb;
                a = nb;
                fichier >> nb;
                b = nb;

                p_Blocs = new BlocsCassables(a, b);
                m_tabBlocs.push_back(p_Blocs);
                p_Blocs = NULL;
            }

            fichier.get(caractere);//on va aux prochain caractere interressant
            fichier.get(caractere);
            fichier.get(caractere);

            //recuperation des T

            fichier >> nb;
            valeur = nb;
            for (int i(0); i<valeur; i++)
            {
                fichier >> nb;
                a = nb;
                fichier >> nb;
                b = nb;

                p_Blocs = new BlocsPieges(a, b);
                m_tabBlocs.push_back(p_Blocs);
                p_Blocs = NULL;
            }

            fichier.get(caractere);//on va aux prochain caractere interressant
            fichier.get(caractere);
            fichier.get(caractere);

            //recuperartion des O

            fichier >> nb;
            valeur = nb;
            for (int i(0); i<valeur; i++)
            {
                fichier >> nb;
                a = nb;
                fichier >> nb;
                b = nb;

                p_Oiseau = new Oiseau(a, b);
                m_tabOiseau.push_back(*p_Oiseau);
                p_Oiseau = NULL;
            }

            for(unsigned i(0); i<4-m_tabOiseau.size(); i++)
            {
                snoopy->setPlusOiseau();
            }


            fichier.get(caractere);//on va aux prochain caractere interressant
            fichier.get(caractere);
            fichier.get(caractere);

            //recuperation du temps, peut etre mettre un float?

            fichier >> nb;
            valeur = nb;

            if(!partieEnCours)
            {
                nivSuiv << snoopy->getNiveauActuel();
                niveau->setPlateau(nivSuiv.str());
                snoopy->setNbrOiseauxANul();

                tailleTableau = getTabBlocs().size();
                for(int i(0); i<tailleTableau; i++){
                delete m_tabBlocs[i];}

                for(int i(0); i<tailleTableau; i++){
                m_tabBlocs.pop_back();}

                tailleTableau = getTabOiseau().size();
                for(int i(0); i<tailleTableau; i++){
                m_tabOiseau.pop_back();}

                delete m_balle;


                niveau->creerObjetDebut(snoopy, nom, nivSuiv.str());
                niveau->initCoordSnoop(snoopy);
            }

        fichier.close();
    }
    else
    {
        std::cout << "Impossible d'ouvrir le fichier !!" << std::endl;
    }

}



void Niveau::initCoordSnoop(PersoSnoopy* snoopy)//initialisation des coordonne de snoôpy(surtout quand on charge le plateau proposé par le jeu)
{
    for(int j=0; j< m_lig; j++)
    {
        for (int i=0; i< m_col; i++)
        {
            if(this->m_plateau[i][j]=='S')
            {
            snoopy->setCoordonnees(i,j);
            }
        }
    }
}











void Niveau::setCordSnoopClav(PersoSnoopy* snoopy, Niveau* niveau, char toucheUtisateur)
{
    Blocs* blocs;
    int key(toucheUtisateur);
    int index;

        if ((key == 'j')||(key == 'J')) ///  gauche
        {
            if((snoopy->getX()-1 >=0) && getPlateau()[snoopy->getX()-1][snoopy->getY()] == '.')
            {
                snoopy->setX(snoopy->getX()-1);//si il y a un point dans la direction on veut avancer
            }
            else if((snoopy->getX()-1 >=0) && getPlateau()[snoopy->getX()-1][snoopy->getY()] >= '0' && getPlateau()[snoopy->getX()-1][snoopy->getY()] < '4' )
            {
                snoopy->setX(snoopy->getX()-1);//si il y a un point dans la direction on veut avancer
            }
            else if((snoopy->getX() > 1) && (getPlateau()[snoopy->getX()-1][snoopy->getY()] == 'P') && (getPlateau()[snoopy->getX()-2][snoopy->getY()] == '.' ))//si il y a un point P et deriere un point alors on fait avancer les deux
            {
                blocs = getBlocsAuCord(getTabBlocs(),snoopy->getX()-1,snoopy->getY());// recuperer le blocs concerner à partir des coordonnes
                if(blocs->getPoussable())//si il n'a pas ete encore bougé
                {
                blocs->deplacement(-1,0,blocs);//alors on le deplace le bloc dans la bonne direction
                snoopy->setX(snoopy->getX()-1);//alors on le deplace snoopy dans la meme direction
                }
            }
            else if((snoopy->getX()-1 >=0) && getPlateau()[snoopy->getX()-1][snoopy->getY()] == 'C')//si il y a un blocs cassable
            {
                blocs = getBlocsAuCord(getTabBlocs(),snoopy->getX()-1,snoopy->getY());// recuperer le blocs concerner à partir des coordonnes
                if(snoopy->getModeDemolition())//si le mode demolition est actif
                {
                    index=getPositionBlocs(niveau,blocs);//recuperer la position de ce blocs dans le vector
                    m_tabBlocs.erase(m_tabBlocs.begin()+index);//le supprimer
                    snoopy->setX(snoopy->getX()-1);//deplacer ves le bloc qui vient de se casser
                }
            }
            else if((snoopy->getX()-1 >=0) && getPlateau()[snoopy->getX()-1][snoopy->getY()] == 'T')//si c'est un blocs piege
            {
                snoopy->setVivant(false);//snoopy meurt
                snoopy->setToucheParPiege(true);//On indique qui les mort touche par un piege, (pour les explications de la mort juste avant le retour au menu)
            }
            else if((snoopy->getX()-1 >=0) && getPlateau()[snoopy->getX()-1][snoopy->getY()] == 'O')//Si il y a un oiseau
            {
                snoopy->setPlusOiseau();//snoopy recupere un oiseau
                index = getPosiOiseauAuNivTab(m_tabOiseau, snoopy->getX()-1, snoopy->getY());//on recupere la position de l'oiseau au niveau du vector
                m_tabOiseau.erase(m_tabOiseau.begin()+index);//on supprime l'oiseau du vector
                snoopy->setX(snoopy->getX()-1);//on deplace snoopy vers l'ancienne position de l'oiseau
            }

            snoopy->setModeDemolition(false);//on supprime le mode demolition, pour qu'il ne dure qu'un tour(à chaque fois qu'on tape sur une des 4 directions)
        }
        if ((key == 'l')||(key == 'L')) ///  droite // toutes les explication sont au niveau du haut de la methode sur le 'J'
        {
            if((snoopy->getX()+1< m_col) && (getPlateau()[snoopy->getX()+1][snoopy->getY()] == '.'))
            {
            snoopy->setX(snoopy->getX()+1);
            }
            else if((snoopy->getX()+1< m_col) && (getPlateau()[snoopy->getX()+1][snoopy->getY()] >= '0' && getPlateau()[snoopy->getX()+1][snoopy->getY()]  < '4' ))
            {
                snoopy->setX(snoopy->getX()+1);//si il y a un point dans la direction on veut avancer
            }
            else if((snoopy->getX() < m_col-2) && (getPlateau()[snoopy->getX()+1][snoopy->getY()] == 'P') && (getPlateau()[snoopy->getX()+2][snoopy->getY()] == '.' ))
            {
                blocs = getBlocsAuCord(getTabBlocs(),snoopy->getX()+1,snoopy->getY());
                if(blocs->getPoussable())
                {
                blocs->deplacement(+1,0,blocs);
                snoopy->setX(snoopy->getX()+1);
                }
            }
            else if((snoopy->getX()+1< m_col) && getPlateau()[snoopy->getX()+1][snoopy->getY()] == 'C')
            {
                blocs = getBlocsAuCord(getTabBlocs(),snoopy->getX()+1,snoopy->getY());
                if(snoopy->getModeDemolition())
                {
                    index=getPositionBlocs(niveau,blocs);
                    m_tabBlocs.erase(m_tabBlocs.begin()+index);
                    snoopy->setX(snoopy->getX()+1);
                }
            }
            else if((snoopy->getX()+1< m_col) && getPlateau()[snoopy->getX()+1][snoopy->getY()] == 'T')
            {
                snoopy->setVivant(false);
                snoopy->setToucheParPiege(true);
            }
            else if((snoopy->getX()+1< m_col) && getPlateau()[snoopy->getX()+1][snoopy->getY()] == 'O')
            {
                snoopy->setPlusOiseau();
                index = getPosiOiseauAuNivTab(m_tabOiseau, snoopy->getX()+1, snoopy->getY());
                m_tabOiseau.erase(m_tabOiseau.begin()+index);
                snoopy->setX(snoopy->getX()+1);
            }
            snoopy->setModeDemolition(false);
        }
        if ((key == 'k')||(key == 'K')) /// bas// toutes les explication sont au niveau du haut de la methode sur le 'J'
        {
            if((snoopy->getY()+1 <= m_lig-1 ) && getPlateau()[snoopy->getX()][snoopy->getY()+1] == '.')
            {
                snoopy->setY(snoopy->getY()+1);
            }
            else if((snoopy->getY()+1 <= m_lig-1 ) && getPlateau()[snoopy->getX()][snoopy->getY()+1] >= '0' && getPlateau()[snoopy->getX()][snoopy->getY()+1]   < '4' )
            {
                snoopy->setY(snoopy->getY()+1);//si il y a un point dans la direction on veut avancer
            }
            else if((snoopy->getY()< m_lig-1) && (getPlateau()[snoopy->getX()][snoopy->getY()+1] == 'P') && (getPlateau()[snoopy->getX()][snoopy->getY()+2] == '.' ))
            {
                blocs = getBlocsAuCord(getTabBlocs(),snoopy->getX(),snoopy->getY()+1);
                if(blocs->getPoussable())
                {
                blocs->deplacement(0,+1,blocs);
                snoopy->setY(snoopy->getY()+1);
                }
            }
            else if((snoopy->getY()+1 <= m_lig-1 ) && getPlateau()[snoopy->getX()][snoopy->getY()+1] == 'C')
            {
                blocs = getBlocsAuCord(getTabBlocs(),snoopy->getX(),snoopy->getY()+1);
                if(snoopy->getModeDemolition())
                {
                    index=getPositionBlocs(niveau,blocs);
                    m_tabBlocs.erase(m_tabBlocs.begin()+index);
                    snoopy->setY(snoopy->getY()+1);
                }
            }
            else if((snoopy->getY()+1 <= m_lig-1 ) && getPlateau()[snoopy->getX()][snoopy->getY()+1] == 'T')
            {
                snoopy->setVivant(false);
                snoopy->setToucheParPiege(true);
            }
            else if((snoopy->getY()+1 <= m_lig-1 ) && getPlateau()[snoopy->getX()][snoopy->getY()+1] == 'O')
            {
                snoopy->setPlusOiseau();
                index = getPosiOiseauAuNivTab(m_tabOiseau, snoopy->getX(), snoopy->getY()+1);
                m_tabOiseau.erase(m_tabOiseau.begin()+index);
                snoopy->setY(snoopy->getY()+1);
            }
            snoopy->setModeDemolition(false);
        }
        if ((key == 'i')||(key == 'I')) ///  haut // toutes les explication sont au niveau du haut de la methode sur le 'J'
        {
            if((snoopy->getY()-1 >=0) && getPlateau()[snoopy->getX()][snoopy->getY()-1] == '.')
            {
                snoopy->setY(snoopy->getY()-1);
            }
            else if((snoopy->getY()-1 >=0) && getPlateau()[snoopy->getX()][snoopy->getY()-1] >= '0' && getPlateau()[snoopy->getX()][snoopy->getY()-1] < '4' )
            {
                snoopy->setY(snoopy->getY()-1);//si il y a un point dans la direction on veut avancer
            }
            else if((snoopy->getY() > 1) && (getPlateau()[snoopy->getX()][snoopy->getY()-1] == 'P') && (getPlateau()[snoopy->getX()][snoopy->getY()-2] == '.' ))
            {
                blocs = getBlocsAuCord(getTabBlocs(),snoopy->getX(),snoopy->getY()-1);
                if(blocs->getPoussable())
                {
                blocs->deplacement(0,-1,blocs);
                snoopy->setY(snoopy->getY()-1);
                }
            }
            else if((snoopy->getY()-1 >=0) && getPlateau()[snoopy->getX()][snoopy->getY()-1] == 'C')
            {
                blocs = getBlocsAuCord(getTabBlocs(),snoopy->getX(),snoopy->getY()-1);
                if(snoopy->getModeDemolition())
                {
                    index=getPositionBlocs(niveau,blocs);
                    m_tabBlocs.erase(m_tabBlocs.begin()+index);
                    snoopy->setY(snoopy->getY()-1);
                }
            }
            else if((snoopy->getY()-1 >=0) && getPlateau()[snoopy->getX()][snoopy->getY()-1] == 'T')
            {
                snoopy->setVivant(false);
                snoopy->setToucheParPiege(true);
            }
            else if((snoopy->getY()-1 >=0) && getPlateau()[snoopy->getX()][snoopy->getY()-1] == 'O')
            {
                snoopy->setPlusOiseau();
                index = getPosiOiseauAuNivTab(m_tabOiseau, snoopy->getX(), snoopy->getY()-1);
                m_tabOiseau.erase(m_tabOiseau.begin()+index);
                snoopy->setY(snoopy->getY()-1);
            }
            snoopy->setModeDemolition(false);
        }
}










bool Niveau::toucheBalle(PersoSnoopy* snoopy, Niveau* niveau)//savoir la la balle touche snoopy
{
  if(snoopy->getX() == niveau->m_balle->getX() && snoopy->getY() == niveau->m_balle->getY())
  {
    return true;
  }
  else
  {
    return false;
  }

}

/// On vérifie si la balle ne veut pas sortir du plateau
char Niveau::verificationBalle_Bords()
{
    if(!((m_balle->getX() == 0)&&(m_balle->getDepX() == -1)) && !((m_balle->getX() == m_col-1)&&(m_balle->getDepX() == 1)) && !((m_balle->getY() == 0)&&(m_balle->getDepY() == -1)) && !((m_balle->getY() == m_lig-1)&&(m_balle->getDepY() == 1))  )
    {
        return 1;
    }
    else return 0;
}

/// On vérifie si la balle va taper dans un bloc poussable
void Niveau::verificationBalle_BlocsPoussables()
{
    /// Pas la peine de vérifier si la balle est sur les bords droit ou bas du tableau
    /// Quand l'obstacle P est en bas a droite de la balle
    if((m_balle->getX() != m_col-1) && (m_balle->getY() != m_lig-1) && (m_plateau[m_balle->getX()+1][m_balle->getY()+1] == 'P') && (m_balle->getDepX()==1) && (m_balle->getDepY()==1) )
    {
        if((m_plateau[m_balle->getX()+1][m_balle->getY()] == 'P')) /// A-t-on un P a droite de la balle ?
        {
            m_balle->setDepX(-m_balle->getDepX());
        }
        else if((m_plateau[m_balle->getX()][m_balle->getY()+1] == 'P')) /// A-t-on un P en dessous de la balle ?
        {
            m_balle->setDepY(-m_balle->getDepY());
        }
        else
        {
            m_balle->setDepX(-m_balle->getDepX());
            m_balle->setDepY(-m_balle->getDepY());
        }
    }
    /// Pas la peine de vérifier si la balle est sur les bords gauche ou bas du tableau
    /// Quand l'obstacle P est en bas a gauche de la balle
    if((m_balle->getX() != 0) && (m_balle->getY() != m_lig-1) && (m_plateau[m_balle->getX()-1][m_balle->getY()+1] == 'P') && (m_balle->getDepX()==-1) && (m_balle->getDepY()==1) )
    {
        if((m_plateau[m_balle->getX()-1][m_balle->getY()] == 'P')) /// A-t-on un P a gauche de la balle ?
        {
            m_balle->setDepX(-m_balle->getDepX());
        }
        else if((m_plateau[m_balle->getX()][m_balle->getY()+1] == 'P')) /// A-t-on un P en dessous de la balle ?
        {
            m_balle->setDepY(-m_balle->getDepY());
        }
        else
        {
            m_balle->setDepX(-m_balle->getDepX());
            m_balle->setDepY(-m_balle->getDepY());
        }
    }
    /// Pas la peine de vérifier si la balle est sur les bords droit ou haut du tableau
    /// Quand l'obstacle P est en haut a droite de la balle
    if((m_balle->getX() != m_col-1) && (m_balle->getY() != 0) && (m_plateau[m_balle->getX()+1][m_balle->getY()-1] == 'P') && (m_balle->getDepX()==1) && (m_balle->getDepY()==-1) )
    {
        if((m_plateau[m_balle->getX()][m_balle->getY()-1] == 'P')) /// A-t-on un P au dessus de la balle ?
        {
            m_balle->setDepY(-m_balle->getDepY());
        }
        else if((m_plateau[m_balle->getX()+1][m_balle->getY()] == 'P')) /// A-t-on un P a droite de la balle ?
        {
            m_balle->setDepX(-m_balle->getDepX());
        }
        else
        {
            m_balle->setDepX(-m_balle->getDepX());
            m_balle->setDepY(-m_balle->getDepY());
        }
    }
    /// Pas la peine de vérifier si la balle est sur les bords gauche ou haut du tableau
    /// Quand l'obstacle P est en haut a gauche de la balle
    if((m_balle->getX() != 0) && (m_balle->getY() != 0) && (m_plateau[m_balle->getX()-1][m_balle->getY()-1] == 'P') && (m_balle->getDepX()==-1) && (m_balle->getDepY()==-1) )
    {
        if((m_plateau[m_balle->getX()][m_balle->getY()-1] == 'P')) /// A-t-on un P au dessus de la balle ?
        {
            m_balle->setDepY(-m_balle->getDepY());
        }
        else if((m_plateau[m_balle->getX()-1][m_balle->getY()] == 'P')) /// A-t-on un P a gauche de la balle ?
        {
            m_balle->setDepX(-m_balle->getDepX());
        }
        else
        {
            m_balle->setDepX(-m_balle->getDepX());
            m_balle->setDepY(-m_balle->getDepY());
        }
    }
}

/// On vérifie si la balle va taper dans un bloc cassable
void Niveau::verificationBalle_BlocsCassables()
{
    /// Pas la peine de vérifier si la balle est sur les bords droit ou bas du tableau
    /// Quand l'obstacle C est en bas a droite de la balle
    if((m_balle->getX() != m_col-1) && (m_balle->getY() != m_lig-1) && (m_plateau[m_balle->getX()+1][m_balle->getY()+1] == 'C') && (m_balle->getDepX()==1) && (m_balle->getDepY()==1) )
    {
        if((m_plateau[m_balle->getX()+1][m_balle->getY()] == 'C')) /// A-t-on un C a droite de la balle ?
        {
            m_balle->setDepX(-m_balle->getDepX());
        }
        else if((m_plateau[m_balle->getX()][m_balle->getY()+1] == 'C')) /// A-t-on un C en dessous de la balle ?
        {
            m_balle->setDepY(-m_balle->getDepY());
        }
        else
        {
            m_balle->setDepX(-m_balle->getDepX());
            m_balle->setDepY(-m_balle->getDepY());
        }
    }
    /// Pas la peine de vérifier si la balle est sur les bords gauche ou bas du tableau
    /// Quand l'obstacle C est en bas a gauche de la balle
    if((m_balle->getX() != 0) && (m_balle->getY() != m_lig-1) && (m_plateau[m_balle->getX()-1][m_balle->getY()+1] == 'C') && (m_balle->getDepX()==-1) && (m_balle->getDepY()==1) )
    {
        if((m_plateau[m_balle->getX()-1][m_balle->getY()] == 'C')) /// A-t-on un C a gauche de la balle ?
        {
            m_balle->setDepX(-m_balle->getDepX());
        }
        else if((m_plateau[m_balle->getX()][m_balle->getY()+1] == 'C')) /// A-t-on un C en dessous de la balle ?
        {
            m_balle->setDepY(-m_balle->getDepY());
        }
        else
        {
            m_balle->setDepX(-m_balle->getDepX());
            m_balle->setDepY(-m_balle->getDepY());
        }
    }
    /// Pas la peine de vérifier si la balle est sur les bords droit ou haut du tableau
    /// Quand l'obstacle C est en haut a droite de la balle
    if((m_balle->getX() != m_col-1) && (m_balle->getY() != 0) && (m_plateau[m_balle->getX()+1][m_balle->getY()-1] == 'C') && (m_balle->getDepX()==1) && (m_balle->getDepY()==-1) )
    {
        if((m_plateau[m_balle->getX()][m_balle->getY()-1] == 'C')) /// A-t-on un C au dessus de la balle ?
        {
            m_balle->setDepY(-m_balle->getDepY());
        }
        else if((m_plateau[m_balle->getX()+1][m_balle->getY()] == 'C')) /// A-t-on un C a droite de la balle ?
        {
            m_balle->setDepX(-m_balle->getDepX());
        }
        else
        {
            m_balle->setDepX(-m_balle->getDepX());
            m_balle->setDepY(-m_balle->getDepY());
        }
    }
    /// Pas la peine de vérifier si la balle est sur les bords gauche ou haut du tableau
    /// Quand l'obstacle C est en haut a gauche de la balle
    if((m_balle->getX() != 0) && (m_balle->getY() != 0) && (m_plateau[m_balle->getX()-1][m_balle->getY()-1] == 'C') && (m_balle->getDepX()==-1) && (m_balle->getDepY()==-1) )
    {
        if((m_plateau[m_balle->getX()][m_balle->getY()-1] == 'C')) /// A-t-on un C au dessus de la balle ?
        {
            m_balle->setDepY(-m_balle->getDepY());
        }
        else if((m_plateau[m_balle->getX()-1][m_balle->getY()] == 'C')) /// A-t-on un C a gauche de la balle ?
        {
            m_balle->setDepX(-m_balle->getDepX());
        }
        else
        {
            m_balle->setDepX(-m_balle->getDepX());
            m_balle->setDepY(-m_balle->getDepY());
        }
    }
}

/// On vérifie si la balle va taper dans un bloc piégé
void Niveau::verificationBalle_BlocsPieges()
{
    /// Pas la peine de vérifier si la balle est sur les bords droit ou bas du tableau
    /// Quand l'obstacle T est en bas a droite de la balle
    if((m_balle->getX() != m_col-1) && (m_balle->getY() != m_lig-1) && (m_plateau[m_balle->getX()+1][m_balle->getY()+1] == 'T') && (m_balle->getDepX()==1) && (m_balle->getDepY()==1) )
    {
        if((m_plateau[m_balle->getX()+1][m_balle->getY()] == 'T')) /// A-t-on un T a droite de la balle ?
        {
            m_balle->setDepX(-m_balle->getDepX());
        }
        else if((m_plateau[m_balle->getX()][m_balle->getY()+1] == 'T')) /// A-t-on un T en dessous de la balle ?
        {
            m_balle->setDepY(-m_balle->getDepY());
        }
        else
        {
            m_balle->setDepX(-m_balle->getDepX());
            m_balle->setDepY(-m_balle->getDepY());
        }
    }
    /// Pas la peine de vérifier si la balle est sur les bords gauche ou bas du tableau
    /// Quand l'obstacle T est en bas a gauche de la balle
    if((m_balle->getX() != 0) && (m_balle->getY() != m_lig-1) && (m_plateau[m_balle->getX()-1][m_balle->getY()+1] == 'T') && (m_balle->getDepX()==-1) && (m_balle->getDepY()==1) )
    {
        if((m_plateau[m_balle->getX()-1][m_balle->getY()] == 'T')) /// A-t-on un T a gauche de la balle ?
        {
            m_balle->setDepX(-m_balle->getDepX());
        }
        else if((m_plateau[m_balle->getX()][m_balle->getY()+1] == 'T')) /// A-t-on un T en dessous de la balle ?
        {
            m_balle->setDepY(-m_balle->getDepY());
        }
        else
        {
            m_balle->setDepX(-m_balle->getDepX());
            m_balle->setDepY(-m_balle->getDepY());
        }
    }
    /// Pas la peine de vérifier si la balle est sur les bords droit ou haut du tableau
    /// Quand l'obstacle T est en haut a droite de la balle
    if((m_balle->getX() != m_col-1) && (m_balle->getY() != 0) && (m_plateau[m_balle->getX()+1][m_balle->getY()-1] == 'T') && (m_balle->getDepX()==1) && (m_balle->getDepY()==-1) )
    {
        if((m_plateau[m_balle->getX()][m_balle->getY()-1] == 'T')) /// A-t-on un T au dessus de la balle ?
        {
            m_balle->setDepY(-m_balle->getDepY());
        }
        else if((m_plateau[m_balle->getX()+1][m_balle->getY()] == 'T')) /// A-t-on un T a droite de la balle ?
        {
            m_balle->setDepX(-m_balle->getDepX());
        }
        else
        {
            m_balle->setDepX(-m_balle->getDepX());
            m_balle->setDepY(-m_balle->getDepY());
        }
    }
    /// Pas la peine de vérifier si la balle est sur les bords gauche ou haut du tableau
    /// Quand l'obstacle T est en haut a gauche de la balle
    if((m_balle->getX() != 0) && (m_balle->getY() != 0) && (m_plateau[m_balle->getX()-1][m_balle->getY()-1] == 'T') && (m_balle->getDepX()==-1) && (m_balle->getDepY()==-1) )
    {
        if((m_plateau[m_balle->getX()][m_balle->getY()-1] == 'T')) /// A-t-on un T au dessus de la balle ?
        {
            m_balle->setDepY(-m_balle->getDepY());
        }
        else if((m_plateau[m_balle->getX()-1][m_balle->getY()] == 'T')) /// A-t-on un T a gauche de la balle ?
        {
            m_balle->setDepX(-m_balle->getDepX());
        }
        else
        {
            m_balle->setDepX(-m_balle->getDepX());
            m_balle->setDepY(-m_balle->getDepY());
        }
    }
}

/// On vérifie si la balle va taper dans un oiseau
void Niveau::verificationBalle_Oiseaux()
{
    /// Pas la peine de vérifier si la balle est sur les bords droit ou bas du tableau
    /// Quand l'obstacle O est en bas a droite de la balle
    if((m_balle->getX() != m_col-1) && (m_balle->getY() != m_lig-1) && (m_plateau[m_balle->getX()+1][m_balle->getY()+1] == 'O') && (m_balle->getDepX()==1) && (m_balle->getDepY()==1) )
    {
        m_balle->setDepX(-m_balle->getDepX());
        m_balle->setDepY(-m_balle->getDepY());
    }
    /// Pas la peine de vérifier si la balle est sur les bords gauche ou bas du tableau
    /// Quand l'obstacle O est en bas a gauche de la balle
    if((m_balle->getX() != 0) && (m_balle->getY() != m_lig-1) && (m_plateau[m_balle->getX()-1][m_balle->getY()+1] == 'O') && (m_balle->getDepX()==-1) && (m_balle->getDepY()==1) )
    {
        m_balle->setDepX(-m_balle->getDepX());
        m_balle->setDepY(-m_balle->getDepY());
    }
    /// Pas la peine de vérifier si la balle est sur les bords droit ou haut du tableau
    /// Quand l'obstacle O est en haut a droite de la balle
    if((m_balle->getX() != m_col-1) && (m_balle->getY() != 0) && (m_plateau[m_balle->getX()+1][m_balle->getY()-1] == 'O') && (m_balle->getDepX()==1) && (m_balle->getDepY()==-1) )
    {
        m_balle->setDepX(-m_balle->getDepX());
        m_balle->setDepY(-m_balle->getDepY());
    }
    /// Pas la peine de vérifier si la balle est sur les bords gauche ou haut du tableau
    /// Quand l'obstacle O est en haut a gauche de la balle
    if((m_balle->getX() != 0) && (m_balle->getY() != 0) && (m_plateau[m_balle->getX()-1][m_balle->getY()-1] == 'O') && (m_balle->getDepX()==-1) && (m_balle->getDepY()==-1) )
    {
        m_balle->setDepX(-m_balle->getDepX());
        m_balle->setDepY(-m_balle->getDepY());
    }
}


bool Niveau::is_readable( const std::string & file )//savoir si le ficheir existe
{
    std::ifstream fichier( file.c_str() );
    return !fichier.fail();
}


