#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <string>

class Menu
{
    public:

    Menu();

	void afficherMenu();
	void choix(char decisionJoueur) const ;
	void créerPartie() ;
	void highScores() const ;



    protected:
    std::string m_motDePasse = "Snoop" ;
	char m_choixMenu = 'O';
};



#endif // MENU_H_INCLUDED
