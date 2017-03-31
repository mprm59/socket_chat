#include "MainWindow.h"
#include <QTime>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setupUi(this);
    stackedWidget->setCurrentWidget(loginPage);
    avatarslabel->setStyleSheet("border-image: url(:/images/Avatars/avatars.png)");
    socket = new QTcpSocket(this);
    connect(socket,      SIGNAL(connected()), this, SLOT(connected()));
    connect(socket,      SIGNAL(readyRead()), this, SLOT(readLine()));

    connect(loginButton, SIGNAL(clicked()),   this, SLOT(login()));
    connect(randButton,  SIGNAL(clicked()),   this, SLOT(randomName()));
    connect(sendButton,  SIGNAL(clicked()),   this, SLOT(sendMessage()));
    connect(fileButton,  SIGNAL(clicked()),   this, SLOT(sendFile()));

    AvatarId = 0;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    setRandomNames();
    setAvatars();
}

void MainWindow::setAvatars() {
    avatar[0].addFile(":/images/Avatars/Angel.png");
    avatar[1].addFile(":/images/Avatars/Engineer.png");
    avatar[2].addFile(":/images/Avatars/King.png");
    avatar[3].addFile(":/images/Avatars/Lady.png");
    avatar[4].addFile(":/images/Avatars/Mexican.png");
    avatar[5].addFile(":/images/Avatars/Policeman.png");
    avatar[6].addFile(":/images/Avatars/Professor.png");
    avatar[7].addFile(":/images/Avatars/Superman.png");
    avatar[8].addFile(":/images/Avatars/UncleSam.png");
    avatar[9].addFile(":/images/Avatars/Server.png");
}

void MainWindow::setRandomNames(){
    firstName[0]="Grand_";      middleName[0]="Master_";      lastName[0]="Bit";
    firstName[1]="Sexy_";       middleName[1]="Boy_";         lastName[1]="1998";
    firstName[2]="Big_";        middleName[2]="Flower_";      lastName[2]="420";
    firstName[3]="Tough_";      middleName[3]="Kitty_";       lastName[3]="228";
    firstName[4]="Great_";      middleName[4]="Guy_";         lastName[4]="007";
    firstName[5]="Fabulous_";   middleName[5]="Angel_";       lastName[5]="1987";
    firstName[6]="Blood_";      middleName[6]="Lady_";        lastName[6]="2000";
    firstName[7]="Smart_";      middleName[7]="Kek_";         lastName[7]="777";
    firstName[8]="Super_";      middleName[8]="Beast_";       lastName[8]="3d";
    firstName[9]="Summer_";     middleName[9]="Princess_";    lastName[9]="123";
}

QString MainWindow::findImagebyId(int id)
{
    switch (id) {
    case (0): return "Angel"; break;
    case (1): return "Engineer"; break;
    case (2): return "King"; break;
    case (3): return "Lady"; break;
    case (4): return "Mexican"; break;
    case (5): return "Policeman"; break;
    case (6): return "Professor"; break;
    case (7): return "Superman"; break;
    case (8): return "UncleSam"; break;
    default:
        return "Invalid id";
        break;
    }
}

void MainWindow::login()
{
    if (userLineEdit->text().length() <= 24 && !userLineEdit->text().isEmpty() && !userLineEdit->text().contains("+"))
        socket->connectToHost(serverLineEdit->text(), 2280);
    else
    {
        QMessageBox::information(this,
                                 tr("Wrong username"),
                                 tr("Your nickname must be 24 characters or shorter. And it can't contain \"+\"\n "
                                    "Check out our nickname generator if you're having problems with coming up with your username"),
                                 QMessageBox::Ok);
        return;
    }
        socket->write(QString("C+" + QString::number(AvatarId) + userLineEdit->text()).toUtf8() + "\n");
}

void MainWindow::sendMessage()
{
    QString message = messageLineEdit->text();

    if(!message.isEmpty())
    {
        message.replace(" XD ",  " <img src=':/images/Smiles/0.png'  width=18 height=18> ");
        message.replace(" :D ",  " <img src=':/images/Smiles/1.png'  width=18 height=18> ");
        message.replace(" :) ",  " <img src=':/images/Smiles/2.png'  width=18 height=18> ");
        message.replace(" :3 ",  " <img src=':/images/Smiles/3.png'  width=18 height=18> ");
        message.replace(" ;) ",  " <img src=':/images/Smiles/4.png'  width=18 height=18> ");
        message.replace(" :* ",  " <img src=':/images/Smiles/5.png'  width=18 height=18> ");
        message.replace(" :P ",  " <img src=':/images/Smiles/6.png'  width=18 height=18> ");
        message.replace(" :0 ",  " <img src=':/images/Smiles/7.png'  width=18 height=18> ");
        message.replace(" :( ",  " <img src=':/images/Smiles/8.png'  width=18 height=18> ");
        message.replace(" KEK ", " <img src=':/images/Smiles/9.png'  width=18 height=18> ");
        message.replace(" ;( ",  " <img src=':/images/Smiles/10.png' width=18 height=18> ");
        message.replace(" :[] ", " <img src=':/images/Smiles/11.png' width=18 height=18> ");
        socket->write(QString("M+" + message + "\n").toUtf8());
    }
    messageLineEdit->clear();
    messageLineEdit->setFocus();
}

void MainWindow::sendFile()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    QFile* file = new QFile(fileName);
    if (file->size() <= 7168)
    {
        fileName = QFileInfo(fileName).fileName();
        file->open(QIODevice::ReadOnly);
        socket->write(QString("F+" + fileName + "\n").toUtf8());
        socket->write(file->readAll());
    }
    else
    {
        QMessageBox::information(this,
                                   tr("Too big or bad file"),
                                   tr("Your file is too big (7 kylobytes or bigger) "
                                      "or there is something wrong with it."),
                                   QMessageBox::Ok);
          return;
    }
}

void MainWindow::readLine()
{
    while(socket->canReadLine())
    {
        QString line = QString::fromUtf8(socket->readLine()).trimmed();
        QString user = "";
        if (line[0] == 'M') {
            QString message = "";
            int id = line[2].digitValue();
            int i = 3;
            while (line[i] != '+') { user += line[i]; i++; }
            i++;
            while (i<line.length()) { message += line[i]; i++; }

            textEdit->insertHtml("<p><img src=':/images/Avatars/" + findImagebyId(id)
                                 + ".png' width=18 height=18>  <b>" + user + " :</b>  " + message + " </p>");
            textEdit->insertPlainText("\n");
        }
        else if (line[0] == 'C') {
            for (int i = 2; i < line.length(); i++) user += line[i];
            textEdit->insertHtml("<p><img src=':/images/Avatars/Server.png' width=18 height=18> User " + user + " has <u>joined.</u> </p>");
            textEdit->insertPlainText("\n");
        }
        else if (line[0] == 'D') {
            for (int i = 2; i < line.length(); i++) user += line[i];
            textEdit->insertHtml("<p><img src=':/images/Avatars/Server.png' width=18 height=18> User " + user + " has <u>disconnected.</u> </p>");
            textEdit->insertPlainText("\n");
        }
        else if (line[0] == 'U') {
            line.remove(0,2);
            QStringList userList = line.split('+');
            usersListWidget->clear();
            foreach (QString user, userList) {
                int id = user[0].digitValue();
                user.remove(0, 1);
                new QListWidgetItem(avatar[id], user, usersListWidget);
            }
        }
        else if (line[0] == 'F')
        {
            QString filename = "";
            int id = line[2].digitValue();
            int i = 3;
            while (line[i] != '+') { user += line[i]; i++; }
            i++;
            while (i<line.length()) { filename += line[i]; i++; }
            QByteArray BArray;
            while(!socket->atEnd())
            {
                BArray.append(socket->readAll());
            }
            textEdit->insertHtml("<p><img src=':/images/Avatars/" + findImagebyId(id) + ".png' width=18 height=18> <u><b>File</b></u> \"" + filename + "\" was sent by <b>" + user + "</b> </p>");
            textEdit->insertPlainText("\n");
            QMessageBox::StandardButton ret;
            ret = QMessageBox::question(this,
                                  tr("Save File?"),
                                  tr("Wouls you like to save incoming file?"),
                                  QMessageBox::Ok | QMessageBox::Cancel);
            if (ret == QMessageBox::Ok)
            {
                QFile file("C:\\" + filename);
                if (!file.open(QIODevice::WriteOnly))
                {
                    textEdit->insertHtml("<p><img src=':/images/Avatars/Server.png' width=18 height=18> Can not save file <img src=':/images/Smiles/10.png' width=18 height=18> </p>");
                    textEdit->insertPlainText("\n");
                }
                else
                {
                    file.write(BArray);
                    file.close();
                    textEdit->insertHtml("<p><img src=':/images/Avatars/Server.png' width=18 height=18> File saved to  \"C:\\" + filename + "\"</p>");
                    textEdit->insertPlainText("\n");
                }
            }
        }
    }
}

void MainWindow::randomName()
{
    userLineEdit->clear();
    userLineEdit->insert(firstName[qrand()%10] + middleName[qrand()%10] + lastName[qrand()%10]);
}

void MainWindow::connected()
{
    stackedWidget->setCurrentWidget(chatPage);
}


void MainWindow::on_radioButton_1_clicked(){AvatarId = 0;}
void MainWindow::on_radioButton_2_clicked(){AvatarId = 1;}
void MainWindow::on_radioButton_3_clicked(){AvatarId = 2;}
void MainWindow::on_radioButton_4_clicked(){AvatarId = 3;}
void MainWindow::on_radioButton_5_clicked(){AvatarId = 4;}
void MainWindow::on_radioButton_6_clicked(){AvatarId = 5;}
void MainWindow::on_radioButton_7_clicked(){AvatarId = 6;}
void MainWindow::on_radioButton_8_clicked(){AvatarId = 7;}
void MainWindow::on_radioButton_9_clicked(){AvatarId = 8;}

void MainWindow::on_smile0_clicked() {messageLineEdit->insert(" XD ");  messageLineEdit->setFocus();}
void MainWindow::on_smile1_clicked() {messageLineEdit->insert(" :D ");  messageLineEdit->setFocus();}
void MainWindow::on_smile2_clicked() {messageLineEdit->insert(" :) ");  messageLineEdit->setFocus();}
void MainWindow::on_smile3_clicked() {messageLineEdit->insert(" :3 ");  messageLineEdit->setFocus();}
void MainWindow::on_smile4_clicked() {messageLineEdit->insert(" ;) ");  messageLineEdit->setFocus();}
void MainWindow::on_smile5_clicked() {messageLineEdit->insert(" :* ");  messageLineEdit->setFocus();}
void MainWindow::on_smile6_clicked() {messageLineEdit->insert(" :P ");  messageLineEdit->setFocus();}
void MainWindow::on_smile7_clicked() {messageLineEdit->insert(" :0 ");  messageLineEdit->setFocus();}
void MainWindow::on_smile8_clicked() {messageLineEdit->insert(" :( ");  messageLineEdit->setFocus();}
void MainWindow::on_smile9_clicked() {messageLineEdit->insert(" KEK "); messageLineEdit->setFocus();}
void MainWindow::on_smile10_clicked(){messageLineEdit->insert(" ;( ");  messageLineEdit->setFocus();}
void MainWindow::on_smile11_clicked(){messageLineEdit->insert(" :[] "); messageLineEdit->setFocus();}

