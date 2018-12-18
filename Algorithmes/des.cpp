#include "des.h"
//#include <cassert>
#include <QString>
#include <QVector>
#include <QBitArray>
#include <sstream>

namespace DES {

    /**
        @name DecoupeText
        Découpe le texte passé en blocs de 64 bits

        @param textClair texte à découper de taille quelconque
        @param blocVector vector dans lequel on stock les blocs de 64 bits
    */
    // TODO gestion du dernier bloc si elui-ci ne fait pas 64 bits
    void DecoupeText(QBitArray const &textClair, QVector<QBitArray> & blocVector)
    {
        QBitArray bloc(64, false);
        int nbBlocs(ceil(static_cast<float>(textClair.size()) / 64.f)); // nombre de blocs à créer
        for (int i=0; i<nbBlocs; i++)
        {
            bloc.fill(false);
            for(int j=0; j<64; j++)
            {
                if(i*64 + j > textClair.size()-1) // On ne rempli plus, le reste est déjà initialisé
                    break;
                bloc[j] = textClair[i*64 + j];
            }
            blocVector.push_back(bloc);
        }
    }

    /**
        @name Permutter;
        Permutte tous les bits d'un bloc

        @param bloc le bloc dont on souhaite permutter les bits
    */
    void Permutter(QBitArray &bloc)
    {
        // la plupart du temps size() vaut 64 mais il peut arriver qu'un bloc ait moins de 64 éléments
        bool elt(false);
        int indexEltCentral(ceil(static_cast<float>(bloc.size())/2.f)); // index du milieu du bloc
        for(int i=0; i<indexEltCentral; i++)
        {
            elt = bloc[bloc.size()-1-i];
            bloc[bloc.size()-1-i] = bloc[i];
            bloc[i] = elt;
        }
    }

    /**
        @name DecoupeDemiBlocs
        Découpe le bloc blocOrigine en un demi bloc gauche et un demi bloc droit

        @param blocOrigine le bloc à diviser en deux, taille 64 bits
        @param blocGauche partie gauche du bloc d'origine, taille 32 bits
        @param blocDroit partie droite du bloc d'origine, taille 32 bits
    */
    // TODO faire un assert sur la taille des paramètres ?
    void DecoupeDemiBlocs(QBitArray const &blocOrigine, QBitArray &blocGauche, QBitArray &blocDroit)
    {
        for(int i=0; i<blocOrigine.size(); i++)
        {
            if(i<32)
            {
                blocGauche[i] = blocOrigine[i];
            }else{
                blocDroit[i-32] = blocOrigine[i];
            }
        }
    }

    /**
        @name ExtraireBits
        extrait taille bits de source à partir de l'index posDepart

        @param source source dont on extrait les bits
        @param posDepart index de départ pour l'extraction
        @param taille nombre de bits à extraire
        @return les taille premiers bits de source à partir de l'index posDepart
    */
    // TODO assert si posDepart+taille < source.size ?
    QBitArray ExtraireBits(QBitArray const & source, int posDepart, int taille)
    {
        QBitArray result(taille);
        for(int i=0; i< taille; i++)
        {
            result[i] = source[i+posDepart];
        }
        return result;
    }

    /**
        @name Crypter
        Réalise le cryptage d'un texte selon l'algorithme DES

        @param textClair le texte à crytper
        @param cle la clé de cryptage
        @return le texte crypté
    */
    QString Crypter(QBitArray const &textClair, QBitArray const &cle)
    {
        QString result("");
        QBitArray blocGauche(32), blocDroit(32);
        // tester si la clé fait 56 bits, faire un asert?
        if (cle.size() == 56)
        {
            // découper le message en blocs de 64 bits
            QVector<QBitArray> blocVector;
            QVector<std::pair<QBitArray, QBitArray>> blocVectorGD;
            DecoupeText(textClair, blocVector);

            // pour chaque bloc faire
            for(int i=0; i<blocVector.size(); i++)
            {
                // permutter les bits du bloc
                Permutter(blocVector[i]);

                // diviserle bloc en un bloc gauche et un bloc droit de 32 bits
                blocGauche.fill(false);
                blocDroit.fill(false);
                DecoupeDemiBlocs(blocVector[i], blocGauche, blocDroit);
                blocVectorGD.append(std::pair<QBitArray, QBitArray>(blocGauche, blocDroit));
                if(i>0)
                {
                    // faire 16 fois ce qui suit
                    for(int j=0; j<16; j++)
                    {
                        QBitArray cle48bits(ExtraireBits(cle, j, 48));
                        // le bloc gauche devient le bloc droit de l'itération précédente
                        std::swap(blocVectorGD[i].first, blocVectorGD[i-1].second);
                        // le bloc droit devient le boc gauche de l'itération précédente XOR f(Di-1, Ki)
//                        blocVectorGD[i].second = blocVectorGD[i-1].first ^ f(blocVectorGD[i-1].second, cle48bits);
                    }
                    // On recompose un bloc B'16 en "recollant" D16 et G16 dans cet ordre
                }
            }
        }
        return result;
    }
}
