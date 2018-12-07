#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QStringListModel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void AfficherAlphabetPersonnalise();
    void Crypter();
    void Decrypter();

private:
    Ui::MainWindow *ui;
    QStringListModel * cesar_model_list_alphabets;
};

#endif // MAINWINDOW_H
