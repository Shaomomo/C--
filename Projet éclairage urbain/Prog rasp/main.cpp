#include <stdio.h>
#include <iostream>
#include <fstream>
#include "serveurLORA.h"
#include <string>
#include <pthread.h>
#include <thread>
#include "serveurTCP.h"
#include "serveurHTTP.h"
#include <unistd.h>
#include "VSCOM.h"
#include "SNIRconversions.h"
#include <time.h>


using namespace std;

const std::string currentDateTime() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
	// for more information about date/time format
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	return buf;
}

// Définition des ports
	string nomDuPort_LORA, nomDuPort_VSCOM = "/dev/ttyUSB1"; int numDuPort_TCP, numDuPort_HTTP = 8080;
// Déclaration des objets
	SERVEURLORA LORA ; SERVEURTCP TCP ; SERVEURTCP TCP_HTTP ; SERVEURHTTP HTTP; CREATIONHTML HTML; VSCOM VSCOM;
	DonneeCAN extractCAN;
	MessageCANetendu Mcan;
// Déclaration des variables globale
	string messageRecu, messageArretServeur, string_messageTCPtoCAN = ""; 
	int nbOct = 0;
	char messageDuClient[1000]; char sendMessage[23] = "Reception serveur : OK"; 
	string str_Reception_VSCOM;
// Déclaration objet type fichier
	string nomFichier_defauts = "ressourcesTXT/fiche_defauts.txt";
	ofstream F_DEFAUTS(nomFichier_defauts.c_str(), ios::app);
//

//

void * thread_EcouteLora( void * pData ){ 
	string temp_string = "";
	while (1) {
		messageRecu = LORA.lireMessage();
		sleep(1);
		if ( messageRecu.length() > 2 ){
			cout << "Serveur Lora. Taille : " << messageRecu.length() << " - Message : "<< messageRecu << endl ;
			//VSCOM.EnvoiTrameCAN(messageRecu);
		/*	temp_string*/messageRecu=Mcan.ConstruitTrameVSCOM(extractCAN, false);
                        VSCOM.EnvoiTrameCAN(/*temp_string*/messageRecu); }
                        string_messageTCPtoCAN = "";	}
}

void * thread_EcouteVSCOM( void * pData ){ 
	while (1) {
		str_Reception_VSCOM = VSCOM.ReceptionTrame();
		if(str_Reception_VSCOM != ""){
			cout << "Trame recue : " << str_Reception_VSCOM << endl;
			extractCAN = Mcan.ExtraitDonneeTrameVSCOM(str_Reception_VSCOM);
			if(extractCAN.identifiant == 8193){
				cout << "DEFAUT" <<endl;
				int recup_alarmes_defauts = extractCAN.donnee[1];
				int recup_alarmes_defauts_base2 = SNIR::dec2bin(recup_alarmes_defauts);
		        std::string recup_tab_alarmes_defauts = SNIR::DecToString(recup_alarmes_defauts_base2);
				int i = 0 ;
		        while(recup_tab_alarmes_defauts.length() < 8){
		            recup_tab_alarmes_defauts = "0" + recup_tab_alarmes_defauts;
		        }
		        cout << "Valeur binaire de l'octet recu : " << recup_tab_alarmes_defauts << endl;
		        string defaut_igbt;
		        if(recup_tab_alarmes_defauts[7] == '0'){
		            defaut_igbt = "Pas de défaut IGBT";
		        }
		        else if(recup_tab_alarmes_defauts[7] == '1'){
		            defaut_igbt = "Défaut IGBT";
		        }
		        string defaut_fusible;
		        if(recup_tab_alarmes_defauts[6] == '0'){
		            defaut_fusible = "Pas de défaut fusion fusible";
		        }
		        else if(recup_tab_alarmes_defauts[6] == '1'){
		            defaut_fusible = "Défaut fusion fusible";
		        }
		        string alarme_alim_interne;
		        if(recup_tab_alarmes_defauts[5] == '0'){
		            alarme_alim_interne = "Pas d'alarme d'alimentation interne 5V";
		        }
		        else if(recup_tab_alarmes_defauts[5] == '1'){
		            alarme_alim_interne = "Alarme alimentation interne 5V";
		        }
		        string alarme_te_entree;
		        if(recup_tab_alarmes_defauts[4] == '0'){
		            alarme_te_entree = "Pas d'alarme tension entrée 230V";
		        }
		        else if(recup_tab_alarmes_defauts[4] == '1'){
		            alarme_te_entree = "Alarme tension entrée 230V";
		        }
		        string alarme_temp_radiateur;
		        if(recup_tab_alarmes_defauts[3] == '0'){
		            alarme_temp_radiateur = "Pas d'alarme température radiateur";
		        }
		        else if(recup_tab_alarmes_defauts[3] == '1'){
		            alarme_temp_radiateur = "Alarme température radiateur";
		        }
		        string alarme_temp_air_ambiant;
		        if(recup_tab_alarmes_defauts[2] == '0'){
		            alarme_temp_air_ambiant = "Pas d'alarme température air ambiant";
		        }
		        else if(recup_tab_alarmes_defauts[2] == '1'){
		            alarme_temp_air_ambiant = "Alarme température air ambiant";
		        }
		        string alarme_sonde_temp;
		        if(recup_tab_alarmes_defauts[1] == '0'){
		            alarme_sonde_temp = "Pas d'alarme : sonde temérature débranchée";
		        }
		        else if(recup_tab_alarmes_defauts[1] == '1'){
		            alarme_sonde_temp = "Alarme Sonde température débranchée";
		        }
		        string alarme_temp_transfo;
		        if(recup_tab_alarmes_defauts[0] == '0'){
		            alarme_temp_transfo = "Pas d'alarme température transformateur (surcharge)";
		        }
		        else if(recup_tab_alarmes_defauts[0] == '1'){
		            alarme_temp_transfo = "Alarme température transformateur (surcharge)";
		        }
		        int alarme_horloge = extractCAN.donnee[0];
		        int alarme_horloge_base2 = SNIR::dec2bin(alarme_horloge);
		        std::string alarme_tab_horloge = SNIR::DecToString(alarme_horloge_base2);
		        while(alarme_tab_horloge.length() < 8){
		            alarme_tab_horloge = "0" + alarme_tab_horloge;
		        }
		        string alarme_horloge_txt;
		        if(alarme_tab_horloge[7] == '0'){
		            alarme_horloge_txt = "Pas d'alarme horloge";
		        }
		        else if(alarme_tab_horloge[7] == '1'){
		            alarme_horloge_txt = "Alarme horloge";
		        }
				if(F_DEFAUTS){
		        	F_DEFAUTS << ";17/05/2017;11:10'55;" << defaut_igbt << ";" << endl;
		        	F_DEFAUTS << ";17/05/2017;11:10'55;" << defaut_fusible << ";" << endl;
		        	F_DEFAUTS << ";17/05/2017;11:10'55;" << alarme_alim_interne << ";" << endl;
		        	F_DEFAUTS << ";17/05/2017;11:10'55;" << alarme_te_entree << ";" << endl;
		        	F_DEFAUTS << ";17/05/2017;11:10'55;" << alarme_temp_radiateur << ";" << endl;
		        	F_DEFAUTS << ";17/05/2017;11:10'55;" << alarme_temp_air_ambiant << ";" << endl;
		        	F_DEFAUTS << ";17/05/2017;11:10'55;" << alarme_sonde_temp << ";" << endl;
		        	F_DEFAUTS << ";17/05/2017;11:10'55;" << alarme_temp_transfo << ";" << endl;
		        	F_DEFAUTS << ";17/05/2017;11:10'55;" << alarme_horloge_txt << ";" << endl;
				}
		    } //Fin du if 'je suis un défaut'
		} //Fin du if 'c'est un message'
	}//Fin de la boucle
}

void * thread_ServeurTCP (void * pDataBis ){ 
	while(1){
		TCP.attendreUnNouveauClient();
		nbOct = TCP.recevoirUnMessage(messageDuClient,1000);
		string str(messageDuClient, nbOct); messageArretServeur = str;
		cout << "Serveur TCP : " << str << "." << endl; 
		string_messageTCPtoCAN = str;
		TCP.envoyerUnMessage(sendMessage, 23);
		TCP.fermerLaCommunicationAvecLeClient();
	}
}

void * thread_ServeurWeb (void * pDataBis ){ 
	while(1){
		TCP_HTTP.attendreUnNouveauClient();
        char messageDuClient[1000]; int nbOct = TCP_HTTP.recevoirUnMessage(messageDuClient, 1000);string str(messageDuClient, nbOct);
        
        if(HTML.VerrifMessage(messageDuClient)) HTML.CreateRueFile();
		HTTP.ChargeDernierMessage(str);
		string dernierMessage = HTTP.DernierMessage();
        if(HTTP.AnalyseGET()){
            string nomRessourceDemandee=HTTP.NomRessourceDemandee(); string extensionDemandee=HTTP.ExtensionDemandee();
            char *buffer=HTTP.BufferRessourceDemandee(); int tailleRessource = HTTP.TailleRessourceDemandee();
            TCP_HTTP.envoyerUnMessage(buffer,tailleRessource);

            if(extensionDemandee=="jpg"||extensionDemandee=="txt"||extensionDemandee=="html"||extensionDemandee=="css"||extensionDemandee=="js"){
                cout<<"Ressource : "<<nomRessourceDemandee<<endl;
                cout<<"Extension : "<<extensionDemandee<<endl;
                cout<<"Taille : "<<tailleRessource<<endl;
            } else cout<<"Erreur : "<<buffer<<endl;
        }else cout<<"Ce n'est pas une requete HTTP"<<endl;
        TCP_HTTP.fermerLaCommunicationAvecLeClient();
	}
}

int main () {
	std::cout << "currentDateTime()=" << currentDateTime() << std::endl;
    getchar();
	pthread_t thread_lora ;
        pthread_t thread_vscom ;
        pthread_t thread_tcp ;
        pthread_t thread_tcp_http ;

// Lancement du serveur Lora
	cout << "Bienvenue sur le projet : Eclairage-Groupe-Quartier" << endl;
	cout << "Veuillez renseigner les ports des differents serveurs..." << endl;
	int  compteur_Lora = 0;
	do {
		if(compteur_Lora > 0)
			cout << "PORT LORA : ECHEC" << endl;
		cout << "Port du serveur Lora : " ;
		cin >> nomDuPort_LORA;
		cout << endl << "Initialisation du port ..." << endl;
		if(LORA.ouvrir(nomDuPort_LORA) == 0)
			break;
		compteur_Lora++;
	} while (1);
	cout << "PORT LORA : OK "<<endl;
	string trame_envoyer = "Lora_Projet_Eclairage : OK"; trame_envoyer + "\r\n" ;
	if ( LORA.envoyerTrame(trame_envoyer) == true ) cout << "Envoi message Lora : OK " << endl ;  
	else cout << "Envoi message Lora : ECHEC" << endl ;
	pthread_create(&thread_lora,NULL,thread_EcouteLora,NULL);
// Lancement serveur TCP
	cout << endl << endl;
	int compteur_tcp = 0;
	do {
		if(compteur_tcp > 0)
			cout << "Port non compatible ou echec lors de l'ouverture du Port..." << endl;
		cout << "Port du serveur TCP : ";
		cin >> numDuPort_TCP;
		cout << endl << "Initialisation du port ..." << endl;
		if(numDuPort_TCP > 999 && numDuPort_TCP < 65535) 
			if(TCP.mettreEnEcouteSurLePort(numDuPort_TCP))
				break;
		compteur_tcp++;
	} while(1);
	pthread_create(&thread_tcp,NULL,thread_ServeurTCP,NULL);
// Lancement du serveur WEB
	TCP_HTTP.mettreEnEcouteSurLePort(numDuPort_HTTP);
	HTTP.ModifieTailleMAXRessource(500000); HTTP.ModifieNomVariableJS("envoiValeur");
	pthread_create(&thread_tcp_http,NULL,thread_ServeurWeb,NULL);
// Lancement VSCOM
	VSCOM.ModifierCOM(nomDuPort_VSCOM);
	if(!VSCOM.OuvrirCOM()){ cout << "Echec de l'ouverture du port série" << endl; return -1;}
	usleep(10000);
	cout << "Connexion : " << VSCOM.ConnexionVSCOM() << endl;
	pthread_create(&thread_vscom,NULL,thread_EcouteVSCOM,NULL);
	sleep(2);
	VSCOM.EnvoiTrameCAN("T0000080075A090218011101");

	messageRecu = "" ;
	string temp_string="";
	while (1){
		if ( messageArretServeur == "stop" ) {
			pthread_cancel(thread_tcp);
			pthread_cancel(thread_lora);
			pthread_cancel(thread_tcp_http);
			TCP.arreterLeServeur();
			TCP_HTTP.arreterLeServeur();
			LORA.fermer();
			VSCOM.FermerCOM();
			return 0;
		}
		if(string_messageTCPtoCAN != ""){
			cout << "Envoi Message CAN ..." <<endl;
			temp_string=Mcan.ConstruitTrameVSCOM(extractCAN, false);
			VSCOM.EnvoiTrameCAN(temp_string);
			string_messageTCPtoCAN = "";
		}
	}
}

        
