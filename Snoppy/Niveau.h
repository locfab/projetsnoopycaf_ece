#ifndef NIVEAU_H_INCLUDED
#define NIVEAU_H_INCLUDED

#include <iostream>
#include <vector>

#include "Menu.h"
#include "Balle.h"
#include "Oiseau.h"
#include "Temps.h"
#include "Blocs.h"
#include "BlocsPoussables.h"
#include "BlocsCassables.h"
#include "BlocsPieges.h"
#include "PersoSnoopy.h"
#include "BonusAttrap.h"

#include <windows.h>
#include "Console.h"


class Niveau
{
    public:

    Niveau();
    ///Niveau(surchargé);
    ~Niveau();
	void setPlateau(std::string niveau);
	void afficherPlateau(PersoSnoopy* snoopy);
	std::vector< std::vector<char> > getPlateau();
	void changerPlateau(PersoSnoopy* snoopy);
	void checkerPlateauPourBalle();
	bool toucheBalle(PersoSnoopy* snoopy, Niveau* niveau);

	std::vector<Blocs*> getTabBlocs();
	std::vector<Oiseau> getTabOiseau();

	void creerObjetDebut(PersoSnoopy* snoopy, std::string nom, std::string decisionJoueurNiveau);
	void creerObjetSauv(std::string nom, PersoSnoopy* snoopy, Niveau* niveau, std::string decisionJoueurNiveau);

    void initCoordSnoop(PersoSnoopy* snoopy);

	double getTemps();
    void getAttendre(double secondes);
    double getTempsRestant();
    char getNiveauCourant();
    Blocs* getBlocsAuCord(std::vector<Blocs*>, int x, int y);
    int getPositionBlocs(Niveau* niveau, Blocs* blocs);
    int getPosiOiseauAuNivTab(std::vector<Oiseau> const tabOiseau, int x, int y);

    void setTempsRestant(double newTempsRestant);
	void setNiveauCourant();
	void setCordSnoopClav(PersoSnoopy* snoopy, Niveau* niveau, char toucheUtisateur);

	char verificationBalle_Bords();
	void verificationBalle_BlocsPoussables();
	void verificationBalle_BlocsCassables();
	void verificationBalle_BlocsPieges();
	void verificationBalle_Oiseaux();

	Console *pConsole = NULL;

	void getDeplacementBalle(std::vector< std::vector<char> > plateau);
	Balle* getBalle();

	void gererBonus(PersoSnoopy* snoopy);

	bool is_readable( const std::string & file );


   protected:

	char m_niveauCourant;
	std::vector< std::vector<char> > m_plateau;
	int m_lignes;
	int m_colonnes;
	double m_tempsRestant;
    Temps *m_temps;
    Balle *m_balle;
    BonusAttrap* m_bonusAttrap;
    std::vector<Oiseau> m_tabOiseau;
    std::vector<Blocs*> m_tabBlocs;
    int const m_lig;
    int const m_col;

 };

#endif // NIVEAU_H_INCLUDED
