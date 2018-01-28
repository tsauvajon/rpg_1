#include "fenetre.h"
#include "personnage.h"
#include "fenetreparametres.h"
#include "arme.h"
#include <QApplication>
#include <QWidget>
#include <iostream>
#include <windows.h>
#include <QBrush>
#include <QProgressBar>
#include <QGridLayout>
#include <QColorDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QGroupBox>

FenetrePrincipale::FenetrePrincipale()
{
    // On créer la seconde fenètre

    setMinimumSize(600,300);// On ajuste la taille de la fenêtre principale
    fenetre2 = new FenetreParametres();
    fenetre2->exec();


    // On récupère les informations de la seconde feneètre

    vieEnemi = fenetre2->parametreVieEnemi();
    degatsEnemi = fenetre2->parametreDegatsEnemi();
    vieHero = fenetre2->parametreVieHero();
    attaqueHero = fenetre2->parametreAttaqueHero();
    nomHero = fenetre2->parametreNomHero();
    nomArmeHero = fenetre2->parametreNomArmeHero();

    // On créer et initialise toutes les variables et objets

    hero = new Personnage(vieHero,nomArmeHero, nomHero, attaqueHero);
    enemi = new Personnage(vieEnemi,"XXXX", "XXXX", degatsEnemi);
    QGridLayout *layoutPrincipal = new QGridLayout;
    progressBarHero = new QProgressBar;
    progressBarEnemi = new QProgressBar;
    menuActions = new QGroupBox;
    boutonAttaquer = new QPushButton("Coup de poing");
    boutonRegenerer = new QPushButton("Boire potion de vie (+40Vie)");
    boutonSoins = new QPushButton ("Soins ultimes(+70Vie)");
    boutonAttaqueEpee = new QPushButton ("Coup d'épée)");
    texte1 = new QLabel;
    texte2 = new QLabel;
    texte1->setText("\nNom du personnage : "+ nomHero +" \nArme : " + hero->nomArmePerso() + "(dégats : " + QString::number(+hero->degatsArmePerso()) +") \n\n Votre vie : " + QString::number(hero->viePersonnage()));
    texte2->setText("Enemi niveau [1]           Vie = ["+QString::number(vieEnemi)+"] \n                                      Attaque : (" + QString::number(degatsEnemi) +")");
    infos = new QTextEdit;
    infos->setReadOnly(true);
    //texteRound->setText("round");
    layoutBox = new QGridLayout; //Menu avec les boutons d'attaques
    QVBoxLayout *layoutText = new QVBoxLayout;  // En bas à droite le texte décriptif des rounds
    incr = 0;

    // On met la couleur du texte à vert et rouge et on met l'image de fond

    QPalette paletteVerte = texte1->palette();
    QPalette paletteRouge = texte2->palette();
    paletteRouge.setColor(QPalette::WindowText, Qt::red);
    paletteVerte.setColor(QPalette::WindowText, Qt::green);
    texte1->setPalette(paletteVerte);
    texte2->setPalette(paletteRouge);
    QPalette palette2;
    palette2.setBrush(this->backgroundRole(), QBrush(QImage("arriereplan.jpg")));
    this->setPalette(palette2);

    // On met la couleur des boutons à BLANC

    QBrush tb(Qt::transparent);
    boutonAttaquer->setStyleSheet("background-color: white;");
    boutonRegenerer->setStyleSheet("background-color: white;");
    boutonAttaqueEpee->setStyleSheet("background-color: white;");
    boutonSoins->setStyleSheet("background-color: white;");
    progressBarEnemi->setStyleSheet("QProgressBar::chunk{background-color:red}");
    boutonSoins->setPalette(QPalette(tb, tb, tb, tb, tb, tb, tb, tb, tb));
    boutonAttaqueEpee->setPalette(QPalette(tb, tb, tb, tb, tb, tb, tb, tb, tb));

    boutonSoins->setEnabled(false);
    boutonAttaqueEpee->setEnabled(false);


    // On ajoute les lignes noires

    QFrame *ligne1 = new QFrame; // trait du milieu de haut en bas
    QFrame *ligne2 = new QFrame; // trait a droite en dessous de progressBarEnemi
    QFrame *ligne3 = new QFrame; // trait a gauche en dessous de progressBarHero
    ligne1->setLineWidth(1);
    ligne1->setFrameStyle(QFrame::Plain | QFrame::VLine);
    ligne2->setLineWidth(1);
    ligne2->setFrameStyle(QFrame::Plain | QFrame::HLine);
    ligne3->setLineWidth(1);
    ligne3->setFrameStyle(QFrame::Plain | QFrame::HLine);

    layoutText->addWidget(infos);
    progressBarEnemi->setMaximum(vieEnemi);
    progressBarHero->setMaximum(vieHero);
    menuActions->setLayout(layoutBox);
    layoutBox->addWidget(boutonAttaquer,0,0);
    layoutBox->addWidget(boutonRegenerer,0,1);
    layoutBox->addWidget(boutonSoins,1,1);
    layoutBox->addWidget(boutonAttaqueEpee,1,0);

    //layoutPrincipal->addWidget(imageFond,0,2);
    layoutPrincipal->addWidget(progressBarHero,1,0);
    layoutPrincipal->addWidget(progressBarEnemi,1,3);
    layoutPrincipal->addWidget(ligne1,0,1,10,1);
    layoutPrincipal->addWidget(ligne2,3,1,1,4);
    layoutPrincipal->addWidget(ligne3,5,0,1,1);
    layoutPrincipal->addWidget(menuActions,6,0,4,1);
    layoutPrincipal->addWidget(texte2,2,3);
    layoutPrincipal->addWidget(texte1,2,0);
    // 3eme = Bas // 4eme = Droite/gauche
    layoutPrincipal->addLayout(layoutText,3,2,7,4);

    textEdit += "Infos de la partie\n\n";
    infos->setText(textEdit);

    // On met la vie des personnages à une barre de vie

    progressBarHero->setValue(hero->viePersonnage());
    progressBarEnemi->setValue(enemi->viePersonnage());

    // On connecte les boutons "ATTAQUER" et "REGENERER" à des actions

    connect(boutonAttaquer, SIGNAL(clicked(bool)), this, SLOT(attaquer()));
    connect(boutonRegenerer, SIGNAL(clicked(bool)), this, SLOT(regenerer()));
    connect(boutonAttaqueEpee, SIGNAL(clicked(bool)), this,SLOT(attaquerEpee()));
    connect(boutonSoins, SIGNAL(clicked(bool)), this,SLOT (soinsUltimes()));

    setLayout(layoutPrincipal);


}


void FenetrePrincipale::attaquer()
{
    fenetre.majText("attaquer")
    infos->setText(textEdit);
    menuActions->setEnabled(false);
    hero->attaquer(enemi);
    texte2->setText("Enemi niveau [1]           Vie = ["+QString::number(enemi->viePersonnage())+"] \n                                      Attaque : (" + QString::number(degatsEnemi) +")");
    progressBarEnemi->setValue(enemi->viePersonnage());

    // On vérifie si ils ne sont pas morts


    if(!enemi->estVivant())
    {
        if (fenetre2->parametreClasseChoisie() == true && incr == 0)
        {
           QMessageBox::information(this, "Victoire", "Vous vous êtes amélioré en Guerrier\n +20Vie +20 Attaque\n Nouvelle compétence : Coup d'épée");
           boutonAttaqueEpee->setPalette(QPalette());
           boutonAttaqueEpee->setEnabled(true);
           boutonAttaquer->setEnabled(false);
           hero->changerArmeHero("Épée de guerrier", attaqueHero + 20, fenetre2->parametreVieHero() + 20);
           progressBarHero->setMaximum(fenetre2->parametreVieHero()+20);
           progressBarEnemi->setMaximum(fenetre2->parametreVieEnemi()+20);
           enemi->changerArmeHero("XXX", 20, 120);
           incr++;


        }
        else if (fenetre2->parametreClasseChoisie() == false && incr == 0)
        {
            QMessageBox::information(this, "Victoire", "Vous vous êtes amélioré en Magicien\n +30Vie +5 Attaque\n Nouvelle compétence : Soins ultimes");
            boutonSoins->setPalette(QPalette());
            boutonSoins->setEnabled(true);
            boutonRegenerer->setEnabled(false);
            hero->changerArmeHero("Baton de magicien débutant", attaqueHero + 5, fenetre2->parametreVieHero() + 30);
            progressBarEnemi->setMaximum(fenetre2->parametreVieEnemi()+20);
            progressBarHero->setMaximum(fenetre2->parametreVieHero()+30);
            enemi->changerArmeHero("XXX", 20, 120);
            incr++;

        }
        else if(incr > 0)
        {
            QMessageBox::information(this, "Victoire", "Enemi battu, +10Vie +10Attaque");
            int incr2 = 10;
            int resIncr = 0;
            resIncr = 0;
            resIncr = incr * incr2;
            maxVie = fenetre2->parametreVieHero() + 30 + resIncr;
            hero->changerArmeHero("Baton de magicien débutant", attaqueHero + resIncr , fenetre2->parametreVieHero() + 30 + resIncr);
            enemi->changerArmeHero("XXX", 20, 120);
            progressBarEnemi->setMaximum(fenetre2->parametreVieEnemi()+25);
            progressBarHero->setMaximum(fenetre2->parametreVieHero()+ 30 +resIncr);
            incr++;
        }
    }


    Sleep(1500); // On met une pause de 3 secondes
    textEdit += "L'ennemi vous attaque !\n\n";
    enemi->attaquer(hero);
    texte1->setText("\nNom du personnage : "+ nomHero +" \nArme : " + hero->nomArmePerso() + "(dégats : " + QString::number(+hero->degatsArmePerso()) +") \n\n Votre vie : " + QString::number(hero->viePersonnage()));
    texte2->setText("Enemi niveau [1]           Vie = ["+QString::number(enemi->viePersonnage())+"] \n                                      Attaque : (" + QString::number(degatsEnemi) +")");
    progressBarHero->setValue(hero->viePersonnage());
    progressBarEnemi->setValue(enemi->viePersonnage());
    menuActions->setEnabled(true);
    infos->setText(textEdit);
    if (!hero->estVivant())
    {
        QMessageBox::critical(this, "GAME OVER", "Vous êtes mort");
        exit(1);
    }

}

void FenetrePrincipale::regenerer()

{
    fenetre.majText("soigner")
    infos->setText(textEdit);
    menuActions->setEnabled(false);
    hero->seRegenerer(40, maxVie);
    texte1->setText("\nNom du personnage : "+ nomHero +" \nArme : " + hero->nomArmePerso() + "(dégats : " + QString::number(+hero->degatsArmePerso()) +") \n\n Votre vie : " + QString::number(hero->viePersonnage()));
    progressBarHero->setValue(hero->viePersonnage());


    Sleep(3000);
    textEdit += "L'ennemi vous attaque !\n\n";
    enemi->attaquer(hero);
    texte1->setText("\nNom du personnage : "+ nomHero +" \nArme : " + hero->nomArmePerso() + "(dégats : " + QString::number(+hero->degatsArmePerso()) +") \n\n Votre vie : " + QString::number(hero->viePersonnage()));
    progressBarHero->setValue(hero->viePersonnage());
    menuActions->setEnabled(true);
    infos->setText(textEdit);

}

void FenetrePrincipale::setDegatsEnemi(int dgts)
{
    degatsEnemi = dgts;
}

FenetrePrincipale::~FenetrePrincipale()
{}

void FenetrePrincipale::attaquerEpee()

{

    fenetre.majText("attaquer")
    infos->setText(textEdit);
    menuActions->setEnabled(false);
    hero->attaquer(enemi);
    texte2->setText("Enemi niveau [1]           Vie = ["+QString::number(enemi->viePersonnage())+"] \n                                      Attaque : (" + QString::number(degatsEnemi) +")");
    progressBarEnemi->setValue(enemi->viePersonnage());

    // On vérifie si ils ne sont pas morts


    if(!enemi->estVivant())
    {
        QMessageBox::information(this, "Victoire", "Enemi battu, +10Vie +10Attaque");
        int incr2 = 10;
        int resIncr = 0;
        resIncr = 0;
        resIncr = incr * incr2;
        resIncr += 20;
        maxVie = fenetre2->parametreVieHero() + resIncr;
        hero->changerArmeHero("Épée de guerrier", attaqueHero + resIncr , fenetre2->parametreVieHero() + resIncr);
        enemi->changerArmeHero("XXX", 20, 120);
        progressBarEnemi->setMaximum(fenetre2->parametreVieEnemi()+20);
        progressBarHero->setMaximum(fenetre2->parametreVieHero()+ resIncr);
        incr++;
    }

    Sleep(1500); // On met une pause de 3 secondes
    textEdit += "L'ennemi vous attaque !\n\n";
    enemi->attaquer(hero);
    texte1->setText("\nNom du personnage : "+ nomHero +" \nArme : " + hero->nomArmePerso() + "(dégats : " + QString::number(+hero->degatsArmePerso()) +") \n\n Votre vie : " + QString::number(hero->viePersonnage()));
    texte2->setText("Enemi niveau [1]           Vie = ["+QString::number(enemi->viePersonnage())+"] \n                                      Attaque : (" + QString::number(degatsEnemi) +")");
    progressBarHero->setValue(hero->viePersonnage());
    progressBarEnemi->setValue(enemi->viePersonnage());
    menuActions->setEnabled(true);
    infos->setText(textEdit);
    if (!hero->estVivant())
    {
        QMessageBox::critical(this, "GAME OVER", "Vous êtes mort");
        exit(1);
    }

}
void FenetrePrincipale::soinsUltimes()
{

    fenetre.majText("soins ultimes")
    infos->setText(textEdit);
    menuActions->setEnabled(false);
    hero->seRegenerer(70, maxVie);
    texte1->setText("\nNom du personnage : "+ nomHero +" \nArme : " + hero->nomArmePerso() + "(dégats : " + QString::number(+hero->degatsArmePerso()) +") \n\n Votre vie : " + QString::number(hero->viePersonnage()));
    progressBarHero->setValue(hero->viePersonnage());


    Sleep(3000);
    textEdit += "L'ennemi vous attaque !\n\n";
    enemi->attaquer(hero);
    texte1->setText("\nNom du personnage : "+ nomHero +" \nArme : " + hero->nomArmePerso() + "(dégats : " + QString::number(+hero->degatsArmePerso()) +") \n\n Votre vie : " + QString::number(hero->viePersonnage()));
    progressBarHero->setValue(hero->viePersonnage());
    menuActions->setEnabled(true);
    infos->setText(textEdit);

}

void FenetrePrincipale::majText(QString typeAction)
{
    textEdit.clear();
    textEdit += "Infos de la partie\n\n";
    textEdit += "Vous venez de faire l'action "+typeAction+"!\n";
    textEdit += "C'est au tour de l'ennemi...\n";
}

