#include "algorithmes.h"
#include <QString>
#include <QVector>
#include <QChar>

QString CrypterCesar(const QString &textClair, int decallage, const QVector<QChar> &alphabet)
{
    QString result("");
    int pos(0);
    QChar LettreCryptee;

    if (alphabet.size()) // Utiliser l'alphabet fournit
    {
        for(const QChar lettre : textClair)
        {
            pos = alphabet.indexOf(lettre);
            if (pos > -1) // symbole cryptable, le substituer
            {
               if((pos+decallage)%alphabet.size()) // la nouvelle position est supérieure à la taille de l'alphabet
               {
                    LettreCryptee = alphabet[((pos+decallage)%alphabet.size())-1];
               }else{
                    LettreCryptee = alphabet[pos+decallage];
               }
            }else{ // symbole non cryptable, le laisser tel-quel
                LettreCryptee = lettre;
            }
            result.append(LettreCryptee);
        }
    }else{// Alphabet vide, on utilise la table ASCII complète
        for(QChar lettre : textClair)
        {
            LettreCryptee = lettre.toLatin1() + decallage;
            result.append(LettreCryptee);
        }
    }

    return result;
}
