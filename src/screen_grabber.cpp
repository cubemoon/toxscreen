#include <QApplication>
#include <QDesktopWidget>
#include <QPixmap>
#include <QScreen>
#include <vpx/vpx_image.h>

#include "screen_grabber.h"

ScreenGrabber::ScreenGrabber()
    : ScreenGrabber(QGuiApplication::primaryScreen())
{
}

ScreenGrabber::ScreenGrabber(QScreen *screen)
    : pScreen(screen),
      mFramesPerSecond(30)
{
}

void ScreenGrabber::handleImageUpdate()
{
    QImage image = grabImage();
    emit onImageUpdate(image);
}

void ScreenGrabber::handleVpxImageUpdate()
{
    vpx_image_t image;
    grabVpxImage(&image);
    emit onVpxImageUpdate(image);
}

/**
 * Check whether or not this ScreenGrabber has a screen.
 * @return true if screen, false if not
 */
bool ScreenGrabber::hasScreen() const
{
    return pScreen != nullptr;
}

/**
 * Get the number of milliseconds per interval, or how long to
 * wait before grabbing a new image and emitting a signal.
 */
uint ScreenGrabber::getInterval() const
{
    return (1000 / mFramesPerSecond);
}

/**
 * Grab a QPixmap of the screen.
 * @return Image of screen. May be null (isNull()) if no screen.
 */
QPixmap ScreenGrabber::grabPixmap() const
{
    if(hasScreen())
    {
        return pScreen->grabWindow(QApplication::desktop()->winId());
    }
    else
    {
        return QPixmap();
    }
}

/**
 * Grab a QImage of the screen.
 * @return Image of the screen. May be null if no screen.
 */
QImage ScreenGrabber::grabImage() const
{
    if(hasScreen())
    {
        return grabPixmap().toImage().convertToFormat(QImage::Format_RGB888);
    }
    else
    {
        return QImage();
    }
}

/**
 * Grab a vpx_image_t of the screen.
 * @param image Pointer to vpx_image_t struct to save the image in
 */
void ScreenGrabber::grabVpxImage(vpx_image_t *image) const
{
    ScreenGrabber::toVpxImage(grabImage(), image);
}

/**
 * Whether or not the timer is running/started.
 * @return true if timer is running, false if not
 */
bool ScreenGrabber::isActive() const
{
    return mTimer.isActive();
}

void ScreenGrabber::setFPS(uint framesPerSecond)
{
    // Limit to 60 for now
    if(framesPerSecond > 60) framesPerSecond = 60;
    mFramesPerSecond = framesPerSecond;
}

/**
 * Start the timer.
 */
void ScreenGrabber::start()
{
    mTimer.setInterval(getInterval());
    mTimer.start();
}

/**
 * Stop the timer.
 */
void ScreenGrabber::stop()
{
    mTimer.stop();
}

/**
 * Initialize timer connections.
 * @todo Only handle one or the other, depending on flags passed to constructor?
 */
void ScreenGrabber::initTimer()
{
    QObject::connect(&mTimer, &QTimer::timeout, this, &ScreenGrabber::handleImageUpdate);
    QObject::connect(&mTimer, &QTimer::timeout, this, &ScreenGrabber::handleVpxImageUpdate);
}

/**
 * Set a vpx_image_t from a QImage.
 * @param image QImage with format QImage::Format_RGB888
 * @param vpxImage vpx_image_t to set
 */
void ScreenGrabber::toVpxImage(const QImage &image, vpx_image_t *vpxImage)
{
    if(image.isNull())
    {
        qDebug("Cannot set vpx_image_t to null image");
        return;
    }
    else if(vpxImage == nullptr)
    {
        qDebug("vpx_image_t == nullptr");
        return;
    }
    else if(image.format() != QImage::Format_RGB888)
    {
        qDebug("QImage::Format_RGB888 required for conversion between QImage and vpx_image_t");
        return;
    }

    const uint8_t *raw = image.bits();
    ScreenGrabber::toVpxImage(raw, image.size(), vpxImage);
}

/**
 * Set a vpx_image_t from raw RGB24 data.
 * Made reference of Swiften's VP8Encoder.cpp: Swiften/ScreenSharing/VP8Encoder.cpp
 * @param raw Raw data formatted as RGB24 (aka QImage::Format_RGB888)
 * @param size Size of the image
 * @param vpxImage vpx_image_t to set
 */
void ScreenGrabber::toVpxImage(const uint8_t *raw, const QSize &size, vpx_image_t *vpxImage)
{
    if(raw == nullptr || vpxImage == nullptr || size.isEmpty())
    {
        return;
    }

    uint8_t* yPlane = vpxImage->planes[VPX_PLANE_Y];
    uint8_t* uPlane = vpxImage->planes[VPX_PLANE_U];
    uint8_t* vPlane = vpxImage->planes[VPX_PLANE_V];

    unsigned int width = (unsigned int)size.width(),
                 height = (unsigned int)size.height(),
                 area = (width * height);

    for(unsigned int i = 0; i < area; i++)
    {
        const uint8_t* p = &raw[3 * i];
        yPlane[i] = ((66 * p[0] + 129 * p[1] + 25 * p[2] + 128) >> 8) + 16;
    }

    for (unsigned int line = 0; line < height / 2; line++)
    {
        for (unsigned int col = 0; col < width / 2; col++)
        {
            int pos = 2 * (line * width + col);
            const uint8_t* p1 = &raw[3 * (pos)];
            const uint8_t* p2 = &raw[3 * (pos + 1)];
            const uint8_t* p3 = &raw[3 * (pos + width)];
            const uint8_t* p4 = &raw[3 * (pos + width + 1)];

            int r = (p1[0] + p2[0] + p3[0] + p4[0]) * 0.25;
            int g = (p1[1] + p2[1] + p3[1] + p4[1]) * 0.25;
            int b = (p1[2] + p2[2] + p3[2] + p4[2]) * 0.25;

            uPlane[line * vpxImage->stride[VPX_PLANE_U] + col] = ((-38 * r - 74 * g + 112 * b + 128) >> 8) + 128;
            vPlane[line * vpxImage->stride[VPX_PLANE_V] + col] = ((112 * r - 94 * g - 18  * b + 128) >> 8) + 128;
        }
    }
}
