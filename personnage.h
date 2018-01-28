#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include <QString>
#include "arme.h"

class Personnage
{

public:

    Personnage(int vie ,QString nomArme,QString nomPersonnage, int degatsArme);
    ~Personnage();

    void recevoirDegats(int dgts);
    void attaquer(Personnage *cible);
    void seRegenerer(int vie,int maxVie);
    bool estVivant();

    void changerArmeHero(QString nomArme, int DegatsArme, int Vie);
    int viePersonnage();
    QString nomArmePerso();
    int degatsArmePerso();

private:

    int m_vie;
    QString m_nomPersonnage;
    Arme m_arme;

};

#endif // PERSONNAGE_H
