#ifndef PARTIE_H_INCLUDED
#define PARTIE_H_INCLUDED

#include "PersoSnoopy.h"
#include "Niveau.h"

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
        void jouer(Partie *partie);

};

#endif // PARTIE_H_INCLUDED
