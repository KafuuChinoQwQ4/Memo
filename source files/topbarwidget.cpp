#include "topbarwidget.h"
#include <QHBoxLayout>
#include <QIcon>
#include <QSize>

TopBarWidget::TopBarWidget(QWidget *parent)
    : QWidget{parent}
{
    // --- Top Buttons ---
    m_closeButton = new QPushButton(this);
    m_closeButton->setIcon(QIcon(":images/关闭.svg"));
    m_closeButton->setObjectName("closeButton");

    m_settingsButton = new QPushButton(this);
    m_settingsButton->setIcon(QIcon(":images/设置.svg"));
    m_settingsButton->setObjectName("settingsButton");

    for (auto button : {m_closeButton, m_settingsButton}) {
        button->setIconSize(QSize(16, 16));
        button->setFixedSize(26, 26);
        button->setCursor(Qt::PointingHandCursor);
    }
    connect(m_closeButton, &QPushButton::clicked, this, &TopBarWidget::closeButtonClicked);
    connect(m_settingsButton, &QPushButton::clicked, this, &TopBarWidget::settingsButtonClicked);

    QHBoxLayout *topLayout = new QHBoxLayout(this);
    topLayout->addStretch();
    topLayout->addWidget(m_settingsButton);
    topLayout->addWidget(m_closeButton);
    topLayout->setContentsMargins(0, 5, 5, 0);
}