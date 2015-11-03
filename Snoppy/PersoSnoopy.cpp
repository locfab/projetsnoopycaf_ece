#include <iostream>
#include "PersoSnoopy.h"

using namespace std;

PersoSnoopy::PersoSnoopy(): m_nbOiseauxAttrap(0),m_vivant(true), m_vie(3),m_saLetrre('S')
{}

void PersoSnoopy::setPlusOiseau()
{
    if(m_nbOiseauxAttrap<4)
    m_nbOiseauxAttrap+=1;
    else
    cout << "Niveau suivant" << endl;
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
