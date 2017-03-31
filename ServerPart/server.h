#ifndef __ServerPart_H__
#define __ServerPart_H__

#include <QStringList>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>
#include <QSet>
#include "mainwindow.h"

class ServerPart : public QTcpServer
{
    Q_OBJECT

    public:
        ServerPart(QObject *parent=0);

    private slots:
        void readyRead();
        void disconnected();
        void sendUserList();

    protected:
        void incomingConnection(int socketfd);

    private:
        QSet<QTcpSocket*> clients;
        QMap<QTcpSocket*, QString> users;
        QMap<QTcpSocket*, QIcon> avatars;
        MainWindow w;

};

#endif
