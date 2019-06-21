#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_browseA_clicked()
{
    this->ui->pathA->setText(QFileDialog::getExistingDirectory(this, "Chose path", QDir::homePath()));
}

void MainWindow::on_browseB_clicked()
{
    this->ui->pathB->setText(QFileDialog::getExistingDirectory(this, "Chose path", QDir::homePath()));
}

void MainWindow::on_button_generate_clicked()
{
    qint64 size = 100;
    switch (this->ui->comboBox->currentIndex())
    {
    case 0: size = 10485760; break;
    case 1: size = 104857600; break;
    case 2: size = 1073741824; break;
    case 3: size = 10737418240; break;
    }

    QString conf = QString("%1\n%2\n%3\n%4\n%5\n%6\n%7").arg(this->ui->server->text()).arg(this->ui->port->value()).arg(this->ui->channel->text()).arg(this->ui->hmac->getKey()).arg(size).arg(this->ui->pseudoA->text()).arg(this->ui->pseudoB->text());

    this->ui->button_generate->setEnabled(false);
    if (!this->ui->pathA->text().endsWith(QDir::separator()))
    {
        this->ui->pathA->setText(this->ui->pathA->text() + QDir::separator());
    }
    if (!this->ui->pathB->text().endsWith(QDir::separator()))
    {
        this->ui->pathB->setText(this->ui->pathB->text() + QDir::separator());
    }

    generator *gen = new generator(this->ui->pathA->text(), this->ui->pathB->text(), 0, size,conf);
    connect(gen, SIGNAL(progress(int)), this->ui->progressBar, SLOT(setValue(int)));
    gen->start();
}

void MainWindow::on_button_rngkey_clicked()
{
    QByteArray key;
    for (int i = 0; i < 16; i++)
    {
        key[i] = (char)QRandomGenerator::system()->generate();
    }
    this->ui->hmac->setText(key.toHex());
}

void MainWindow::on_button_rngchannel_clicked()
{
    this->ui->channel->setText(QString("#conversation%1").arg(QRandomGenerator::system()->generate()));
}
