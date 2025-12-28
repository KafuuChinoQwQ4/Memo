#include "backgroundanimator.h"
#include <QLinearGradient>
#include <QColor>

BackgroundAnimator::BackgroundAnimator(QObject *parent)
    : QObject{parent},
      m_timer(new QTimer(this)),
      m_angle(0.0),
      m_hue1(0.4),
      m_hue2(0.2)
{
    connect(m_timer, &QTimer::timeout, this, &BackgroundAnimator::updateAnimation);
}

BackgroundAnimator::~BackgroundAnimator()
{
    stopAnimation();
}

void BackgroundAnimator::startAnimation()
{
    if (!m_timer->isActive()) {
        m_timer->start(16); // ~60 FPS
        updateAnimation(); // Initial call to set colors immediately
    }
}

void BackgroundAnimator::stopAnimation()
{
    if (m_timer->isActive()) {
        m_timer->stop();
    }
}

void BackgroundAnimator::updateAnimation()
{
    m_angle += 0.015;
    if (m_angle > 2 * M_PI) {
        m_angle -= 2 * M_PI;
    }

    m_hue1 = 0.65 + 0.1 * sin(m_angle);
    m_hue2 = 0.9 + 0.05 * sin(m_angle + M_PI);

    QColor color1, color2;
    color1.setHsvF(m_hue1, 0.15, 0.98);
    color2.setHsvF(m_hue2, 0.10, 0.98);
    emit backgroundColorsChanged(color1, color2);

    // Calculate title color
    QColor titleColor;
    double titleHue = m_hue1 + 0.1;
    if (titleHue > 1.0) titleHue -= 1.0;
    titleColor.setHsvF(titleHue, 0.25, 0.95);
    emit titleColorChanged(titleColor);
}
