#ifndef BALLE_H_INCLUDED
#define BALLE_H_INCLUDED

class Balle
{
    public:
    Balle();
    Balle(int x, int y);
    void deplacement(int x, int y);
    void setCoordonnees(int x, int y);
    void setX(int x);
    void setY(int y);
    int getX();
    int getY();

    protected:

    int m_x;
    int m_y;
    char m_saLetrre = 'B';
};

#endif // BALLE_H_INCLUDED
