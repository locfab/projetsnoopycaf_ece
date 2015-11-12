#include <iostream>
#include "BlocsPoussables.h"


BlocsPoussables::BlocsPoussables(): Blocs()
{
}

BlocsPoussables::BlocsPoussables(int x, int y, bool poussable): Blocs(x,y), m_poussable(poussable)
{
}

/// Getter sur le booléen Poussable
void BlocsPoussables::getPoussable()
{
    if(m_poussable == true) std::cout << "Bloc poussable";

    else std::cout << "Bloc non poussable";
}
