#ifndef CRYPTOCONTROLLER_H
#define CRYPTOCONTROLLER_H

#include <QDebug>
#include <QObject>
#include <QFile>
#include <QMessageAuthenticationCode>
#include <QCryptographicHash>

class CryptoController : public QObject
{
    Q_OBJECT
public:
    explicit CryptoController(QObject *parent = 0);
    QString encodeMessage(QString msg, QByteArray key);
    QString decodeMessage(QString msg);
    bool verifyMessage(QString msg, QByteArray key);
    QByteArray hmac(QByteArray msg, QByteArray key);
    QByteArray myfile_pop(int bytes);
    QByteArray peerfile_pop(int bytes);



    QFile myfile;
    QFile peerfile;

signals:

public slots:

};

#endif // CRYPTOCONTROLLER_H
