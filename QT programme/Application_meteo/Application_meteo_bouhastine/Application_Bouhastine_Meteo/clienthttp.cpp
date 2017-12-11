#include "clienthttp.h"



#ifdef _WIN32 || _WIN64
#include <winsock2.h>
#include <sys/types.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#endif
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;



int ClientHTTP::nbClientTCP = 0;

ClientHTTP::ClientHTTP()
{
	if(nbClientTCP == 0)
	{
		cout << "Bonjour" << endl;
#ifdef _WIN32 || _WIN64
		WSADATA wsaData ;
		int iResult;

		cout << "Bonjour 2 " << endl;

		iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
		if(iResult != 0)
		{
			cout << "Initialisation de la DLL Winsock : ERROR." << endl;
		}
		cout << "Initialisation de la DLL Winsock : OK." << endl;
#endif

	}

	nbClientTCP++;
}

bool ClientHTTP::connexionAuServeurParNomDeDomaine(string nomDeDomaine, unsigned short portServeur)
{
	// Création de la socket TCP
    m_maSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(m_maSocket == -1)
	{
		cout << "Creation de la socket : ERREUR" << endl;
		return false;
	}

	// Recherche de l'adresse IP du serveur de l'API
	char * hostName = "api.wunderground.com";
	struct hostent * host = NULL;
	host = gethostbyname(nomDeDomaine.c_str());
	if(host == NULL)
	{
		cout << "Nom de domaine : INTROUVABLE." << endl;
		return false;
	}
	//cout << "Nom de domaine : OK." << endl;

	m_portServeur = portServeur;

	// Connexion au serveur
	struct sockaddr_in serveurAJoindre;
	serveurAJoindre.sin_family = AF_INET;
	serveurAJoindre.sin_addr.s_addr = *(u_long *) host->h_addr;
	serveurAJoindre.sin_port = htons(m_portServeur);
	int resultat = connect(m_maSocket, (const struct sockaddr *) &serveurAJoindre, sizeof(serveurAJoindre));
	if(resultat != 0)
	{
		cout << "Connexion au serveur : ERREUR." << endl;
		return false;
	}
    //cout << "Connexion au serveur : OK" << endl;

	return true;

}


bool ClientHTTP::connexionAuServeurParAdresseIP(string adresseIPServeur, unsigned short portServeur)
{
	// Création de la socket TCP
    m_maSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(m_maSocket == -1)
	{
		cout << "Creation de la socket : :ERREUR." << endl;
		return false;
	}

	m_adresseIPServeur = adresseIPServeur;
	m_portServeur = portServeur;

	// Connexion au serveur
	struct sockaddr_in serveurAJoindre;
	serveurAJoindre.sin_family = AF_INET;
	serveurAJoindre.sin_addr.s_addr = inet_addr(m_adresseIPServeur.c_str());
	serveurAJoindre.sin_port = htons(m_portServeur);
	int resultat = connect(m_maSocket, (const struct sockaddr *) &serveurAJoindre, sizeof(serveurAJoindre));
	if(resultat != 0)
	{
		cout << "Connexion au serveur : ERREUR." << endl;
		return false;
	}

	return true;

}


bool ClientHTTP::envoyer(string requete)
{
	int resultat = send(m_maSocket, requete.c_str(), requete.length(), 0);
    if(resultat != requete.length())
	{
		cout << "Envoi du message : ERREUR." << endl;
		return false;
	}
	return true;
}

string ClientHTTP::recevoir()
{
	string messageRecu = "";
	int nbOctetsLus;
	int nbOctetsLusTotal = 0;
	int nbOctetsAttendus = 0;
	char buffer[1500];  // Lecture par bloc de 1500 octets
	bool encore = true;
	int contentLength = 0;
	do
	{
		nbOctetsLus = recv(m_maSocket, buffer, 1500, 0);
		//memcpy(reponse+nbOctetsLusTotal, buffer, nbOctetsLus);
		if(nbOctetsLusTotal == 0)
		{
			//cout << buffer << endl;
			string strBuffer(buffer);
			int pos = strBuffer.find("\r\n\r\n");
			messageRecu.append(buffer+pos+4, nbOctetsLus-(pos+4));
			//cout << "Pos : " << pos << endl;
			if(pos <= 0) return "";
				// Recherche de "Content-Length :"
				string chaineATrouver = "Content-Length: ";
				int pos2 = strBuffer.find(chaineATrouver);
				//cout << "Pos2 : " << pos2 << endl;
				if(pos2 <=0 ) return "";
				int pos3 = strBuffer.find("\r\n", pos2);
				//cout << "Pos3 : " << pos3 << endl;
				if(pos3 <= 0 ) return "";
				if (pos3 <= pos2+chaineATrouver.length()) return "";
				for(int i=pos2+chaineATrouver.length(); i<pos3; i++)
				{
					//cout << i << ":" << strBuffer[i] << endl;
					contentLength = contentLength*10 + (int)(strBuffer[i]-'0');
				}
				//cout << "Content-Length : " << contentLength << endl;
				nbOctetsAttendus = contentLength + pos + 4;
				//cout << "Nb octets attendus : " << nbOctetsAttendus << endl;
		}
		else
		{
			messageRecu.append(buffer, nbOctetsLus);
		}
		nbOctetsLusTotal += nbOctetsLus;
		//cout << "Nb octets lus : " << nbOctetsLus << endl;
		//cout << "Nb octets lus total : " << nbOctetsLusTotal << endl;

	}while(nbOctetsLusTotal < nbOctetsAttendus);
	//cout << "Fin de la lecture... " << endl;

	return messageRecu;
}


int ClientHTTP::recevoirBinaire(string nomDuFichier)
{
	ofstream fichierBinaire;
	int nbOctetsLus;
	int nbOctetsLusTotal = 0;
	int nbOctetsAttendus = 0;
	char buffer[1500];  // Lecture par bloc de 1500 octets
	bool encore = true;
	int contentLength = 0;

	fichierBinaire.open(nomDuFichier.c_str());

	do
	{
		nbOctetsLus = recv(m_maSocket, buffer, 1500, 0);
		//memcpy(reponse+nbOctetsLusTotal, buffer, nbOctetsLus);
		if(nbOctetsLusTotal == 0)
		{
			//cout << buffer << endl;
			string strBuffer(buffer);
			int pos = strBuffer.find("\r\n\r\n");
			if (pos <= 0 ) return -1;
			fichierBinaire.write(buffer+pos+4, nbOctetsLus-(pos+4));
			//cout << "Pos : " << pos << endl;
			// Recherche de "Content-Length :"
			string chaineATrouver = "Content-Length: ";
			int pos2 = strBuffer.find(chaineATrouver);
			//cout << "Pos2 : " << pos2 << endl;
			if(pos2 <=0 ) return -1;
			int pos3 = strBuffer.find("\r\n", pos2);
			//cout << "Pos3 : " << pos3 << endl;
			if(pos3 <= 0 ) return -1;
			if (pos3 <= pos2+chaineATrouver.length()) return -1;
			for(int i=pos2+chaineATrouver.length(); i<pos3; i++)
			{
				//cout << i << ":" << strBuffer[i] << endl;
				contentLength = contentLength*10 + (int)(strBuffer[i]-'0');
			}
			//cout << "Content-Length : " << contentLength << endl;
			nbOctetsAttendus = contentLength + pos + 4;
			//cout << "Nb octets attendus : " << nbOctetsAttendus << endl;
		}
		else
		{
			fichierBinaire.write(buffer, nbOctetsLus);
		}
		nbOctetsLusTotal += nbOctetsLus;
		//cout << "Nb octets lus : " << nbOctetsLus << endl;
		//cout << "Nb octets lus total : " << nbOctetsLusTotal << endl;

	}while(nbOctetsLusTotal < nbOctetsAttendus);
	//cout << "Fin de la lecture... " << endl;
	fichierBinaire.close();

	return nbOctetsLusTotal;
}




