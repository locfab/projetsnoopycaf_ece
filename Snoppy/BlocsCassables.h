#ifndef BLOCSCASSABLES_H_INCLUDED
#define BLOCSCASSABLES_H_INCLUDED
#include "Blocs.h"

class BlocsCassables : public Blocs
{
    public:

    BlocsCassables();
    BlocsCassables(int x, int y);

    void casserBloc(bool modeDemolition);

    void setModeDemolition();


    protected:

    char m_saLetrre = 'C';
    bool m_modeDemolition = false;
};



#endif // BLOCSCASSABLES_H_INCLUDED
