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
	void setPlateau(char niveau);
	void afficherPlateau(char niveau);
	void creerObjet();
    void initCoordSnoop(PersoSnoopy* snoopy);
	double getTemps();
    void getAttendre(double secondes);
    double getTempsRestant();
    void setTempsRestant(double newTempsRestant);

	char getNiveauCourant();
	void setNiveauCourant();

	Console *pConsole = NULL;

	///char getNombreBalles();
    ///void setNombreBalles(char nombreBalles);
    ///void ajouterBalle();


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
    ///char m_nombreBalles;

 };

#endif // NIVEAU_H_INCLUDED
