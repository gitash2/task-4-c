//
// Created by ash on 5/19/25.
//

#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.setMinimumSize(QSize(600, 400));
    window.setMaximumSize(QSize(1200, 800));
    window.show();
    return QApplication::exec();
}