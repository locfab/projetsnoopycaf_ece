#include <iostream>
#include "Balle.h"


Balle::Balle()
{
}
Balle::Balle(int x, int y) : m_x(x), m_y(y)
{
}
Balle::Balle(int x, int y, int depx, int depy) : m_x(x), m_y(y)
{
	setDepX(depx);
	setDepY(depy);
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
	if(getX()+getDepX()>0 && getX()+getDepX()<20)
	this->m_x = getX()+getDepX();
}
void Balle::setY()
{
	if(getY()+getDepY()>0 && getY()+getDepY()<10)
	this->m_x = getY()+getDepY();
}
void Balle::setDepX(int depx)
{
	if (depx==1)
	this->m_depx=1;
	if (depx==-1)
	this->m_depx=-1;
	if (depx!=1 && depx!=-1)
	std::cout << "FAUTE SUR LE VECTEUR VITESSE DEPX" << std::endl;

}
void Balle::setDepY(int depy)
{
	if (depy==1)
	this->m_depy=1;
	if (depy==-1)
	this->m_depy=-1;
	if (depy!=1 && depy!=-1)
	std::cout << "FAUTE SUR LE VECTEUR VITESSE DEPY" << std::endl;
}
