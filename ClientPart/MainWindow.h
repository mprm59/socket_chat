#include <QMainWindow>
#include <QTcpSocket> 
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent=0);
        int AvatarId;
        QIcon avatar[10];
        void appendToChat(QIcon, QString);

    private slots:
        void login();
        void sendMessage();
        void sendFile();
        void randomName();
        void readLine();
        void connected();
        void setRandomNames();
        void setAvatars();
        QString findImagebyId(int id);

        void on_radioButton_1_clicked();
        void on_radioButton_2_clicked();
        void on_radioButton_3_clicked();
        void on_radioButton_4_clicked();
        void on_radioButton_5_clicked();
        void on_radioButton_6_clicked();
        void on_radioButton_7_clicked();
        void on_radioButton_8_clicked();
        void on_radioButton_9_clicked();

        void on_smile0_clicked();
        void on_smile1_clicked();
        void on_smile2_clicked();
        void on_smile3_clicked();
        void on_smile4_clicked();
        void on_smile5_clicked();
        void on_smile6_clicked();
        void on_smile7_clicked();
        void on_smile8_clicked();
        void on_smile9_clicked();
        void on_smile10_clicked();
        void on_smile11_clicked();

private:
        QTcpSocket *socket;
        QString firstName[10];
        QString middleName[10];
        QString lastName[10];
};
