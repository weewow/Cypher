#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "algorithmes.h"
#include "affichagetext.h"

#include <QStringListModel>
#include <QModelIndexList>
#include <QMessageBox>

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
    ui->cesar_choix_alphabet->setCurrentIndex(cesar_model_list_alphabets->index(0, 0));
    //
    ui->cesar_label_alphabet_personnalise->setVisible(false);
    ui->cesar_alphabet_personnalise->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
//    delete cesar_model_list_alphabets;
}

void MainWindow::AfficherAlphabetPersonnalise()
{
    // Récupérer le choix de l'alphabet
    QItemSelectionModel *selectionModel = ui->cesar_choix_alphabet->selectionModel();
    QString choix("autre");
    if (cesar_model_list_alphabets)
    {
        choix = cesar_model_list_alphabets->data(selectionModel->currentIndex(), Qt::DisplayRole).toString();
    }

    // Si l'alphabet vaut "autre" alors on affiche des champs supplémentaires
    ui->cesar_label_alphabet_personnalise->setVisible(choix=="autre");
    ui->cesar_alphabet_personnalise->setVisible(choix=="autre");

}

void MainWindow::PreparerAlphabetCesar(QVector<QChar> &Alphabet)
{
    QModelIndex index(ui->cesar_choix_alphabet->currentIndex());
    QString choixAlphabet("");
    if (cesar_model_list_alphabets)
    {
        choixAlphabet = cesar_model_list_alphabets->data(index, Qt::DisplayRole).toString();
    }

    if (choixAlphabet == "alphabet à 26 lettres")
    {
        for(QChar lettre : "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ")
        {
            Alphabet.push_back(lettre);
        }
    }else if(choixAlphabet == "autre"){
        for(QChar lettre : ui->cesar_alphabet_personnalise->text())
        {
            Alphabet.push_back(lettre);
        }
    } // Laisser le vector Alphabet vide si on travail sur la table ASCII
}

void MainWindow::Crypter()
{
    // Texte clair
    QString textClair(ui->texteClairCrypte->toPlainText());

    // Texte crypté
    QString textCrypte("");

    // Algorithme choisi
    QString choixAlgorithme(ui->SelecteurAlgo->tabText(ui->SelecteurAlgo->currentIndex()).toLower());

    if (choixAlgorithme=="césar") {
        // Récupérer les paramètres de cryptage
        int decallage(ui->cesar_decallage->value());
        QVector<QChar> Alphabet;
        PreparerAlphabetCesar(Alphabet);

        textCrypte = CrypterCesar(textClair, decallage, Alphabet);

        // Afficher le résultat
        AffichageText *fenetre = new AffichageText(this, textCrypte);
        fenetre->show();
    }
}

void MainWindow::Decrypter()
{
    // Texte crypté
    QString textCrypte(ui->texteClairCrypte->toPlainText());

    // Texte clair
    QString textClair("");

    // Algorithme choisi
    QString choixAlgorithme(ui->SelecteurAlgo->tabText(ui->SelecteurAlgo->currentIndex()).toLower());

    if (choixAlgorithme=="césar") {
        // Récupérer les paramètres de cryptage
        int decallage(ui->cesar_decallage->value());
        QVector<QChar> Alphabet;
        PreparerAlphabetCesar(Alphabet);

        textClair = DecrypterCesar(textCrypte, decallage, Alphabet);

        // Afficher le résultat
        AffichageText *fenetre = new AffichageText(this, textClair);
        fenetre->show();
    }
}
