#include "registerformwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QIcon>

RegisterFormWidget::RegisterFormWidget(QWidget *parent)
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

    m_confirmPasswordLineEdit = new QLineEdit(this);
    m_confirmPasswordLineEdit->setPlaceholderText(tr("请再次输入密码"));
    m_confirmPasswordLineEdit->setEchoMode(QLineEdit::Password);
    m_confirmPasswordLineEdit->setObjectName("confirmPasswordLineEdit");

    // --- Input Validation ---
    QRegularExpression accountRegex("^[a-zA-Z0-9]+$");
    auto *accountValidator = new QRegularExpressionValidator(accountRegex, this);
    m_accountLineEdit->setValidator(accountValidator);

    QRegularExpression passwordRegex(R"(^[a-zA-Z0-9!@#$%^&*()_+-=\[\]{};':",./<>?]+$)");
    auto *passwordValidator = new QRegularExpressionValidator(passwordRegex, this);
    m_passwordLineEdit->setValidator(passwordValidator);
    m_confirmPasswordLineEdit->setValidator(passwordValidator);

    // --- Password Visibility Button ---
    m_passwordVisibilityButton = new QToolButton(m_passwordLineEdit);
    m_passwordVisibilityButton->setIcon(QIcon(":images/显示.svg"));
    m_passwordVisibilityButton->setObjectName("passwordVisibilityButton");
    m_passwordVisibilityButton->setCursor(Qt::PointingHandCursor);

    // --- Signal/Slot Connections ---
    connect(m_passwordVisibilityButton, &QToolButton::clicked, this, &RegisterFormWidget::onPasswordVisibilityButtonToggled);
    connect(m_accountLineEdit, &QLineEdit::textChanged, this, &RegisterFormWidget::accountTextChanged);
    connect(m_passwordLineEdit, &QLineEdit::textChanged, this, &RegisterFormWidget::passwordTextChanged);
    connect(m_confirmPasswordLineEdit, &QLineEdit::textChanged, this, &RegisterFormWidget::confirmPasswordTextChanged);

    // --- Layouts ---
    QHBoxLayout* passwordInnerLayout = new QHBoxLayout(m_passwordLineEdit);
    passwordInnerLayout->addStretch();
    passwordInnerLayout->addWidget(m_passwordVisibilityButton);
    passwordInnerLayout->setContentsMargins(0,0,5,0);
    m_passwordLineEdit->setLayout(passwordInnerLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_accountLineEdit);
    mainLayout->addSpacing(15);
    mainLayout->addWidget(m_passwordLineEdit);
    mainLayout->addSpacing(15);
    mainLayout->addWidget(m_confirmPasswordLineEdit);
    mainLayout->setContentsMargins(0, 0, 0, 0);
}

QString RegisterFormWidget::accountText() const
{
    return m_accountLineEdit->text();
}

QString RegisterFormWidget::passwordText() const
{
    return m_passwordLineEdit->text();
}

QString RegisterFormWidget::confirmPasswordText() const
{
    return m_confirmPasswordLineEdit->text();
}

void RegisterFormWidget::onPasswordVisibilityButtonToggled()
{
    m_isPasswordVisible = !m_isPasswordVisible;
    if (m_isPasswordVisible) {
        m_passwordLineEdit->setEchoMode(QLineEdit::Normal);
        m_confirmPasswordLineEdit->setEchoMode(QLineEdit::Normal);
        m_passwordVisibilityButton->setIcon(QIcon(":images/隐藏.svg"));
    } else {
        m_passwordLineEdit->setEchoMode(QLineEdit::Password);
        m_confirmPasswordLineEdit->setEchoMode(QLineEdit::Password);
        m_passwordVisibilityButton->setIcon(QIcon(":images/显示.svg"));
    }
    emit passwordVisibilityToggled(m_isPasswordVisible);
}
