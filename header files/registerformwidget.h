#ifndef REGISTERFORMWIDGET_H
#define REGISTERFORMWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QToolButton>
#include <QPushButton>

class RegisterFormWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RegisterFormWidget(QWidget *parent = nullptr);

    QString accountText() const;
    QString passwordText() const;
    QString confirmPasswordText() const;
    QString emailText() const;
    QString verificationCodeText() const;

signals:
    void accountTextChanged(const QString &text);
    void passwordTextChanged(const QString &text);
    void confirmPasswordTextChanged(const QString &text);
    void emailTextChanged(const QString &text);
    void verificationCodeChanged(const QString &text);
    void sendCodeClicked();
    void passwordVisibilityToggled(bool visible);
    void registerButtonClicked();
    void backButtonClicked();

private slots:
    void onPasswordVisibilityButtonToggled();

private:
    QLineEdit *m_accountLineEdit;
    QLineEdit *m_passwordLineEdit;
    QLineEdit *m_confirmPasswordLineEdit;
    QLineEdit *m_emailLineEdit;
    QLineEdit *m_verificationCodeLineEdit;
    QPushButton *m_sendCodeButton;
    QToolButton *m_passwordVisibilityButton;
    QPushButton *m_registerButton;
    QPushButton *m_backButton;
    bool m_isPasswordVisible;
};

#endif // REGISTERFORMWIDGET_H
