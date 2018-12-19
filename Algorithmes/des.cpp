#include "des.h"
#include <cassert>
#include <QString>
#include <QVector>
#include <QBitArray>
#include <sstream>

namespace DES {
    // Table permettant de générer une clé de 56 bits à partir d'une clé de 64 bits
    // par exemple, le premier bit de la clé arrondis sera le 57ème bit de la clé de base
    // trouvé sur http://desimplementation.blogspot.com/
    int CleArrondi[56]={57, 49, 41, 33, 25, 17, 9,
                         1, 58, 50, 42, 34, 26, 18,
                        10, 2,  59, 51, 43, 35, 27,
                        19, 11, 3,  60, 52, 44, 36,
                        63, 55, 47, 39, 31, 23, 15,
                        7,  62, 54, 46, 38, 30, 22,
                        14, 6,  61, 53, 45, 37, 29,
                        21, 13, 5,  28, 20, 12, 4};

    // Tableau des 8 tables de substitution utilisées par DES
    int sBox[8][64]=
        {
            {
                14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
                0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
                4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
                15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13
            },
            {
                15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
                3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
                0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
                13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9
            },
            {
                10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
                13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
                13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
                1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12
            },
            {
                7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
                13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
                10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
                3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14
            },
            {
                2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
                14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
                4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
                11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3
            },
            {
                12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
                10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
                9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
                4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13
            },
            {
                4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
                13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
                1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
                6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12
            },
            {
                13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
                1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
                7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
                2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11
            }
        };

    /**
        @name DecoupeText
        Découpe le texte passé en blocs de 64 bits

        @param textClair texte à découper de taille quelconque
        @param blocVector vector dans lequel on stock les blocs de 64 bits
    */
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
        @name ExtraireBits
        extrait taille bits de source à partir de l'index posDepart

        @param source source dont on extrait les bits
        @param posDepart index de départ pour l'extraction
        @param taille nombre de bits à extraire
        @return les taille premiers bits de source à partir de l'index posDepart
    */
    QBitArray ExtraireBits(QBitArray const & source, int posDepart, int taille)
    {
        assert(("l'élément source est trop petit ",posDepart+taille > source.size()));
        //
        QBitArray result(taille);
        for(int i=0; i< taille; i++)
        {
            result[i] = source[i+posDepart];
        }
        return result;
    }

    /**
        @name DeterminerCle48bits
        Convertis une clé de 64 bits en une clé de 48 bits

        @param cle la clé de 64 bits à convertir
    */
    QBitArray DeterminerCle48bits(QBitArray const & cle)
    {
        QBitArray result(48);
        for(int i=0; i<48; i++)
        {
            result[i] = cle[CleArrondi[i]];
        }

        return result;
    }

    /**
        @name f
        coeur de l'algorithme DES, altère le bloc bloc grâce à la clé passée en paramètre

        @param bloc le bloc de données à altérer (64 bits)
        @param cle une clé de 48 bits
    */
    void f(QBitArray  &bloc, QBitArray const &cle)
    {
        // Décomposer la clé en deux sous parties
        QBitArray cleGauche(ExtraireBits(cle, 0, 24)),
                  cleDroit(ExtraireBits(cle, 24, 24));
        // TODO
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
        // tester si la clé fait 64 bits, faire un asert?
        if (cle.size() == 64)
        {
            // découper le message en blocs de 64 bits
            QVector<QBitArray> blocVector;
            QVector<std::pair<QBitArray, QBitArray>> blocVectorGD;
            DecoupeText(textClair, blocVector);

            // Génération d'une clé de 48 bits
            QBitArray cle48bits(DeterminerCle48bits(cle));

            // pour chaque bloc faire
            for(int i=0; i<blocVector.size(); i++)
            {
                // permutter les bits du bloc
                Permutter(blocVector[i]);

                // diviserle bloc en un bloc gauche et un bloc droit de 32 bits
                blocGauche.fill(false);
                blocDroit.fill(false);
                blocGauche = ExtraireBits(blocVector[i], 0, 32);
                blocDroit = ExtraireBits(blocVector[i], 32, 32);
                blocVectorGD.append(std::pair<QBitArray, QBitArray>(blocGauche, blocDroit));

                if(i>0)
                {
                    // faire 16 fois ce qui suit
                    for(int j=0; j<16; j++)
                    {
                        // le bloc gauche devient le bloc droit de l'itération précédente
                        std::swap(blocVectorGD[i].first, blocVectorGD[i-1].second);
                        // le bloc droit devient le boc gauche de l'itération précédente XOR f(Di-1, Ki)
                        f(blocVectorGD[i-1].second, cle48bits);
                        blocVectorGD[i].second = blocVectorGD[i-1].first ^ blocVectorGD[i-1].second;
                    }
                    // On recompose un bloc B'16 en "recollant" D16 et G16 dans cet ordre
                    // TODO
                }
            }
        }
        return result;
    }
}
