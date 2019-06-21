#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <iostream>
#include <QMainWindow>
#include <QMessageBox>
#include <QInputDialog>
#include <QScrollBar>
#include "cryptocontroller.h"
#include "ircprotocol.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_input_returnPressed();
    void recvData(QString data);
    void displayMsg(QString name, QString msg);
    void updateProgress();

    void on_button_clean_clicked();

private:
    Ui::MainWindow *ui;
    IRCProtocol *protocol;
    QString nick;
    QByteArray hmac_key;

    QString server;
    int port;
    QString channel;
    int randsize;
    QString path;
    bool beA;

    CryptoController crypto;

};

#endif // MAINWINDOW_H
