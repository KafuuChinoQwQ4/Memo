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
#include <QFile> // Added for stylesheet loading
#include <QTextStream> // Added for stylesheet loading
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
    setFixedSize(300, 450); // Keep original window size
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    connect(m_backgroundAnimator, &BackgroundAnimator::backgroundColorsChanged, this, &LoginWigets::updateBackgroundColors);
    m_backgroundAnimator->startAnimation();

    m_backgroundAnimator->startAnimation();

    m_topBarWidget = new TopBarWidget(this);
    connect(m_topBarWidget, &TopBarWidget::closeButtonClicked, this, &QWidget::close);
    //connect(m_topBarWidget, &TopBarWidget::settingsButtonClicked, this, &LoginWigets::onSettingsClicked); // Assuming a slot will be added for settings
    m_topBarWidget->setContentsMargins(0, 5, 5, 0); // Apply original topLayout margins to the widget itself

    m_loginHeaderWidget = new LoginHeaderWidget(this);
    connect(m_backgroundAnimator, &BackgroundAnimator::titleColorChanged, m_loginHeaderWidget, &LoginHeaderWidget::updateTitleColor);


    // --- Main Layout ---
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(m_topBarWidget, 0, Qt::AlignRight | Qt::AlignTop);
    mainLayout->addStretch(1);
    mainLayout->addWidget(m_loginHeaderWidget, 0, Qt::AlignCenter);
    mainLayout->addSpacing(15); // Move inputs up

    // Center the input fields horizontally
    QHBoxLayout *inputsContainer = new QHBoxLayout();
    QVBoxLayout *inputsLayout = new QVBoxLayout();

    m_loginFormWidget = new LoginFormWidget(this);
    inputsLayout->addWidget(m_loginFormWidget);
    inputsLayout->addSpacing(10);

    // Connect signals from LoginFormWidget to LoginWigets slots/logic
    // For now, these signals might not be directly used, but they are available for future logic.
    // connect(m_loginFormWidget, &LoginFormWidget::accountTextChanged, this, &LoginWigets::onAccountTextChanged);
    // connect(m_loginFormWidget, &LoginFormWidget::passwordTextChanged, this, &LoginWigets::onPasswordTextChanged);
    // connect(m_loginFormWidget, &LoginFormWidget::passwordVisibilityToggled, this, &LoginWigets::onPasswordVisibilityToggled);
    // connect(m_loginFormWidget, &LoginFormWidget::accountDropdownClicked, this, &LoginWigets::onAccountDropdownClicked);

    inputsLayout->addSpacing(10); // Space after LoginFormWidget

    m_loginControlWidget = new LoginControlWidget(this);
    inputsLayout->addWidget(m_loginControlWidget);

    connect(m_loginControlWidget, &LoginControlWidget::agreementToggled, this, &LoginWigets::onAgreementToggled);
    // Connect other signals from LoginControlWidget to LoginWigets slots if needed.
    // connect(m_loginControlWidget, &LoginControlWidget::loginButtonClicked, this, &LoginWigets::onLoginClicked);
    // connect(m_loginControlWidget, &LoginControlWidget::scanCodeClicked, this, &LoginWigets::onScanCodeClicked);
    // connect(m_loginControlWidget, &LoginControlWidget::moreOptionsClicked, this, &LoginWigets::onMoreOptionsClicked);

    inputsLayout->setSpacing(0);

    inputsContainer->addLayout(inputsLayout);
    inputsContainer->setContentsMargins(15, 0, 15, 0); // Adjust margins to prevent clipping

    mainLayout->addLayout(inputsContainer);
    mainLayout->addStretch(1); // Further reduced stretch to move elements upwards
    setLayout(mainLayout);

    // --- Load and apply stylesheet ---
    QFile file(":/styles/loginwidget.qss"); // Assuming the qss is added to qrc
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        // Handle error if stylesheet cannot be opened
        qWarning("Could not open stylesheet file!");
    } else {
        QString styleSheet = QTextStream(&file).readAll();
        this->setStyleSheet(styleSheet);
        file.close();
    }
    // --- End stylesheet loading ---

    setLayout(mainLayout);
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

    update(); // Trigger a repaint

}