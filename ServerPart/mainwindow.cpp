#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStringList>
#include <QMovie>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    avatar[0].addFile(":/images/Angel.png");
    avatar[1].addFile(":/images/Engineer.png");
    avatar[2].addFile(":/images/King.png");
    avatar[3].addFile(":/images/Lady.png");
    avatar[4].addFile(":/images/Mexican.png");
    avatar[5].addFile(":/images/Policeman.png");
    avatar[6].addFile(":/images/Professor.png");
    avatar[7].addFile(":/images/Superman.png");
    avatar[8].addFile(":/images/UncleSam.png");
    QMovie *movie = new QMovie(":/images/pulse.gif");
        movie->resized(ui->movieLabel->size());
        ui->movieLabel->setMovie(movie);
        movie->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::appendToLog(QIcon Icon, QString note)
{
    new QListWidgetItem(Icon, note, ui->logListWidget);
}

void MainWindow::updateUserList(QStringList userList)
{
    ui->usersListWidget->clear();
    int id;
    foreach(QString user, userList)
    {
        id = user[0].digitValue();
        user.remove(0,1);
        new QListWidgetItem(QIcon(avatar[id]), user, ui->usersListWidget);
    }
}
