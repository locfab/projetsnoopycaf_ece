#include <iostream>
#include "PersoSnoopy.h"

PersoSnoopy::PersoSnoopy(): m_saLetrre('S'),m_vivant(true), m_modeDemolition(false), m_nbOiseauxAttrap(0), m_vie(3), m_score(0)
{
}

PersoSnoopy::PersoSnoopy(int x, int y): m_x(x), m_y(y), m_nbOiseauxAttrap(0), m_vie(3), m_saLetrre('S'), m_vivant(true), m_modeDemolition(false), m_score(0)
{
}

PersoSnoopy::PersoSnoopy(int x, int y, int score, int vie)
			: m_x(x), m_y(y), m_nbOiseauxAttrap(0), m_vie(vie), m_saLetrre('S'), m_vivant(true), m_modeDemolition(false), m_score(score)
{
}
PersoSnoopy::~PersoSnoopy()
{

}


bool PersoSnoopy::toucheBalle(PersoSnoopy* snoopy, Balle* balle)
{
  if(snoopy->getX() == balle->getX() && snoopy->getY() == balle->getY())
  {
    return true;
  }
}


void PersoSnoopy::setPlusOiseau()
{
    if(m_nbOiseauxAttrap<4)
    m_nbOiseauxAttrap+=1;
    if(m_nbOiseauxAttrap==4)
    std::cout << "Niveau suivant" << std::endl;
}
void PersoSnoopy::setVivant(bool vivant)
{
    if (!vivant)
    m_vivant=false;
}

void PersoSnoopy::setNbrVie(int vie)
{
    m_vie = vie;
}
void PersoSnoopy::setScore(int score)
{
    m_score = score;
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
