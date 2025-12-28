#include "logincontrolwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QAction>

LoginControlWidget::LoginControlWidget(QWidget *parent)
    : QWidget{parent},
      m_optionsMenu(nullptr)
{
    // --- Agreement Checkbox and Label ---
    QHBoxLayout *agreementLayout = new QHBoxLayout();
    agreementLayout->setSpacing(0); // Spacing is handled by the label's margin

    m_agreementCheckBox = new QCheckBox(this);
    m_agreementCheckBox->setCursor(Qt::PointingHandCursor);

    QLabel *agreementLabel = new QLabel(this);
    // The rich text sets the content's style, the stylesheet sets the widget box's style
    agreementLabel->setStyleSheet("margin-left: 5px;");
    agreementLabel->setText(R"(<span style="font-size:12px; color:gray;">已阅读并同意 </span><a href="#" style="font-size:12px; color:blue; text-decoration:none;">服务协议</a><span style="font-size:12px; color:gray;"> 和 </span><a href="#" style="font-size:12px; color:blue; text-decoration:none;">隐私保护指引</a>)");
    agreementLabel->setTextFormat(Qt::RichText);
    agreementLabel->setOpenExternalLinks(true); // Allows clicking links

    agreementLayout->addWidget(m_agreementCheckBox);
    agreementLayout->addWidget(agreementLabel);
    agreementLayout->addStretch();

    // --- Login Button ---
    m_loginButton = new QPushButton(tr("登录"), this);
    m_loginButton->setObjectName("loginButton");
    m_loginButton->setCursor(Qt::PointingHandCursor);
    m_loginButton->setEnabled(false); // Disabled by default

    connect(m_agreementCheckBox, &QCheckBox::stateChanged, this, &LoginControlWidget::onAgreementCheckBoxStateChanged);
    connect(m_loginButton, &QPushButton::clicked, this, &LoginControlWidget::loginButtonClicked);

    // --- More Options ---
    QHBoxLayout *optionsLayout = new QHBoxLayout();
    optionsLayout->setSpacing(8);

    const QString optionLabelStyle = "QLabel { color: #0078D7; font-size: 12px; }";

    QLabel *scanCodeLabel = new QLabel(tr("扫码登录"), this);
    scanCodeLabel->setStyleSheet(optionLabelStyle);
    scanCodeLabel->setCursor(Qt::PointingHandCursor);
    // Connect scanCodeLabel to emit signal
    scanCodeLabel->installEventFilter(this); // To handle clicks on QLabel
    connect(scanCodeLabel, &QLabel::linkActivated, this, &LoginControlWidget::scanCodeClicked); // This is a workaround, better to subclass QLabel for proper click signal.

    QLabel *separatorLabel = new QLabel("|", this);
    separatorLabel->setStyleSheet("QLabel { color: #D3D3D3; }");

    m_moreOptionsButton = new QPushButton(tr("更多选项"), this);
    m_moreOptionsButton->setStyleSheet("QPushButton { color: #0078D7; font-size: 12px; border: none; background: transparent; padding: 2px; }"
                                       "QPushButton:hover { background-color: #E0E0E0; border-radius: 2px; }");
    m_moreOptionsButton->setCursor(Qt::PointingHandCursor);
    connect(m_moreOptionsButton, &QPushButton::clicked, this, &LoginControlWidget::onMoreOptionsButtonClicked);

    optionsLayout->addStretch();
    optionsLayout->addWidget(scanCodeLabel);
    optionsLayout->addWidget(separatorLabel);
    optionsLayout->addWidget(m_moreOptionsButton);
    optionsLayout->addStretch();

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(agreementLayout);
    mainLayout->addSpacing(10); // Reduced spacing
    mainLayout->addWidget(m_loginButton);
    mainLayout->addSpacing(15); // Reduced spacing
    mainLayout->addLayout(optionsLayout);
    mainLayout->setContentsMargins(0, 0, 0, 0); // No extra margins for this widget itself
}

void LoginControlWidget::setLoginButtonEnabled(bool enable)
{
    m_loginButton->setEnabled(enable);
}

void LoginControlWidget::onAgreementCheckBoxStateChanged(int state)
{
    emit agreementToggled(state == Qt::Checked);
}

void LoginControlWidget::onMoreOptionsButtonClicked()
{
    if (!m_optionsMenu) {
        m_optionsMenu = new QMenu(this);
        m_optionsMenu->addAction(tr("忘记密码"));
        m_optionsMenu->addSeparator();
        m_optionsMenu->addAction(tr("注册账号"));
        m_optionsMenu->setStyleSheet(
            "QMenu {"
            "  background-color: #FCFCFC;"
            "  border: 1px solid #E0E0E0;"
            "  border-radius: 8px;"
            "  padding: 5px;"
            "}"
            "QMenu::item {"
            "  font-size: 13px;"
            "  color: #333333;"
            "  padding: 10px 25px;"
            "  border-radius: 4px;"
            "  margin: 0px 5px;"
            "}"
            "QMenu::item:selected {"
            "  background-color: #F0F0F0;"
            "  color: #0078D7;"
            "}"
            "QMenu::separator {"
            "  height: 1px;"
            "  background: #E5E5E5;"
            "  margin-left: 10px;"
            "  margin-right: 10px;"
            "}"
            );
    }
    m_optionsMenu->popup(m_moreOptionsButton->mapToGlobal(QPoint(0, m_moreOptionsButton->height())));
    emit moreOptionsClicked();
}