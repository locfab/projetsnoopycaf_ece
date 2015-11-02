#include <iostream>
#include "PersoSnoopy.h"

using namespace std;

Snoopy::Snoopy(): m_nbOiseauxAttrap(0),m_vivant(true), m_vie(3),m_saLetrre('S')
{}

void Snoopy::setPlusOiseau()
{
    if(m_nbOiseauxAttrap<4)
    m_nbOiseauxAttrap+=1;
    else
    cout << "Niveau suivant" << endl;
}

int Snoopy::getNbOiseauAttrap() const
{
    return m_nbOiseauxAttrap;
}

void Snoopy::setVivant(bool vivant)
{
    if (!vivant)
    m_vivant=false;
}

bool Snoopy::getVivant() const
{
    return m_vivant;
}
