#ifndef OISEAU_H_INCLUDED
#define OISEAU_H_INCLUDED

class Oiseau
{
    public:
    Oiseau();
    Oiseau(int x, int y);
    ~Oiseau();

    void setX(int x);
    void setY(int y);

    int getX() const;
    int getY() const;

    protected:

    int m_x;
    int m_y;
    char m_saLetrre;
};

#endif // OISEAU_H_INCLUDED
