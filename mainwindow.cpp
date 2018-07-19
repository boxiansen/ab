#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDataStream>
#include <QMessageBox>
#include <QString>
#include <QByteArray>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->socket = new QTcpSocket(this);
    this->server = new QTcpServer(this);
    this->server->listen(QHostAddress::Any,6666);
    connect(this->server,SIGNAL(newConnection()),this,SLOT(acceptConnection()));

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::acceptConnection()
{

    //返回一个socket连接
        this->socket = this->server->nextPendingConnection();//nextPendingConnection获取已建立连接的套接字
        connect(socket,SIGNAL(readyRead()),this,SLOT(receiveData()));
}


void MainWindow::sendMessage()
{
    QString str = ui->input_line_edit->text();
    this->socket->write(ui->input_line_edit->text().toUtf8());
        ////显示
        current_date_time = QDateTime::currentDateTime();
        str_date_time = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
         str = "You "+str_date_time+"\n"+ui->input_line_edit->text();
        this->ui->screen->append(str);

}
void MainWindow::receiveData()
{

    /////获取当前时间
        current_date_time = QDateTime::currentDateTime();
        str_date_time = current_date_time.toString("yyyy-MM-dd hh:mm:ss")+"\n";

        ////接收数据
        QString str = this->socket->readAll();

        ////显示
        str = "Client "+str_date_time+str;
        this->ui->screen->append(str);
}
void MainWindow::displayError(QAbstractSocket::SocketError socketError)
{



    qDebug()<<socket->errorString();
        socket->close();
}

void MainWindow::on_sendmessage_clicked()
{
    this->socket->write(ui->input_line_edit->text().toLatin1());
        ////显示
        current_date_time = QDateTime::currentDateTime();
        str_date_time = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
        QString str = "You "+str_date_time+"\n"+ui->input_line_edit->text();
        ui->screen->append(str);
}
