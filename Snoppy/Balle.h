#ifndef BALLE_H_INCLUDED
#define BALLE_H_INCLUDED

class Balle
{
    public:
    Balle();
    Balle(int x, int y);

    void directionDuDeplacementSuivant(bool droite, bool haut); // modification de m_depX et m_depY
    void deplacement(); // modification de m_x et m_y

    void setX();
    void setY();
    void setDepX();
    void setDepY();

    int getX() const;
    int getY() const;

    protected:

    int m_x;
    int m_y;
    int depx;
    int depy;
    char m_saLetrre = 'B';
};

#endif // BALLE_H_INCLUDED
