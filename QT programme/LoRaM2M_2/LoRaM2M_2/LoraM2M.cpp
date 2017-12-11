#include "LoraM2M.h"
#include <iostream>

QString reponse;

LoRaM2M::LoRaM2M()
{
    strcpy(message,"");
    ouvertLoRa=false;
}
void LoRaM2M::ModifierCOM(string scom)
{
    comLoRa=scom;
}

bool LoRaM2M::OuvrirCOM()
{
        portComLoRa.setPortName(comLoRa.c_str());
        portComLoRa.setBaudRate(QSerialPort::Baud19200);
        portComLoRa.setDataBits(QSerialPort::Data8);
        portComLoRa.setParity(QSerialPort::NoParity);
        portComLoRa.setStopBits(QSerialPort::OneStop);
        portComLoRa.setFlowControl(QSerialPort::NoFlowControl);
        portComLoRa.open(QIODevice::ReadWrite);
        if(portComLoRa.write("\n")!=-1)	//envoi du 1er caractère du mode AT
         {   ouvertLoRa=true;
             Sleep(200);
         }
         return ouvertLoRa;
}

void LoRaM2M::FermerCOM()
{
    portComLoRa.close();
    ouvertLoRa=false;
}

void LoRaM2M::ConfigurationUsine()
{
    strcpy(message,"+++");
    if (ouvertLoRa)
    {
        portComLoRa.write(message);
        Sleep(200);
        strcpy(message,"ATF\r\n");
        portComLoRa.write(message);
        Sleep(200);
        strcpy(message,"ATQ\r\n");
        portComLoRa.write(message);
        Sleep(200);
    }
}

void   LoRaM2M::RemiseAZero()
{   strcpy(message,"+++");
    if(ouvertLoRa)
    {
        portComLoRa.write(message);
        Sleep(200);
        strcpy(message,"ATR\r\n");
        portComLoRa.write(message);
        Sleep(200);
    }
}

void   LoRaM2M::EnvoiTrame(char mess[NBCARLORA])
{   strcpy(message,mess);
    strcat(message,"\r\n");
    //for(int i=0;i<strlen(message);i++)
        portComLoRa.write(message);
}

QString LoRaM2M::ReceptionTrame(int &nbCaractRecus)
{
    //char TOctets[NBCARLORA]="";
        reponse+= portComLoRa.readAll();
        cout << reponse.toStdString()<<endl;

    //strcpy(message,reponse.toStdString().c_str());

    //return message;
    return reponse;
}
