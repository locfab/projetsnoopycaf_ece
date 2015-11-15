#ifndef NIVEAU_H_INCLUDED
#define NIVEAU_H_INCLUDED

#include "Menu.h"
#include "Balle.h"
#include "Oiseau.h"
#include <vector>
#include <iostream>
#include <windows.h>
#include "Console.h"
#include "Temps.h"
#include "Blocs.h"
#include "BlocsPoussables.h"
#include "BlocsCassables.h"
#include "BlocsPieges.h"
#include "PersoSnoopy.h"

class Niveau
{
    public:
    Niveau();
    ///Niveau(surchargé);
    ~Niveau();
	void setPlateau(std::string niveau);
	void afficherPlateau(char niveau);
	std::vector< std::vector<char> > getPlateau();
	void changerPlateau();
	void checkerPlateauPourBalle();

	std::vector<Blocs*> getTabBlocs();
	std::vector<Oiseau> getTabOiseau();

	void creerObjet();

    void initCoordSnoop(PersoSnoopy* snoopy);
	double getTemps();
    void getAttendre(double secondes);
    double getTempsRestant();
    void setTempsRestant(double newTempsRestant);

	char getNiveauCourant();
	void setNiveauCourant();

	char verificationBalle_Bords();
	char verificationBalle_BlocsPoussables();

	Console *pConsole = NULL;

	void getDeplacementBalle(std::vector< std::vector<char> > plateau);
	Balle* getBalle();


   protected:

	char m_niveauCourant;
	std::vector< std::vector<char> > m_plateau;
	int m_lignes;
	int m_colonnes;
	double m_tempsRestant;
    Temps *m_temps;
    Balle *m_balle;
    std::vector<Oiseau> m_tabOiseau;
    std::vector<Blocs*> m_tabBlocs;

 };

#endif // NIVEAU_H_INCLUDED
