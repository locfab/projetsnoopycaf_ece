#ifndef NIVEAU_H_INCLUDED
#define NIVEAU_H_INCLUDED

#include "menu.h"
#include <vector>
#include <iostream>

class Niveau
{
    public:
    Niveau();
	void setPlateau(std::string niveau);
	void afficherPlateau() const;
	void gestionTemps();
	void afficherTemps();

	void setTempsRestant(double newTempsRestant);
	void getAttendre(double secondes);

	double getTemps();
	double getTempsRestant();

      // Void creerObjet // je sais pas ce que c'est (a rajouter)




   protected:

	int m_temps;
	int m_tempsRestant;
	//Temps *m_temps;// A rajouter
	std::vector< std::vector<char> > m_plateau;
	int m_lignes;
	int m_colonnes;

 };

#endif // NIVEAU_H_INCLUDED
