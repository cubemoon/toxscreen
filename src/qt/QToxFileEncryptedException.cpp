#include "QToxFileEncryptedException.h"

QToxFileEncryptedException::QToxFileEncryptedException(QTox *parent)
    : QToxException(parent), mFilepath(QString())
{
}

QToxFileEncryptedException::QToxFileEncryptedException(QTox *parent, const QString &filepath)
    : QToxException(parent), mFilepath(filepath)
{
}

QString QToxFileEncryptedException::getFilepath() const
{
    return mFilepath;
}

void QToxFileEncryptedException::raise() const
{
    throw *this;
}

QToxFileEncryptedException * QToxFileEncryptedException::clone() const
{
    return new QToxFileEncryptedException(*this);
}

QString QToxFileEncryptedException::toString() const
{
    if(mFilepath.isEmpty())
    {
        return QString("Tox file is encrypted");
    }
    else
    {
        return QString("Tox file is encrypted: ").append(mFilepath);
    }
}
