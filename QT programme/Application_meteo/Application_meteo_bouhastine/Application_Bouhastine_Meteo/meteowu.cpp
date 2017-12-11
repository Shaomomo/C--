#include "meteowu.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

MeteoWU::MeteoWU()
{
}

int MeteoWU::rechercherMeteo(string ville, string pays)
{
	requete.modifierVille(ville);
	requete.modifierPays(pays);
	string laRequete = requete.creerRequeteWU();
	std::cout << laRequete << std::endl;

	bool b = clientWU.connexionAuServeurParNomDeDomaine("api.wunderground.com", 80);
	if (!b)
		return -1;

	// Envoi de la requete
	b = clientWU.envoyer(laRequete);
	if(!b)
		return -1;

	reponseXML = clientWU.recevoir();

    if(reponseXML == "")
        return -1;

	ofstream meteoCourante;
	meteoCourante.open("meteoCourante.xml");
	meteoCourante << reponseXML;
	meteoCourante.close();

	cout << "Ouvrir le fichier meteoCourante.xml pour lire le resultat..." << endl;
	/*
	string delimiteur = "\r\n\r\n";
	int position = reponseHTTP.find(delimiteur);
	reponseXML = reponseHTTP.substr(position+4, reponseHTTP.length()-(position+4));

	cout << reponseXML <<endl;
*/
	cout << "Contenu entre les balises FEATURE : " << extraireContenuEntreBalises("feature") << endl;
	int positionCurrentObservation =  reponseXML.find("<current_observation>");
    cout << "Position Current observation : " << positionCurrentObservation << endl;
	if (positionCurrentObservation < 0) return -1;
	//cout << current_observation << endl;

	/*	typedef struct {
		string nomVillePays;		// full
		string description;			// weather
		int temperature;			// temp_c
		int temperatureRessentie;	// feelslike_c
		string directionVent;		// wind_dir
		int vitesseVent;			// wind_kph
		string urlIcone;			// icon_url
	}ConditionsActuelles; */

	// Extraction des données
    /*actuellement.nomVillePays = extraireContenuEntreBalises("full",positionCurrentObservation);
	actuellement.description = extraireContenuEntreBalises("weather", positionCurrentObservation);
    string temperature = extraireContenuEntreBalises("temp_c", positionCurrentObservation);
   // istringstream (temperature) >> actuellement.temperature;
	string temperatureRessentie = extraireContenuEntreBalises("feelslike_c", positionCurrentObservation);
   // istringstream (temperatureRessentie) >> actuellement.temperatureRessentie;
	actuellement.directionVent = extraireContenuEntreBalises("wind_dir", positionCurrentObservation);
	string vitesseVent = extraireContenuEntreBalises("wind_kph", positionCurrentObservation);
   // istringstream(vitesseVent) >> actuellement.vitesseVent;
	actuellement.urlIcone = extraireContenuEntreBalises("icon_url", positionCurrentObservation);
    */
    // Prevision journaliere
    actuellement.nomVillePays = extraireContenuEntreBalises("full",0);
    actuellement.description = extraireContenuEntreBalises("weather",0);
    actuellement.urlIcone = extraireContenuEntreBalises("icon_url",0);

    istringstream journalier1(extraireContenuEntreBalises("temp_c",0));
    journalier1 >> actuellement.temperature ;
    istringstream journalier2(extraireContenuEntreBalises("wind_dir",0)) ;
    journalier2 >> actuellement.directionVent ;
    istringstream journalier3(extraireContenuEntreBalises("wind_kph",0)) ;
    journalier3 >> actuellement.vitesseVent ;
    istringstream journalier4(extraireContenuEntreBalises("feelslike_c",0));
    journalier4 >> actuellement.temperatureRessentie ;

    // Prevision jour+1

   /* previsions[0].date = extraireContenuEntreBalises(" ",);
    previsions[0].description = extraireContenuEntreBalises(" ",);
    previsions[0].urlIcone = extraireContenuEntreBalises(" ",);

    istringstream prevision1(extraireContenuEntreBalises(" ",));
    prevision1 >> previsions[0].temperatureMax ;
    istringstream prevision2(extraireContenuEntreBalises(" ",)) ;
    prevision2 >> previsions[0].temperatureMin ;
    istringstream prevision3(extraireContenuEntreBalises(" ",)) ;
    prevision3 >> previsions[0].vitesseVentMax ;
    istringstream prevision4(extraireContenuEntreBalises(" ",)) ;
    prevision4 >> previsions[0].directionVentMax ;
*/
	//cout << reponseHTTP << endl;


	/*	typedef struct {
		DatePrevision date;			// date -> day, year, monthname, weekday
		int temperatureMax;			// high -> celsius
		int temperatureMin;			// low -> celsius
		string description;			// conditions
		string urlIcone;			// icon_url
		int vitesseVentMax;			// maxwind -> kph
		string directionVentMax;	// maxwind -> dir
	}ConditionsAVenir;*/

	// Extraction des données
	int positionSimpleForecast = reponseXML.find("<simpleforecast>", positionCurrentObservation);
    cout << "Position Simple forecast : " << positionSimpleForecast << endl;
	int positionForecastDay = positionSimpleForecast;
	for (int i = 0; i<4 ; i++)
	{
		positionForecastDay = reponseXML.find("<forecastday>", positionForecastDay);

		int positionDate = reponseXML.find("<date>", positionForecastDay);
		// Date
		string annee = extraireContenuEntreBalises("year", positionDate);
		istringstream (annee) >> previsions[i].date.annee;
		string jour = extraireContenuEntreBalises("day", positionDate);
		istringstream (jour) >> previsions[i].date.jour;
		previsions[i].date.jourSemaine = extraireContenuEntreBalises("weekday", positionDate);
		previsions[i].date.mois = extraireContenuEntreBalises("monthname", positionDate);
		// Temperature MAX
		int positionHigh = reponseXML.find("<high>", positionForecastDay);
		string temperatureMax = extraireContenuEntreBalises("celsius", positionHigh);
        cout << "Température MAX : " << temperatureMax << endl;
        istringstream (temperatureMax) >> previsions[i].temperatureMax;
		// Temperature MIN
		int positionLow = reponseXML.find("<low>", positionForecastDay);
		string temperatureMin = extraireContenuEntreBalises("celsius", positionLow);
        istringstream (temperatureMin) >> previsions[i].temperatureMin;
		// Description
		previsions[i].description = extraireContenuEntreBalises("conditions", positionForecastDay);
		// Icone URL
		previsions[i].urlIcone = extraireContenuEntreBalises("icon_url", positionForecastDay);

		// Vent max
		int positionMaxWind = reponseXML.find("<maxwind>", positionForecastDay);
		string vitesseVentMax = extraireContenuEntreBalises("kph", positionMaxWind);
        istringstream(vitesseVentMax) >> previsions[i].vitesseVentMax;
		previsions[i].directionVentMax = extraireContenuEntreBalises("dir", positionMaxWind);

		positionForecastDay++;
	}


	return 0;

}

string MeteoWU::extraireContenuEntreBalises(string balise, int position)
{
	string baliseOuvrante = "<" + balise + ">";
	string baliseFermante = "</" + balise +">";

	int posDepart = reponseXML.find(baliseOuvrante, position);
	if(posDepart < 0) return "";
	int posArrivee = reponseXML.find(baliseFermante, posDepart);
	if(posArrivee < 0) return "";
	return reponseXML.substr(posDepart+baliseOuvrante.length(), posArrivee-(posDepart+baliseOuvrante.length()));
}


ConditionsActuelles MeteoWU::Actuellement()
{
	return actuellement;
}


ConditionsAVenir MeteoWU::Previsions(int numJour)
{
	return previsions[numJour];
}


