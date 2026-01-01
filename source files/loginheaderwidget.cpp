#include "loginheaderwidget.h"
#include <QVBoxLayout>
#include <QPixmap>
#include <QFont>
#include <QColor>

// LoginHeaderWidget 是用于显示登录界面顶部Logo和标题的控件
LoginHeaderWidget::LoginHeaderWidget(QWidget *parent)
    : QWidget{parent}
{
    // --- Logo ---
    m_logoLabel = new QLabel(this); // 创建用于显示Logo的QLabel
    QPixmap logoPixmap(":images/transparent_bg.png"); // 从Qt资源文件加载Logo图片
    // 设置图片，并将其缩放为80x80像素，保持宽高比，使用平滑变换
    m_logoLabel->setPixmap(logoPixmap.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    m_logoLabel->setFixedSize(80, 80); // 固定Logo标签的大小
    m_logoLabel->setAlignment(Qt::AlignCenter); // 确保图片在标签内居中
    // 使用样式表设置一个半透明的背景和圆角
    m_logoLabel->setStyleSheet("background-color: rgba(255, 255, 255, 0.1); border-radius: 5px;");

    // --- 标题 ---
    m_titleLabel = new QLabel("Memo", this); // 创建标题标签
    QFont titleFont("Segoe UI", 36, QFont::Bold); // 创建一个字体对象，设置字体、大小和粗体
    m_titleLabel->setFont(titleFont); // 应用字体到标题标签
    m_titleLabel->setStyleSheet("qproperty-alignment: 'AlignCenter';"); // 使用样式表设置文本居中

    // --- 布局 ---
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    // 将标题和Logo添加到垂直布局中，并设置为水平居中
    mainLayout->addWidget(m_titleLabel, 0, Qt::AlignCenter);
    mainLayout->addWidget(m_logoLabel, 0, Qt::AlignCenter);
    mainLayout->setContentsMargins(0, 0, 0, 0); // 控件本身无外边距
    setLayout(mainLayout);
}

// 公共槽函数，用于更新标题颜色
void LoginHeaderWidget::updateTitleColor(QColor color)
{
    if (m_titleLabel) {
        // 动态生成样式表字符串，来改变标题的颜色
        // .arg(color.name()) 会将颜色（如 QColor(255,0,0)）转换为CSS识别的名称（如 "#ff0000"）
        m_titleLabel->setStyleSheet(QString("color: %1; qproperty-alignment: 'AlignCenter';").arg(color.name()));
    }
}