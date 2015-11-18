#include <iostream>
#include "PersoSnoopy.h"

PersoSnoopy::PersoSnoopy(): m_saLetrre('S'),m_vivant(true), m_modeDemolition(false)
{
}

PersoSnoopy::PersoSnoopy(int x, int y): m_x(x), m_y(y), m_nbOiseauxAttrap(0), m_vie(3), m_saLetrre('S'), m_vivant(true), m_modeDemolition(false)
{
}

PersoSnoopy::PersoSnoopy(int x, int y, int nbOiseauxAttrap, int vie)
			: m_x(x), m_y(y), m_nbOiseauxAttrap(nbOiseauxAttrap), m_vie(vie), m_saLetrre('S'), m_vivant(true), m_modeDemolition(false)
{
}
PersoSnoopy::~PersoSnoopy()
{

}


void PersoSnoopy::setPlusOiseau()
{
    if(m_nbOiseauxAttrap<4)
    m_nbOiseauxAttrap+=1;
    else
    std::cout << "Niveau suivant" << std::endl;
}
void PersoSnoopy::setVivant(bool vivant)
{
    if (!vivant)
    m_vivant=false;
}


void PersoSnoopy::setCoordonnees(int x, int y)
{
  if ((x>=0 && x<20)&&(y>=0 && y<10))
  	{
  		setX(x);
  		setY(y);
	}
}

void PersoSnoopy::setX(int x)
{
  if (x>=0 && x<20)
  	{
  		m_x=x;
	}
}
void PersoSnoopy::setY(int y)
{
  	if (y>=0 && y<10)
  	{
  		m_y=y;
	}
}

void PersoSnoopy::setModeDemolition(bool modeDemolition) 
{
    m_modeDemolition = modeDemolition;
}





int PersoSnoopy::getNbOiseauAttrap() const
{
    return m_nbOiseauxAttrap;
}

bool PersoSnoopy::getVivant() const
{
    return m_vivant;
}
int PersoSnoopy::getNbrVie() const
{
    return m_vie;
}
int PersoSnoopy::getScore() const
{
    return m_score;
}
int PersoSnoopy::getX() const
{
    return m_x;
}

int PersoSnoopy::getY() const
{
    return m_y;
}

bool PersoSnoopy::getModeDemolition() const
{
    return m_modeDemolition;
}