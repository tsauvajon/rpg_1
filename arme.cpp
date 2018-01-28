#include "arme.h"
#include "fenetreparametres.h"

Arme::Arme(QString nom, int degats)
    : m_degats(degats), m_nom(nom)
{}

int Arme::nombreDegats()
{
    return m_degats;
}


QString Arme::nomArme()
{
    return m_nom;
}

Arme::~Arme()
{}

void Arme::setNomArme(QString nom)
{
    m_nom = nom;
}

void Arme::setNombreDegats(int degats)
{
    m_degats = degats;
}
