#include "cryptocontroller.h"

CryptoController::CryptoController(QObject *parent) : QObject(parent)
{

}

QString CryptoController::encodeMessage(QString msg, QByteArray key)
{
    QByteArray otp = myfile_pop(msg.toUtf8().length());
    QByteArray msg1 = msg.toUtf8();
    for (int i = 0; i < msg1.length(); i++)
    {
        msg1[i] = msg1[i] ^ otp[i];
    }
    return QByteArray(msg1 + hmac(msg1, key)).toBase64();
}

QString CryptoController::decodeMessage(QString msg)
{
    msg = QByteArray::fromBase64(msg.toUtf8()).toHex();
    QByteArray msg1 = QByteArray::fromHex(msg.mid(0, msg.length()-64).toUtf8());

    QByteArray otp = peerfile_pop(msg1.length());
    for (int i = 0; i < msg1.length(); i++)
    {
        msg1[i] = msg1[i] ^ otp[i];
    }

    return QString(msg1);
}

bool CryptoController::verifyMessage(QString msg, QByteArray key)
{
    msg = QByteArray::fromBase64(msg.toUtf8()).toHex();
    if (msg.length() < 64) return false;


    QByteArray hmac1 = msg.mid(msg.length()-64,-1).toUtf8();
    QByteArray msg1 = QByteArray::fromHex(msg.mid(0, msg.length()-64).toUtf8());

    QByteArray hmac_verification = hmac(msg1, key);

    if (hmac1 == hmac_verification.toHex())
    {
        return true;
    }

    return false;
}


QByteArray CryptoController::hmac(QByteArray msg, QByteArray key)
{
    QMessageAuthenticationCode mac(QCryptographicHash::Sha256,key);
    mac.addData(msg);
    return mac.result();
}

QByteArray CryptoController::myfile_pop(int bytes)
{
    myfile.seek(myfile.size()-bytes);
    QByteArray res = myfile.read(bytes);
    myfile.resize(myfile.size()-bytes);
    qDebug() << "myfile: " <<res.toHex();
    return res;
}

QByteArray CryptoController::peerfile_pop(int bytes)
{
    peerfile.seek(peerfile.size()-bytes);
    QByteArray res = peerfile.read(bytes);
    peerfile.resize(peerfile.size()-bytes);
    qDebug() << "peerfile: " << res.toHex();
    return res;
}

