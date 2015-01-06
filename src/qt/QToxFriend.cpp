#include "QToxFriend.h"

QToxFriend::QToxFriend(QTox *parent, int32_t friendNumber)
    : pParent(parent), mNumber(friendNumber)
{
}

int32_t QToxFriend::getFriendNumber() const
{
    return mNumber;
}

QString QToxFriend::getName() const
{
    return mName;
}

/**
 * Get the QTox parent.
 */
QTox * QToxFriend::getParent() const
{
    return pParent;
}

QString QToxFriend::getStatusMessage() const
{
    return mStatusMessage;
}

uint8_t QToxFriend::getUserStatus() const
{
    return mUserStatus;
}

void QToxFriend::handleLosslessPacket(const QByteArray &bytes)
{
    emit onLosslessPacket(bytes);
}

void QToxFriend::handleLossyPacket(const QByteArray &bytes)
{
    emit onLossyPacket(bytes);
}
