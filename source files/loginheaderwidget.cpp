#include "loginheaderwidget.h"
#include <QVBoxLayout>
#include <QPixmap>
#include <QFont>
#include <QColor>

LoginHeaderWidget::LoginHeaderWidget(QWidget *parent)
    : QWidget{parent}
{
    // --- Logo ---
    m_logoLabel = new QLabel(this);
    QPixmap logoPixmap(":images/transparent_bg.png");
    m_logoLabel->setPixmap(logoPixmap.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    m_logoLabel->setFixedSize(80, 80);
    m_logoLabel->setAlignment(Qt::AlignCenter);
    m_logoLabel->setStyleSheet("background-color: rgba(255, 255, 255, 0.1); border-radius: 5px;");

    // --- Title ---
    m_titleLabel = new QLabel("Memo", this);
    QFont titleFont("Segoe UI", 36, QFont::Bold);
    m_titleLabel->setFont(titleFont);
    m_titleLabel->setStyleSheet("qproperty-alignment: 'AlignCenter';");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_titleLabel, 0, Qt::AlignCenter);

    mainLayout->addWidget(m_logoLabel, 0, Qt::AlignCenter);
    mainLayout->setContentsMargins(0, 0, 0, 0); // No extra margins for this widget itself
    setLayout(mainLayout);
}

void LoginHeaderWidget::updateTitleColor(QColor color)
{
    if (m_titleLabel) {
        m_titleLabel->setStyleSheet(QString("color: %1; qproperty-alignment: 'AlignCenter';").arg(color.name()));
    }
}
