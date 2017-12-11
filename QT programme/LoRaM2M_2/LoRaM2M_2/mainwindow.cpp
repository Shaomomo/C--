#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <iostream>
#include "QThread"
//#include "loram2m.h"


QSerialPort portComLoRa;
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this,SLOT(Lecture()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Lecture()
{
     int Nb;
     QString mess = Lm2m.ReceptionTrame(Nb);
     if(mess[0]!=0) ui->lineEdit_3->setText(mess);//+mess;  //->Text=RichEdit3->Text+mess;
}

void MainWindow::on_pushButton_clicked()
{
    Lm2m.ModifierCOM(ui->lineEdit->text().toStdString());
    Lm2m.OuvrirCOM();
    timer->start(100);
}

void MainWindow::on_pushButton_3_clicked()
{
    Lm2m.FermerCOM();
    timer->stop();
}

void MainWindow::on_pushButton_2_clicked()
{
    Lm2m.EnvoiTrame((char*)ui->lineEdit_2->text().toStdString().c_str());
}

void MainWindow::on_pushButton_4_clicked()
{

    if(Lm2m.OuvrirCOM()) Lm2m.ConfigurationUsine();

}

void MainWindow::on_pushButton_5_clicked()
{
    if(Lm2m.OuvrirCOM()) Lm2m.RemiseAZero();
}
