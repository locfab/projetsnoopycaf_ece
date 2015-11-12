#ifndef BLOCS_H_INCLUDED
#define BLOCS_H_INCLUDED


class Blocs
{
    public:

    Blocs();
    Blocs(int x, int y);

    virtual bool getPoussable() const;


    int getX();
    int getY();

    protected:
    int m_x;
    int m_y;
};


#endif // BLOCS_H_INCLUDED
