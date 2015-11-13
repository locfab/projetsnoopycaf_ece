#ifndef BALLE_H_INCLUDED
#define BALLE_H_INCLUDED

#include <vector>

class Balle
{
    public:
    Balle();
    Balle(int x, int y);
    Balle(int x, int y, int depx, int depY);

    void deplacement(std::vector<std::vector<char> > plateau); // Appellera directionDuPepalcementSuivant et il y aura des modifications de m_x et m_y
    void directionDuDeplacementSuivant(std::vector< std::vector<char> > plateau); // modification de m_depX et m_depY

    void setX();
    void setY();
    void setDepX(int depx);
    void setDepY(int depy);

    int getX() const;
    int getY() const;
    int getDepX() const;
    int getDepY() const;

    protected:

    int m_x;
    int m_y;
    int m_depx;
    int m_depy;
    char m_saLetrre;
};

#endif // BALLE_H_INCLUDED
