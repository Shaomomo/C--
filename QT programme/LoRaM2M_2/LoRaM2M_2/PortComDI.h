// version pour Xe6
//////////////////////////////////////////////////////////////////////////////////////////////////
//Inclure ce fichier header : #include<PortCom.h>												//
//Exemple d'utilisation de la classe Rs232 :													//
//  Rs232 *PortCom1; 					//déclaration d'un pointeur sur portcom					//
//	PortCom1 = new Rs232("COM1"); 		//création de l’objet portcom		9600    8N1			//
//	PortCom1->configurer(CBR_9600,8,NOPARITY,ONESTOPBIT)										//
//	PortCom1->ouvrir();																			//
//	if (PortCom1->envoyer(0x02)!=-1)	//envoi du caractère 0x02 et test du port COM1			//
//	{	PortCom1->envoyer(0x30);		//envoi du caractère '0'								//
//		PortCom1->fermer();																		//
//	}																							//
//	delete PortCom1; 				//détruit notre objet portcom								//
//////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef RS232_H
#define RS232_H
//#include <Classes.hpp>
#include <windows.h>

#include <string>
using namespace std;

class Rs232
{	private:
			HANDLE Hportcom;
			DCB ConfigDCB;
			DWORD Noctlus;
			BYTE Parite,Nbstop,Nbbits;
			DWORD Vitesse;
            bool estOuvert;

	public:
            string  Nomport;
            Rs232(string nomport);
			void configurer(DWORD vitesse,BYTE nbbits,BYTE parite,BYTE nbstop);
            bool ouvrir(void);
			int envoyer (char);
			int recevoir(char*);
			void fermer(void);
            inline bool EstOuvert() {return estOuvert;}
};
#endif
