#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "LoRaM2M.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    LoRaM2M Lm2m;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void Lecture();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
};

#endif // MAINWINDOW_H
