#include "test_packet.h"

void PacketTest::initTestCase()
{
}

void PacketTest::cleanupTestCase()
{
}

void PacketTest::testWritePacket()
{
    QByteArray bytes("\xA0"); // 160
    Packet packet(InfoPacket);
    QByteArray packetBytes = packet.getBytes();
    QCOMPARE(bytes, packetBytes);
}
