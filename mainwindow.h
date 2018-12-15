#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QStringListModel;
//class QChar;
template
class QVector<QChar>;
class QBitArray;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QBitArray QStringToQBitArray(QString const &text, int arraySize);


public slots:
    void AfficherAlphabetPersonnalise();
    void Crypter();
    void Decrypter();

private:
    Ui::MainWindow *ui;
    QStringListModel *cesar_model_list_alphabets;

    void PreparerAlphabetCesar(QVector<QChar> &Alphabet);
};

#endif // MAINWINDOW_H
