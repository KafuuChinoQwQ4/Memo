#ifndef TOPBARWIDGET_H
#define TOPBARWIDGET_H

#include <QWidget>
#include <QPushButton>

class TopBarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TopBarWidget(QWidget *parent = nullptr);

signals:
    void closeButtonClicked();
    void settingsButtonClicked();

private:
    QPushButton *m_closeButton;
    QPushButton *m_settingsButton;
};

#endif // TOPBARWIDGET_H