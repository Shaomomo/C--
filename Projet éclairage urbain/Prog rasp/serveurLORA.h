#ifndef SERVEURLORA_H
#define SERVEURLORA_H



#include <string.h>
#include <string>
using namespace std;

class SERVEURLORA
{		
public:
    SERVEURLORA();
    ~SERVEURLORA();
    int ouvrir(string nomDuPortSerie);
    int fermer();
    bool envoyerCaractere(const char c) const;
	  bool envoyerTrame(const char trame[]) const;
	  bool envoyerTrame(string trame) const;
    int lireMessage(char message[], int tailleMaximaleDuMessage) const;
    string lireMessage() const;
private:
    string m_nomDuPortSerie;
    int m_descripteurFichier;
    bool m_estOuvert;
};
#endif
