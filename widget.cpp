#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);
    setWindowTitle("Сервер");

    pTcpServer = new QTcpServer(this);
    pTcpSocket = nullptr;

    if(pTcpServer->listen(QHostAddress::LocalHost, 13303)) {
        lblServerState->setText("Listen");
    }
    else {
        lblServerState->setText("Error");
    }

    lblServerIP->setText(pTcpServer->serverAddress().toString());
    lblServerPort->setNum(pTcpServer->serverPort());

    connect(pTcpServer, &QTcpServer::newConnection, this, &Widget::processingRequest);
}

Widget::~Widget()
{

}

void Widget::processingRequest()
{
    lblServerState->setText("Connected");
    lblExchange->setText("Request in process");
    pTcpSocket = pTcpServer->nextPendingConnection();
    connect(pTcpSocket, SIGNAL(readyRead()), SLOT(readyRead()));
    connect(pTcpSocket, &QTcpSocket::disconnected, pTcpSocket, &QTcpSocket::deleteLater);
}

void Widget::readyRead()
{
    QByteArray ba;

    ba = pTcpSocket->readAll();
    lblExchange->setText("Request to send file:" + ba);
    QFile file(ba);
    if(file.exists()) {
        file.open(QFile::ReadOnly);
        lblFile->setText(ba);
        lblSize->setText(QString::number(file.size()));
        pTcpSocket->write(file.readAll());
        lblExchange->setText("File sended");
        file.close();
    }
    else {
        lblExchange->setText("File doesn't exist");
    }
}

