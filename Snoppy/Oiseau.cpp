#include <iostream>
#include "Oiseau.h"


Oiseau::Oiseau()
{

}

Oiseau::Oiseau(int x, int y): m_x(x),m_y(y)
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
