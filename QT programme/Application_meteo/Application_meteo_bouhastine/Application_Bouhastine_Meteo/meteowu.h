#ifndef METEOWU_H
#define METEOWU_H
#include <string>
#include "requetewu.h"
#include "clienthttp.h"
#include <fstream>
#include <iostream>


using namespace std;

typedef struct {
    string nomVillePays;		// full
    string description;			// weather
    string temperature;			// temp_c
    string temperatureRessentie;	// feelslike_c
    string directionVent;		// wind_dir
    string vitesseVent;			// wind_kph
    string urlIcone;			// icon_url
}ConditionsActuelles;



typedef struct {
	string jourSemaine;
	string mois;
	int jour;
	int annee;
}DatePrevision;



typedef struct {
	DatePrevision date;
    int temperatureMax;
    int temperatureMin;
	string description;
	string urlIcone;
    int vitesseVentMax;
	string directionVentMax;
}ConditionsAVenir;




class MeteoWU
{
public:
	MeteoWU();
    int rechercherMeteo( string ville,  string pays);
    ConditionsActuelles Actuellement();
    ConditionsAVenir Previsions(int numJour);
    string extraireContenuEntreBalises(string balise, int position=0);

private:
	RequeteWU requete;
	ClientHTTP clientWU;
	string reponseXML;
	ConditionsActuelles actuellement;
	ConditionsAVenir previsions[4];



};

#endif // METEOWU_H
