#include <stdio.h>
#include <string>
#include "mainwindow.h"
#include "QtSerialPort"
#include <iostream>
#include "PortComDI.h"
#include <QThread>
#define NBCARLORA 1000

#ifndef LORAM2M_H
#define LORAM2M_H

//19200 bauds 8N1 no control
/*
"+++" pour mode AT
"ATF" factory
"ATR" reset
"ATQ" quit mode AT
*/
class LoRaM2M
{
    private:
        string comLoRa;
        bool ouvertLoRa;
        QSerialPort portComLoRa;
        char message[NBCARLORA];

    public:
        LoRaM2M();
        void ConfigurationUsine();
        void RemiseAZero();
        void EnvoiTrame(char mess[NBCARLORA]);
        QString ReceptionTrame(int &nbCaractRecus);
        void ModifierCOM(string scom);
        bool OuvrirCOM();  //false si erreur
        void FermerCOM();
       // QString SauveMessage;

};

#endif // LORAM2M_H
