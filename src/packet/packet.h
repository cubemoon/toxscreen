#ifndef TOXSCREEN_PACKET_PACKET_H
#define TOXSCREEN_PACKET_PACKET_H

#include <cstdint>
#include <QBuffer>
#include <QByteArray>
#include <QDataStream>

/**
 * PacketType.
 */
enum PacketType : uint8_t
{
    InfoPacket = 160,
    ConnectPacket = 161,
    PermissionsPacket = 162,
    KeyEventPacket = 170,
    MouseEventPacket = 171,
    ClipboardEventPacket = 172
};

class Packet
{
public:
    Packet(PacketType type);
    Packet(const uint8_t *data, size_t length);
    explicit Packet(const QByteArray &bytes);
    ~Packet();
    QByteArray getBytes() const;
    int length() const;
    int size() const;
private:
    QByteArray mBytes;
    QBuffer mBuffer;
    QDataStream mStream;
    int mLength;
};

#endif // TOXSCREEN_PACKET_PACKET_H
