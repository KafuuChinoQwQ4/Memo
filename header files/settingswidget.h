#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>

class QLabel;
class QComboBox;
class QPushButton;

class SettingsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SettingsWidget(QWidget *parent = nullptr);

signals:
    void accepted();
    void rejected();
private:
    QLabel *m_titleLabel;
    QLabel *m_typeLabel;
    QComboBox *m_proxyComboBox;
    QPushButton *m_okButton;
    QPushButton *m_cancelButton;
};

#endif // SETTINGSWIDGET_H
