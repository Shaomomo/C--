#ifndef CLIENTHTTP_H
#define CLIENTHTTP_H

#include <string>
using namespace std;

class ClientHTTP
{
public:
    ClientHTTP();
    //bool connexionAuServeur(const char * adresseIPServeur, unsigned short portServeur);
    bool connexionAuServeurParAdresseIP(string adresseIPServeur, unsigned short portServeur);
    bool connexionAuServeurParNomDeDomaine(string nomDeDomaine, unsigned short portServeur);
    //bool envoyer(const char * requete, int longueurRequete);
    bool envoyer(string requete);
    string recevoir();
	int recevoirBinaire(string nomDuFichier);
    //int recevoir(char * reponse, int longueurMaxReponse);


private :
    static int nbClientTCP;
    int m_maSocket;
    string m_adresseIPServeur;
    unsigned short m_portServeur;
};

#endif // G2CLIENTTCP_H
