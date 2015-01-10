#ifndef TOXSCREEN_QT_QTOXRETURNEXCEPTION
#define TOXSCREEN_QT_QTOXRETURNEXCEPTION

#include "QToxException.h"

class QToxReturnException : QToxException
{
public:
    QToxReturnException(QTox *parent, const QString &functionName, int result);
    virtual QToxReturnException * clone() const;
    virtual void raise() const;
    virtual QString toString() const;
private:
    QString mFunctionName;
    int mResult;
};

#endif // TOXSCREEN_QT_QTOXRETURNEXCEPTION
