#include <iostream>
#include "Blocs.h"


Blocs::Blocs()
{

}
Blocs::Blocs(int x, int y): m_x(x), m_y(y)
{

}
Blocs::~Blocs()
{

}

void Blocs::setX(int x)
{
	if(x>=0 && x<20)
	{
		m_x = x;
	}
}

void Blocs::setY(int y)
{
	if(y>=0 && y<10)
	{
		m_y = y;
	}
}


/// Getter de la coordonnée X
int Blocs::getX() const
{
    return m_x;
}

/// Getter de la coordonnée Y
int Blocs::getY() const
{
    return m_y;
}








char Blocs::getLettre() const
{
}

bool Blocs::getPoussable() const
{
}
void Blocs::deplacement(int largeur, int hauteur, Blocs* blocs)
{
}

