#include <iostream>
#include "Balle.h"


Balle::Balle()
{
}
Balle::Balle(int x, int y) : m_x(x), m_y(y)
{
}

void Balle::deplacement()
{
	this->directionDuDeplacementSuivant();
}
void Balle::directionDuDeplacementSuivant()
{

}


int Balle::getX() const
{
	return this->m_x;
}
int Balle::getY() const
{
	return this->m_y;
}
int Balle::getDepX() const
{
	return this->m_depx;
}
int Balle::getDepY() const
{
	return this->m_depy;
}


void Balle::setX()
{
	if(getX()>1 && getX()<19)
	this->m_x = getX()+getDepX();
}
void Balle::setY()
{
	if(getY()>1 && getY()<9)
	this->m_x = getY()+getDepY();
}
