#include <vector>
#include "QTox.h"

void proxy_tox_friend_request(Tox *tox, const uint8_t *publicKey, const uint8_t *data, uint16_t length, void *object);
int proxy_tox_lossless_packet(Tox *tox, int32_t friendNumber, const uint8_t *data, uint32_t length, void *object);
int proxy_tox_lossy_packet(Tox *tox, int32_t friendNumber, const uint8_t *data, uint32_t length, void *object);

QTox::QTox()
    : QObject(), pTox(nullptr), mFriends(QMap<int32_t, QToxFriend*>())
{
    initTox();
    initSlots();
}

QTox::~QTox()
{
    if(hasHandle())
    {
        tox_kill(pTox);
    }
}

/**
 * Initialize Tox callbacks.
 */
void QTox::initSlots() const
{
    tox_callback_friend_request(getHandle(), proxy_tox_friend_request, (void*)this);
}

/**
 * Initialize the tox handle.
 */
void QTox::initTox()
{
    pTox = tox_new(nullptr);
}

/**
 * Emits onFriendRequest.
 */
void QTox::handleFriendRequest(const uint8_t *publicKey, const uint8_t *data, uint16_t length)
{
    QByteArray publicKeyBytes((const char *)publicKey, TOX_CLIENT_ID_SIZE);
    QByteArray dataBytes((const char*)data, length);

    emit onFriendRequest(publicKeyBytes, dataBytes);
}

/**
 * Emits onLosslessPacket. Passes data to specified QToxFriend object if friend found.
 */
void QTox::handleLosslessPacket(int32_t friendNumber, const uint8_t *data, uint32_t length)
{
    QByteArray bytes((const char *)data, length);

    // Emit QTox's signal
    emit onLosslessPacket(bytes);

    // Let friend object handle if friend exists
    QToxFriend *toxFriend = getFriend(friendNumber);
    if(toxFriend != nullptr)
    {
        toxFriend->handleLosslessPacket(bytes);
    }
}

/**
 * Emits onLossyPacket. Passes data to specified QToxFriend object if friend found.
 */
void QTox::handleLossyPacket(int32_t friendNumber, const uint8_t *data, uint32_t length)
{
    QByteArray bytes((const char *)data, length);

    // Emit QTox's signal
    emit onLossyPacket(bytes);

    // Let friend object handle if friend exists
    QToxFriend *toxFriend = getFriend(friendNumber);
    if(toxFriend != nullptr)
    {
        toxFriend->handleLossyPacket(bytes);
    }
}

/**
 * Get our address.
 * @return QByteArray with address
 */
QByteArray QTox::getAddress() const
{
    QByteArray address(TOX_FRIEND_ADDRESS_SIZE, 0);
    tox_get_address(pTox, (uint8_t*)address.data());
    return address;
}

/**
 * Get a pointer to a QToxFriend by their friend number.
 * @param friendNumber Friend number of friend to get
 * @return Pointer to specified friend, or nullptr if none found
 */
QToxFriend * QTox::getFriend(int32_t friendNumber)
{
    if(mFriends.contains(friendNumber))
    {
        return mFriends.value(friendNumber);
    }
    else
    {
        return nullptr;
    }
}

/**
 * Get the Tox handle.
 * @return Pointer to Tox handle
 */
Tox * QTox::getHandle() const
{
    return pTox;
}

/**
 * Get the Tox public and private keys as a QPair of QByteArrays.
 * @param includePriv Whether or not to include the private key
 * @return QPair of QByteArrays containing the keys. If includePriv
 *         was passed as false, all bytes in private key will be 0
 */
QPair<QByteArray, QByteArray> QTox::getKeys(bool includePriv) const
{
    QByteArray publicKey(TOX_CLIENT_ID_SIZE, 0),
               privateKey(TOX_CLIENT_ID_SIZE, 0);

    if(includePriv)
    {
        tox_get_keys(pTox, (uint8_t*)publicKey.data(), (uint8_t*)privateKey.data());
    }
    else
    {
        tox_get_keys(pTox, (uint8_t*)publicKey.data(), nullptr);
    }

    QPair<QByteArray, QByteArray> keys(publicKey, privateKey);
    return keys;
}

/**
 * Get our private key.
 * @return QByteArray with private key
 */
QByteArray QTox::getPrivateKey() const
{
    return getKeys(true).second;
}

/**
 * Get our public key.
 * @return QByteArray with public key
 */
QByteArray QTox::getPublicKey() const
{
    return getKeys(false).first;
}

/**
 * Whether or not we have a Tox handle.
 * @return true if handle, false if none
 */
bool QTox::hasHandle() const
{
    return pTox != nullptr;
}

/**
 * Handle lossless packets for a friend with a specific byte Id.
 * @param friendNumber Friend number
 * @param byte Byte Id
 */
void QTox::registerLossless(int32_t friendNumber, uint8_t byte) const
{
    tox_lossless_packet_registerhandler(getHandle(), friendNumber, byte, proxy_tox_lossless_packet, (void*)this);
}

/**
 * Handle lossy packets for a friend with a specific byte Id.
 * @param friendNumber Friend number
 * @param byte Byte Id
 */
void QTox::registerLossy(int32_t friendNumber, uint8_t byte) const
{
    tox_lossy_packet_registerhandler(getHandle(), friendNumber, byte, proxy_tox_lossy_packet, (void*)this);
}

/**
 * Proxy function to be passed to tox_callback_friend_request(3).
 * Assumes the user object passed is a pointer to a QTox instance.
 * @param tox Pointer to Tox handle
 * @param publicKey Pointer to public key, length is TOX_CLIENT_ID_SIZE
 * @param data Pointer to data
 * @param length Data length
 * @param object User object, QTox pointer expected
 */
void proxy_tox_friend_request(Tox *tox, const uint8_t *publicKey, const uint8_t *data, uint16_t length, void *object)
{
    ((QTox*)object)->handleFriendRequest(publicKey, data, length);
}

/**
 * Proxy function to be passed to tox_lossless_packet_registerhandler(3).
 * Assumes the user object passed is a pointer to a QTox instance.
 * @param tox Pointer to Tox handle
 * @param friendNumber Friend number
 * @param data Pointer to data
 * @param length Data length
 * @param object User object, QTox pointer expected
 */
int proxy_tox_lossless_packet(Tox *tox, int32_t friendNumber, const uint8_t *data, uint32_t length, void *object)
{
    ((QTox*)object)->handleLosslessPacket(friendNumber, data, length);
    return 0;
}

/**
 * Proxy function to be passed to tox_lossy_packet_registerhandler(3).
 * Assumes the user object passed is a pointer to a QTox instance.
 * @param tox Pointer to Tox handle
 * @param friendNumber Friend number
 * @param data Pointer to data
 * @param length Data length
 * @param object User object, QTox pointer expected
 */
int proxy_tox_lossy_packet(Tox *tox, int32_t friendNumber, const uint8_t *data, uint32_t length, void *object)
{
    ((QTox*)object)->handleLossyPacket(friendNumber, data, length);
    return 0;
}
