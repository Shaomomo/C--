//-------------------------------------------------------------------------

#pragma hdrstop

#include "serveurHTTP.h"
#include <iostream>
using namespace std;
//---------------------------------------------------------------------------
#pragma package(smart_init)
SERVEURHTTP::SERVEURHTTP()
{
    string checkTheDate;
    checkTheDate = searchDate.CheckTheDate();

    dataTXT="www/data.txt";
	indexHTML="index.html";
    httpOK="HTTP/1.0 200 OK\r\nDate: "+checkTheDate+"\r\nServer: PROJET_SNIR\r\nContent-length: ";
    keepAlive="\r\nkeep-Alive: timeout=5, max=100\r\nContent-Type: text/";
	finHTTP="\r\n\r\n";
    erreur404="HTTP/1.0 404 Not Found\r\n\r\n";
	tailleRessourceDemandee=0;
	cestUneDemande=true;
	cestUneImage=false;
	nomVariableJS="mavaleurest";

    /*
     * Connection: Keep-Alive\r\n
    */
}
void SERVEURHTTP::EcritDataTxt(string texte)
{	ofstream f;
	f.open(dataTXT.c_str());
	f<<texte;
	f.close();
}
void SERVEURHTTP::ChargeDernierMessage(string texte)
{   dernierMessage=texte;
}
string SERVEURHTTP::DernierMessage()
{   return dernierMessage;
}
int SERVEURHTTP::AnalyseGET()  	  // 0 GET non trouvé, 1 Ressource demandée, 2 Valeur reçue
{	int numDepart = dernierMessage.find("GET ");
	if(numDepart != string::npos)
	{       int numFin = dernierMessage.find("HTTP");
			//envoi de la page index.html
			if(( numFin-1-(numDepart+5) == 0)||(dernierMessage.find("GET /?")!= string::npos))
			{       int debutTexteRecu=dernierMessage.find(nomVariableJS);
					nomRessourceDemandee = "index.html";
					if(debutTexteRecu==string::npos)
					{	cestUneDemande=true;
					}
					else
					{   cestUneDemande=false;
		cout<<"Envoi de donnees"<<endl;
                        int finTexteRecu=dernierMessage.find(" HTTP/1.0");
						if(finTexteRecu!=string::npos)
						{   texteRecu=dernierMessage.substr(debutTexteRecu+nomVariableJS.length()+1,finTexteRecu-debutTexteRecu-12);
						}
					}
			}
			else
			{       cestUneDemande=true;
					nomRessourceDemandee = dernierMessage.substr(numDepart+5, numFin-1-(numDepart+5));
					int positionPoint = nomRessourceDemandee.find(".");
					int positionEt = nomRessourceDemandee.find("&")-1;
					if (positionEt <= positionPoint) { positionEt = nomRessourceDemandee.length();}
					nomRessourceDemandee =  nomRessourceDemandee.substr(0,positionEt);
			}
			int positionPoint = nomRessourceDemandee.find(".");
			extensionDemandee = nomRessourceDemandee.substr(positionPoint+1, nomRessourceDemandee.length() -positionPoint);
			stringstream httpOKetLg; ifstream fichier;
			char *octets;
			bufferRessourceDemandee=new char [tailleMAXRessource];
			octets=new char [tailleMAXRessource];
			int i=0,j,lg,finentete;
			cestUneImage=!((extensionDemandee == "html") || (extensionDemandee == "css") || (extensionDemandee == "js") || (extensionDemandee == "txt"));
            nomRessourceDemandee=nomRessourceDemandee;
			if(!cestUneImage)
            {
                fichier.open(nomRessourceDemandee.c_str());
			}
			else
			{       fichier.open(nomRessourceDemandee.c_str(),std::fstream::binary);
			}
			if(fichier.is_open())
            {
                    cout << "Ouverture du fichier réussie" << endl;
                    while (!fichier.eof())   octets[i++]=fichier.get();
					lg=i-1;
					fichier.close();
					if(!cestUneImage)
                    {       httpOKetLg<<httpOK<<lg<<"\r\nkeep-Alive: timeout=5, max=100\r\nContent-Type: text/"<<extensionDemandee<<"\r\n\r\n";
					}
					else
                    {       httpOKetLg<<httpOK<<lg<<"\r\nkeep-Alive: timeout=5, max=100\r\nContent-Type: image/"<<extensionDemandee<<"\r\n\r\n";
					}
					strcpy(bufferRessourceDemandee,(httpOKetLg.str()).c_str());
					finentete=strlen(bufferRessourceDemandee);
					for(j=0;j<lg;j++)bufferRessourceDemandee[finentete+j]=octets[j];
					tailleRessourceDemandee=finentete+lg;
			}
			else
            {
                cout << "Ouverture du fichier impossible" << endl;
                strcpy(bufferRessourceDemandee,erreur404.c_str());
					tailleRessourceDemandee=strlen(bufferRessourceDemandee);
			}
			delete[] octets;
			if(cestUneDemande) return 1;
			return 2;
	}        //reste à gérer CestUneDemande + extraire données recues
	return 0;
}
bool SERVEURHTTP::CestUneDemande()
{   return cestUneDemande;
}
string SERVEURHTTP::NomRessourceDemandee()
{   return nomRessourceDemandee;
}
string SERVEURHTTP::ExtensionDemandee()
{   return extensionDemandee;
}
char * SERVEURHTTP::BufferRessourceDemandee()
{   return bufferRessourceDemandee;
}
int SERVEURHTTP::TailleRessourceDemandee()
{   return tailleRessourceDemandee;
}
void SERVEURHTTP::LibereBuffer()
{   delete[] bufferRessourceDemandee;
}
string SERVEURHTTP::TexteRecu()
{   return texteRecu;
}
string SERVEURHTTP::NomVariableJS()
{	return nomVariableJS;
}
void SERVEURHTTP::ModifieNomVariableJS(string nomVariable)
{	nomVariableJS=nomVariable;
}
void SERVEURHTTP::ModifieTailleMAXRessource(int taille)
{   tailleMAXRessource=taille;
}
