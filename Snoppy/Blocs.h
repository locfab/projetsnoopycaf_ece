#ifndef BLOCS_H_INCLUDED
#define BLOCS_H_INCLUDED


class Blocs
{
    public:

    Blocs();
    Blocs(int x, int y);
    ~Blocs();

    void setX(int x);
    void setY(int y);

    int getX() const;
    int getY() const;
    virtual bool getPoussable() const;
    virtual void deplacement(int largeur, int hauteur, Blocs* blocs);

    protected:
    int m_x;
    int m_y;
};


#endif // BLOCS_H_INCLUDED
