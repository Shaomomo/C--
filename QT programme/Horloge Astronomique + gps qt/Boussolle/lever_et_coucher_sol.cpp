/*
 * Primary and Secondary School License - for use in teaching and meeting
 * course requirements at primary and secondary schools only.  Not for
 * government, commercial, university, or other organizational use.
 *
 * lever_et_coucher_sol.c
 *
 * Code generation for function 'lever_et_coucher_sol'
 *
 */

/* Include files */
//#include "boussolle.h"
//#include "rt_nonfinite.h"
//#include "lever_et_coucher_sol.h"

/* Function Definitions */
void lever_et_coucher_sol(double Latitude, double Longitude, unsigned short
  Jour_du_Mois, unsigned char Mois, unsigned short an, double HetD[6])
{
  double Lat;
  int Erreur;
  int bissextile;
  int j;
  int Jour;
  unsigned int u0;
  double declinaison;
  double h_Aube_CEE;

  /*  Le programme demande la latitude, la longitude d'un point ,le jour du mois ,le mois et l'année. */
  /* Il remplit un tableau de réels (précision double) à 6 cases, nommé HetD à créer en variable globale */
  /*  Je me limite a un point dans hémisphère Nord. */
  /*  Le programme fournit l'Aube, le Coucher et la durée D du jour comptés tous 3  en heures et minutes  . */
  /*  Cela fonctionne à 4 minutes près ... */
  Lat = Latitude * 3.1415926535897931 / 180.0;

  /* RT=6371e3; */
  /* alphaT=23.43*pi/180; */
  Erreur = 1;

  /* alphaT= Angle inclinaison axe de rotation de la Terre par rapport à écliptique  */
  bissextile = 0;
  switch (an) {
   case 2017:
    /* case 2013 */
    /* j=0; */
    /* case 2014 */
    /* j=365; */
    /* case 2015 */
    /* j=365+365; */
    /* case 2016; */
    /* j=365+365+365; */
    j = 1461;

    /*  1461=365+365+365+366 <=> 31 Décembre 2016 */
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

  switch (Mois) {
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

  /* La déclinaison varie à peu près sinusoïdalement entre + et -23,45° au */
  /* cours d'une année: déclinaison = 23,45 *sin(2*pi*(J+284)/365) avec J = n° */
  /* du Jour "normal" dans une année... */
  /*  En réalité, la déclinaison est plus longtemps >0  (186j) que <0 (179j) au */
  /*  cours d'une année ... */
  declinaison = 0.017453292519943295 * ((0.38 + 23.26 * sin(6.2831853071795862 *
    (double)Jour / 365.24 - 1.395)) + 0.375 * sin(12.566370614359172 * (double)
    Jour / 365.24 - 1.47));

  /*  Durée en heures du jour, proportionnelle à l'angle balayé sur un cercle de latitude constante, entre les 2 point Aube et Coucher. */
  /* Avec une Correction de 50' due à la réfraction atmosphérique et au diamètre non nul du soleil */
  declinaison = 3.8197186342054881 * (2.0 * acos((-0.014543897651582656 - sin
    (Lat) * sin(declinaison)) / (cos(Lat) * cos(declinaison))));

  /*  Heure du zénith admin = Heure solaire Zénith + Avance Heure été/Hiver - Décalage de 4 min par degré de longitude (compté >0 vers EST) + Equation du temps  */
  /*  HZadmin=HZsol + delta_ete_hiver + deltaLongitude+ E. */
  /*  L'équation du temps vient du fait que la Terre tourne en 23h56 min sur elle-même ,tout en se déplaçant autour du soleil sur une ellipse ... */
  /*  E = 7.53*cos(B)+1.5*sin(B)-9.87*sin(2*B)    avec B = 2*pi*(journormal-81)/365 */
  /*  Une formule plus complexe tient compte de l'influence des autres */
  /*  planètes. */
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

  Lat = ((12.0 + (double)bissextile) - 0.066666666666666666 * Longitude) +
    0.016666666666666666 * ((7.36 * sin(6.2831853071795862 * (double)Jour /
    365.242 - 0.071) + 9.92 * sin(12.566370614359172 * (double)Jour / 365.242 +
    0.357)) + 0.305 * sin(18.849555921538759 * (double)Jour / 365.242 + 0.256));
  h_Aube_CEE = Lat - declinaison / 2.0;
  Lat += declinaison / 2.0;

  /* HetD(1,7)=h_Aube_CEE; */
  /* HetD(1,8)=h_Coucher_CEE; */
  /* HetD(1,9)=D; */
  HetD[0] = floor(h_Aube_CEE) * (double)Erreur;
  HetD[1] = floor((h_Aube_CEE - floor(h_Aube_CEE)) * 60.0) * (double)Erreur;
  HetD[2] = floor(Lat) * (double)Erreur;
  HetD[3] = floor((Lat - floor(Lat)) * 60.0) * (double)Erreur;
  HetD[4] = floor(declinaison) * (double)Erreur;
  HetD[5] = floor((declinaison - floor(declinaison)) * 60.0) * (double)Erreur;
}

/* End of code generation (lever_et_coucher_sol.c) */
