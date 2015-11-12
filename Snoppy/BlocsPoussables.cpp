#include <iostream>
#include "BlocsPoussables.h"


BlocsPoussables::BlocsPoussables(): Blocs(), m_saLetrre('P')
{
}

BlocsPoussables::BlocsPoussables(int x, int y, bool poussable): Blocs(x,y), m_poussable(poussable), m_saLetrre('P')
{
}

/// Getter sur le booléen Poussable
bool BlocsPoussables::getPoussable() const
{
 	return m_poussable;
}
