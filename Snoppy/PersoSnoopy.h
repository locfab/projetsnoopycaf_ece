#ifndef PERSOSNOOPY_H_INCLUDED
#define PERSOSNOOPY_H_INCLUDED
#include <string>



class PersoSnoopy
{
    public:

    PersoSnoopy();
    PersoSnoopy(int x, int y);
    PersoSnoopy(int x, int y, int nbOiseauxAttrap, int vie);
    ~PersoSnoopy();

    void deplacement(bool droite, bool haut);
    void poussBloc();
    void cassBloc();
    void touchePiegeBloc();
    void toucheBalle();
    void touchOiseau();

    void setPlusOiseau();
    void setVivant(bool vivant);
    void setCoordonnees(int x, int y);
    void setX(int x);
    void setY(int y);


    int getNbOiseauAttrap() const;
    bool getVivant() const;
    int getNbrVie() const;
    int getScore() const;
    int getX() const;
    int getY() const;





    protected:



    int m_nbOiseauxAttrap;
    int m_score;
    int m_vie;
    int m_x;
    int m_y;
    bool m_vivant;
    char m_saLetrre;
};


#endif // PERSOSNOOPY_H_INCLUDED
