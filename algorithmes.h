#ifndef ALGORITHMES_H
#define ALGORITHMES_H

class QString;
class QChar;

template<typename T>
class QVector;


QString CrypterCesar(const QString &textClair, int decallage, const QVector<QChar> &alphabet);

#endif // ALGORITHMES_H
