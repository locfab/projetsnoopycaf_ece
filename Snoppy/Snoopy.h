#ifndef SNOOPY_H_INCLUDED
#define SNOOPY_H_INCLUDED
#include <string>

class Snoopy
{
    public:

    Snoopy();

    void deplacement(int x, int y);
    void poussBloc();
    void cassBloc();
    void touchePiegeBloc();
    void toucheBalle();

    void setPlusOiseau();
    void setVivant(bool vivant);
    void setDemolitionModeA();
    void setCoordonnees(int x, int y);
    void setX(int x);
    void setY(int y);

    int getNbOiseauAttrap();
    bool getVivant();
    int getX();
    int getY();




    protected:

    int m_nbOiseauxAttrap;
    int m_score;
    int m_vie;
    int m_x;
    int m_y;
    bool m_vivant;
    bool m_demolotionMode;
    char m_saLetrre;
};

#endif // SNOOPY_H_INCLUDED
