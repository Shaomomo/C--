#ifndef LORAKIT_H
#define LORAKIT_H

#define NBCARLORA 1000

#include <QMainWindow>
#include <string>
#include <QSerialPort>
#include <QTimer>


using namespace std;

namespace Ui {
class LoraKit;
}

class LoraKit : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoraKit(QWidget *parent = 0);
    ~LoraKit();
    bool   EnvoiOK(char mess[NBCARLORA]);
    bool   ReceptionLoRaRecue(char mess[NBCARLORA]);
    bool FinModeReception(char mess[NBCARLORA]);
    void ModifierCOM(string scom);
    bool OuvrirCOM();  //false si erreur
    void FermerCOM();
    void   EnvoiModeReception();//true si OK
    void   EnvoiTrame(char mess[NBCARLORA]);//true si OK
    char* ReceptionTrame(int &nbCaractRecus);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::LoraKit *ui;
    string comLoRa;
    QTimer *timer;
    bool ouvertLoRa;
    char trameLoRa[NBCARLORA];
    int nbCaracteresTrames;
    char hexaASCII[2*NBCARLORA];
    char message[NBCARLORA];
    char * ModeRadio(int &nbCaractEnvoyes);
    char * ModeReception(int &nbCaractEnvoyes);
    char * TrameAEnvoyer(int &nbCaractEnvoyes, char mess[NBCARLORA]);
    //EnvoiTrame Utilise MessageVersHexaASCII()
    char * MessageVersHexaASCII(char mess[NBCARLORA]);
    char * TrameRecue(int &nbCaractRecus,char hexaASC[2*NBCARLORA]);
    //TrameRecue Utilise HexaASCIIVersMessage()
    char * HexaASCIIVersMessage(char hexaASC[2*NBCARLORA]);
    void   EnvoiWatchDog(int valeur);
    void   EnvoiModeRadio();
    void   EnvoiModeLora();
    QSerialPort SerialPort;

};

#endif // LORAKIT_H
