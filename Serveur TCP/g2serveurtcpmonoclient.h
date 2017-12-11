#ifndef G2SERVEURTCPMONOCLIENT_H
#define G2SERVEURTCPMONOCLIENT_H

class G2ServeurTCPMonoClient
{
private:
    int m_socketEcoute;
    unsigned short m_portEcoute;
    int m_socketDeCommunication; // la socket permettant de communiquer avec le 'mono' client connecté

public:
    G2ServeurTCPMonoClient();
    ~G2ServeurTCPMonoClient();
    bool mettreEnEcouteSurLePort(unsigned short portEcoute);
    bool attendreUnNouveauClient();
    int envoyerUnMessage(char message[], int longueurDuMessage);
    int recevoirUnMessage(char message[], int longueurMaxDuMessage);
    void fermerLaCommunicationAvecLeClient();
    void arreterLeServeur();
};

#endif // G2SERVEURTCPMONOCLIENT_H
