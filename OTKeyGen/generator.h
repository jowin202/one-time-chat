#ifndef GENERATOR_H
#define GENERATOR_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QThread>
#include <QRandomGenerator>

class generator : public QThread
{
    Q_OBJECT

public:
    generator(QString pathA, QString pathB, int method, qint64 size, QString conf);
    void run();

signals:
    void progress(int);

private:
    QString pathA;
    QString pathB;
    int method;
    qint64 size;
};

#endif // GENERATOR_H
