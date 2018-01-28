#ifndef FENETREPARAMETRES_H
#define FENETREPARAMETRES_H

#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>

class FenetreParametres : public QDialog
{

    Q_OBJECT

public:
    FenetreParametres();
    ~FenetreParametres();
    int parametreDegatsEnemi();
    int parametreVieEnemi();

    int parametreVieHero();
    int parametreAttaqueHero();
    QString parametreNomHero();
    QString parametreNomArmeHero();
    bool parametreClasseChoisie();

public slots:

    void boutonContinuerCliquer();
private:

    QLineEdit *ligneVieEnemi;
    QLineEdit *ligneAttaqueEnemi;
    QPushButton *quitter;

    QLineEdit *ligneVieHero;
    QLineEdit *ligneAttaqueHero;
    QLineEdit *ligneNomHero;
    QLineEdit *ligneNomArmeHero;

    bool classeChoisie;

    int attaqueEnemi;
    int vieEnemi;

    int vieHero;
    int attaqueHero;
    QString nomHero;
    QString nomArmeHero;

    QRadioButton *test;
    QRadioButton *magicien;
    QRadioButton *guerrier;

};

#endif // FENETREPARAMETRES_H
