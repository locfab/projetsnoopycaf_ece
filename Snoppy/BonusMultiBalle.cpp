#include <iostream>
#include "BonusMultiBalle.h"

BonusMultiBalle::BonusMultiBalle(): m_x(-1), m_y(-1), m_saLetrre('m'), m_tempsALaCreation(0)
{
}

BonusMultiBalle::BonusMultiBalle(int x, int y, int tempsALaCreation) : m_x(x), m_y(y), m_saLetrre('m'), m_tempsALaCreation(tempsALaCreation)
{
}
BonusMultiBalle::~BonusMultiBalle()
{
}

char BonusMultiBalle::getLettre() const
{
 	return m_saLetrre;
}





void BonusMultiBalle::setX(int x)
{
	if(x>=0 && x<20)
	{
		m_x = x;
	}
}

void BonusMultiBalle::setY(int y)
{
	if(y>=0 && y<10)
	{
		m_y = y;
	}
}
void BonusMultiBalle::setTempsALaCreation(int tempsALaCreation)
{
	if(tempsALaCreation>0 && tempsALaCreation<60)
	{
		m_tempsALaCreation = tempsALaCreation;
	}
}


/// Getter de la coordonnée X
int BonusMultiBalle::getX() const
{
    return m_x;
}

/// Getter de la coordonnée Y
int BonusMultiBalle::getY() const
{
    return m_y;
}
int BonusMultiBalle::getTempsALaCreation() const
{
	return m_tempsALaCreation;
}