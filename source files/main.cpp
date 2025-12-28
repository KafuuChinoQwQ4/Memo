#include "loginwigets.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWigets w;
    w.show();
    return a.exec();
}
