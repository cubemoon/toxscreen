#ifndef TOXSCREEN_SCREEN_GRABBER_H
#define TOXSCREEN_SCREEN_GRABBER_H

#include <QScreen>

class ScreenGrabber
{
public:
    ScreenGrabber(QScreen *screen);
    QPixmap grabPixmap() const;
private:
    QScreen *pScreen;
};

#endif // TOXSCREEN_SCREEN_GRABBER_H
