#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStringListModel>
#include <QModelIndexList>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Algorithme de césar
    QStringList listAlaphabets;
    listAlaphabets<< "alphabet à 26 lettres";
    listAlaphabets<< "table ASCII";
    listAlaphabets<< "autre";
    cesar_model_list_alphabets = new QStringListModel(listAlaphabets);
    ui->cesar_choix_alphabet->setModel(cesar_model_list_alphabets);
    //
    ui->cesar_label_alphabet_personnalise->setVisible(false);
    ui->cesar_alphabet_personnalise->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete cesar_model_list_alphabets;
}

void MainWindow::AfficherAlphabetPersonnalise()
{
    // Récupérer le choix de l'alphabet
    QItemSelectionModel *selectionModel = ui->cesar_choix_alphabet->selectionModel();
    QString choix = cesar_model_list_alphabets->data(selectionModel->currentIndex(), Qt::DisplayRole).toString();

    // Si l'alphabet vaut "autre" alors on affiche des champs supplémentaires
    ui->cesar_label_alphabet_personnalise->setVisible(choix=="autre");
    ui->cesar_alphabet_personnalise->setVisible(choix=="autre");

}

void MainWindow::Crypter()
{
    // Texte clair
    QString textClair(ui->texteClairCrypte->toPlainText());

    // Algorithme choisi
    QString choix(ui->SelecteurAlgo->tabText(ui->SelecteurAlgo->currentIndex()).toLower());

    if (choix=="césar") {
        // Récupérer les paramètres de cryptage

        // Appel de la classe de cryptage adéquate

        // Afficher le résultat
    }
}

void MainWindow::Decrypter()
{

}
