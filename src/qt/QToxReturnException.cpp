#include <QString>
#include "QToxReturnException.h"

QToxReturnException::QToxReturnException(QTox *parent, const QString &functionName, int result)
    : QToxException(parent), mFunctionName(functionName), mResult(result)
{
}

QToxReturnException * QToxReturnException::clone() const
{
    return new QToxReturnException(*this);
}

void QToxReturnException::raise() const
{
    throw *this;
}

QString QToxReturnException::toString() const
{
    return QString("Error: %1 returned %2").arg(mFunctionName).arg(QString::number(mResult));
}
