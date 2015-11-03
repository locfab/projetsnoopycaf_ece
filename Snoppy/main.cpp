#include <iostream>
#include "PersoSnoopy.h"

using namespace std;

int main()
{
    Snoopy* snoopy = new Snoopy();
    cout << snoopy->getNbOiseauAttrap() << endl;
    snoopy->setPlusOiseau();
    cout << snoopy->getVivant() << endl;
    snoopy->setVivant(false);
    cout << snoopy->getNbOiseauAttrap() << endl;
    cout << snoopy->getVivant() << endl;
    return 0;
}
