#ifndef CESAR_H
#define CESAR_H

class QString;
class QChar;

template<typename T>
class QVector;

namespace Cesar
{
    QString Crypter(QString const &textClair, int decallage, QVector<QChar> const &alphabet);
    QString Decrypter(QString const &textCrytpe, int decallage, QVector<QChar> const &alphabet);
};

#endif // CESAR_H
