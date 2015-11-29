#include <iostream>
#include "Oiseau.h"


Oiseau::Oiseau(): m_x(-1),m_y(-1), m_saLetrre('O')
{

}

Oiseau::Oiseau(int x, int y): m_x(x),m_y(y), m_saLetrre('O')
{

}
Oiseau::~Oiseau()
{

}

int Oiseau::getX() const
{
    return this->m_x;
}

int Oiseau::getY() const
{
    return m_y;
}
