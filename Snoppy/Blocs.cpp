#include <iostream>
#include "Blocs.h"


Blocs::Blocs()
{

}
Blocs::Blocs(int x, int y): m_x(x), m_y(y)
{

}

/// Getter de la coordonn�e X
int Blocs::getX()
{
    return m_x;
}

/// Getter de la coordonn�e Y
int Blocs::getY()
{
    return m_y;
}
