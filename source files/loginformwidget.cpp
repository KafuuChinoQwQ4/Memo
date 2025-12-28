#include "loginformwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QIcon>

LoginFormWidget::LoginFormWidget(QWidget *parent)
    : QWidget{parent},
      m_isPasswordVisible(false)
{
    // --- Input Fields ---
    m_accountLineEdit = new QLineEdit(this);
    m_accountLineEdit->setPlaceholderText(tr("请输入账号"));
    m_accountLineEdit->setObjectName("accountLineEdit");

    m_passwordLineEdit = new QLineEdit(this);
    m_passwordLineEdit->setPlaceholderText(tr("请输入密码"));
    m_passwordLineEdit->setEchoMode(QLineEdit::Password);
    m_passwordLineEdit->setObjectName("passwordLineEdit");

    // --- Input Validation ---
    QRegularExpression accountRegex("^[a-zA-Z0-9]+$");
    auto *accountValidator = new QRegularExpressionValidator(accountRegex, this);
    m_accountLineEdit->setValidator(accountValidator);

    QRegularExpression passwordRegex(R"(^[a-zA-Z0-9!@#$%^&*()_+-=\[\]{};':",./<>?]+$)");
    auto *passwordValidator = new QRegularExpressionValidator(passwordRegex, this);
    m_passwordLineEdit->setValidator(passwordValidator);

    // --- Input Field Buttons ---
    m_accountDropdownButton = new QToolButton(m_accountLineEdit);
    m_accountDropdownButton->setIcon(QIcon(":images/下拉.svg"));
    m_accountDropdownButton->setObjectName("accountDropdownButton");

    m_passwordVisibilityButton = new QToolButton(m_passwordLineEdit);
    m_passwordVisibilityButton->setIcon(QIcon(":images/显示.svg"));
    m_passwordVisibilityButton->setObjectName("passwordVisibilityButton");

    m_accountDropdownButton->setCursor(Qt::PointingHandCursor);
    m_passwordVisibilityButton->setCursor(Qt::PointingHandCursor);

    connect(m_passwordVisibilityButton, &QToolButton::clicked, this, &LoginFormWidget::onPasswordVisibilityButtonToggled);
    connect(m_accountDropdownButton, &QToolButton::clicked, this, &LoginFormWidget::accountDropdownClicked);
    connect(m_accountLineEdit, &QLineEdit::textChanged, this, &LoginFormWidget::accountTextChanged);
    connect(m_passwordLineEdit, &QLineEdit::textChanged, this, &LoginFormWidget::passwordTextChanged);

    // Place buttons inside the QLineEdit
    QHBoxLayout* accountInnerLayout = new QHBoxLayout(m_accountLineEdit);
    accountInnerLayout->addStretch();
    accountInnerLayout->addWidget(m_accountDropdownButton);
    accountInnerLayout->setContentsMargins(0,0,5,0);
    m_accountLineEdit->setLayout(accountInnerLayout);

    QHBoxLayout* passwordInnerLayout = new QHBoxLayout(m_passwordLineEdit);
    passwordInnerLayout->addStretch();
    passwordInnerLayout->addWidget(m_passwordVisibilityButton);
    passwordInnerLayout->setContentsMargins(0,0,5,0);
    m_passwordLineEdit->setLayout(passwordInnerLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_accountLineEdit);
    mainLayout->addSpacing(15);
    mainLayout->addWidget(m_passwordLineEdit);
    mainLayout->setContentsMargins(0, 0, 0, 0); // No extra margins for this widget itself
}

QString LoginFormWidget::accountText() const
{
    return m_accountLineEdit->text();
}

QString LoginFormWidget::passwordText() const
{
    return m_passwordLineEdit->text();
}

void LoginFormWidget::onPasswordVisibilityButtonToggled()
{
    m_isPasswordVisible = !m_isPasswordVisible;
    if (m_isPasswordVisible) {
        m_passwordLineEdit->setEchoMode(QLineEdit::Normal);
        m_passwordVisibilityButton->setIcon(QIcon(":images/隐藏.svg"));
    } else {
        m_passwordLineEdit->setEchoMode(QLineEdit::Password);
        m_passwordVisibilityButton->setIcon(QIcon(":images/显示.svg"));
    }
    emit passwordVisibilityToggled(m_isPasswordVisible);
}
