#ifndef BLOCSPOUSSABLES_H_INCLUDED
#define BLOCSPOUSSABLES_H_INCLUDED
#include "Blocs.h"

class BlocsPoussables : public Blocs
{
    public:

    BlocsPoussables();
    BlocsPoussables(int x, int y, bool poussable);
    virtual ~BlocsPoussables();

    void deplacement(int largeur, int hauteur, Blocs* blocs);

    void setPoussable(bool poussable);

    bool getPoussable() const;

    char getLettre() const;


    protected:

    char m_saLetrre;
    bool m_poussable;
};


#endif // BLOCSPOUSSABLES_H_INCLUDED
