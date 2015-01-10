#ifndef TOXSCREEN_BENCHMARK_BENCHMARK_SCREEN_GRABBER_H
#define TOXSCREEN_BENCHMARK_BENCHMARK_SCREEN_GRABBER_H

#include <QtTest/QtTest>
#include <QTest>
#include "../../src/screen_grabber.h"

class ScreenGrabberBenchmark : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void cleanupTestCase();
    void benchmarkGrabPixmap();
    void benchmarkGrabVpxImage();
private:
    ScreenGrabber *pGrabber;
};

#endif // TOXSCREEN_BENCHMARK_BENCHMARK_SCREEN_GRABBER_H
