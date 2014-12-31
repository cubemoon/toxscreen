#ifndef TOXSCREEN_TEST_TEST_PACKET_H
#define TOXSCREEN_TEST_TEST_PACKET_H

#include <QtTest/QtTest>
#include <QTest>
#include "../../src/packet/packet.h"

class PacketTest : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void cleanupTestCase();
    void testWritePacket();
};

#endif // TOXSCREEN_TEST_TEST_PACKET_H
