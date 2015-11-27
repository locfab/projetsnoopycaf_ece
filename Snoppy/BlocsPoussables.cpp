#include <iostream>
#include "BlocsPoussables.h"


BlocsPoussables::BlocsPoussables(): Blocs(), m_saLetrre('P'), m_poussable(true)
{
}

BlocsPoussables::BlocsPoussables(int x, int y, bool poussable): Blocs(x,y), m_poussable(poussable), m_saLetrre('P')
{
}
BlocsPoussables::~BlocsPoussables()
{
}

void BlocsPoussables::deplacement(int largeur, int hauteur, Blocs* blocs)
{
    BlocsPoussables* blocsPoussables = (BlocsPoussables*)blocs;
    bool changementDeCoordBlocsPouss(false);

	if(blocsPoussables->m_poussable)//Si bloc poussable
	{
		if(((largeur==-1||largeur==1)) || ((hauteur==-1 || hauteur==1))) // les deplacements sont de 1
		{
			if(((largeur==0) && (hauteur==-1||hauteur==1)) || ((hauteur==0) && (largeur==-1||largeur==1)) )//il y a un 1 et un 0
			{
				if(largeur==1)
				{
					if(getX()+1<20)
					{
					setX(getX()+1);
					changementDeCoordBlocsPouss = true;
					}
				}
				if(largeur==-1)
				{
					if(getX()-1>=0)
					{
					setX(getX()-1);
					changementDeCoordBlocsPouss = true;
					}
				}
				if(hauteur==-1)
				{
					if(getY()-1>=0)
					{
					setY(getY()-1);
					changementDeCoordBlocsPouss = true;
					}
				}
				if(hauteur==1)
				{
					if(getY()+1<10)
					{
					setY(getY()+1);
					changementDeCoordBlocsPouss = true;
					}
				}
			}
		}
	}

	if (changementDeCoordBlocsPouss == true) //désactiver le fait de pouvoir etre pousser.
	{
		blocsPoussables->setPoussable(false);
	}

}




void BlocsPoussables::setPoussable(bool poussable)
{
    m_poussable = poussable;
}


/// Getter sur le booléen Poussable
bool BlocsPoussables::getPoussable() const
{
 	return m_poussable;
}

char BlocsPoussables::getLettre() const
{
 	return m_saLetrre;
}


