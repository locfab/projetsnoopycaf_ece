#ifndef BALLE_H_INCLUDED
#define BALLE_H_INCLUDED

class Balle
{
    public:
    Balle();
    Balle(int x, int y);

    void deplacement(); // Appellera directionDuPepalcementSuivant et il y aura des modifications de m_x et m_y
    void directionDuDeplacementSuivant(); // modification de m_depX et m_depY

    void setX();
    void setY();
    void setDepX();
    void setDepY();

    int getX() const;
    int getY() const;
    int getDepX() const;
    int getDepY() const;

    protected:

    int m_x;
    int m_y;
    int m_depx;
    int m_depy;
    char m_saLetrre = 'B';
};

#endif // BALLE_H_INCLUDED
