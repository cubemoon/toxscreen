#include <QApplication>
#include <QGuiApplication>
#include <QWindow>
#include "benchmark_screen_grabber.h"

void ScreenGrabberBenchmark::initTestCase()
{
    pGrabber = new ScreenGrabber(QGuiApplication::primaryScreen());
}

void ScreenGrabberBenchmark::cleanupTestCase()
{
    delete pGrabber;
}

void ScreenGrabberBenchmark::benchmarkGrabPixmap()
{
    QBENCHMARK {
        pGrabber->grabPixmap();
    }
}

void ScreenGrabberBenchmark::benchmarkGrabVpxImage()
{
    //vpx_image_t image;
    //
    //QBENCHMARK {
    //    pGrabber->grabVpxImage(&image);
    //}
}
