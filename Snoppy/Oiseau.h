#ifndef OISEAU_H_INCLUDED
#define OISEAU_H_INCLUDED

class Oiseau
{
    public:
    Oiseau(int x, int y);
    void setX(int x);
    void setY(int y);
    int getX();
    int getY();

    protected:

    int m_x;
    int m_y;
    char m_saLetrre;
};

#endif // OISEAU_H_INCLUDED
