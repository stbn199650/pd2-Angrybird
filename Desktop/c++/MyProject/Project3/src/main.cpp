#include "mainwindow.h"
#include <QApplication>

//extern MainWindow w;
int main(int argc, char *argv[])
{
    int ExitCode=0;
    do{
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        ExitCode = a.exec();
    }while(ExitCode == MainWindow::EXIT_REBOOT);


    return ExitCode;
}
