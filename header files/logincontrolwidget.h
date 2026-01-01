#ifndef LOGINCONTROLWIDGET_H
#define LOGINCONTROLWIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QPushButton>
#include <QMenu>
#include <QLabel>

class LoginControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoginControlWidget(QWidget *parent = nullptr);

    void setLoginButtonEnabled(bool enable);

signals:
    void loginButtonClicked();
    void agreementToggled(bool checked);
    void scanCodeClicked();
    void moreOptionsClicked();
    void registerAccountClicked();

private slots:
    void onAgreementCheckBoxStateChanged(int state);
    void onMoreOptionsButtonClicked();

private:
    QCheckBox *m_agreementCheckBox;
    QPushButton *m_loginButton;
    QPushButton *m_moreOptionsButton;
    QMenu *m_optionsMenu;
};

#endif // LOGINCONTROLWIDGET_H