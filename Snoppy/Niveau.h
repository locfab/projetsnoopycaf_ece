#ifndef NIVEAU_H_INCLUDED
#define NIVEAU_H_INCLUDED

#include "Menu.h"
#include "Balle.h"
#include <vector>
#include <iostream>
#include <windows.h>
#include "Console.h"
#include "Temps.h"

class Niveau
{
    public:
    Niveau();
    ///Niveau(surchargé);
    ~Niveau();
	void setPlateau(char niveau);
	void afficherPlateau(char niveau);
	void creerObjet();

	double getTemps();
    void getAttendre(double secondes);
    double getTempsRestant();
    void setTempsRestant(double newTempsRestant);

	char getNiveauCourant();
	void setNiveauCourant();

	Console *pConsole = NULL;


   protected:

	char m_niveauCourant;
	std::vector< std::vector<char> > m_plateau;
	int m_lignes;
	int m_colonnes;
	double m_tempsRestant;
    Temps *m_temps;

 };

#endif // NIVEAU_H_INCLUDED
