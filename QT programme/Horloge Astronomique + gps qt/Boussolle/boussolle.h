#ifndef BOUSSOLLE_H
#define BOUSSOLLE_H
#include "string.h"
#include "QtSerialPort"
#include <QThread>
#include "QDate"

using namespace std;


class Boussolle
{
private:
    QSerialPort portboussolle;
    QDate date;

public:
    Boussolle();
    QString ReceptionMessage();
    QString message;
    bool ouvrirCOM();
    void fermerCOM();
    bool OuvrirBoussolle;
    void ModifierCOM(string scom);
    string combouss;
    void lever_et_coucher_sol(double Latitude, double Longitude, unsigned short Jour_du_Mois, unsigned char Mois, unsigned short an, double HetD[6]);




};

#endif // BOUSSOLLE_H
