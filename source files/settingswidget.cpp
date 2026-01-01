#include "settingswidget.h"
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSizePolicy>

SettingsWidget::SettingsWidget(QWidget *parent)
    : QWidget{parent}
{
    m_titleLabel = new QLabel("网络代理设置", this);
    m_titleLabel->setObjectName("settingsTitle");
    m_titleLabel->setAlignment(Qt::AlignCenter);

    m_typeLabel = new QLabel("类型", this);

    m_proxyComboBox = new QComboBox(this);
    m_proxyComboBox->setObjectName("proxyComboBox");
    m_proxyComboBox->addItem("不使用代理");
    m_proxyComboBox->addItem("http代理");
    m_proxyComboBox->addItem("socket5代理");
    m_proxyComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QHBoxLayout *proxyTypeLayout = new QHBoxLayout();
    proxyTypeLayout->addWidget(m_typeLabel);
    proxyTypeLayout->addWidget(m_proxyComboBox);
    proxyTypeLayout->setSpacing(10);

    m_okButton = new QPushButton("确定", this);
    m_okButton->setObjectName("okButton");

    m_cancelButton = new QPushButton("取消", this);
    m_cancelButton->setObjectName("cancelButton");

    connect(m_okButton, &QPushButton::clicked, this, &SettingsWidget::accepted);
    connect(m_cancelButton, &QPushButton::clicked, this, &SettingsWidget::rejected);
    
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(m_okButton);
    buttonLayout->addWidget(m_cancelButton);
    buttonLayout->setSpacing(15);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_titleLabel);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(proxyTypeLayout);
    mainLayout->addStretch(); 
    mainLayout->addLayout(buttonLayout);
    mainLayout->setContentsMargins(15, 10, 15, 15);
}
