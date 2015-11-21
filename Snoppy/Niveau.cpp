#include <iostream>
#include <sstream>
#include "Niveau.h"
#include <fstream>
#include <string>

/// Constructeur par défaut
Niveau::Niveau()
            :   m_niveauCourant(0)
{
    // Alloue la mémoire du pointeur
    pConsole = Console::getInstance();
    m_temps = new Temps();
    m_tempsRestant = m_temps->getTempsMax();
    m_balle=NULL;

}

/// Destructeur
Niveau::~Niveau()
{
        for(int i=0; i<m_tabBlocs.size();++i){
    delete m_tabBlocs[i];}
    delete m_temps;
    delete m_balle;
}

void Niveau::setPlateau(std::string niveau)
{

    std::string nb = niveau; //choisir quel fichier on ouvre 1, 2 ,3
    std::string debut("matriceNiveau");
    std::string fin("UtilisableSansEspace.txt");
    std::string nomFichier = debut + nb + fin;

        std::ifstream fichier(nomFichier.c_str(), std::ios::in);  // on ouvre

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
            std::cout << "Impossible d'ouvrir le fichier !!!" << std::endl;

        this->m_plateau = grille;// peut etre mettre un getter

}

void Niveau::afficherPlateau()
{
    pConsole->gotoLigCol(5, 50);
    std::cout << "Temps restant : " << (int)getTempsRestant() << "  ";
    setTempsRestant(getTempsRestant()); /// Calcul du nouveau temps restant
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
void Niveau::changerPlateau(PersoSnoopy* snoopy)
{
    for (int j=0; j<10; j++)
    {
        for (int i=0; i<20; i++)
        {
            this->m_plateau[i][j] = '.';
        }
    }


    if(verificationBalle_Bords() == 1)
    {
        char lettreIntermediaire;
        lettreIntermediaire = m_plateau[m_balle->getX()+m_balle->getDepX()][m_balle->getY()+m_balle->getDepY()];
        m_plateau[m_balle->getX()+m_balle->getDepX()][m_balle->getY()+m_balle->getDepY()] = m_balle->getLettre();
        m_plateau[m_balle->getX()][m_balle->getY()] = lettreIntermediaire;

        m_balle->setY();
        m_balle->setX();
    }

    m_plateau[snoopy->getX()][snoopy->getY()] = 'S';

    for(int i=0; i<m_tabBlocs.size();++i)
    {
       m_plateau[m_tabBlocs[i]->getX()][m_tabBlocs[i]->getY()] = m_tabBlocs[i]->getLettre() ;
    }

    for(int i=0; i<m_tabOiseau.size();++i)
    {
       m_plateau[m_tabOiseau[i].getX()][m_tabOiseau[i].getY()] = 'O' ;
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


Blocs* Niveau::getBlocsAuCord(std::vector<Blocs*> tabBlocs, int x, int y)
{

    for(int i(0); i< tabBlocs.size(); i++)
    {
        if((tabBlocs[i]->getX() == x) && (tabBlocs[i]->getY() == y))
        {
        return tabBlocs[i];
        }
    }
}

int Niveau::getPositionBlocs(Niveau* niveau,Blocs* blocs)
{
    for(int i(0); i<niveau->getTabBlocs().size(); i++)
    {
        if(niveau->getTabBlocs()[i]== blocs)
        {
            return i;
        }
    }
}

int Niveau::getPosiOiseauAuNivTab(std::vector<Oiseau> const tabOiseau, int x, int y)
{

    for(int i(0); i< tabOiseau.size(); i++)
    {
        if((tabOiseau[i].getX() == x) && (tabOiseau[i].getY() == y))
        {
        return i;
        }
    }
}


/// Creer un objet
void Niveau::creerObjetDebut(PersoSnoopy* snoopy, std::string nom, std::string decisionJoueurNiveau)
{
    std::string const dossier("sauvegarde//");
    std::string const pseudo(nom);
    std::string const extention(".txt");
    std::string nomFichier = dossier + nom + extention;

    int a;

    Oiseau *p_Oiseau;
    Blocs* p_Blocs;

    for(int j=0; j<10; j++)
    {
        for (int i=0; i<20; i++)
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
            if(is_readable(nomFichier))
            {
               std::ifstream fichier(nomFichier.c_str(), std::ios::in);  // on ouvre
                if(fichier)
                {
                    fichier >> a;
                    fichier >> a;
                    fichier >> a;
                    snoopy->setNiveauDejaAtteint(a);
                    snoopy->setNiveauActuel(atoi(decisionJoueurNiveau.c_str()));

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
    int rien(1);
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


            for (int j=0; j<10; j++)// recuperation de la table
            {
                for (int i=0; i<20; i++)
                {
                    fichier.get(caractere);  // on lit un caractre et on le stocke dans caractere
                    getPlateau()[i][j]=caractere;
                }
            }

            fichier.get(caractere);
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

           // std::cout << a << " " << b << " " << c << " " << d << std::endl;;

            snoopy->setX(a);
            snoopy->setY(b);
            snoopy->setNbrVie(c);
            snoopy->setScore(d);
            snoopy->setNiveauActuel(niveauActuel);
            snoopy->setNiveauDejaAtteint(niveauDejaAtteint);


            fichier.get(caractere);
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


            fichier.get(caractere);
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

            fichier.get(caractere);
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

            fichier.get(caractere);
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

            fichier.get(caractere);
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

            for(int i(0); i<4-m_tabOiseau.size(); i++)
            {
                snoopy->setPlusOiseau();
            }


            fichier.get(caractere);
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
                delete m_balle;
                tailleTableau = getTabBlocs().size();
                for(int i(0); i< tailleTableau ;i++)
                {
                    m_tabBlocs.pop_back();
                }
                tailleTableau = getTabOiseau().size();
                for(int i(0); i< tailleTableau ;i++)
                {
                    m_tabOiseau.pop_back();
                }
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











void Niveau::setCordSnoopClav(PersoSnoopy* snoopy, Niveau* niveau, char toucheUtisateur)
{
    Blocs* blocs;
    int key(toucheUtisateur);
    int index;

        if ((key == 'j')||(key == 'J')) ///  gauche
        {
            if((snoopy->getX()-1 >=0) && getPlateau()[snoopy->getX()-1][snoopy->getY()] == '.')
            {
                snoopy->setX(snoopy->getX()-1);
            }
            else if((snoopy->getX() > 1) && (getPlateau()[snoopy->getX()-1][snoopy->getY()] == 'P') && (getPlateau()[snoopy->getX()-2][snoopy->getY()] == '.' ))
            {
                blocs = getBlocsAuCord(getTabBlocs(),snoopy->getX()-1,snoopy->getY());
                if(blocs->getPoussable())
                {
                blocs->deplacement(-1,0,blocs);
                snoopy->setX(snoopy->getX()-1);
                }
            }
           else if((snoopy->getX()-1 >=0) && getPlateau()[snoopy->getX()-1][snoopy->getY()] == 'C')
            {
                blocs = getBlocsAuCord(getTabBlocs(),snoopy->getX()-1,snoopy->getY());
                if(snoopy->getModeDemolition())
                {
                    index=getPositionBlocs(niveau,blocs);
                    m_tabBlocs.erase(m_tabBlocs.begin()+index);
                    snoopy->setX(snoopy->getX()-1);
                }
            }
            else if((snoopy->getX()-1 >=0) && getPlateau()[snoopy->getX()-1][snoopy->getY()] == 'T')
            {
                snoopy->setVivant(false);
            }
            else if((snoopy->getX()-1 >=0) && getPlateau()[snoopy->getX()-1][snoopy->getY()] == 'O')
            {
                snoopy->setPlusOiseau();
                index = getPosiOiseauAuNivTab(m_tabOiseau, snoopy->getX()-1, snoopy->getY());
                m_tabOiseau.erase(m_tabOiseau.begin()+index);
                snoopy->setX(snoopy->getX()-1);
            }

            snoopy->setModeDemolition(false);
        }
        if ((key == 'l')||(key == 'L')) ///  droite
        {
            if((snoopy->getX()+1<20) && (getPlateau()[snoopy->getX()+1][snoopy->getY()] == '.'))
            {
            snoopy->setX(snoopy->getX()+1);
            }
            else if((snoopy->getX() < 18) && (getPlateau()[snoopy->getX()+1][snoopy->getY()] == 'P') && (getPlateau()[snoopy->getX()+2][snoopy->getY()] == '.' ))
            {
                blocs = getBlocsAuCord(getTabBlocs(),snoopy->getX()+1,snoopy->getY());
                if(blocs->getPoussable())
                {
                blocs->deplacement(+1,0,blocs);
                snoopy->setX(snoopy->getX()+1);
                }
            }
            else if((snoopy->getX()+1<20) && getPlateau()[snoopy->getX()+1][snoopy->getY()] == 'C')
            {
                blocs = getBlocsAuCord(getTabBlocs(),snoopy->getX()+1,snoopy->getY());
                if(snoopy->getModeDemolition())
                {
                    index=getPositionBlocs(niveau,blocs);
                    m_tabBlocs.erase(m_tabBlocs.begin()+index);
                    snoopy->setX(snoopy->getX()+1);
                }
            }
            else if((snoopy->getX()+1<20) && getPlateau()[snoopy->getX()+1][snoopy->getY()] == 'T')
            {
                snoopy->setVivant(false);
            }
            else if((snoopy->getX()+1<20) && getPlateau()[snoopy->getX()+1][snoopy->getY()] == 'O')
            {
                snoopy->setPlusOiseau();
                index = getPosiOiseauAuNivTab(m_tabOiseau, snoopy->getX()+1, snoopy->getY());
                m_tabOiseau.erase(m_tabOiseau.begin()+index);
                snoopy->setX(snoopy->getX()+1);
            }
            snoopy->setModeDemolition(false);
        }
        if ((key == 'k')||(key == 'K')) /// bas
        {
            if((snoopy->getY()+1 <=9 ) && getPlateau()[snoopy->getX()][snoopy->getY()+1] == '.')
            {
            snoopy->setY(snoopy->getY()+1);
            }
            else if((snoopy->getY()<9) && (getPlateau()[snoopy->getX()][snoopy->getY()+1] == 'P') && (getPlateau()[snoopy->getX()][snoopy->getY()+2] == '.' ))
            {
                blocs = getBlocsAuCord(getTabBlocs(),snoopy->getX(),snoopy->getY()+1);
                if(blocs->getPoussable())
                {
                blocs->deplacement(0,+1,blocs);
                snoopy->setY(snoopy->getY()+1);
                }
            }
            else if((snoopy->getY()+1 <=9 ) && getPlateau()[snoopy->getX()][snoopy->getY()+1] == 'C')
            {
                blocs = getBlocsAuCord(getTabBlocs(),snoopy->getX(),snoopy->getY()+1);
                if(snoopy->getModeDemolition())
                {
                    index=getPositionBlocs(niveau,blocs);
                    m_tabBlocs.erase(m_tabBlocs.begin()+index);
                    snoopy->setY(snoopy->getY()+1);
                }
            }
            else if((snoopy->getY()+1 <=9 ) && getPlateau()[snoopy->getX()][snoopy->getY()+1] == 'T')
            {
                snoopy->setVivant(false);
            }
            else if((snoopy->getY()+1 <=9 ) && getPlateau()[snoopy->getX()][snoopy->getY()+1] == 'O')
            {
                snoopy->setPlusOiseau();
                index = getPosiOiseauAuNivTab(m_tabOiseau, snoopy->getX(), snoopy->getY()+1);
                m_tabOiseau.erase(m_tabOiseau.begin()+index);
                snoopy->setY(snoopy->getY()+1);
            }
            snoopy->setModeDemolition(false);
        }
        if ((key == 'i')||(key == 'I')) ///  haut
        {
            if((snoopy->getY()-1 >=0) && getPlateau()[snoopy->getX()][snoopy->getY()-1] == '.')
            {
                snoopy->setY(snoopy->getY()-1);
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













/// On vérifie si la balle ne veut pas sortir du plateau
char Niveau::verificationBalle_Bords()
{
    if(!((m_balle->getX() == 0)&&(m_balle->getDepX() == -1)) && !((m_balle->getX() == 19)&&(m_balle->getDepX() == 1)) && !((m_balle->getY() == 0)&&(m_balle->getDepY() == -1)) && !((m_balle->getY() == 9)&&(m_balle->getDepY() == 1))  )
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
    if((m_balle->getX() != 19) && (m_balle->getY() != 9) && (m_plateau[m_balle->getX()+1][m_balle->getY()+1] == 'P') && (m_balle->getDepX()==1) && (m_balle->getDepY()==1) )
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
    if((m_balle->getX() != 0) && (m_balle->getY() != 9) && (m_plateau[m_balle->getX()-1][m_balle->getY()+1] == 'P') && (m_balle->getDepX()==-1) && (m_balle->getDepY()==1) )
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
    if((m_balle->getX() != 19) && (m_balle->getY() != 0) && (m_plateau[m_balle->getX()+1][m_balle->getY()-1] == 'P') && (m_balle->getDepX()==1) && (m_balle->getDepY()==-1) )
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
    if((m_balle->getX() != 19) && (m_balle->getY() != 9) && (m_plateau[m_balle->getX()+1][m_balle->getY()+1] == 'C') && (m_balle->getDepX()==1) && (m_balle->getDepY()==1) )
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
    if((m_balle->getX() != 0) && (m_balle->getY() != 9) && (m_plateau[m_balle->getX()-1][m_balle->getY()+1] == 'C') && (m_balle->getDepX()==-1) && (m_balle->getDepY()==1) )
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
    if((m_balle->getX() != 19) && (m_balle->getY() != 0) && (m_plateau[m_balle->getX()+1][m_balle->getY()-1] == 'C') && (m_balle->getDepX()==1) && (m_balle->getDepY()==-1) )
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
    if((m_balle->getX() != 19) && (m_balle->getY() != 9) && (m_plateau[m_balle->getX()+1][m_balle->getY()+1] == 'T') && (m_balle->getDepX()==1) && (m_balle->getDepY()==1) )
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
    if((m_balle->getX() != 0) && (m_balle->getY() != 9) && (m_plateau[m_balle->getX()-1][m_balle->getY()+1] == 'T') && (m_balle->getDepX()==-1) && (m_balle->getDepY()==1) )
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
    if((m_balle->getX() != 19) && (m_balle->getY() != 0) && (m_plateau[m_balle->getX()+1][m_balle->getY()-1] == 'T') && (m_balle->getDepX()==1) && (m_balle->getDepY()==-1) )
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
    if((m_balle->getX() != 19) && (m_balle->getY() != 9) && (m_plateau[m_balle->getX()+1][m_balle->getY()+1] == 'O') && (m_balle->getDepX()==1) && (m_balle->getDepY()==1) )
    {
        m_balle->setDepX(-m_balle->getDepX());
        m_balle->setDepY(-m_balle->getDepY());
    }
    /// Pas la peine de vérifier si la balle est sur les bords gauche ou bas du tableau
    /// Quand l'obstacle O est en bas a gauche de la balle
    if((m_balle->getX() != 0) && (m_balle->getY() != 9) && (m_plateau[m_balle->getX()-1][m_balle->getY()+1] == 'O') && (m_balle->getDepX()==-1) && (m_balle->getDepY()==1) )
    {
        m_balle->setDepX(-m_balle->getDepX());
        m_balle->setDepY(-m_balle->getDepY());
    }
    /// Pas la peine de vérifier si la balle est sur les bords droit ou haut du tableau
    /// Quand l'obstacle O est en haut a droite de la balle
    if((m_balle->getX() != 19) && (m_balle->getY() != 0) && (m_plateau[m_balle->getX()+1][m_balle->getY()-1] == 'O') && (m_balle->getDepX()==1) && (m_balle->getDepY()==-1) )
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


bool Niveau::is_readable( const std::string & file )
{
    std::ifstream fichier( file.c_str() );
    return !fichier.fail();
}
