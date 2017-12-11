#include "g2serveurtcpmonoclient.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

using namespace std;

G2ServeurTCPMonoClient::G2ServeurTCPMonoClient()
{
	m_socketEcoute = socket ( AF_INET, SOCK_STREAM, IPPROTO_TCP );
	if ( m_socketEcoute == -1 )
	{
		cout << "Création de la socket d'écoute : ECHEC." << endl;
		return ;
	}
	cout << "Création de la socket d'écoute : OK." << endl;

}

G2ServeurTCPMonoClient::~G2ServeurTCPMonoClient()
{
	fermerLaCommunicationAvecLeClient();
	arreterLeServeur();
}

bool G2ServeurTCPMonoClient::mettreEnEcouteSurLePort(unsigned short portEcoute)
{
	if(m_socketEcoute == -1)
	{
		return false;
	}
	m_portEcoute = portEcoute;

	struct sockaddr_in addrMonServeur;
	addrMonServeur.sin_family = AF_INET;
	// Ecoute sur le port 4222
	addrMonServeur.sin_port = htons(m_portEcoute);
	// Ecoute sur toutes les adresses IP de ma machine
	addrMonServeur.sin_addr.s_addr = INADDR_ANY;
	if ( bind ( m_socketEcoute, ( struct sockaddr * ) &addrMonServeur, sizeof ( addrMonServeur )  ) < 0 )
	{
		cout << "Association à un port : ECHEC." << endl;
		return false;
	}

	cout << "Association à un port : OK." << endl;

	// Mise en écoute du serveur
	if (listen(m_socketEcoute,1) == -1) {
		cout << "Mise en écoute : ECHEC." << endl;
		return false;
	}
	cout << "Mise en écoute : OK." << endl;
	return true;
}

bool G2ServeurTCPMonoClient::attendreUnNouveauClient()
{
	if(m_socketEcoute == -1)
	{
		return false;
	}
	struct sockaddr_in addrClient;
	int addrClientLen = sizeof(addrClient);
	m_socketDeCommunication = accept(m_socketEcoute,(struct sockaddr*)&addrClient, (socklen_t *) &addrClientLen);
	if(m_socketDeCommunication <= 0)
	{
		cout << "Client accepté : ECHEC." << endl;
		return false;
	}

	cout << "Client accepté : OK." << endl;
	return true;
}

int G2ServeurTCPMonoClient::recevoirUnMessage(char message[], int longueurMaxDuMessage)
{
	int nbOctets = recv(m_socketDeCommunication, message, longueurMaxDuMessage, 0);
	//string str(message, nbOctets);
	//cout << "Message du client (" << nbOctets << " octets) : " << str << endl;
	return nbOctets;
}

int G2ServeurTCPMonoClient::envoyerUnMessage(char message[], int longueurDuMessage)
{
	int nbOctets = send(m_socketDeCommunication, message, longueurDuMessage, 0);
	return nbOctets;

}

void G2ServeurTCPMonoClient::fermerLaCommunicationAvecLeClient()
{
	// Fermeture de la connexion avec le client
	close(m_socketDeCommunication);
	cout << "Fermeture de la communication avec le client : OK." << endl;
}

void G2ServeurTCPMonoClient::arreterLeServeur()
{
	// Fermeture de la socket d'écoute
	close(m_socketEcoute);
	cout << "Arrêt du serveur : OK." << endl;

}

