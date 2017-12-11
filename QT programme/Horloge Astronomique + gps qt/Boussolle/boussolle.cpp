#include "boussolle.h"

QString message;

Boussolle::Boussolle()
{
}

void Boussolle::ModifierCOM(string scom)
{
    combouss = scom;
}

bool Boussolle::ouvrirCOM()
{
    portboussolle.setPortName(combouss.c_str());
    portboussolle.setBaudRate(QSerialPort::Baud4800);
    portboussolle.setDataBits(QSerialPort::Data8);
    portboussolle.setParity(QSerialPort::NoParity);
    portboussolle.setStopBits(QSerialPort::OneStop);
    portboussolle.setFlowControl(QSerialPort::NoFlowControl);
    portboussolle.open(QIODevice::ReadWrite);
    OuvrirBoussolle = true;
    return OuvrirBoussolle;
}

void Boussolle::fermerCOM()
{
    portboussolle.close();
}

QString Boussolle::ReceptionMessage()
{   int pos_Lat_Long = 0 ;
    string contenu ;

    if(OuvrirBoussolle)
    {
        message += portboussolle.readAll();

        string m = message.toStdString();



        pos_Lat_Long = m.find("$GPGGA",0) ;
        if ( pos_Lat_Long != -1 && pos_Lat_Long > 65 ) contenu = m.substr(pos_Lat_Long , 72 ) ;
        if ( pos_Lat_Long != -1 && pos_Lat_Long < 65 ) contenu = m.substr(pos_Lat_Long , 46 ) ;


        message = contenu.c_str() ;

        /*if (m.find("$GPGGA"))
        {
            for (int i=0; i<2;i++)
            {
               //char m2 = m.strlen;
               if(m.find",")
               {

               }
            }
        }
//marche :$GPGGA,131253.000,4850.8136,N,00229.4251,E,0,00,,-58.9,M,47.3,M,,0000*6
// ne marche pas: n  $GPGGA,131235.102,,"LAT","LONG",,0,00,,,M,0.0,M,,0000*52
*/
        return message ;
    }


}
void Boussolle::lever_et_coucher_sol(double Latitude, double Longitude, unsigned short Jour_du_Mois, unsigned char Mois, unsigned short an, double HetD[])
{
    int j ;
    double Lat;
    int Erreur;
    int bissextile;

    int Jour;
    unsigned int u0;
    double declinaison;
    double h_Aube_CEE;

    Lat = Latitude * 3.1415926535897931 / 180.0;
    Erreur = 1;
    bissextile = 0;
    switch (an)
    {

        case 2017:

          j = 1461;
            break;

           case 2018:
            j = 1826;
            break;

           case 2019:
            j = 2191;
            break;

           case 2020:
            j = 2556;
            bissextile = 1;
            break;

           case 2021:
            j = 2922;
            break;

           case 2022:
            j = 3287;
            break;

           case 2023:
            j = 3652;
            break;

           default:
            j = 1461;
            Erreur = 0;
            break;
    }

          switch (Mois)
          {
           case 1:
            Jour = Jour_du_Mois + j;
            if (Jour > 65535) {
              Jour = 65535;
            }
            break;

           case 2:
            Jour = Jour_du_Mois + j;
            if (Jour > 65535) {
              Jour = 65535;
            }

            u0 = Jour + 31U;
            if (u0 > 65535U) {
              u0 = 65535U;
            }

            Jour = (int)u0;
            break;

           case 3:
            Jour = Jour_du_Mois + j;
            if (Jour > 65535) {
              Jour = 65535;
            }

            u0 = Jour + 59U;
            if (u0 > 65535U) {
              u0 = 65535U;
            }

            Jour = (int)u0 + bissextile;
            if (Jour > 65535) {
              Jour = 65535;
            }
            break;

           case 4:
            Jour = Jour_du_Mois + j;
            if (Jour > 65535) {
              Jour = 65535;
            }

            u0 = Jour + 90U;
            if (u0 > 65535U) {
              u0 = 65535U;
            }

            Jour = (int)u0 + bissextile;
            if (Jour > 65535) {
              Jour = 65535;
            }
            break;

           case 5:
            Jour = Jour_du_Mois + j;
            if (Jour > 65535) {
              Jour = 65535;
            }

            u0 = Jour + 120U;
            if (u0 > 65535U) {
              u0 = 65535U;
            }

            Jour = (int)u0 + bissextile;
            if (Jour > 65535) {
              Jour = 65535;
            }
            break;

           case 6:
            Jour = Jour_du_Mois + j;
            if (Jour > 65535) {
              Jour = 65535;
            }

            u0 = Jour + 151U;
            if (u0 > 65535U) {
              u0 = 65535U;
            }

            Jour = (int)u0 + bissextile;
            if (Jour > 65535) {
              Jour = 65535;
            }
            break;

           case 7:
            Jour = Jour_du_Mois + j;
            if (Jour > 65535) {
              Jour = 65535;
            }

            u0 = Jour + 181U;
            if (u0 > 65535U) {
              u0 = 65535U;
            }

            Jour = (int)u0 + bissextile;
            if (Jour > 65535) {
              Jour = 65535;
            }
            break;

           case 8:
            Jour = Jour_du_Mois + j;
            if (Jour > 65535) {
              Jour = 65535;
            }

            u0 = Jour + 212U;
            if (u0 > 65535U) {
              u0 = 65535U;
            }

            Jour = (int)u0 + bissextile;
            if (Jour > 65535) {
              Jour = 65535;
            }
            break;

           case 9:
            Jour = Jour_du_Mois + j;
            if (Jour > 65535) {
              Jour = 65535;
        }

        u0 = Jour + 243U;
        if (u0 > 65535U) {
          u0 = 65535U;
        }

        Jour = (int)u0 + bissextile;
        if (Jour > 65535) {
          Jour = 65535;
        }
        break;

       case 10:
        Jour = Jour_du_Mois + j;
        if (Jour > 65535) {
          Jour = 65535;
        }

        u0 = Jour + 273U;
        if (u0 > 65535U) {
          u0 = 65535U;
        }

        Jour = (int)u0 + bissextile;
        if (Jour > 65535) {
          Jour = 65535;
        }
        break;

       case 11:
        Jour = Jour_du_Mois + j;
        if (Jour > 65535) {
          Jour = 65535;
        }

        u0 = Jour + 304U;
        if (u0 > 65535U) {
          u0 = 65535U;
        }

        Jour = (int)u0 + bissextile;
        if (Jour > 65535) {
          Jour = 65535;
        }
        break;

       case 12:
        Jour = Jour_du_Mois + j;
        if (Jour > 65535) {
          Jour = 65535;
        }

        u0 = Jour + 334U;
        if (u0 > 65535U) {
          u0 = 65535U;
        }

        Jour = (int)u0 + bissextile;
        if (Jour > 65535) {
          Jour = 65535;
        }
        break;

       default:
        Jour = 1;
        Erreur = 0;
        break;
      }

      bissextile = Jour - j;
      declinaison = 0.017453292519943295 * ((0.38 + 23.26 * sin(6.2831853071795862 * (double)Jour / 365.24 - 1.395)) + 0.375 * sin(12.566370614359172 * (double)Jour / 365.24 - 1.47));
      declinaison = 3.8197186342054881 * (2.0 * acos((-0.014543897651582656 - sin(Lat) * sin(declinaison)) / (cos(Lat) * cos(declinaison))));
      switch (an) {
       case 2017:
        /*  Année 2017 */
        if ((bissextile < 88) || (bissextile > 301)) {
          bissextile = 1;
        } else {
          bissextile = 2;
        }
        break;

       case 2018:
        if ((bissextile < 84) || (bissextile > 300)) {
          bissextile = 1;
        } else {
          bissextile = 2;
        }
        break;

       case 2019:
        if ((bissextile < 90) || (bissextile > 299)) {
          bissextile = 1;
        } else {
          bissextile = 2;
        }
        break;

       case 2020:
        if ((bissextile < 89) || (bissextile > 298)) {
          bissextile = 1;
        } else {
          bissextile = 2;
        }
        break;

       case 2021:
        if ((bissextile < 87) || (bissextile > 303)) {
          bissextile = 1;
        } else {
          bissextile = 2;
        }
        break;

       case 2022:
        if ((bissextile < 86) || (bissextile > 302)) {
          bissextile = 1;
        } else {
          bissextile = 2;
        }
        break;

       case 2023:
        if ((bissextile < 85) || (bissextile > 301)) {
          bissextile = 1;
        } else {
          bissextile = 2;
        }
        break;

       default:
        bissextile = 1;
        Erreur = 0;
        break;
      }

      Lat = ((12.0 + (double)bissextile) - 0.066666666666666666 * Longitude) + 0.016666666666666666 * ((7.36 * sin(6.2831853071795862 * (double)Jour /365.242 - 0.071) + 9.92 * sin(12.566370614359172 * (double)Jour / 365.242 + 0.357)) + 0.305 * sin(18.849555921538759 * (double)Jour / 365.242 + 0.256));
      h_Aube_CEE = Lat - declinaison / 2.0;
      Lat += declinaison / 2.0;

      HetD[0] = floor(h_Aube_CEE) * (double)Erreur;
      HetD[1] = floor((h_Aube_CEE - floor(h_Aube_CEE)) * 60.0) * (double)Erreur;
      HetD[2] = floor(Lat) * (double)Erreur;
      HetD[3] = floor((Lat - floor(Lat)) * 60.0) * (double)Erreur;
      HetD[4] = floor(declinaison) * (double)Erreur;
      HetD[5] = floor((declinaison - floor(declinaison)) * 60.0) * (double)Erreur;
/*HetD=[ Heure lever,
           minute Lever,
           Heure coucher,
             minute coucher,
             Durée du Jour (nombre d'heures)
             Durée du jour (nombre de minutes résiduelles) ]
  */
}
