#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTcpServer *server;
    QTcpSocket *socket;

private slots:
    void sendMessage();
    void acceptConnection();
    //接收客户端发送的数据
    void receiveData();
    void displayError(QAbstractSocket::SocketError socketError);

    void on_sendmessage_clicked();

private:
    Ui::MainWindow *ui;
    //本地缓冲区
        QByteArray inBlock;
        QByteArray outBlock;

    //系统时间
        QDateTime current_date_time;
        QString str_date_time;
};

#endif // MAINWINDOW_H
