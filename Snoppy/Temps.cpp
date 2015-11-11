#include "Temps.h"

/// Construcuteur par défaut
Temps::Temps()
            : m_tempsMax(60)
{

}

/// Constructeur surchargé
Temps::Temps(double _secondes)
            : m_tempsMax(_secondes)
{

}

/// Destructeur
Temps::~Temps()
{

}

/// Fonction de temporisation
void Temps::attendre(double temps)
{
    clock_t arrivee = clock() + (temps * CLOCKS_PER_SEC);

    while(clock() < arrivee);
}

/// Getter du temps maximum de la partie
double Temps::getTempsMax()
{
    return m_tempsMax;
}
