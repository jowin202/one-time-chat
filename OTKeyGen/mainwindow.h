#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QRandomGenerator>
#include "generator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_browseA_clicked();
    void on_browseB_clicked();
    void on_button_generate_clicked();

    void on_button_rngkey_clicked();

    void on_button_rngchannel_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
