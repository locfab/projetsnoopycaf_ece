#ifndef PARTIE_H_INCLUDED
#define PARTIE_H_INCLUDED

#include "PersoSnoopy.h"
#include "Niveau.h"
#include <fstream>


/// Classe Partie g�rant les niveaux et personnage
class Partie
{
    private:

        PersoSnoopy *m_snoopy;
        Niveau *m_niveau;

    public:

        Partie();
        ///Partie(surcharg�);
        ~Partie();
        void jouer(Partie *partie, char decisionJoueur);

};

#endif // PARTIE_H_INCLUDED
