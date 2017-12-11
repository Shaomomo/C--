#ifndef SNIMAGEH
#define SNIMAGEH
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#define TOUR 100
#define SEUILROND 100
#define ZONE 10
#define PROPORTIONCENTRE 1.30
#define AJUSTECENTRE 0
#define SEUILIMPACT 60
#define ZONEIMPACT 10
#define ZONEIMPACTCOLOREE 6
#define AJUSTETROU 2
#define PORPORTIONPOINTSDIAMETRE 19.5

using namespace std;

typedef struct {unsigned char bleu;unsigned char vert;unsigned char rouge;} Pixel;
typedef struct {int ligne; int colonne;} Coordonnee;

class SNImage
{       private:
		unsigned long dimensionMax;
		unsigned long tailleFile,offset;
		unsigned long tailleImage,tailleTete,zero,format,resoLarg,resoHaut;
	protected:
		Pixel **image;
		unsigned short sign;
		unsigned long largeur,hauteur;
	public:
		SNImage();
		~SNImage();
		inline unsigned short Signature(){return sign;}
		inline unsigned long Largeur(){return largeur;}
		inline unsigned long Hauteur(){return hauteur;}
		inline unsigned long TailleFichier(){return tailleFile;}
		inline unsigned long Offset(){return offset;}
		inline unsigned long TailleImage(){return tailleImage;}
		inline unsigned long TailleEntete(){return tailleTete;}
		inline unsigned long Format(){return format;}
		inline unsigned long ResolutionLargeur(){return resoLarg;}
		inline unsigned long ResolutionHauteur(){return resoHaut;}
		void Chargement(string nomFichier);
		void Sauvegarde(string nomFichier);
		void Tourne90Droite();
		void Tourne90Gauche();
		void Tourne180();
		void Negatif();
		void RetourneHorizontal();
		void RetourneVertical();
		void NiveauGris();
		void Eclaircit(int niveau);
		void Assombrit(int niveau);
		void SeuilleNoirBlanc(int niveau);
		void Colorie(Coordonnee coord,int l,int h,Pixel couleur);
		void Detoure(int largeurGauche,int largeurDroite,int largeurHaut,int largeurBas,Pixel couleur);
		void Recadre(Coordonnee coord,int l,int h);
		Coordonnee RechercheZone(int l,int h,Pixel couleur);
		void DessineCroix(Coordonnee coord,int taille,int epaisseur,Pixel couleur);
		void DessineCarre(Coordonnee coord,int taille,int epaisseur,Pixel couleur);
		void Dessine7Segments(Coordonnee coord,int taille,int epaisseur,Pixel couleur,string message);
		void Dessine11Segments(Coordonnee coord,int taille,int epaisseur,Pixel couleur,string message);
		void TraceDiagonaleUnPixel(Coordonnee debut,Coordonnee fin, Pixel couleur);
		void TraceDiagonale(Coordonnee debut,Coordonnee fin, int epaisseur, Pixel couleur);
		void TraceCercleUnPixel(Coordonnee centre, int rayon, Pixel couleur);
		void TraceCercle(Coordonnee centre, int rayon, int epaisseur, Pixel couleur);
		void ChangeCouleurSegment(Coordonnee coord,int taille,int epaisseur,Pixel couleur,char segment);//segment='a' 'b' 'c' 'd' 'e' 'f'

};
#endif



