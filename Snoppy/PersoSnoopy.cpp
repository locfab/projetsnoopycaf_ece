#include <iostream>
#include "PersoSnoopy.h"

PersoSnoopy::PersoSnoopy()
            : m_saLetrre('S'),m_vivant(true), m_modeDemolition(false), m_nbOiseauxAttrap(0), m_vie(3),
              m_niveauActuel(1), m_niveauDejaAtteint(1), m_toucherParPiege(false)
{
    m_scoreVectParNiv.push_back(0);
    m_scoreVectParNiv.push_back(0);
    m_scoreVectParNiv.push_back(0);
}

PersoSnoopy::PersoSnoopy(int x, int y)
          : m_x(x), m_y(y), m_nbOiseauxAttrap(0), m_vie(3), m_saLetrre('S'), m_vivant(true), m_modeDemolition(false),
            m_niveauActuel(1), m_niveauDejaAtteint(1), m_toucherParPiege(false)
{
    m_scoreVectParNiv.push_back(0);
    m_scoreVectParNiv.push_back(0);
    m_scoreVectParNiv.push_back(0);
}

PersoSnoopy::PersoSnoopy(int x, int y, int scoreNiv1, int scoreNiv2, int scoreNiv3, int vie)
			: m_x(x), m_y(y), m_nbOiseauxAttrap(0), m_vie(vie), m_saLetrre('S'), m_vivant(true), m_modeDemolition(false),
        m_niveauActuel(1), m_niveauDejaAtteint(1), m_toucherParPiege(false)
{
    m_scoreVectParNiv.push_back(scoreNiv1);
    m_scoreVectParNiv.push_back(scoreNiv2);
    m_scoreVectParNiv.push_back(scoreNiv3);
}
PersoSnoopy::~PersoSnoopy()
{

}

void PersoSnoopy::setPlusOiseau()
{
    if(m_nbOiseauxAttrap<4)
    m_nbOiseauxAttrap+=1;
}
void PersoSnoopy::setNbrOiseauxANul()
{
  m_nbOiseauxAttrap = 0;
}
void PersoSnoopy::setVivant(bool vivant)
{
    if (!vivant)
    m_vivant=false;
}

void PersoSnoopy::setNbrVie(int vie)
{
   if(m_vie >=0 && m_vie < 10)//A ne pas modifier!!! si on met au dessus de 10, ou negatif, ca bloque tout on ne pourra plus modifier dans le fichier
    m_vie = vie;
}
void PersoSnoopy::setScore(int score, int niv)
{
    if(niv > 0 && niv < 4 && score > m_scoreVectParNiv[niv-1] )
    m_scoreVectParNiv[niv-1] = score;
}

void PersoSnoopy::setCoordonnees(int x, int y)
{
  if ((x>=0 && x<20)&&(y>=0 && y<10))
  	{
  		setX(x);
  		setY(y);
	}
}

void PersoSnoopy::setX(int x)
{
  if (x>=0 && x<20)
  	{
  		m_x=x;
	}
}
void PersoSnoopy::setY(int y)
{
  	if (y>=0 && y<10)
  	{
  		m_y=y;
	  }
}

void PersoSnoopy::setModeDemolition(bool modeDemolition)
{
    m_modeDemolition = modeDemolition;
}

void PersoSnoopy::setNiveauDejaAtteint(int niveauDejaAtteint)
{
   if (niveauDejaAtteint>=1 && niveauDejaAtteint <4)
    {
      m_niveauDejaAtteint = niveauDejaAtteint;
    }
   else
   {
    std::cout << "!probleme pas de niveau inferieur a 0 ou supperrieur a 3!";
   }
}
void PersoSnoopy::setNiveauActuel(int niveauActuel)
{
   if (niveauActuel>=1 && niveauActuel <4)
    {
      m_niveauActuel = niveauActuel;
    }
   else
   {
    std::cout << "§probleme pas de niveau inferieur a 0 ou supperrieur a 3§" ;
   }
}
void PersoSnoopy::setToucheParPiege(bool toucheParPiege)
{
  m_toucherParPiege = toucheParPiege;
}





int PersoSnoopy::getNbOiseauAttrap() const
{
    return m_nbOiseauxAttrap;
}

bool PersoSnoopy::getVivant() const
{
    return m_vivant;
}
int PersoSnoopy::getNbrVie() const
{
    return m_vie;
}
int PersoSnoopy::getScore() const
{
    return m_scoreVectParNiv[0] + m_scoreVectParNiv[1] + m_scoreVectParNiv[2];
}
int PersoSnoopy::getScoreParNiv(int niv) const
{
    if(niv > 0 && niv < 4)
    return m_scoreVectParNiv[niv-1];
    else
    return 0;
}
int PersoSnoopy::getX() const
{
    return m_x;
}

int PersoSnoopy::getY() const
{
    return m_y;
}

bool PersoSnoopy::getModeDemolition() const
{
    return m_modeDemolition;
}
int PersoSnoopy::getNiveauDejaAtteint() const
{
    return m_niveauDejaAtteint;
}
int PersoSnoopy::getNiveauActuel() const
{
    return m_niveauActuel;
}
bool PersoSnoopy::getToucheParPiege() const
{
    return m_toucherParPiege;
}
