#ifndef TOXSCREEN_QT_QTOXFRIEND_H
#define TOXSCREEN_QT_QTOXFRIEND_H

#include <cstdint>
#include <QByteArray>
#include <QObject>

class QTox;

/**
 * Qt QObject representing a Tox friend. Uses signals/slots of
 * the parent QTox object to track a friend's state.
 */
class QToxFriend : public QObject
{
    Q_OBJECT
public:
    QToxFriend(QTox *parent, int32_t friendNumber);
    explicit QToxFriend(const QToxFriend &toxFriend);
    int32_t getFriendNumber() const;
    QString getName() const;
    QTox * getParent() const;
    QString getStatusMessage() const;
    uint8_t getUserStatus() const;
    bool hasParent() const;
public slots:
    void handleLosslessPacket(const QByteArray &bytes);
    void handleLossyPacket(const QByteArray &bytes);
    //void setName(const QString &name);
    //void setStatusMessage(const QString &statusMessage);
    //void setUserStatus(uint8_t userStatus);
signals:
    void onLosslessPacket(const QByteArray &bytes);
    void onLossyPacket(const QByteArray &bytes);
    //void onNameChange(const QString &name);
    //void onStatusMessage(const QString &statusMessage);
    //void onUserStatus(uint8_t userStatus);
private:
    QTox *pParent;
    int32_t mNumber;

    QString mName;
    QString mStatusMessage;
    uint8_t mUserStatus;
};

#endif // TOXSCREEN_QT_QTOXFRIEND_H
