#ifndef NIVEAU_H_INCLUDED
#define NIVEAU_H_INCLUDED


#include <iostream>
#include <vector>
#include <windows.h>
#include "Console.h"
#include "Blocs.h"
#include "BlocsPoussables.h"
#include "BlocsCassables.h"
#include "BlocsPieges.h"
#include "Balle.h"
#include "Oiseau.h"
#include "Temps.h"
#include "PersoSnoopy.h"
#include "BonusMultiBalle.h"
#include "BonusAttrap.h"




class Niveau
{
    public:

    Niveau();
    ///Niveau(surchargé);
    ~Niveau();
	void setPlateauDeb(std::string niveau);
	void setPlateauDejaCree(std::string niveau);
	void afficherPlateau(PersoSnoopy* snoopy, char decisionJoueurMenu, std::string decisionJoueurNiveau);
	std::vector< std::vector<char> > getPlateau();
	void changerPlateau(PersoSnoopy* snoopy);
	void checkerPlateauPourBalle();
	bool toucheBalle(PersoSnoopy* snoopy, Niveau* niveau);

	std::vector<Blocs*> getTabBlocs();//recupere le vect
	std::vector<Oiseau> getTabOiseau();//recupere le vect
	std::vector<Balle> getVectBalle();//recupere le vect

	void creerObjetDebut(PersoSnoopy* snoopy, std::string nom, std::string decisionJoueurNiveau);//creer des objets sans de sauvegardes
	void creerObjetSauv(std::string nom, PersoSnoopy* snoopy, Niveau* niveau, std::string decisionJoueurNiveau);//avec sauvegarde

    void initCoordSnoop(PersoSnoopy* snoopy);

	double getTemps();
    void getAttendre(double secondes);
    double getHeureCrea();
    char getNiveauCourant();
    Blocs* getBlocsAuCord(std::vector<Blocs*>, int x, int y);
    int getPositionBlocs(Niveau* niveau, Blocs* blocs);
    int getPosiOiseauAuNivTab(std::vector<Oiseau> const tabOiseau, int x, int y);

    void setHeureCrea(double newTempsRestant);
	void setNiveauCourant();
	void setCordSnoopClav(PersoSnoopy* snoopy, Niveau* niveau, char toucheUtisateur);
	void setDeplacementBalle();

	/*on va faire pour tout lees types de blocs des 
	vérifiction pour connzitre le mouvement de la balle*/
	char verificationBalle_Bords(Balle* balle);
	void verificationBalle_BlocsPoussables(Balle* balle);
	void verificationBalle_BlocsCassables(Balle* balle);
	void verificationBalle_BlocsPieges(Balle* balle);
	void verificationBalle_Oiseaux(Balle* balle);

	Console *pConsole = NULL;



	void gererBonus(PersoSnoopy* snoopy);//permet de gerer les deux gros bonus du jeu

	bool is_readable( const std::string & file );




   protected:

	char m_niveauCourant;
	std::vector< std::vector<char> > m_plateau;
	double m_heureCrea;
    Temps *m_temps;
    std::vector<Balle> m_vectBalle;
    BonusMultiBalle* m_bonusMultiBalle;
    BonusAttrap* m_bonusAttrap;
    std::vector<Oiseau> m_tabOiseau;
    std::vector<Blocs*> m_tabBlocs;
    int const m_lig;
    int const m_col;

 };

#endif // NIVEAU_H_INCLUDED
