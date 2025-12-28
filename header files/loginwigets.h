#ifndef LOGINWIGETS_H
#define LOGINWIGETS_H

#include <QWidget>
#include <QPushButton>

class QTimer;
class QMouseEvent;
class QLabel;
class QLineEdit;
class QToolButton;
class QCheckBox;
class QMenu;

#include "backgroundanimator.h"
#include "loginheaderwidget.h"
#include "topbarwidget.h"
#include "loginformwidget.h"
#include "logincontrolwidget.h"


class LoginWigets : public QWidget

{

    Q_OBJECT

public:

    explicit LoginWigets(QWidget *parent = nullptr);



protected:

    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;



private slots:

    
    void onAgreementToggled(bool checked);

    void updateBackgroundColors(QColor color1, QColor color2);



private:
    QPoint m_dragPosition;

    // Login UI elements
    LoginHeaderWidget *m_loginHeaderWidget;
    BackgroundAnimator *m_backgroundAnimator;
    QColor m_currentBgColor1;
    QColor m_currentBgColor2;
    TopBarWidget *m_topBarWidget;
    LoginFormWidget *m_loginFormWidget;
    LoginControlWidget *m_loginControlWidget;


};

#endif // LOGINWIGETS_H
