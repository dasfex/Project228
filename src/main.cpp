#include "headers//mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // насколько понимаю, не даёт создавать копии приложения
    a.setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);

    MainWindow w;
    w.show();

    return a.exec();
}
