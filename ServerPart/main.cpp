#include "mainwindow.h"
#include "server.h"
#include <QApplication>
#include <QTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ServerPart *server = new ServerPart();
    server->listen(QHostAddress::LocalHost, 2280);

    return a.exec();
}
