#ifndef BLOCSPIEGES_H_INCLUDED
#define BLOCSPIEGES_H_INCLUDED
#include "Blocs.h"

class BlocsPieges : public Blocs
{
    public:

    BlocsPieges();
    BlocsPieges(int x, int y);
    virtual ~BlocsPieges();

    char getLettre() const;

    protected:

    char m_saLetrre;
};


#endif // BLOCSPIEGES_H_INCLUDED
