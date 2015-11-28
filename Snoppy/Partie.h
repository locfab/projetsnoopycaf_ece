#ifndef PARTIE_H_INCLUDED
#define PARTIE_H_INCLUDED

#include "PersoSnoopy.h"
#include "Niveau.h"
#include <fstream>


/// Classe Partie gérant les niveaux et personnage
class Partie
{
    private:

        PersoSnoopy *m_snoopy;
        Niveau *m_niveau;
        void chargerPartieAvecMenu1(std::string nom, PersoSnoopy* snoopy, Niveau* niveau, std::string decisionJoueurNiveau);
        void chargerPartieAvecMenu2(std::string nom, PersoSnoopy* snoopy, Niveau* niveau, std::string decisionJoueurNiveau);
        void setScoreMax(int scoreJoueur);
        bool is_readable( const std::string & file );

    public:

        Partie();
        ~Partie();
        void jouer(Partie *partie, char decisionJoueurMenu, std::string pseudo, std::string decisionJoueurNiveau);
        void changerVie(std::string nom, PersoSnoopy* snoopy);
        void recupererEntresClav(Niveau* niveau, PersoSnoopy* snoopy, int& pause, int& save, int& esc, char& toucheUtilisateur);
        void chargerPartieAvecMenu(std::string nom, PersoSnoopy* snoopy, Niveau* niveau, std::string decisionJoueurNiveau, char decisionJoueurMenu);
        void sauvegarde(std::string pseudo, PersoSnoopy* snoopy, Niveau* niveau, bool partieEnCours);
        void tempsEcoule(Niveau* niveau, int& timeOut);
        void quitterSansEnregister(Niveau* niveau);
        void niveauJamaisAtteintRetour(Niveau* niveau, PersoSnoopy* snoopy);
        void prepaSauvPartieGagnee(Niveau* niveau, PersoSnoopy* snoopy, bool& partieEnCours, int& save);
        void gestionDeMort(Niveau* niveau, PersoSnoopy* snoopy, std::string pseudo, std::string nomFichier);
        void gestionPlusDeVie(PersoSnoopy* snoopy, Niveau* niveau, std::string pseudo, std::string nomFichier, int& save);
        void gestionDePause(Niveau* niveau, int& pause, char& toucheUtilisateur, double& tempsDePause, int& esc);
        bool onContinu(PersoSnoopy* snoopy, Niveau*niveau, int esc, int timeOut, bool accepter, int save, char decisionJoueurMenu);
        void prepaEtLancerNivSuiv(PersoSnoopy* snoopy, Niveau*niveau, std::string pseudo, std::string decisionJoueurNiveau, bool partieEnCours);
};

#endif // PARTIE_H_INCLUDED
