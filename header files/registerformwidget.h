#ifndef REGISTERFORMWIDGET_H
#define REGISTERFORMWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QToolButton>

class RegisterFormWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RegisterFormWidget(QWidget *parent = nullptr);

    QString accountText() const;
    QString passwordText() const;
    QString confirmPasswordText() const;

signals:
    void accountTextChanged(const QString &text);
    void passwordTextChanged(const QString &text);
    void confirmPasswordTextChanged(const QString &text);
    void passwordVisibilityToggled(bool visible);

private slots:
    void onPasswordVisibilityButtonToggled();

private:
    QLineEdit *m_accountLineEdit;
    QLineEdit *m_passwordLineEdit;
    QLineEdit *m_confirmPasswordLineEdit;
    QToolButton *m_passwordVisibilityButton;
    bool m_isPasswordVisible;
};

#endif // REGISTERFORMWIDGET_H
