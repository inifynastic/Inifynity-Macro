#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //w.resize(742, 465);
    w.setWindowTitle("Inifynity Macro v1.0.0");
    a.setWindowIcon(QIcon(":../resources/icon.ico"));
    return QApplication::exec();
}
