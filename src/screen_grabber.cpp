#include <QApplication>
#include <QDesktopWidget>
#include <QPixmap>
#include <QScreen>

#include "screen_grabber.h"

ScreenGrabber::ScreenGrabber(QScreen *screen)
    : pScreen(screen)
{
}

QPixmap ScreenGrabber::grabPixmap() const
{
    return pScreen->grabWindow(QApplication::desktop()->winId());
}
