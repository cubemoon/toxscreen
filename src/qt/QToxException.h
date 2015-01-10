#ifndef TOXSCREEN_QT_QTOXEXCEPTION_H
#define TOXSCREEN_QT_QTOXEXCEPTION_H

#include <QException>

class QTox;

class QToxException : public QException
{
public:
    QToxException(QTox *parent = nullptr);
    virtual QToxException * clone() const;
    virtual void raise() const;
    virtual QString toString() const;
private:
    QTox *pParent;
};

#endif // TOXSCREEN_QT_QTOXEXCEPTION_H
