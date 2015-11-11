#ifndef PARTIE_H_INCLUDED
#define PARTIE_H_INCLUDED

#include "PersoSnoopy.h"
#include "Niveau.h"

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
        void jouer(Partie *partie);

};

#endif // PARTIE_H_INCLUDED
