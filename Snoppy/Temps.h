#ifndef TEMPS_H_INCLUDED
#define TEMPS_H_INCLUDED

#include <ctime>

/// Classe Temps gérant temporisation
class Temps
{
    private:
        double m_tempsMax;

    public:
        Temps();
        Temps(double _secondes);
        ~Temps();
        void attendre(double temps);
        double getTempsMax();
        void Score(double newTempsRestant);


};

#endif // TEMPS_H_INCLUDED
