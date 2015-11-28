#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <string>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include "Partie.h"

class Menu
{
    public:

    Menu();
    ~Menu();

	void afficherMenu();
	void choix(char decisionJoueur);
	void creerPartie(char decisionJoueurMenu);
    void highscore( int TempsRestant, int score);
	bool is_readable( const std::string & file );

	void setChoixMenu(char choixMenu);
	char getChoixMenu() const;

    protected:

    std::string m_motDePasse;
	char m_choixMenu;
};



#endif // MENU_H_INCLUDED
