//---------------------------------------------------------------------------

#ifndef SERVEURHTTP_H
#define SERVEURHTTP_H
//---------------------------------------------------------------------------
#include <string>
#include <string.h>
#include <fstream>
#include <sstream>

#include "creationHTML.h"
using namespace std;

class SERVEURHTTP
{
	private:
		string dataTXT;
		string indexHTML;
		string httpOK, keepAlive,finHTTP,erreur404;
		string dernierMessage;
		bool cestUneDemande,cestUneImage;
		string nomRessourceDemandee;
		string extensionDemandee;
		string nomVariableJS;
		char * bufferRessourceDemandee;
		int tailleRessourceDemandee;
		int tailleMAXRessource;
		string texteRecu;

        CREATIONHTML searchDate;
	public:
        SERVEURHTTP();
		void EcritDataTxt(string texte);
		void ChargeDernierMessage(string texte);
		int AnalyseGET();	  // 0 GET non trouvé, 1 Ressource demandée, 2 Valeur reçue
		bool CestUneDemande();
		string DernierMessage();
		string NomRessourceDemandee();
		string ExtensionDemandee();
		char * BufferRessourceDemandee();
		int TailleRessourceDemandee();
		void LibereBuffer();
		string NomVariableJS();
		void ModifieNomVariableJS(string nomVariable);
		string TexteRecu();
		void ModifieTailleMAXRessource(int taille);
};
#endif
