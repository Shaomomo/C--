#ifndef SERVEURTCP_H
#define SERVEURTCP_H

class SERVEURTCP
{
private:
    int m_socketEcoute;
    unsigned short m_portEcoute;
    int m_socketDeCommunication; // la socket permettant de communiquer avec le 'mono' client connecté

public:
    SERVEURTCP();
    ~SERVEURTCP();
    bool mettreEnEcouteSurLePort(unsigned short portEcoute);
    bool attendreUnNouveauClient();
    int envoyerUnMessage(char message[], int longueurDuMessage);
    int recevoirUnMessage(char message[], int longueurMaxDuMessage);
    void fermerLaCommunicationAvecLeClient();

    void arreterLeServeur();


};

#endif // G2SERVEURTCPMONOCLIENT_H
