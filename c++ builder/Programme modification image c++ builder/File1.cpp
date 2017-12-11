#pragma hdrstop
#pragma argsused

#ifdef _WIN32
#include <tchar.h>
#include <iostream>
#include <fstream>
#include "SNImage.h"
#include "Windows.h"
#include "Cible.h"
#include <string>
#else
  typedef char _TCHAR;
  #define _tmain main
#endif

#include <stdio.h>
 using namespace std;
 int _tmain(int argc, _TCHAR* argv[])

{
SNImage image;
	string img;
	cout << " choix de l'image D = desert et C = cible " << endl;
	cin >> img;


	if (img == "D") {

	cout << "Voici un menu vous permetant de modifier une image a votre guise" <<endl;
	cout << endl;
	cout << " afficher la taille de l'image : 1 " << endl;
	cout << " Retourner l'image a la vertical : 2" <<endl;
	cout << " Retourner l'image a l'horizontal : 3" <<endl;
	cout << " Afficher l'image en format n�gatif : 4" << endl;
	cout << " seuil noir et blanc : 5 " << endl;
	cout << " Rotation a droite (90�) : 6" << endl;
	cout<<" Rotation a 180� : 7"<<endl ;
	cout<<" Rotation a gauche (270�) : 8"<<endl ;
	cout << " Dessiner dans l'image : 9 " << endl;
	cout << " Dessiner croix : 10 " << endl;
	cout << " exit : 0" <<endl;
	int choix;
	cin >> choix;
	image.Chargement("Desert.bmp");

		if (choix == 1)
		{
			cout<<"Largeur: ";
			cout<<image.Largeur()<<endl;
			cout<<"Hauteur: " ;
			cout<<image.Hauteur()<<endl;
			image.Sauvegarde("image1.bmp");
		}

		if (choix == 2)
		{
			image.RetourneVertical();
			image.Sauvegarde("image2.bmp");
			cout<<"rotation vertical check"<<endl;
		}

		if (choix == 3)
		{
			image.RetourneHorizontal();
			image.Sauvegarde("image3.bmp");
			cout<<"rotation horizontal check" ;
		}

		if (choix == 4)
		{
			image.Negatif();
			image.Sauvegarde("image4.bmp");
			cout<<"	Negatif check" ;
		}

		if (choix == 5)
		{
			cout<<"choisir le seuil : ";
			int niveau;
			cin>>niveau;
			image.SeuilleNoirBlanc(niveau);
			image.Sauvegarde("image5.bmp");
			cout<<"seuillage fait"<<endl ;
		}

		 if (choix == 6)
		 {
			image.Tourne90Droite();
			image.Sauvegarde("image6.bmp");
			cout<<"Rotation a 90� a droite"<<endl ;
		 }

		 if (choix == 7)
		 {
			image.Tourne90Gauche();
			image.Sauvegarde("image7.bmp");
			cout<<"Rotation a 90� a gauche"<<endl ;
		 }

		 if (choix == 8)
		 {
			image.Tourne180();
			image.Sauvegarde("image8.bmp");
			cout<<"Rotation a 180�"<<endl ;
		 }


		 if (choix == 9 )
		 {
			int x, y, l, h, blue, red, green;

			cout<<"point de d�part ligne : ";
			cin>>x;
			cout<<"point de d�part colonne : ";
			cin>>y;
			cout<<"Distance horizontal : ";
			cin>>l;
			cout<<"Distance vertical : ";
			cin>>h;

			cout<<"code Couleur bleu: ";
			cin>>blue;

			cout<<"code Couleur vert: ";
			cin>>green;

			cout<<"code Couleur rouge: ";
			cin>>red;

			Coordonnee coord={x,y};
			Pixel couleur={blue,green,red};
			image.Colorie( coord,h,l,couleur);
			image.Sauvegarde("image9.bmp");
			cout<<"changement de couleur"<<endl ;

		 }

		 if (choix == 10)
		 {
			int  debut, taille, epaisseur, blue, red, green  ;

			cout<<"point de d�part ligne : ";
			cin>>debut;
			cout<<"epaisseur : ";
			cin>>epaisseur;
			cout<<"taille : ";
			cin>>taille;

			cout<<"code Couleur bleu: ";
			cin>>blue;

			cout<<"code Couleur vert: ";
			cin>>green;

			cout<<"code Couleur rouge: ";
			cin>>red;
			Coordonnee coord={debut,debut};
			Pixel couleur={blue,green,red};
			image.Colorie(coord,taille,epaisseur,couleur);
			image.Sauvegarde("image10.bmp");
			cout<<"changement de couleur"<<endl ;
		 }
		 if (choix == 0 ) {
			 exit(0);
		 }
	}

	if (img == "C" )
	{ int choix;
	 Cible maCible;
	 cout<<"choix possible : 1"<<endl ;
		cin >> choix;
		if (choix == 1)
		{
		 maCible.Chargement("image01.bmp");
		 maCible.recadrage();
		 cin.get();
		}
	}






}
