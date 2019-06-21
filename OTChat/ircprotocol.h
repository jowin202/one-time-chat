#ifndef IRCPROTOCOL_H
#define IRCPROTOCOL_H

#include <QDebug>
#include <QtNetwork>

class IRCProtocol : public QTcpSocket
{
    Q_OBJECT

public:
    IRCProtocol(QString host, int port, QString nickname, QString channel);
    void sendData(QString data);

private slots:
    void readData();


signals:
    void dataForGUI(QString data);
    void messageFromPerson(QString name, QString msg);


private:
    QString nickname;
    QString channel;
};

#endif // IRCPROTOCOL_H
