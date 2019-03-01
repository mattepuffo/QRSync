#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;

#if defined (Q_OS_LINUX) || defined (Q_OS_OSX)
    w.show();
#else
    QMessageBox::about(
                nullptr,
                "Attenzione",
                "Windows non è supportato"
                );
    exit(0);
#endif

    return a.exec();
}
