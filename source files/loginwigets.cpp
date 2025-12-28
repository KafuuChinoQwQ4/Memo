#include "loginwigets.h"
#include "backgroundanimator.h"
#include <QPainter>
#include <QTimer>
#include <QColor>
#include <QLinearGradient>
#include <QMouseEvent>
#include <QLabel>
#include <QLineEdit>
#include <QToolButton>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <cmath>
#include <QMenu>
#include <QAction>
#include <QFile> 
#include <QTextStream> 
#include "loginheaderwidget.h"
#include "topbarwidget.h"
#include "loginformwidget.h"
#include "logincontrolwidget.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846;
#endif

LoginWigets::LoginWigets(QWidget *parent)
    : QWidget{parent},
      m_backgroundAnimator(new BackgroundAnimator(this))
{
    setWindowTitle(tr("memoLogin"));
    setFixedSize(300, 450); 
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    connect(m_backgroundAnimator, &BackgroundAnimator::backgroundColorsChanged, this, &LoginWigets::updateBackgroundColors);
    m_backgroundAnimator->startAnimation();

    m_topBarWidget = new TopBarWidget(this);
    connect(m_topBarWidget, &TopBarWidget::closeButtonClicked, this, &QWidget::close);
    m_topBarWidget->setContentsMargins(0, 5, 5, 0); 

    m_loginHeaderWidget = new LoginHeaderWidget(this);
    connect(m_backgroundAnimator, &BackgroundAnimator::titleColorChanged, m_loginHeaderWidget, &LoginHeaderWidget::updateTitleColor);

    // --- Main Layout ---
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(0, 0, 0, 0);
    
    // 1. 顶部栏
    mainLayout->addWidget(m_topBarWidget, 0, Qt::AlignRight | Qt::AlignTop);
    
    // 2. [修改] 移除之前的 stretch，改为固定间距，让内容靠上 
    
    // 3. Logo/Header
    mainLayout->addWidget(m_loginHeaderWidget, 0, Qt::AlignCenter);
    mainLayout->addSpacing(20); 

    // 4. 输入框容器
    QHBoxLayout *inputsContainer = new QHBoxLayout();
    QVBoxLayout *inputsLayout = new QVBoxLayout();

    m_loginFormWidget = new LoginFormWidget(this);
    inputsLayout->addWidget(m_loginFormWidget);
    inputsLayout->addSpacing(10);

    m_loginControlWidget = new LoginControlWidget(this);
    inputsLayout->addWidget(m_loginControlWidget);
    
    connect(m_loginControlWidget, &LoginControlWidget::agreementToggled, this, &LoginWigets::onAgreementToggled);

    inputsLayout->setSpacing(0);
    inputsContainer->addLayout(inputsLayout);
    inputsContainer->setContentsMargins(15, 0, 15, 0); 

    mainLayout->addLayout(inputsContainer);

    // 5. [关键] 底部添加弹簧，把上面所有内容往上顶
    mainLayout->addStretch(1); 
    
    setLayout(mainLayout);

    // --- Load and apply stylesheet ---
    QFile file(":/styles/loginwidget.qss"); 
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qWarning("Could not open stylesheet file!");
    } else {
        QString styleSheet = QTextStream(&file).readAll();
        this->setStyleSheet(styleSheet);
        file.close();
    }
}

void LoginWigets::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QLinearGradient gradient(rect().topLeft(), rect().bottomRight());
    gradient.setColorAt(0.0, m_currentBgColor1);
    gradient.setColorAt(1.0, m_currentBgColor2);

    painter.setBrush(gradient);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(this->rect(), 20.0, 20.0);
}

void LoginWigets::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_dragPosition = event->globalPosition().toPoint() - this->frameGeometry().topLeft();
        event->accept();
    }
}

void LoginWigets::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPosition().toPoint() - m_dragPosition);
        event->accept();
    }
}

void LoginWigets::onAgreementToggled(bool checked)
{
    m_loginControlWidget->setLoginButtonEnabled(checked);
}

void LoginWigets::updateBackgroundColors(QColor color1, QColor color2)
{
    m_currentBgColor1 = color1;
    m_currentBgColor2 = color2;
    update(); 
}