#ifndef BONUSATTRAP_H_INCLUDED
#define BONUSATTRAP_H_INCLUDED

class BonusAttrap
{
	public:

    BonusAttrap();
    BonusAttrap(int x, int y, int tempsALaCreation);
    ~BonusAttrap();

    void setX(int x);
    void setY(int y);
    void setTempsALaCreation(int tempsALaCreation);

    int getX() const;
    int getY() const;
    int getTempsALaCreation() const;

    char getLettre() const;
    //int getTempsALaCreation(Temps* tempsRestant);

    protected:

    int m_x;
    int m_y;
    char m_saLetrre;
    int m_tempsALaCreation;
};

#endif // BONUSATTRAP_H_INCLUDED
