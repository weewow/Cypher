#ifndef AFFICHAGETEXT_H
#define AFFICHAGETEXT_H

#include <QDialog>

namespace Ui {
class AffichageText;
}

class AffichageText : public QDialog
{
    Q_OBJECT

public:
    explicit AffichageText(QWidget *parent = 0, const QString &texte = "");
    ~AffichageText();

private:
    Ui::AffichageText *ui;
};

#endif // AFFICHAGETEXT_H
