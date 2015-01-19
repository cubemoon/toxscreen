#ifndef TOXSCREEN_SCREEN_GRABBER_H
#define TOXSCREEN_SCREEN_GRABBER_H

#include <cstdint>
#include <QImage>
#include <QObject>
#include <QPixmap>
#include <QScreen>
#include <QSize>
#include <QTimer>
#include <vpx/vpx_image.h>

class ScreenGrabber : public QObject
{
    Q_OBJECT

public:
    ScreenGrabber();
    explicit ScreenGrabber(QScreen *screen);
    uint getInterval() const;
    QPixmap grabPixmap() const;
    QImage grabImage() const;
    void grabVpxImage(vpx_image_t *image) const;
    bool hasScreen() const;
    bool isActive() const;
    void setFPS(uint framesPerSecond);
    void start();
    void stop();
    static void toVpxImage(const QImage &image, vpx_image_t *vpxImage);
    static void toVpxImage(const uint8_t *raw, const QSize &size, vpx_image_t *vpxImage);

public slots:
    void handleImageUpdate();
    void handleVpxImageUpdate();

signals:
    void onImageUpdate(const QImage &image);
    void onVpxImageUpdate(const vpx_image_t &image);

private:
    void initTimer();
    QTimer mTimer;
    QScreen *pScreen;
    uint mFramesPerSecond;
};

#endif // TOXSCREEN_SCREEN_GRABBER_H
