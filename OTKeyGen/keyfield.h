#ifndef KEYFIELD_H
#define KEYFIELD_H

#include <QLineEdit>
#include <QWidget>
#include <QDebug>

class keyField : public QLineEdit
{
    Q_OBJECT

public:
    explicit keyField(QWidget *parent);
    ~keyField();
    void setKeyLength(int length);
    QString getKey();

public slots:
    void refreshText();

private:
    int keylen;
    bool locked;

};

#endif // KEYFIELD_H
