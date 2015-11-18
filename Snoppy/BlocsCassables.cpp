#include <iostream>
#include "BlocsCassables.h"


BlocsCassables::BlocsCassables(): Blocs(), m_saLetrre('C')
{
}

BlocsCassables::BlocsCassables(int x, int y) : Blocs(x,y), m_saLetrre('C')
{
}
BlocsCassables::~BlocsCassables()
{
}

char BlocsCassables::getLettre() const
{
 	return m_saLetrre;
}
