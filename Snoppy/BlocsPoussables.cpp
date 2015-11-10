#include <iostream>
#include "BlocsPoussables.h"


BlocsPoussables::BlocsPoussables(): Blocs()
{
}

BlocsPoussables::BlocsPoussables(int x, int y, bool poussable): Blocs(x,y), m_poussable(poussable)
{
}
