#ifndef TOXSCREEN_QT_QTOX_H
#define TOXSCREEN_QT_QTOX_H

#include <cstdint>
#include <QByteArray>
#include <QMap>
#include <QObject>
#include <QPair>
#include <tox/tox.h>
#include "QToxFriend.h"

/**
 * Qt wrapper for Tox.
 */
class QTox : public QObject
{
    Q_OBJECT

public:
    QTox();
    ~QTox();
    QTox(const QTox &qtox) = delete;
    QTox(QTox &&qtox) = delete;
    QByteArray getAddress() const;
    QToxFriend * getFriend(int32_t friendNumber);
    Tox * getHandle() const;
    QPair<QByteArray, QByteArray> getKeys(bool includePriv) const;
    QByteArray getPrivateKey() const;
    QByteArray getPublicKey() const;
    bool hasHandle() const;
    void load(const QByteArray &data);
    void loadFromFile(const QString &filepath);
    //void loadFromFile(const QString &filepath, const QString &password);
    void registerLossless(int32_t friendNumber, uint8_t byte) const;
    void registerLossy(int32_t friendNumber, uint8_t byte) const;
    //QByteArray save() const;
    //void saveToFile(const QString &filepath) const;
    //void saveToFile(const QString &filepath, const QString &password) const;
public slots:
    void handleLosslessPacket(int32_t friendNumber, const uint8_t *data, uint32_t length);
    void handleLossyPacket(int32_t friendNumber, const uint8_t *data, uint32_t length);
    void handleFriendRequest(const uint8_t *publicKey, const uint8_t *data, uint16_t length);
    //void emitFriendMessage(Tox *tox, int32_t friendNumber, const uint8_t *message, uint16_t length, void *userdata);
    //void emitFriendAction(Tox *tox, int32_t friendNumber, const uint8_t *action, uint16_t length, void *userdata);
    //void emitNameChange(Tox *tox, int32_t friendNumber, const uint8_t *name, uint16_t length, void *userdata);
signals:
    void onLosslessPacket(const QByteArray &data);
    void onLossyPacket(const QByteArray &data);
    void onFriendRequest(const QByteArray &publicKey, const QByteArray &data);
    //void onFriendMessage(int32_t friendNumber, const QString &message);
    //void onFriendAction(int32_t friendNumber, const QString &action);
    //void onNameChange(int32_t friendNumber, const QString &name);
    //void onStatusMessage(int32_t friendNumber, const QString &statusMessage);
    //void onUserStatus(int32_t friendNumber, uint8_t userStatus);
    //void onTypingChange(int32_t friendNumber, bool typing);
    //void onReadReceipt(int32_t friendNumber, uint32_t receipt);
    //void onConnectionStatus(int32_t friendNumber, bool online);
private:
    void initTox();
    void initSlots() const;
    Tox *pTox;
    QMap<int32_t, QToxFriend*> mFriends;
};

#endif // TOXSCREEN_QT_QTOX_H
