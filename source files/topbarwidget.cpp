#include "topbarwidget.h"
#include <QHBoxLayout>
#include <QIcon>
#include <QSize>

// TopBarWidget 是位于窗口顶部的栏，主要包含一些控制按钮，如设置和关闭
TopBarWidget::TopBarWidget(QWidget *parent)
    : QWidget{parent}
{
    // --- 创建顶部按钮 ---
    // 关闭按钮
    m_closeButton = new QPushButton(this);
    m_closeButton->setIcon(QIcon(":images/关闭.svg")); // 从资源文件设置图标
    m_closeButton->setObjectName("closeButton"); // 设置对象名，用于QSS样式

    // 设置按钮
    m_settingsButton = new QPushButton(this);
    m_settingsButton->setIcon(QIcon(":images/设置.svg")); // 从资源文件设置图标
    m_settingsButton->setObjectName("settingsButton"); // 设置对象名

    // --- 统一配置按钮样式和行为 ---
    // C++11 范围for循环，用于批量处理按钮
    for (auto button : {m_closeButton, m_settingsButton}) {
        button->setIconSize(QSize(16, 16)); // 设置图标大小
        button->setFixedSize(26, 26);       // 设置按钮固定大小
        button->setCursor(Qt::PointingHandCursor); // 设置鼠标悬停时为手形光标
    }

    // --- 信号与槽连接 ---
    // 将按钮的 clicked 信号连接到本类的信号
    // 这样，当按钮被点击时，TopBarWidget 会发射一个信号，由父控件(LoginWigets)接收处理
    connect(m_closeButton, &QPushButton::clicked, this, &TopBarWidget::closeButtonClicked);
    connect(m_settingsButton, &QPushButton::clicked, this, &TopBarWidget::settingsButtonClicked);

    // --- 布局 ---
    QHBoxLayout *topLayout = new QHBoxLayout(this);
    topLayout->addStretch(); // 添加一个弹性空间，将按钮推到右侧
    topLayout->addWidget(m_settingsButton); // 添加设置按钮
    topLayout->addWidget(m_closeButton); // 添加关闭按钮
    topLayout->setContentsMargins(0, 0, 5, 0); // 设置布局的边距（右边距5px）
}
