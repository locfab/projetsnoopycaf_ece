#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <string>

class Menu
{
    public:

    Menu();
    ~Menu();

	void afficherMenu();
	void choix(char decisionJoueur);
	void creerPartie(char decisionJoueur);
	void highScores() const;

	void setChoixMenu(char choixMenu);
	char getChoixMenu() const;

    protected:

    std::string m_motDePasse;
	char m_choixMenu;
};



#endif // MENU_H_INCLUDED
