#ifndef LOGINHEADERWIDGET_H
#define LOGINHEADERWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QColor>

class LoginHeaderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoginHeaderWidget(QWidget *parent = nullptr);

public slots:
    void updateTitleColor(QColor color);

private:
    QLabel *m_logoLabel;
    QLabel *m_titleLabel;
};

#endif // LOGINHEADERWIDGET_H
