#ifndef NIVEAU_H_INCLUDED
#define NIVEAU_H_INCLUDED

#include "Menu.h"
#include "Balle.h"
#include <vector>
#include <iostream>

class Niveau
{
    public:

    Niveau();

	void afficherPlateau() const;
	void creerObjet();
	void gestionTemps();
	void afficherTemps();

	void setPlateau(std::string niveau);
	void setTempsRestant(double newTempsRestant);
	void getAttendre(double secondes);

	double getTemps();
	double getTempsRestant();





   protected:

	int m_temps;
	int m_tempsRestant;
	//Temps *m_temps;// A rajouter
	std::vector< std::vector<char> > m_plateau;
	int m_lignes;
	int m_colonnes;

 };

#endif // NIVEAU_H_INCLUDED
