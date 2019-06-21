#include "ircprotocol.h"

IRCProtocol::IRCProtocol(QString host, int port, QString nickname, QString channel)
{
    this->nickname = nickname;
    this->channel = channel;

    this->connectToHost(host, (quint16)port);
    this->waitForConnected();

    qDebug() << QString("USER " + nickname + "0 * :" + nickname + "\r\n");

    connect(this, SIGNAL(readyRead()), this, SLOT(readData()));
    this->write(QString("NICK " + nickname + "\r\n").toUtf8());
    this->write(QString("USER " + nickname + " 0 * :" + nickname + "\r\n").toUtf8());
    this->write(QString("JOIN #" + channel + "\r\n").toUtf8());
    this->flush();
}

void IRCProtocol::sendData(QString data)
{
    this->write(QString("PRIVMSG #" + channel + " :" + data + "\r\n").toUtf8());
    qDebug() << QString("PRIVMSG #" + channel + " :" + data + "\r\n");
}

void IRCProtocol::readData()
{
    while (this->canReadLine())
    {
        QString line = this->readLine().trimmed();

        int pos1 = line.indexOf("PRIVMSG");
        int pos2 = line.indexOf(":", pos1);
        int pos3 = line.indexOf("!");

        if (pos1 < 0)
        {
            emit dataForGUI(line);
        }
        else
        {
            emit messageFromPerson(line.mid(1,pos3-1), line.mid(pos2+1,-1));
        }
    }
}
