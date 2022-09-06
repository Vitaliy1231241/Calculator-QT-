#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    // Hack to ensure the correct digit count on the display when the program starts.
    w.resize(QSize(800, 400));
    w.resize(QSize(500, 400));
    return a.exec();
}

