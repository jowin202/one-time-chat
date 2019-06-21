#include "keyfield.h"

keyField::keyField(QWidget *parent) : QLineEdit(parent)
{
    this->setKeyLength(128); //Bit
    this->setFont(QFont("Monospace"));

    locked = false;
    connect(this,SIGNAL(textChanged(QString)), this, SLOT(refreshText()));
}

keyField::~keyField()
{
    //
}

void keyField::setKeyLength(int length)
{
    if (length == 128 || length == 16)
    {
        this->setMaxLength(48);
        this->setInputMask(">HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH");
        this->setText("00000000000000000000000000000000");
        keylen = 128;
    }
    else if (length == 192 || length == 24)
    {
        this->setMaxLength(72);
        this->setInputMask(">HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH");
        this->setText("000000000000000000000000000000000000000000000000");
        keylen = 192;
    }
    else if (length == 256 || length == 32)
    {
        this->setMaxLength(96);
        this->setInputMask(">HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH");
        this->setText("0000000000000000000000000000000000000000000000000000000000000000");
        keylen = 256;
    }
    else
    {
        this->setMaxLength(0);
    }

}

QString keyField::getKey()
{
    return QString(this->text()).replace("-","");
}

void keyField::refreshText()
{
    int pos = this->cursorPosition();


    /*
    if (!locked)
    {
        locked = true;

        if (keylen == 128)
        {
            while (this->text().length() < 47)
            {
                qDebug() << pos;
                this->setText(this->text().insert(pos, QChar('0')));
            }
        }
        else if (keylen == 192)
        {
            if (this->text().length() < 71)
            {

                this->setText(this->text().insert(pos, QChar('0')));
            }
        }
        else if (keylen == 256)
        {
            if (this->text().length() < 95)
            {
                this->setText(this->text().insert(pos, QChar('0')));
            }
        }
    }
    */

    this->setCursorPosition(pos);
    locked = false;
}

