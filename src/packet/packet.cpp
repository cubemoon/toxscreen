#include "packet.h"

Packet::Packet(PacketType type)
    : mBytes(QByteArray()), mBuffer(&mBytes), mStream(&mBuffer), mType(type)
{
    mBuffer.open(QBuffer::WriteOnly);

    // Write the type as first byte
    mStream << ((quint8)type);
}

Packet::Packet(const uint8_t *data, size_t length)
    : Packet(QByteArray((const char *)data, (int)length))
{
}

Packet::Packet(const QByteArray &bytes)
    : mBytes(bytes), mBuffer(&mBytes), mStream(&mBuffer)
{
    mBuffer.open(QBuffer::ReadOnly);

    if(!isEmpty())
    {
        mStream >> mType;
    }

    // Todo: Throw exception?
}

Packet::~Packet()
{
    mBuffer.close();
}

QByteArray Packet::getBytes() const
{
    return mBytes;
}

/**
 * Whether or not this Packet is empty.
 * @return true if empty, false if not
 */
bool Packet::isEmpty() const
{
    return length() == 0;
}

/**
 * Get the number of bytes in this packet.
 * @return Number of bytes
 */
int Packet::length() const
{
    return mBytes.size();
}

/**
 * @see Packet::length()
 */
int Packet::size() const
{
    return mBytes.size();
}
