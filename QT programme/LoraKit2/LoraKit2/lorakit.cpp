#include "lorakit.h"
#include "ui_lorakit.h"
#include "SNIRconversions.h"
#include <QDebug>
#include <QThread>


LoraKit::LoraKit(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoraKit)
{
    ui->setupUi(this);
    strcpy(trameLoRa,"");
    nbCaracteresTrames=0;
    ouvertLoRa=false;
}

LoraKit::~LoraKit()
{
    delete ui;
}

//Conversion du Message vers l'hexadecimal afin de pouvoir transmettre le message a la Lora.
char * LoraKit::MessageVersHexaASCII(char mess[NBCARLORA])
{	//Exemple: abcdj10->616263646A3130
    strcpy(message,mess);
    int j=0;
    for(int i=0;i<qstrlen(message);i++)
    {	string h=SNIR::HexToString(message[i]);
        hexaASCII[j++]=h[0];
        hexaASCII[j++]=h[1];
    }
    hexaASCII[j]=0;
    return hexaASCII;
}
//Conversion du message trasmit par la Lora en ASCII afin de pouvoir le lire et le comprendre.
char * LoraKit::HexaASCIIVersMessage(char hexaASC[2*NBCARLORA])
{	//616263646A3130->abcdj10
    strcpy(hexaASCII,hexaASC);
    int j=0;
    for(int i=10;i<qstrlen(hexaASCII)-2;i+=2)//on retire \r\n ainsi que les 10 premiers caractères (radio_rx  )
    {	 message[j++]=SNIR::ChaineHexaVersInt(&hexaASCII[i],2);
    }
    message[j]=0;
    return message;
}

char * LoraKit::ModeRadio(int &nbCaractEnvoyes)
{	strcpy(message,"mac pause\r\n");
    nbCaractEnvoyes=qstrlen(message);
    return message;
}

char * LoraKit::TrameAEnvoyer(int &nbCaractEnvoyes, char mess[NBCARLORA])
{	MessageVersHexaASCII(mess);
    strcpy(message,"radio tx ");
    strcat(message,hexaASCII);
    strcat(message,"\r\n");
    nbCaractEnvoyes=qstrlen(message);
    return message;
}

char * LoraKit::ModeReception(int &nbCaractEnvoyes)
{	strcpy(message,"radio rx 15\r\n");
    nbCaractEnvoyes=qstrlen(message);
    return message;
}

char * LoraKit::TrameRecue(int &nbCaractRecus,char hexaASC[2*NBCARLORA])
{   strcpy(hexaASCII,hexaASC);
    if(ReceptionLoRaRecue(hexaASC))
    {char messageradiorx[NBCARLORA]="radio_rx  ";
     strcat(messageradiorx,HexaASCIIVersMessage(hexaASC));
     strcpy(message,messageradiorx);
    }
    else
    strcpy(message,hexaASC);
    nbCaractRecus=qstrlen(message);
    //okradio_rx  0
    //busyradio_rx  0
    return message;
}

bool LoraKit::EnvoiOK(char mess[NBCARLORA])
{   string m=mess;
    if(m.find("radio_tx_ok")!=-1) return true;
    return false;
}
bool   LoraKit::ReceptionLoRaRecue(char mess[NBCARLORA])
{   string m=mess;
    if(m.find("radio_rx")!=-1) return true;
    return false;

}
bool LoraKit::FinModeReception(char mess[NBCARLORA])
{   string m=mess;
    if(m.find("radio_err")!=-1) return true;
    return false;
}
void LoraKit::ModifierCOM(string scom)
{    comLoRa=scom;
}
bool LoraKit::OuvrirCOM()
    {qDebug() <<"configuration du COM";
     QString comlora_qstring = (ui->lineEdit->text());
     comLoRa = comlora_qstring.toStdString();
     SerialPort.setPortName(comlora_qstring);
     SerialPort.open(QIODevice::ReadWrite);
     SerialPort.setBaudRate(QSerialPort::Baud57600);
     SerialPort.setDataBits(QSerialPort::Data8);
     SerialPort.setParity(QSerialPort::NoParity);
     SerialPort.setStopBits(QSerialPort::OneStop);
     SerialPort.setFlowControl(QSerialPort::NoFlowControl);

     if((SerialPort.write("m"))!=-1)	//envoi du 1er caractère du mode radio test du port COM1
     {   ouvertLoRa=true;
         EnvoiModeRadio();
         // vérifier la bonne reception de l'heure : la LoRa renvoi un chiffre
         timer = new QTimer(this);
         connect(timer, SIGNAL(timeout()), this, SLOT(updateCaption()));
         timer->start(200);
         int nb;
         char *message;
         message=ReceptionTrame(nb);
         //ShowMessage(message);
         if(message[0]<'0' || message[0]>'9')
         {  FermerCOM();
            return false;
         }
         //mode Lora
         EnvoiModeLora();
            timer->start(200);
         EnvoiWatchDog(0);
            timer->start(200);
         //passage en mode réception
         EnvoiModeReception();
         //Sleep(500);
     }
     return ouvertLoRa;
}
void LoraKit::FermerCOM()
{    SerialPort.close();
     //delete SerialPort;
     ouvertLoRa=false;
}

void   LoraKit::EnvoiModeRadio()
{   char *message;    //commence au 2ème caractère de mac pause
    int nb;
    if(ouvertLoRa)
    {	message=ModeRadio(nb);
         SerialPort.write(message);
    }
}
void   LoraKit::EnvoiModeLora()
{   char message[100]="radio set mod lora\r\n";
    if(ouvertLoRa)
    {	SerialPort.write(message);
    }
}
void   LoraKit::EnvoiWatchDog(int valeur)
{   char message[100]="radio set wdt ";
    strcat(message,SNIR::DecToString(valeur).c_str());
    strcat(message,"\r\n");
    if(ouvertLoRa)
    {	SerialPort.write(message);
    }
}
void   LoraKit::EnvoiModeReception()//true si OK
{   char *message;    //commence au 2ème caractère de mac pause
    int nb;
    if(ouvertLoRa)
    {	message=ModeReception(nb);
        SerialPort.write(message);
    }
}
void   LoraKit::EnvoiTrame(char mess[NBCARLORA])
{   char TOctets[1000];
    int Nb;
    char *message=TrameAEnvoyer(Nb, mess);
    SerialPort.write(message);
    //Sleep(200);
    //passage en mode réception
    //EnvoiModeReception();
    //Sleep(500);
}
char* LoraKit::ReceptionTrame(int &nbCaractRecus)
{   int Reponse;
    char TOctets[1000];
    int Nb=0;
    //char *message;
    do
    {
        Reponse=SerialPort.read(TOctets,1000);
    }while((TOctets[Nb++]!='\r')&&(Reponse>=0));
    TOctets[Nb]=0;
    nbCaractRecus=Nb;
    return TrameRecue(Nb,TOctets);
}



void LoraKit::on_pushButton_clicked()
{
    if (ui->pushButton->text()=="ouvrir")
    {
        ModifierCOM(comLoRa);
        if(OuvrirCOM())
        {
            timer = new QTimer(this);
            connect(timer, SIGNAL(timeout()), this, SLOT( ()));
            timer->start(100);
            ui->pushButton->setText("fermer");
            ouvertLoRa=true;

        }
    }else
    {
            FermerCOM();
            timer->stop();
            ui->pushButton->setText("ouvrir");
            ouvertLoRa=false;
    }
}

void LoraKit::on_pushButton_2_clicked()
{
    /*SerialPort.TrameAEnvoyer(ui->lineEdit_2->text());
    QString trame = SerialPort.readAll();
    ui->lineEdit_3->setText(trame);*/
}

