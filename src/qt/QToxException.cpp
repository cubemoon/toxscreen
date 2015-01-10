#include <QString>
#include "QToxException.h"

QToxException::QToxException(QTox *parent)
    : pParent(parent)
{
}

QToxException * QToxException::clone() const
{
    return new QToxException(*this);
}

void QToxException::raise() const
{
    throw *this;
}

QString QToxException::toString() const
{
    return QString("QToxException");
}
