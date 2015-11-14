#ifndef BLOCSCASSABLES_H_INCLUDED
#define BLOCSCASSABLES_H_INCLUDED
#include "Blocs.h"

class BlocsCassables : public Blocs
{
    public:

    BlocsCassables();
    BlocsCassables(int x, int y);
    ~BlocsCassables();

    void casserBloc(bool modeDemolition);

    void setModeDemolition();


    protected:

    char m_saLetrre;
    bool m_modeDemolition;
};



#endif // BLOCSCASSABLES_H_INCLUDED
