#ifndef PARTIE_H_INCLUDED
#define PARTIE_H_INCLUDED

#include "PersoSnoopy.h"
#include "Niveau.h"
#include <fstream>
#include <string>
#include <vector>


/// Classe Partie gérant les niveaux et personnage
class Partie
{
    private:

        PersoSnoopy *m_snoopy;
        Niveau *m_niveau;
        void chargerPartieAvecMenu1(std::string nom, PersoSnoopy* snoopy, Niveau* niveau, std::string decisionJoueurNiveau);
        void chargerPartieAvecMenu2(std::string nom, PersoSnoopy* snoopy, Niveau* niveau, std::string decisionJoueurNiveau);
        void setScoreMax(int scoreJoueur, std::string pseudo);
        bool is_readable( const std::string & file );//savoir si un fichier est lisible

    public:

        Partie();
        Partie(char decisionJoueurMenu, std::string decisionJoueurNiveau, std::string pseudo);
        ~Partie();
        void jouer(Partie *partie, char decisionJoueurMenu, std::string pseudo, std::string decisionJoueurNiveau);//principalement la boucle de jeu et l'analyse de la partie être sortie de la boucle de jeu
        void changerVie(std::string nom, PersoSnoopy* snoopy, bool plusDeVie);// Permet de changer le nbre de vie sans faire une sauvegarde de tout le jeu, on revient donc à la derniere sauvegarde avec une vie en moins, le plusVie, permet d'initialiser le score à 0 quand le joueur reviendra car la vie sera deja à 3 dans le fichier
        void recupererEntresClav(Niveau* niveau, PersoSnoopy* snoopy, int& pause, int& save, int& esc, char& toucheUtilisateur);//permet à l'aide de ifkeyset.. derecuperer l'entrer clavier et ensuite en faire des traitements
        void chargerPartieAvecMenu(std::string nom, PersoSnoopy* snoopy, Niveau* niveau, std::string decisionJoueurNiveau, char decisionJoueurMenu);//permet de charger et creer tous les objet et le plateau à partir des choix du menu
        void sauvegarde(std::string pseudo, PersoSnoopy* snoopy, Niveau* niveau, bool partieEnCours, bool plusDeVie);//fait une sauvegarde de tous les objets, le temps , snoopy ...
        void tempsEcoule(Niveau* niveau, PersoSnoopy* snoopy, std::string pseudo, int& timeOut);//action a faire si le temps est ecoule
        void quitterSansEnregister(Niveau* niveau);//action a faire si on a quitter dans enregistrer (avec echap)
        void niveauJamaisAtteintRetour(Niveau* niveau, PersoSnoopy* snoopy);//Si jamais le joueur demande un niveau qu'il n'a jamais atteint on le fera revenir au menu
        void prepaSauvPartieGagnee(Niveau* niveau, PersoSnoopy* snoopy, bool& partieEnCours, int& save);//change les paramettres quanf la partie a ete gagnee
        void gestionDeMort(Niveau* niveau, PersoSnoopy* snoopy, std::string pseudo, std::string nomFichier);//ce que l'on fait si snoopy toucher par la balle ou si il est touche par un bloc piege
        void gestionPlusDeVie(PersoSnoopy* snoopy, Niveau* niveau, std::string pseudo, std::string nomFichier, int& save, std::string decisionJoueurNiveau);//si jamais il n'y a plus de vie, commme initizlisationd des score ; remmettre les vie
        void gestionDePause(Niveau* niveau, int& pause, char& toucheUtilisateur, double& tempsDePause, int& esc);//fait les actions necessaire à la gestion de la pause
        bool onContinu(PersoSnoopy* snoopy, Niveau*niveau, int esc, int timeOut, bool accepter, int save, char decisionJoueurMenu);//condition pour que la boucle de jeu continue
        void prepaEtLancerNivSuiv(PersoSnoopy* snoopy, Niveau*niveau, std::string pseudo, std::string decisionJoueurNiveau, bool partieEnCours);//si la partie a ete gagne, on lance le nouveau nivezu on deletznt les objet et les reinitizlisznt
};

#endif // PARTIE_H_INCLUDED
