#include <iostream>
#include "BonusAttrap.h"


BonusAttrap::BonusAttrap(): m_saLetrre('b'), m_tempsALaCreation(0)
{
}

BonusAttrap::BonusAttrap(int x, int y, int tempsALaCreation) : m_x(x), m_y(y), m_saLetrre('b'), m_tempsALaCreation(tempsALaCreation)
{
}
BonusAttrap::~BonusAttrap()
{
}

char BonusAttrap::getLettre() const
{
 	return m_saLetrre;
}

/*int BonusAttrap::getTempsALaCreation(Temps* temps)
{
	tempsALaCreation->getTempsRestant;
}*/





void BonusAttrap::setX(int x)
{
	if(x>=0 && x<20)
	{
		m_x = x;
	}
}

void BonusAttrap::setY(int y)
{
	if(y>=0 && y<10)
	{
		m_y = y;
	}
}
void BonusAttrap::setTempsALaCreation(int tempsALaCreation)
{
	if(tempsALaCreation>0 && tempsALaCreation<60)
	{
		m_tempsALaCreation = tempsALaCreation;
	}
}


/// Getter de la coordonnée X
int BonusAttrap::getX() const
{
    return m_x;
}

/// Getter de la coordonnée Y
int BonusAttrap::getY() const
{
    return m_y;
}
int BonusAttrap::getTempsALaCreation() const
{
	return m_tempsALaCreation;
}




