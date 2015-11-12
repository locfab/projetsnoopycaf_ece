#ifndef BLOCSPOUSSABLES_H_INCLUDED
#define BLOCSPOUSSABLES_H_INCLUDED
#include "Blocs.h"

class BlocsPoussables : public Blocs
{
    public:

    BlocsPoussables();
    BlocsPoussables(int x, int y, bool poussable);

    void deplacement(bool droite, bool haut);

    bool getPoussable() const;


    protected:

    char m_saLetrre = 'P';
    bool m_poussable;
};


#endif // BLOCSPOUSSABLES_H_INCLUDED
