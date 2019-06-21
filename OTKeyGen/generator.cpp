#include "generator.h"

generator::generator(QString pathA, QString pathB, int method, qint64 size, QString conf)
{
    this->pathA = pathA;
    this->pathB = pathB;
    this->method = method;
    this->size = size;
    QFile conf_file(pathA + "chat.conf");
    conf_file.open(QIODevice::WriteOnly);
    conf_file.write(conf.toUtf8());
    conf_file.copy(pathB + "chat.conf");
    conf_file.close();
}

void generator::run()
{
    QFile fileApathA(pathA + "randA.dat");
    QFile fileBpathA(pathA + "randB.dat");

    fileApathA.open(QIODevice::WriteOnly);
    fileBpathA.open(QIODevice::WriteOnly);


    while (fileApathA.pos() < size)
    {
        QByteArray buffer;
        buffer.resize(qMin((qint64)65536,size-fileApathA.pos()));
        for (int i = 0; i < qMin((qint64)65536,size-fileApathA.pos()); i++)
        {
            buffer[i] = (char)QRandomGenerator::system()->generate() & 0xFF;
        }
        emit progress( (int) (fileApathA.pos()/(0.02 * size))   );
        fileApathA.write(buffer);

        emit progress( (int) (fileApathA.pos()/(0.02 * size))   );
    }
    fileApathA.copy(pathB + "randA.dat");


    while (fileBpathA.pos() < size)
    {
        QByteArray buffer;
        buffer.resize(qMin((qint64)65536,size-fileBpathA.pos()));
        for (int i = 0; i < qMin((qint64)65536,size-fileBpathA.pos()); i++)
        {
            buffer[i] = (char)QRandomGenerator::system()->generate() & 0xFF;
        }
        emit progress( 50 + (int) (fileBpathA.pos()/(0.02 * size))   );
        fileBpathA.write(buffer);
    }
    fileBpathA.copy(pathB + "randB.dat");



    emit progress(100);

    fileApathA.close();
    fileBpathA.close();

}
