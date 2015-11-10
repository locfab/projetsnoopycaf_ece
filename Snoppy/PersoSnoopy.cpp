#include <iostream>
#include "PersoSnoopy.h"

PersoSnoopy::PersoSnoopy()
{
}

PersoSnoopy::PersoSnoopy(int x, int y): m_x(x), m_y(y), m_nbOiseauxAttrap(0), m_vie(3)
{
}

PersoSnoopy::PersoSnoopy(int x, int y, int nbOiseauxAttrap, int vie)
			: m_x(x), m_y(y), m_nbOiseauxAttrap(nbOiseauxAttrap), m_vie(vie)
{
}


void PersoSnoopy::setPlusOiseau()
{
    if(m_nbOiseauxAttrap<4)
    m_nbOiseauxAttrap+=1;
    else
    std::cout << "Niveau suivant" << std::endl;
}

int PersoSnoopy::getNbOiseauAttrap() const
{
    return m_nbOiseauxAttrap;
}

void PersoSnoopy::setVivant(bool vivant)
{
    if (!vivant)
    m_vivant=false;
}

bool PersoSnoopy::getVivant() const
{
    return m_vivant;
}
