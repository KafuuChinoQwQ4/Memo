#ifndef LOGINWIGETS_H
#define LOGINWIGETS_H
#include <QWidget>

class QMouseEvent;
class QStackedWidget;

#include "backgroundanimator.h"
#include "loginheaderwidget.h"
#include "topbarwidget.h"
#include "loginformwidget.h"
#include "logincontrolwidget.h"
#include "settingswidget.h"
#include "registerformwidget.h"

class LoginWigets : public QWidget
{
    Q_OBJECT

public:

    explicit LoginWigets(QWidget *parent = nullptr);

protected:

    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

public slots:
    void onSettingsButtonClicked();

private slots:
    void updateBackgroundColors(QColor color1, QColor color2);
    void onSettingsAccepted();
    void onSettingsRejected();
    void onGoToRegister();

private:
    QPoint m_dragPosition;

    // Core Components
    BackgroundAnimator *m_backgroundAnimator;
    TopBarWidget *m_topBarWidget;
    LoginHeaderWidget *m_loginHeaderWidget;

    // Page Management
    QStackedWidget *m_stackedWidget;
    QWidget *m_loginPage; // A widget to contain all login elements
    QWidget *m_registerPage;
    SettingsWidget *m_settingsPage;

    // Style/Animation Data
    QColor m_currentBgColor1;
    QColor m_currentBgColor2;
};

#endif // LOGINWIGETS_H
