#ifndef TOXSCREEN_SCREEN_GRABBER_H
#define TOXSCREEN_SCREEN_GRABBER_H

#include <cstdint>
#include <QImage>
#include <QPixmap>
#include <QScreen>
#include <QSize>
#include <vpx/vpx_image.h>

class ScreenGrabber
{
public:
    ScreenGrabber(QScreen *screen);
    QPixmap grabPixmap() const;
    void grabVpxImage(vpx_image_t *image) const;
    bool hasScreen() const;
    static void toVpxImage(const QPixmap &pixmap, vpx_image_t *image);
    static void toVpxImage(const QImage &image, vpx_image_t *vpxImage);
    static void toVpxImage(const uint8_t *raw, const QSize &size, vpx_image_t *vpxImage);
private:
    QScreen *pScreen;
};

#endif // TOXSCREEN_SCREEN_GRABBER_H
