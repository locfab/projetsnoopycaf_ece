#ifndef BONUSMULTIBALLE_H_INCLUDED
#define BONUSMULTIBALLE_H_INCLUDED

class BonusMultiBalle
{
	public:

    BonusMultiBalle();
    BonusMultiBalle(int x, int y, int tempsALaCreation);
    ~BonusMultiBalle();

    void setX(int x);
    void setY(int y);
    void setTempsALaCreation(int tempsALaCreation);

    int getX() const;
    int getY() const;
    int getTempsALaCreation() const;

    char getLettre() const;
  

    protected:

    int m_x;
    int m_y;
    char m_saLetrre;
    int m_tempsALaCreation;
};


#endif // BONUSMULTIBALLE_H_INCLUDED
