#ifndef CESAR_H
#define CESAR_H

class QString;
class QChar;

template<typename T>
class QVector;

namespace Cesar
{
    QString Crypter(QString const &textClair, int decallage, QVector<QChar> const &alphabet);
    QString Decrypter(const QString &textClair, int decallage, const QVector<QChar> &alphabet);
};

#endif // CESAR_H
