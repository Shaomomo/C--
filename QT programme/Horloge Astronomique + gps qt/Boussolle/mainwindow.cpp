#include "mainwindow.h"
#include "ui_mainwindow.h"

QSerialPort portboussolle;
QDate date;



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



void MainWindow::on_pushButton_clicked()
{
    BS.ModifierCOM(ui->lineEdit_2->text().toStdString());
    BS.ouvrirCOM();
   // BS.ReceptionMessage();

}

void MainWindow::on_pushButton_2_clicked()
{
    BS.fermerCOM();
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->lineEdit->clear();
    mess = BS.ReceptionMessage();
    ui->lineEdit->setText(  mess ) ;

    parametre = ui->lineEdit->text().toStdString() ;

    if ( parametre.length() > 40 ){


    Latt = parametre.substr(18,2/*9*/) ;
    longitude = parametre.substr(32,1/*10*/);
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_3->setText(Latt.c_str());
    ui->lineEdit_4->setText(longitude.c_str());

    }
    else
    {
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_3->setText("Pb GPS ");
        ui->lineEdit_4->setText("Pb GPS");
    }




}

void MainWindow::on_pushButton_4_clicked()
{
    //QDateTime jourr = QDateTime::currentDateTime();

    QString savLat = ui->lineEdit_3->text();
    QString savLong = ui->lineEdit_4->text();
   // ui->lineEdit_5->setText(savLat);

    double ccc = savLat.toDouble();
    double ddd = savLong.toDouble();

    date = QDate::currentDate();
    int jour_int =date.day();
    int mois = date.month();
    int annee = date.year();
    //jour.toUShort(0, 10);
    unsigned short Jour_du_Mois = jour_int;
    unsigned char Mois = mois;
    unsigned short an = annee;

    double HetD[6] ;


    BS.lever_et_coucher_sol(ccc,ddd,Jour_du_Mois,Mois,an, HetD );
    //BS.lever_et_coucher_sol(48,2,4,5,2017, HetD );

    QString Heure_lever = QString::number((int)HetD[0]) + "h" + QString::number((int)HetD[1]);
/*
    char heure_lever[20];
    sprintf(heure_lever,"%d",(int)HetD[0]);//heure levé
    parametre_1 = heure_lever;
*/
/*    for (int i = 0; i<parametre_1.length(); i++)
    {
        if(parametre_1.find(".", 1))
        {
            astro_heure_lever = parametre_1.substr(0, 1);
        }

        if(parametre_1.find(".", 2))
        {
            astro_heure_lever = parametre_1.substr(0, 2);
        }

    }
*//*    astro_heure_lever = parametre_1.substr(0, 2);



    char minute_lever[20];
    sprintf(minute_lever,"%lf",HetD[1]);//heure levé
    parametre = minute_lever;
    for (int i= 0; i<parametre.length(); i++)
    {
        if(parametre.find(".", 1))
        {
            astro_minute_lever = parametre.substr(0, 1);
        }
        if(parametre.find(".", 3))
        {
            astro_minute_lever = parametre.substr(0, 2);
        }

    }
    QString n = astro_heure_lever.c_str() ;
    n += "h" ;
    n += astro_minute_lever.c_str();
*/
    ui->lineEdit_5->setText(Heure_lever);

    QString Heure_coucher = QString::number((int)HetD[2]) + "h" + QString::number((int)HetD[3]);
    /*QString astro_heure_coucher;
    char coucher[20];
    sprintf(coucher,"%lf",HetD[2]);//heure levé
    astro_heure_coucher=coucher;

    ui->lineEdit_6->setText(astro_heure_coucher);
    //int Jourrrr = date.day();
    //sprintf(Jourrrr,"%lf");
    //QString jour = jour.toString();*/


    ui->lineEdit_6->setText(Heure_coucher);


}
