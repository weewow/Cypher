#include "algorithmes.h"
#include <QString>
#include <QVector>
#include <QChar>

#define TAILLE_TABLE_ASCII 128

QString CrypterCesar(const QString &textClair, int decallage, const QVector<QChar> &alphabet)
{
    QString result("");
    int pos(0);
    QChar LettreCryptee;

    if (decallage<0)
    {
        int loTailleAlphabet(alphabet.size()?alphabet.size():TAILLE_TABLE_ASCII);
        decallage = loTailleAlphabet + (decallage%loTailleAlphabet);
    }

    if (alphabet.size()) // Utiliser l'alphabet fournit
    {
        for(const QChar lettre : textClair)
        {
            pos = alphabet.indexOf(lettre);
            if (pos > -1) // symbole cryptable, le substituer
            {
                LettreCryptee = alphabet[(pos+decallage)%alphabet.size()];
            }else{ // symbole non cryptable, le laisser tel-quel
                LettreCryptee = lettre;
            }
                result.append(LettreCryptee);
        }
    }else{// Alphabet vide, on utilise la table ASCII complète
        for(QChar lettre : textClair)
        {
            LettreCryptee = (lettre.toLatin1() + decallage) % TAILLE_TABLE_ASCII;
            result.append(LettreCryptee);
        }
    }

    return result;
}

QString DecrypterCesar(const QString &textClair, int decallage, const QVector<QChar> &alphabet)
{
    return CrypterCesar(textClair, decallage*-1, alphabet);
}
