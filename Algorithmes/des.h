#ifndef DES_H
#define DES_H

class QString;
class QBitArray;

// Alogrithme disponible à la page
// http://www.primenumbers.net/Renaud/fr/crypto/DES.htm
namespace DES {
    QString Crypter(const QBitArray &textClair, const QBitArray &cle);
}

#endif // DES_H
