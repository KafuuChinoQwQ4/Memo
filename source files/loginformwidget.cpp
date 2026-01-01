#include "loginformwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QIcon>

LoginFormWidget::LoginFormWidget(QWidget *parent)
    : QWidget{parent},
      m_isPasswordVisible(false) // 初始化密码可见性状态为false
{
    // --- 输入字段 ---
    m_accountLineEdit = new QLineEdit(this); // 创建账号输入框
    m_accountLineEdit->setPlaceholderText(tr("请输入账号")); // 设置占位提示文本
    m_accountLineEdit->setObjectName("accountLineEdit"); // 设置对象名，用于QSS样式表

    m_passwordLineEdit = new QLineEdit(this); // 创建密码输入框
    m_passwordLineEdit->setPlaceholderText(tr("请输入密码")); // 设置占位提示文本
    m_passwordLineEdit->setEchoMode(QLineEdit::Password); // 设置为密码模式，输入内容显示为点
    m_passwordLineEdit->setObjectName("passwordLineEdit"); // 设置对象名，用于QSS样式表

    // --- 输入验证 ---
    // 设置账号验证器，只允许输入字母和数字
    QRegularExpression accountRegex("^[a-zA-Z0-9]+$");
    auto *accountValidator = new QRegularExpressionValidator(accountRegex, this);
    m_accountLineEdit->setValidator(accountValidator);

    // 设置密码验证器，允许输入字母、数字和一些常用特殊字符
    QRegularExpression passwordRegex(R"(^[a-zA-Z0-9!@#$%^&*()_+-=\[\]{};':",./<>?]+$)");
    auto *passwordValidator = new QRegularExpressionValidator(passwordRegex, this);
    m_passwordLineEdit->setValidator(passwordValidator);

    // --- 输入框内嵌按钮 ---
    // 账号输入框的下拉按钮
    m_accountDropdownButton = new QToolButton(m_accountLineEdit);
    m_accountDropdownButton->setIcon(QIcon(":images/下拉.svg")); // 设置图标
    m_accountDropdownButton->setObjectName("accountDropdownButton"); // 设置对象名

    // 密码输入框的可见性切换按钮
    m_passwordVisibilityButton = new QToolButton(m_passwordLineEdit);
    m_passwordVisibilityButton->setIcon(QIcon(":images/显示.svg")); // 设置初始图标
    m_passwordVisibilityButton->setObjectName("passwordVisibilityButton"); // 设置对象名

    // 设置鼠标悬停在按钮上时显示手形光标
    m_accountDropdownButton->setCursor(Qt::PointingHandCursor);
    m_passwordVisibilityButton->setCursor(Qt::PointingHandCursor);

    // --- 信号与槽连接 ---
    // 连接密码可见性按钮的点击事件到槽函数 onPasswordVisibilityButtonToggled
    connect(m_passwordVisibilityButton, &QToolButton::clicked, this, &LoginFormWidget::onPasswordVisibilityButtonToggled);
    // 连接账号下拉按钮的点击事件到 accountDropdownClicked 信号
    connect(m_accountDropdownButton, &QToolButton::clicked, this, &LoginFormWidget::accountDropdownClicked);
    // 当账号输入框文本变化时，发射 accountTextChanged 信号
    connect(m_accountLineEdit, &QLineEdit::textChanged, this, &LoginFormWidget::accountTextChanged);
    // 当密码输入框文本变化时，发射 passwordTextChanged 信号
    connect(m_passwordLineEdit, &QLineEdit::textChanged, this, &LoginFormWidget::passwordTextChanged);

    // --- 布局管理 ---
    // 将下拉按钮放置在账号输入框内部的右侧
    QHBoxLayout* accountInnerLayout = new QHBoxLayout(m_accountLineEdit);
    accountInnerLayout->addStretch(); // 添加一个弹性空间，将按钮推到右边
    accountInnerLayout->addWidget(m_accountDropdownButton);
    accountInnerLayout->setContentsMargins(0,0,5,0); // 设置内边距，使按钮和边框有一定距离
    m_accountLineEdit->setLayout(accountInnerLayout);

    // 将可见性按钮放置在密码输入框内部的右侧
    QHBoxLayout* passwordInnerLayout = new QHBoxLayout(m_passwordLineEdit);
    passwordInnerLayout->addStretch(); // 添加弹性空间
    passwordInnerLayout->addWidget(m_passwordVisibilityButton);
    passwordInnerLayout->setContentsMargins(0,0,5,0); // 设置内边距
    m_passwordLineEdit->setLayout(passwordInnerLayout);

    // 主布局，垂直排列账号和密码输入框
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_accountLineEdit);
    mainLayout->addSpacing(15); // 在两个输入框之间添加15像素的间距
    mainLayout->addWidget(m_passwordLineEdit);
    mainLayout->setContentsMargins(0, 0, 0, 0); // 控件本身不设置外边距
}

// 获取账号输入框当前的文本
QString LoginFormWidget::accountText() const
{
    return m_accountLineEdit->text();
}

// 获取密码输入框当前的文本
QString LoginFormWidget::passwordText() const
{
    return m_passwordLineEdit->text();
}

// 密码可见性按钮点击后的槽函数
void LoginFormWidget::onPasswordVisibilityButtonToggled()
{
    m_isPasswordVisible = !m_isPasswordVisible; // 切换可见性状态标志
    if (m_isPasswordVisible) {
        // 如果当前需要变为可见
        m_passwordLineEdit->setEchoMode(QLineEdit::Normal); // 设置输入框为正常显示模式
        m_passwordVisibilityButton->setIcon(QIcon(":images/隐藏.svg")); // 更新按钮图标为“隐藏”
    } else {
        // 如果当前需要变为不可见
        m_passwordLineEdit->setEchoMode(QLineEdit::Password); // 设置输入框为密码遮掩模式
        m_passwordVisibilityButton->setIcon(QIcon(":images/显示.svg")); // 更新按钮图标为“显示”
    }
    // 发射信号，通知其他部分密码可见性状态已改变
    emit passwordVisibilityToggled(m_isPasswordVisible);
}