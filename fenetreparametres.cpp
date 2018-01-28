#include "fenetreparametres.h"
#include "fenetre.h"
#include <QVBoxLayout>
#include <QApplication>
#include <QGroupBox>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QRadioButton>

FenetreParametres::FenetreParametres()
{
    setFixedSize(300,400);

    QVBoxLayout *layoutPrincipal = new QVBoxLayout;

    QFormLayout *layoutBox1 = new QFormLayout;
    QVBoxLayout *layoutBox2 = new QVBoxLayout;

    QGroupBox *box1 = new QGroupBox;
    QGroupBox *box2 = new QGroupBox;
    ligneVieHero = new QLineEdit;
    ligneAttaqueHero = new QLineEdit;
    ligneNomHero = new QLineEdit;
    ligneNomArmeHero = new QLineEdit;
    ligneVieEnemi = new QLineEdit;
    ligneAttaqueEnemi = new QLineEdit;
    quitter = new QPushButton("Continuer");

    classeChoisie = false; // False = magicien |||| True = guerrier //

    box1->setTitle("Changer les paramètres de départ");
    box1->setCheckable(true);
    box1->setChecked(false);

    box2->setTitle("Choissisez votre classe");

    guerrier = new QRadioButton("Guerrier");
    magicien = new QRadioButton("Magicien");
    test = new QRadioButton("Test classe");
    guerrier->setChecked(true);
    layoutBox2->addWidget(guerrier);
    layoutBox2->addWidget(magicien);
    layoutBox2->addWidget(test);

    box1->setLayout(layoutBox1);
    box2->setLayout(layoutBox2);

    layoutPrincipal->addWidget(box1);
    layoutPrincipal->addWidget(box2);
    layoutPrincipal->addWidget(quitter);

    layoutBox1->addRow("Combiens de vie aura l'enemi ? ",ligneVieEnemi);
    layoutBox1->addRow("Combiens d'attaque aura l'enemi ? ",ligneAttaqueEnemi);
    layoutBox1->addRow("Nom de votre personnage", ligneNomHero);
    layoutBox1->addRow("Nom de votre arme", ligneNomArmeHero);
    layoutBox1->addRow("Quel degats auront votre arme", ligneAttaqueHero);
    layoutBox1->addRow("Combiens de vie aurez vous", ligneVieHero);

    ligneVieEnemi->setText("100");
    ligneAttaqueEnemi->setText("20");
    ligneNomHero->setText("Bob le bricoleur");
    ligneNomArmeHero->setText("Poings");
    ligneAttaqueHero->setText("15");
    ligneVieHero->setText("80");

    setLayout(layoutPrincipal);

    connect(quitter, SIGNAL(clicked(bool)), this, SLOT(accept()));
    connect(quitter, SIGNAL(clicked(bool)), this, SLOT(boutonContinuerCliquer()));

}

void FenetreParametres::boutonContinuerCliquer()
{
   attaqueEnemi = ligneAttaqueEnemi->text().toInt();
   vieEnemi = ligneVieEnemi->text().toInt();
   attaqueHero = ligneAttaqueHero->text().toInt();
   vieHero = ligneVieHero->text().toInt();
   nomArmeHero = ligneNomArmeHero->text();
   nomHero = ligneNomHero->text();

   if(guerrier->isChecked())
   {
       classeChoisie = true;
    }
   else if(magicien->isChecked())
   {
       classeChoisie = false;
    }

}

FenetreParametres::~FenetreParametres()
{}

int FenetreParametres::parametreDegatsEnemi()
{
    return attaqueEnemi;
}

int FenetreParametres::parametreVieEnemi()
{
    return vieEnemi;
}

QString FenetreParametres::parametreNomHero()
{
    return nomHero;
}

QString FenetreParametres::parametreNomArmeHero()
{
    return nomArmeHero;
}

int FenetreParametres::parametreVieHero()
{
    return vieHero;
}

int FenetreParametres::parametreAttaqueHero()
{
    return attaqueHero;
}

bool FenetreParametres::parametreClasseChoisie()
{
    return classeChoisie;
}

