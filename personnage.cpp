#include "personnage.h"
#include "arme.h"


Personnage::Personnage(int vie, QString nomArme,QString nomPersonnage, int degatsArme)
    : m_nomPersonnage(nomPersonnage), m_arme(nomArme,degatsArme), m_vie(vie)
{

}

Personnage::~Personnage()
{}

void Personnage::attaquer(Personnage *cible)
{
    cible->recevoirDegats(m_arme.nombreDegats());
}

bool Personnage::estVivant()
{
    if (m_vie == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void Personnage::recevoirDegats(int dgts)
{
    m_vie -= dgts;
    if (m_vie < 0)
    {
        m_vie = 0;
    }
}

int Personnage::viePersonnage()
{
    return m_vie;
}

QString Personnage::nomArmePerso()
{
    return m_arme.nomArme();
}

int Personnage::degatsArmePerso()
{
    return m_arme.nombreDegats();
}

void Personnage::changerArmeHero(QString nomArme, int degatsArme, int vie)
{
    m_arme.setNomArme(nomArme);
    m_arme.setNombreDegats(degatsArme);
    m_vie = vie;
}
