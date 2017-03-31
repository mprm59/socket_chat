#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void appendToLog(QIcon, QString);
    void updateUserList(QStringList);
    QIcon avatar[9];

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
