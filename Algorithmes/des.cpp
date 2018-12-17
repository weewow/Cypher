#include "des.h"
//#include <cassert>
#include <QString>
#include <QVector>
#include <QBitArray>

namespace DES {

    /**
        Découpe le texte passé en blocs de 64 bits

        @param textClair texte à découper
        @param blocVector vector dans lequel on stock les blocs
    */
    // TODO gestion du dernier bloc si elui-ci ne fait pas 64 bits
    void DecoupeText(QBitArray const &textClair, QVector<QBitArray> & blocVector)
    {
        QBitArray bloc(64, false);
        int maxIter(ceil(static_cast<float>(textClair.size()) / 56.f)); // nombre de blocs à créer
        for (int i=0; i<maxIter; i++)
        {
            for(int j=0; j<64; j++)
            {
                bloc[j] = textClair[(i*64)+j];
            }
            blocVector.push_back(bloc);
            bloc.fill(false);
        }
    }

    /**
        Permutte tous les bits d'un bloc

        @param bloc le bloc dont on souhaite permutter les bits
    */
    void Permutter(QBitArray &bloc)
    {
        // la plupart du temps size() vaut 64 mais il peut arriver qu'un bloc ait moins de 64 éléments
        bool elt(false);
        for(int i=0; i<ceil(static_cast<float>(bloc.size())/2.f); i++)
        {
            elt = bloc[bloc.size()-i];
            bloc[bloc.size()-i] = bloc[i];
            bloc[i] = elt;
        }
    }

    /**
        Réalise le cryptage d'un texte selon l'algorithme DES

        @param textClair le texte à crytper
        @param cle la clé de cryptage
        @return le texte crypté
    */
    QString Crypter(QBitArray const &textClair, QBitArray const &cle)
    {
        QString result("");
        // tester si la clé fait 56 bits, faire un asert?
        if (cle.size() == 56)
        {
            // découper le message en blocs de 64 bits
            QVector<QBitArray> blocVector;
            DecoupeText(textClair, blocVector);

            // pour chaque bloc faire
            for(QBitArray bloc : blocVector)
            {
                // permutter les bits du bloc
                Permutter(bloc);

                // diviserle bloc en un bloc gauche et un bloc droit de 32 bits
                // faire 16 fois ce qui suit
                    // le bloc gauche devient le bloc droit de l'itération précédente
                    // le bloc droit devient le boc gauche de l'itération précédente XOR f(, )
            }
        }
        return result;
    }
}
