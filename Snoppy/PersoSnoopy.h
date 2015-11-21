#ifndef PERSOSNOOPY_H_INCLUDED
#define PERSOSNOOPY_H_INCLUDED
#include <string>
#include "Balle.h"




class PersoSnoopy
{
    public:

    PersoSnoopy();
    PersoSnoopy(int x, int y);
    PersoSnoopy(int x, int y, int score, int vie);
    ~PersoSnoopy();

    void deplacement(bool droite, bool haut);
    bool toucheBalle(PersoSnoopy* snoopy, Balle* balle);

    void setPlusOiseau();
    void setNbrOiseauxANul();
    void setVivant(bool vivant);
    void setNbrVie(int vie);
    void setScore(int score);
    void setCoordonnees(int x, int y);
    void setModeDemolition(bool modeDemolition);
    void setX(int x);
    void setY(int y);
    void setNiveauDejaAtteint(int niveauDejaAtteint);
    void setNiveauActuel(int niveauActuel);


    int getNbOiseauAttrap() const;
    bool getVivant() const;
    int getNbrVie() const;
    int getScore() const;
    int getX() const;
    int getY() const;
    bool getModeDemolition() const;
    int getNiveauDejaAtteint() const;
    int getNiveauActuel() const;



    protected:

    int m_nbOiseauxAttrap;
    int m_score;
    int m_vie;
    int m_x;
    int m_y;
    bool m_vivant;
    char m_saLetrre;
    bool m_modeDemolition;
    int m_niveauActuel;
    int m_niveauDejaAtteint;
};


#endif // PERSOSNOOPY_H_INCLUDED
