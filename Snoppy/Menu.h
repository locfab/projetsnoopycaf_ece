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

    protected:

    std::string m_motDePasse;//j'ai enlevé le mot de passe
	char m_choixMenu; //j'ai enlevé le ='O'
};



#endif // MENU_H_INCLUDED
