#ifndef BLOCSCASSABLES_H_INCLUDED
#define BLOCSCASSABLES_H_INCLUDED
#include "Blocs.h"

class BlocsCassables : public Blocs
{
    public:

    BlocsCassables();
    BlocsCassables(int x, int y);
    virtual ~BlocsCassables();

    char getLettre() const;


    protected:

    char m_saLetrre;
};



#endif // BLOCSCASSABLES_H_INCLUDED
