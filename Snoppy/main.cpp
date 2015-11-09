#include <iostream>
#include "PersoSnoopy.h"

using namespace std;

int main()
{
    PersoSnoopy* snoopy = new PersoSnoopy();
    cout << snoopy->getNbOiseauAttrap() << endl;
    snoopy->setPlusOiseau();
    snoopy->setPlusOiseau();
    cout << snoopy->getVivant() << endl;
    snoopy->setVivant(false);
    cout << snoopy->getNbOiseauAttrap() << endl;
    cout << snoopy->getVivant() << endl;
    return 0;
}
