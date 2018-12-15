#include "des.h"
//#include <cassert>
#include <QString>
#include <QVector>
#include <QBitArray>

namespace DES {
    QString Crypter(QBitArray const &textClair, QBitArray const &cle)
    {
        QString result("");
        // tester si la clé fait 56 bits, faire un asert?
        if (cle.size() == 56)
        {
            // découper le message en blocs de 64 bits
            QVector<QBitArray> blocVector;
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

            // pour chaque bloc faire
            for(QBitArray bloc : blocVector)
            {
                QBitArray blocPermute(64, false);
                // permutter les bits du bloc

                // diviser un bloc gauche et un bloc droit de 32 bits
                // faire 16 fois ce qui suit
                    // le bloc gauche devient le bloc droit de l'itération précédente
                    // le bloc droit devient le boc gauche de l'itération précédente XOR f(, )
            }
        }
    }
}
