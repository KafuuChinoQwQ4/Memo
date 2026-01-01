#include "backgroundanimator.h"
#include <QLinearGradient>
#include <QColor>
#include <cmath>

// BackgroundAnimator 负责创建和管理背景的平滑渐变动画
BackgroundAnimator::BackgroundAnimator(QObject *parent)
    : QObject{parent},
      m_timer(new QTimer(this)), // 初始化定时器
      m_angle(0.0), // 初始化动画角度
      m_hue1(0.4),  // 初始化第一个颜色的色相
      m_hue2(0.2)   // 初始化第二个颜色的色相
{
    // 连接定时器的 timeout 信号到 updateAnimation 槽函数
    // 每当定时器触发，就会调用 updateAnimation 来更新一帧动画
    connect(m_timer, &QTimer::timeout, this, &BackgroundAnimator::updateAnimation);
}

BackgroundAnimator::~BackgroundAnimator()
{
    stopAnimation(); // 析构时停止动画，防止悬空指针
}

// 启动动画
void BackgroundAnimator::startAnimation()
{
    if (!m_timer->isActive()) {
        m_timer->start(16); // 设置定时器间隔为16毫秒，大约相当于60 FPS (1000/16 ≈ 62.5)
        updateAnimation();  // 立即调用一次以设置初始颜色，避免启动时闪烁
    }
}

// 停止动画
void BackgroundAnimator::stopAnimation()
{
    if (m_timer->isActive()) {
        m_timer->stop();
    }
}

// 更新动画的核心逻辑
void BackgroundAnimator::updateAnimation()
{
    // 角度递增，用于三角函数计算，实现周期性变化
    m_angle += 0.015;
    // 防止角度过大，进行周期性重置
    if (m_angle > 2 * M_PI) {
        m_angle -= 2 * M_PI;
    }

    // 使用 sin 函数来平滑地改变两个颜色的色相(Hue)值
    // 不同的系数和相位（+ M_PI）使得两个颜色的变化步调不一，产生更丰富的效果
    m_hue1 = 0.65 + 0.1 * sin(m_angle);
    m_hue2 = 0.9 + 0.05 * sin(m_angle + M_PI);

    QColor color1, color2;
    // 使用 HSV/HSF 颜色模型创建颜色，固定饱和度(S)和亮度(V)，只改变色相(H)
    // H (色相): 0.0-1.0, S (饱和度): 0.0-1.0, V (明度): 0.0-1.0
    color1.setHsvF(m_hue1, 0.15, 0.98);
    color2.setHsvF(m_hue2, 0.10, 0.98);
    // 发射信号，将新计算出的两个颜色传递出去，由 LoginWigets 接收并用于重绘背景
    emit backgroundColorsChanged(color1, color2);

    // --- 计算并更新标题颜色 ---
    QColor titleColor;
    // 标题的色相基于背景色相进行微调，确保颜色搭配和谐
    double titleHue = m_hue1 + 0.1;
    if (titleHue > 1.0) titleHue -= 1.0; // 保证色相值在 [0, 1] 范围内
    titleColor.setHsvF(titleHue, 0.25, 0.95);
    // 发射信号，将新标题颜色传递出去，由 LoginHeaderWidget 接收并更新Logo颜色
    emit titleColorChanged(titleColor);
}