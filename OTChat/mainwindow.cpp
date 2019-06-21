#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    this->path = "/tmp/A/";

    QFile f(this->path + "chat.conf");
    f.open(QIODevice::ReadOnly);
    f.waitForReadyRead(3000);
    QByteArray content = f.readAll();
    f.close();
    QStringList l = QString(content).split("\n");
    this->server = QString(l.at(0));
    this->port = QString(l.at(1)).toInt();
    this->channel = QString(l.at(2));
    this->hmac_key = QByteArray::fromHex(l.at(3).toUtf8());
    this->randsize = QString(l.at(4)).toInt();

    this->channel = this->channel.replace("#", "");




    QMessageBox box;
    box.setText("Who are you?");
    box.addButton("Person A: " + l.at(5), QMessageBox::AcceptRole);
    box.addButton("Person B: " + l.at(6), QMessageBox::AcceptRole);
    box.addButton("Cancel", QMessageBox::AcceptRole);
    int res = box.exec();
    if (res == 0)
    {
        this->beA = true; //A
        this->path = "/tmp/A/";
        this->nick = l.at(5);
        crypto.myfile.setFileName(this->path + "randA.dat");
        crypto.peerfile.setFileName(this->path + "randB.dat");

    }
    else if (res == 1)
    {
        this->beA = false; //B
        this->path = "/tmp/B/";
        this->nick = l.at(6);
        crypto.myfile.setFileName(this->path + "randB.dat");
        crypto.peerfile.setFileName(this->path + "randA.dat");
    }
    else
    {
        qApp->exit(0);
    }

    crypto.myfile.open(QIODevice::ReadWrite);
    crypto.peerfile.open(QIODevice::ReadWrite);

    //this->nick = QMessageBox::
    qDebug() << this->nick;
    if (this->nick.length() == 0)
    {
        exit(0);
    }





    this->setWindowTitle("OTChat: " + this->nick);



    protocol = new IRCProtocol(this->server, this->port, nick, this->channel);
    connect(protocol, SIGNAL(dataForGUI(QString)), this, SLOT(recvData(QString)));
    connect(protocol, SIGNAL(messageFromPerson(QString,QString)), this, SLOT(displayMsg(QString,QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_input_returnPressed()
{
    if (this->ui->check_encryption->isChecked())
    {
        protocol->sendData(crypto.encodeMessage(this->ui->input->text(), this->hmac_key));
        this->ui->textview->append(QString("<font color=green><b>%1: %2</b></font>").arg(nick).arg(this->ui->input->text()));
        this->updateProgress();
    }
    else
    {
        protocol->sendData(this->ui->input->text());
        this->ui->textview->append(QString("<font color=green>%1: %2</font>").arg(nick).arg(this->ui->input->text()));
    }

    this->ui->textview->verticalScrollBar()->setValue(this->ui->textview->verticalScrollBar()->maximum());
    this->ui->input->setText("");
}

void MainWindow::recvData(QString data)
{
    this->ui->textview->append(data);
    this->ui->textview->verticalScrollBar()->setValue(this->ui->textview->verticalScrollBar()->maximum());
}

void MainWindow::displayMsg(QString name, QString msg)
{
    if (crypto.verifyMessage(msg, this->hmac_key))
    {
        this->ui->textview->append(
                    QString("<b>%1: %2</b>").arg(name).arg(
                        crypto.decodeMessage(msg)
                        )
                    );
        this->ui->textview->verticalScrollBar()->setValue(this->ui->textview->verticalScrollBar()->maximum());
        this->updateProgress();
    }
    else
    {
        this->ui->textview->append(QString("%1: %2").arg(name).arg(msg));
        this->ui->textview->verticalScrollBar()->setValue(this->ui->textview->verticalScrollBar()->maximum());
    }
}

void MainWindow::updateProgress()
{
    this->ui->mykey->setValue(100.0*crypto.myfile.size()/this->randsize);
    this->ui->peerkey->setValue(100.0*crypto.peerfile.size()/this->randsize);
}

void MainWindow::on_button_clean_clicked()
{
    this->ui->textview->setHtml("");
}
