#include "serveurTCP.h"

#ifdef _WIN32 || _WIN64
#include <winsock2.h>
#include <sys/types.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#endif
#include <unistd.h>
#include <iostream>

using namespace std;
SERVEURTCP::SERVEURTCP()
{
#ifdef _WIN32 || _WIN64
        WSADATA wsaData ;
        int iResult;

        iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
        if(iResult != 0)
        {
            cout << "Initialisation de la DLL Winsock : ERROR." << endl;
        }
        cout << "Initialisation de la DLL Winsock : OK." << endl;
#endif

	m_socketEcoute = socket ( AF_INET, SOCK_STREAM, IPPROTO_TCP );
	if ( m_socketEcoute == -1 )
	{
        cout << "Creation de la socket d'écoute : ECHEC." << endl;
		return ;
	}
    cout << "Creation de la socket d'écoute : OK." << endl;

}

SERVEURTCP::~SERVEURTCP()
{
	fermerLaCommunicationAvecLeClient();
	arreterLeServeur();
}

bool SERVEURTCP::mettreEnEcouteSurLePort(unsigned short portEcoute)
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
        cout << "Association a un port : ECHEC." << endl;
		return false;
	}

    cout << "Association a un port : OK." << endl;

	// Mise en écoute du serveur
	if (listen(m_socketEcoute,1) == -1) {
        cout << "Mise en ecoute : ECHEC." << endl;
		return false;
	}
    cout << "Mise en ecoute : OK." << endl;
	return true;
}

bool SERVEURTCP::attendreUnNouveauClient()
{
	if(m_socketEcoute == -1)
	{
		return false;
	}
	struct sockaddr_in addrClient;
	int addrClientLen = sizeof(addrClient);
#ifdef _WIN32 || _WIN64
    m_socketDeCommunication = accept( m_socketEcoute,(struct sockaddr*)&addrClient, (int *) &addrClientLen);
#else
    m_socketDeCommunication = accept( m_socketEcoute,(struct sockaddr*)&addrClient, (socklen_t *) &addrClientLen);
#endif
    if(m_socketDeCommunication <= 0)
	{
        cout << "Client accepte : ECHEC." << endl;
		return false;
	}

    cout << "Client accepte : OK." << endl;
	return true;
}

int SERVEURTCP::recevoirUnMessage(char message[], int longueurMaxDuMessage)
{
	int nbOctets = recv(m_socketDeCommunication, message, longueurMaxDuMessage, 0);
	//string str(message, nbOctets);
	//cout << "Message du client (" << nbOctets << " octets) : " << str << endl;
	return nbOctets;
}

int SERVEURTCP::envoyerUnMessage(char message[], int longueurDuMessage)
{
	int nbOctets = send(m_socketDeCommunication, message, longueurDuMessage, 0);
	return nbOctets;

}

void SERVEURTCP::fermerLaCommunicationAvecLeClient()
{
	// Fermeture de la connexion avec le client
	close(m_socketDeCommunication);
	cout << "Fermeture de la communication avec le client : OK." << endl;
}

void SERVEURTCP::arreterLeServeur()
{
	// Fermeture de la socket d'écoute
	close(m_socketEcoute);
    cout << "Arret du serveur : OK." << endl;

}

