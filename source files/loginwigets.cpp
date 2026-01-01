#include "loginwigets.h"
#include "backgroundanimator.h"
#include <QPainter>
#include <QTimer>
#include <QColor>
#include <QLinearGradient>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFile> 
#include <QTextStream> 
#include <QStackedWidget>
#include "loginheaderwidget.h"
#include "topbarwidget.h"
#include "loginformwidget.h"
#include "logincontrolwidget.h"
#include "settingswidget.h"
#include "registerformwidget.h"


#ifndef M_PI
#define M_PI 3.14159265358979323846;
#endif

// LoginWigets 是登录窗口的主控件，继承自 QWidget
LoginWigets::LoginWigets(QWidget *parent)
    : QWidget{parent},
      m_backgroundAnimator(new BackgroundAnimator(this)), // 初始化背景动画器
      m_lastPageBeforeSettings(nullptr)
{
    setWindowTitle(tr("memoLogin")); // 设置窗口标题
    setFixedSize(300, 450); // 设置固定的窗口大小
    setWindowFlags(Qt::FramelessWindowHint); // 设置为无边框窗口
    setAttribute(Qt::WA_TranslucentBackground); // 设置背景透明，为自定义绘制做准备

    // 连接动画器的颜色变化信号到本类的槽函数，以更新背景
    connect(m_backgroundAnimator, &BackgroundAnimator::backgroundColorsChanged, this, &LoginWigets::updateBackgroundColors);
    m_backgroundAnimator->startAnimation(); // 启动背景动画

    // --- 创建并设置子控件 ---
    // 1. 顶部栏 (关闭、设置等按钮)
    m_topBarWidget = new TopBarWidget(this);
    connect(m_topBarWidget, &TopBarWidget::closeButtonClicked, this, &QWidget::close); // 连接关闭按钮信号到窗口的close槽
    connect(m_topBarWidget, &TopBarWidget::settingsButtonClicked, this, &LoginWigets::onSettingsButtonClicked);
    m_topBarWidget->setContentsMargins(0, 5, 5, 0); 

    // 2. 登录头部 (Logo)
    m_loginHeaderWidget = new LoginHeaderWidget(this);
    // 连接动画器的标题颜色变化信号，用于更新Logo颜色
    connect(m_backgroundAnimator, &BackgroundAnimator::titleColorChanged, m_loginHeaderWidget, &LoginHeaderWidget::updateTitleColor);

    // --- 创建登录页面 ---
    m_loginPage = new QWidget(this);
    LoginFormWidget *loginFormWidget = new LoginFormWidget(m_loginPage);
    LoginControlWidget *loginControlWidget = new LoginControlWidget(m_loginPage);
    
    QVBoxLayout *loginPageLayout = new QVBoxLayout(m_loginPage);
    loginPageLayout->setContentsMargins(15, 0, 15, 0);
    loginPageLayout->setSpacing(0);
    loginPageLayout->addWidget(loginFormWidget);
    loginPageLayout->addSpacing(10);
    loginPageLayout->addWidget(loginControlWidget);
    loginPageLayout->addStretch(); // Push login controls to the top of their page
    
    connect(loginControlWidget, &LoginControlWidget::agreementToggled, [loginControlWidget](bool checked){
        loginControlWidget->setLoginButtonEnabled(checked);
    });
    connect(loginControlWidget, &LoginControlWidget::registerAccountClicked, this, &LoginWigets::onGoToRegister);


    // --- 创建注册页面 ---
    m_registerPage = new QWidget(this);
    RegisterFormWidget *registerFormWidget = new RegisterFormWidget(this);
    QVBoxLayout *registerPageLayout = new QVBoxLayout(m_registerPage);
    registerPageLayout->setContentsMargins(15, 0, 15, 15);
    registerPageLayout->addWidget(registerFormWidget);

    connect(registerFormWidget, &RegisterFormWidget::backButtonClicked, this, [this](){
        m_stackedWidget->setCurrentWidget(m_loginPage);
        m_loginHeaderWidget->setVisible(true);
    });
    connect(registerFormWidget, &RegisterFormWidget::registerButtonClicked, this, &LoginWigets::onRegisterAccount);


    // --- 创建设置页面 ---
    m_settingsPage = new SettingsWidget(this);
    connect(m_settingsPage, &SettingsWidget::accepted, this, &LoginWigets::onSettingsAccepted);
    connect(m_settingsPage, &SettingsWidget::rejected, this, &LoginWigets::onSettingsRejected);

    // --- 页面管理器 ---
    m_stackedWidget = new QStackedWidget(this);
    m_stackedWidget->addWidget(m_loginPage);
    m_stackedWidget->addWidget(m_registerPage);
    m_stackedWidget->addWidget(m_settingsPage);

    // --- 主布局 ---
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    
    // 将顶部栏放置在右上角
    mainLayout->addWidget(m_topBarWidget, 0, Qt::AlignRight | Qt::AlignTop);
        
    // 添加Logo/Header到布局中，并居中
    mainLayout->addWidget(m_loginHeaderWidget, 0, Qt::AlignCenter);
    mainLayout->addSpacing(20); 

    // 将页面管理器添加到主布局
    mainLayout->addWidget(m_stackedWidget);
    
    // --- 从资源文件加载并应用QSS样式表 ---
    QFile file(":/styles/loginwidget.qss"); 
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qWarning("Could not open stylesheet file!"); // 如果打开失败，打印警告
    } else {
        QString styleSheet = QTextStream(&file).readAll(); // 读取样式表全部内容
        this->setStyleSheet(styleSheet); // 应用样式表
        file.close();
    }
}

void LoginWigets::onSettingsButtonClicked()
{
    if (m_stackedWidget->currentWidget() != m_settingsPage) {
        m_lastPageBeforeSettings = m_stackedWidget->currentWidget();
        m_stackedWidget->setCurrentWidget(m_settingsPage);
        m_loginHeaderWidget->setVisible(false);
    } else {
        if (m_lastPageBeforeSettings) {
            m_stackedWidget->setCurrentWidget(m_lastPageBeforeSettings);
        } else {
            m_stackedWidget->setCurrentWidget(m_loginPage);
        }
        if (m_stackedWidget->currentWidget() == m_loginPage) {
            m_loginHeaderWidget->setVisible(true);
        } else {
            m_loginHeaderWidget->setVisible(false);
        }
    }
}

// 重写 paintEvent 来实现自定义窗口背景
void LoginWigets::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 开启抗锯齿，使边缘平滑

    // 创建一个线性渐变，从左上到右下
    QLinearGradient gradient(rect().topLeft(), rect().bottomRight());
    gradient.setColorAt(0.0, m_currentBgColor1); // 设置渐变的起始颜色
    gradient.setColorAt(1.0, m_currentBgColor2); // 设置渐变的结束颜色

    painter.setBrush(gradient); // 使用渐变作为画刷
    painter.setPen(Qt::NoPen); // 不需要边框
    // 绘制一个圆角矩形，圆角半径为20px，覆盖整个窗口区域
    painter.drawRoundedRect(this->rect(), 20.0, 20.0);
}

// 重写 mousePressEvent 来实现窗口拖动
void LoginWigets::mousePressEvent(QMouseEvent *event)
{
    // 只响应鼠标左键
    if (event->button() == Qt::LeftButton) {
        // 记录鼠标按下时，鼠标全局位置与窗口左上角的偏移
        m_dragPosition = event->globalPosition().toPoint() - this->frameGeometry().topLeft();
        event->accept();
    }
}

// 重写 mouseMoveEvent 来实现窗口拖动
void LoginWigets::mouseMoveEvent(QMouseEvent *event)
{
    // 只有在鼠标左键按下的情况下移动
    if (event->buttons() & Qt::LeftButton) {
        // 移动窗口到新的位置：当前鼠标全局位置 - 之前记录的偏移
        move(event->globalPosition().toPoint() - m_dragPosition);
        event->accept();
    }
}

// 更新背景颜色的槽函数
void LoginWigets::updateBackgroundColors(QColor color1, QColor color2)
{
    // 保存从动画器传来的新颜色
    m_currentBgColor1 = color1;
    m_currentBgColor2 = color2;
    update(); // 触发重绘事件 (paintEvent)，从而刷新背景
}

void LoginWigets::onSettingsAccepted()
{
    // TODO: 在这里添加保存设置的逻辑

    if (m_lastPageBeforeSettings) {
        m_stackedWidget->setCurrentWidget(m_lastPageBeforeSettings);
    } else {
        m_stackedWidget->setCurrentWidget(m_loginPage);
    }
    if (m_stackedWidget->currentWidget() == m_loginPage) {
        m_loginHeaderWidget->setVisible(true);
    } else {
        m_loginHeaderWidget->setVisible(false);
    }
}

void LoginWigets::onSettingsRejected()
{
    if (m_lastPageBeforeSettings) {
        m_stackedWidget->setCurrentWidget(m_lastPageBeforeSettings);
    } else {
        m_stackedWidget->setCurrentWidget(m_loginPage);
    }
    if (m_stackedWidget->currentWidget() == m_loginPage) {
        m_loginHeaderWidget->setVisible(true);
    } else {
        m_loginHeaderWidget->setVisible(false);
    }
}

void LoginWigets::onGoToRegister()
{
    m_stackedWidget->setCurrentWidget(m_registerPage);
    m_loginHeaderWidget->setVisible(false);
}

void LoginWigets::onRegisterAccount()
{
    // TODO: Implement registration logic
}
