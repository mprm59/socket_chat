#include "server.h"
#include "mainwindow.h"
#include <QTcpSocket>
#include <QFile>
#include <QTime>

ServerPart::ServerPart(QObject *parent) : QTcpServer(parent)
{
    w.show();
}

void ServerPart::incomingConnection(int socketfd)
{
    QTcpSocket *client = new QTcpSocket(this);
    client->setSocketDescriptor(socketfd);
    clients.insert(client);


    w.appendToLog(QIcon(":/images/Server.png"), QString( QTime::currentTime().toString("hh:mm:ss") + ":  Incoming connection from peer adress \"" + client->peerAddress().toString() + "\""));
    connect(client, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(client, SIGNAL(disconnected()), this, SLOT(disconnected()));
}

void ServerPart::readyRead()
{
    QTcpSocket *client = (QTcpSocket*)sender();

    while(client->canReadLine())
    {
            QString line = QString::fromUtf8(client->readLine()).trimmed();
            w.appendToLog(QIcon(":/images/Envelope.png"), QString(QTime::currentTime().toString("hh:mm:ss") + ":  Incoming line:  " + line));
            if (line[0] == 'C') //Means incoming Connection
            {
                 QString user = "";
                 for (int i = 3; i < line.length(); i++) user += line[i];
                 users[client] = line[2] + user;
                 avatars[client] = w.avatar[line[2].digitValue()];

                 foreach(QTcpSocket *client, clients)
                     client->write(QString("C+" + user + "\n").toUtf8());

                 sendUserList();
                 w.appendToLog(QIcon(":/images/Server.png"), QString(QTime::currentTime().toString("hh:mm:ss") + ":  New user " + user + " has joined"));
            }
            else if (line[0] == 'M') //Means incoming Message
            {
                QString user = users[client];
                QString message = "";
                for (int i = 2; i < line.length(); i++) message += line[i];

                foreach(QTcpSocket *otherClient, clients)
                    otherClient->write(QString("M+" +  user + "+" + message + "\n").toUtf8());
                user.remove(0, 1);
                w.appendToLog(QIcon(avatars[client]), QString(QTime::currentTime().toString("hh:mm:ss") + ":  Message from " + user + ": " + message));
            }
            else if (line[0] == 'F') //Means incoming file
            {
                QString fileName = line.remove(0,2);
                QString user = users[client];
                QByteArray BArray;
                while(!client->atEnd())
                {
                    BArray.append(client->readAll());

                }
                foreach(QTcpSocket *otherClient, clients)
                {
                    otherClient->write(QString("F+" + user + "+" + fileName + "\n").toUtf8());
                    otherClient->write(BArray);
                }
                user.remove(0, 1);
                w.appendToLog(QIcon(":/images/File.png"), QString(QTime::currentTime().toString("hh:mm:ss") + ":  File " + fileName + " from user " + user));
            }
         }
}

void ServerPart::disconnected()
{
    QTcpSocket *client = (QTcpSocket*)sender();

    QString user = users[client];
    user.remove(0, 1);

    foreach(QTcpSocket *others, clients)
        others->write(QString("D+" + user + "\n").toUtf8());



    users.remove(client);
    avatars.remove(client);
    clients.remove(client);

    w.appendToLog(QIcon(":/images/Server.png"), QString(QTime::currentTime().toString("hh:mm:ss") + ":  User " + user +  " with peer adress \"" + client->peerAddress().toString() + "\" has disconected"));
    sendUserList();
}

void ServerPart::sendUserList()
{
    QStringList userList;
    foreach(QString user, users.values())
        userList << user;

    foreach(QTcpSocket *client, clients)
        client->write(QString("U+" + userList.join("+") + "\n").toUtf8());

    w.updateUserList(userList);
}
