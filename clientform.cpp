#include "clientform.h"

#include <QHostAddress>

ClientForm::ClientForm(QWidget *parent) : QWidget(parent)
{
    setupUi(this);
    setWindowTitle("Клиент");

    pTcpSocket = new QTcpSocket(this);
    if(pTcpSocket->bind(QHostAddress::LocalHost)) {
        lblSocketState->setText("Binded");
    }

    connect(btnReceiveFile, &QToolButton::clicked, [=]() {
       pTcpSocket->connectToHost(QHostAddress::LocalHost, 13303);
    });

    connect(pTcpSocket, &QTcpSocket::connected, this, [&]() {
       lblSocketState->setText("Connected");
       lblFileName->setText("ui_clientform.h");
       QByteArray ba ("ui_clientform.h");

       pTcpSocket->write(ba);
       lblExchange->setText("Filename sended");
    });

    connect(pTcpSocket, SIGNAL(readyRead()), SLOT(readyRead()));
}

ClientForm::~ClientForm()
{
    pTcpSocket->close();
}

void ClientForm::readyRead()
{
    textBrowser->setText(pTcpSocket->readAll());
    lblExchange->setText("File received");
    pTcpSocket->close();
}
