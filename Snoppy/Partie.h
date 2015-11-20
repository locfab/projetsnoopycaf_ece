#ifndef PARTIE_H_INCLUDED
#define PARTIE_H_INCLUDED

#include "PersoSnoopy.h"
#include "Niveau.h"
#include <fstream>


/// Classe Partie gérant les niveaux et personnage
class Partie
{
    private:

        PersoSnoopy *m_snoopy;
        Niveau *m_niveau;

    public:

        Partie();
        ///Partie(surchargé);
        ~Partie();
        void jouer(Partie *partie, char decisionJoueurMenu, std::string pseudo, std::string decisionJoueurNiveau);

};

#endif // PARTIE_H_INCLUDED
