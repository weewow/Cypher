#include "affichagetext.h"
#include "ui_affichagetext.h"

AffichageText::AffichageText(QWidget *parent, const QString &texte) :
    QDialog(parent),
    ui(new Ui::AffichageText)
{
    ui->setupUi(this);
    ui->zoneAffichage->setPlainText(texte);
    ui->zoneAffichage->setReadOnly(true);
}

AffichageText::~AffichageText()
{
    delete ui;
}
