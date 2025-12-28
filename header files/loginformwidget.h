#ifndef LOGINFORMWIDGET_H
#define LOGINFORMWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QToolButton>

class LoginFormWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoginFormWidget(QWidget *parent = nullptr);

    QString accountText() const;
    QString passwordText() const;

signals:
    void accountTextChanged(const QString &text);
    void passwordTextChanged(const QString &text);
    void passwordVisibilityToggled(bool visible);
    void accountDropdownClicked();

private slots:
    void onPasswordVisibilityButtonToggled();

private:
    QLineEdit *m_accountLineEdit;
    QToolButton *m_accountDropdownButton;
    QLineEdit *m_passwordLineEdit;
    QToolButton *m_passwordVisibilityButton;
    bool m_isPasswordVisible;
};

#endif // LOGINFORMWIDGET_H