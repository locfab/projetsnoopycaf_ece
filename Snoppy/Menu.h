#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <string>

class Menu
{
    public:

    Menu();

	void afficherMenu();
	void choix(char decisionJoueur);
	void creerPartie();
	void highScores() const;

	void setChoixMenu(char choixMenu);

	char getChoixMenu() const;

    protected:

    std::string m_motDePasse = "Snoop";
	char m_choixMenu = '0';
};



#endif // MENU_H_INCLUDED
