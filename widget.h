#ifndef WIDGET_H
#define WIDGET_H

#include "ui_widget.h"

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>

//QT_BEGIN_NAMESPACE
//namespace Ui { class Widget; }
//QT_END_NAMESPACE

class Widget : public QWidget, private Ui::Widget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    virtual ~Widget();

    QTcpServer *pTcpServer;
    QTcpSocket *pTcpSocket;

public slots:
    void processingRequest();
    void readyRead();

private:
//    Ui::Widget *ui;
};
#endif // WIDGET_H
