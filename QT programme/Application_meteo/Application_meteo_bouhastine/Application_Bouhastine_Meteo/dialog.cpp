#include "dialog.h"
#include "ui_dialog.h"
#include "requetewu.h"
#include <iostream>
#include <string>
#include "clienthttp.h"
#include <fstream>
#include <iostream>
#include "meteowu.h"
#include <QGraphicsPixmapItem>



Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_Rechercher_clicked()
{

    ville = ui->lineEdit_Ville->text().toStdString();
    pays = ui->lineEdit_Pays->text().toStdString();
    maThread = new ThreadMeteoWU(this);
    connect(maThread, SIGNAL(finished()), this, SLOT(afficherResultat()));
    maThread->start(); // Appel ensuite run()

    /*cout << "Nous allons vous presentez la meteo." << endl;
    MeteoWU meteo;
    meteo.rechercherMeteo(ville, pays);

    */

   /* string nomVillePays = meteo.extraireContenuEntreBalises("full", 0);
    cout <<"Voici la meteo dans la ville de ";
    cout << nomVillePays <<endl;

    string description = meteo.extraireContenuEntreBalises("weather", 0);
    cout <<"Actuellement le temps est ";
    cout << description <<endl;

    string temperature = meteo.extraireContenuEntreBalises("temp_c", 0);
    cout <<"La temperature est de ";
    cout << temperature <<endl;

    string temperatureRessentie = meteo.extraireContenuEntreBalises("feelslike_c", 0);
    cout <<"La temperature ressentie ";
    cout << temperatureRessentie <<endl;

    string directionVent = meteo.extraireContenuEntreBalises("wind_dir", 0);
    cout <<"Le vent va dans la direction ";
    cout << directionVent <<endl;

    string vitesseVent = meteo.extraireContenuEntreBalises("wind_kph", 0);
    cout <<"Le vent va a la vitesse de (Km/h): ";
    cout << vitesseVent <<endl;

    string icone = meteo.extraireContenuEntreBalises("icon_url", 0);
    cout << icone <<endl;
*/
}

void Dialog::afficherResultat()
{
    //MeteoWU meteo;
    //meteo.rechercherMeteo(ville, pays);

    //ConditionsActuelles CA = meteo.Actuellement();
    string meteojournaliere = "Nous allons vous presentez la meteo.\r\n";
    meteojournaliere += "Vous vous situez à " + CA.nomVillePays + "\r\n";
    meteojournaliere += "Description : " + CA.description + "\r\n";
    meteojournaliere += "temperature : " + CA.temperature+ "\r\n";
    meteojournaliere += "Temperature ressentie : " + CA.temperatureRessentie + "\r\n";
    meteojournaliere += "direction du vent : " + CA.directionVent + "\r\n";
    meteojournaliere += "Vitesse du vent : " + CA.vitesseVent + "\r\n";

    QString meteoj = (QString::fromStdString(meteojournaliere));
    QGraphicsTextItem * itemText = scene.addText(meteoj);
    itemText->setPos(-50,0);

     //ConditionsAVenir CF = meteo.Previsions(1);
    QString meteo_prevision = "Jour+1.\r\n";
    //meteo_prevision += "Vous vous situez à " + CF.date + "\r\n";
    meteo_prevision += "Description : " + QString::fromStdString(CF[1].description) + "\r\n";
    meteo_prevision += "temperature Max : " + QString::number(CF[1].temperatureMax) + "\r\n";
    meteo_prevision += "Temperature Min : " + QString::number(CF[1].temperatureMin) + "\r\n";
    meteo_prevision += "Vitesse Max : " + QString::number(CF[1].vitesseVentMax) + "\r\n";
    meteo_prevision += "Direction vent max : " + QString::fromStdString(CF[1].directionVentMax) + "\r\n";

    //QString meteo_p= (QString::fromStdString(meteo_prevision));

    QGraphicsTextItem * itemText2 = scene.addText(meteo_prevision);
    itemText2->setPos(-50,100);

    QString meteo_prevision1 = "Jour+2.\r\n";
    //meteo_prevision += "Vous vous situez à " + CF.date + "\r\n";
    meteo_prevision1 += "Description : " + QString::fromStdString(CF[2].description) + "\r\n";
    meteo_prevision1 += "temperature Max : " + QString::number(CF[2].temperatureMax) + "\r\n";
    meteo_prevision1 += "Temperature Min : " + QString::number(CF[2].temperatureMin) + "\r\n";
    meteo_prevision1 += "Vitesse Max : " + QString::number(CF[2].vitesseVentMax) + "\r\n";
    meteo_prevision1 += "Direction vent max : " + QString::fromStdString(CF[2].directionVentMax) + "\r\n";


    QGraphicsTextItem * itemText3 = scene.addText(meteo_prevision1);
    itemText3->setPos(-50,200);

    QString meteo_prevision2 = "Jour+3.\r\n";
    //meteo_prevision += "Vous vous situez à " + CF.date + "\r\n";
    meteo_prevision2 += "Description : " + QString::fromStdString(CF[3].description) + "\r\n";
    meteo_prevision2 += "temperature Max : " + QString::number(CF[3].temperatureMax) + "\r\n";
    meteo_prevision2 += "Temperature Min : " + QString::number(CF[3].temperatureMin) + "\r\n";
    meteo_prevision2 += "Vitesse Max : " + QString::number(CF[3].vitesseVentMax) + "\r\n";
    meteo_prevision2 += "Direction vent max : " + QString::fromStdString(CF[3].directionVentMax) + "\r\n";


    QGraphicsTextItem * itemText4 = scene.addText(meteo_prevision2);
    itemText4->setPos(-50,300);

}


void Dialog::on_graphicsView_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint)
{


}
