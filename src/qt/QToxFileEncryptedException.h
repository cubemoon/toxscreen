#ifndef TOXSCREEN_QT_QTOXFILEENCRYPTEDEXCEPTION_H
#define TOXSCREEN_QT_QTOXFILEENCRYPTEDEXCEPTION_H

#include <QString>
#include "QToxException.h"

class QToxFileEncryptedException : public QToxException
{
public:
    QToxFileEncryptedException(QTox *parent);
    QToxFileEncryptedException(QTox *parent, const QString &filepath);
    virtual QToxFileEncryptedException * clone() const;
    QString getFilepath() const;
    virtual void raise() const;
    virtual QString toString() const;
private:
    QString mFilepath;
};

#endif // TOXSCREEN_QT_QTOXFILEENCRYPTEDEXCEPTION_H
