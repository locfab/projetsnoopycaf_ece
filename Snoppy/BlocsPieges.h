#ifndef BLOCSPIEGES_H_INCLUDED
#define BLOCSPIEGES_H_INCLUDED
#include "Blocs.h"

class BlocsPieges : public Blocs
{
    public:

    BlocsPieges();
    BlocsPieges(int x, int y);

    protected:

    char m_saLetrre = 'T';
};


#endif // BLOCSPIEGES_H_INCLUDED
