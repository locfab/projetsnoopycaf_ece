#include <iostream>
#include "BlocsCassables.h"


BlocsCassables::BlocsCassables(): Blocs(), m_saLetrre('C'), m_modeDemolition(false)
{
}

BlocsCassables::BlocsCassables(int x, int y) : Blocs(x,y), m_saLetrre('C'), m_modeDemolition(false)
{
}
BlocsCassables::~BlocsCassables()
{
}

void BlocsCassables::casserBloc(bool modeDemolition)
{
	//il faudra remplacer dans la table par un '.' ou un ' '
	// Ensuite appeller le destructeur
}

void BlocsCassables::setModeDemolition()
{
}

char BlocsCassables::getLettre() const
{
 	return m_saLetrre;
}
