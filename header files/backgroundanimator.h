#ifndef BACKGROUNDANIMATOR_H
#define BACKGROUNDANIMATOR_H

#include <QObject>
#include <QTimer>
#include <QColor>
#include <cmath> // For M_PI, sin

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class BackgroundAnimator : public QObject
{
    Q_OBJECT
public:
    explicit BackgroundAnimator(QObject *parent = nullptr);
    ~BackgroundAnimator();

    void startAnimation();
    void stopAnimation();

signals:
    void backgroundColorsChanged(QColor color1, QColor color2);
    void titleColorChanged(QColor color); // Signal for the title color

private slots:
    void updateAnimation();

private:
    QTimer *m_timer;
    double m_angle;
    double m_hue1;
    double m_hue2;
};

#endif // BACKGROUNDANIMATOR_H