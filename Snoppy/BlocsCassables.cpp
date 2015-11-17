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

char BlocsCassables::getLettre() const
{
 	return m_saLetrre;
}

bool BlocsCassables::getModeDemolition() const
{
	return m_modeDemolition;
}

void BlocsCassables::setModeDemolition(bool modeDemolition)
{
	m_modeDemolition = modeDemolition;
}
