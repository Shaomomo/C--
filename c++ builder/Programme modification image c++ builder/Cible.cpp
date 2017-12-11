//---------------------------------------------------------------------------

#pragma hdrstop
#include <cmath>
#include "Cible.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

void Cible :: recadrage()
{
	Chargement("image01.bmp");
	Pixel blanc = { 255,255,255};
	Pixel bleu = {255, 0, 0};
	Pixel noir = {0, 0, 0};
	Pixel rouge = {0,0,255};
	Pixel vert = {0,255,0};

	Detoure(150,150,50,75, blanc);
	SeuilleNoirBlanc(70);
	Coordonnee coord = RechercheZone(20,20,noir);      //long - largeur - couleur
	Colorie (coord,20,20, bleu);

	Tourne180();

	Coordonnee coord2 = RechercheZone(20,20,noir);
	Colorie (coord2,20,20, rouge);

	Tourne180();

	Coordonnee centre;
	centre.ligne = (hauteur-coord2.ligne + coord.ligne) /2 ;
	centre.colonne= (coord.colonne+largeur-coord2.colonne)/2;
	DessineCroix(centre,20,2,vert);

	float c2_h = hauteur-coord2.ligne;
	float c2_l = largeur-coord2.colonne;
	float c1_h = coord.ligne;
	float c1_l = coord.colonne;
	float c_largeur = c2_l - c1_l;
	float c_hauteur = c2_h - c1_h;
	float diametre = (c_largeur*c_largeur) + (c_hauteur*c_hauteur);
	diametre = sqrt(diametre);
	float center = diametre/2;
	cout << " diametre : "  << diametre;
	cout << " centre : " << center;




	/*Diametre.colonne = coord2.colonne - coord.colonne;
	Diametre = ((Diametre.ligne*Diametre.ligne)+(Diametre.colonne*Diametre.colonne));
	Diametre =  sqrt(Diametre);
	cout << " Centre Ligne : " centre.ligne
	 */

	Sauvegarde("resultat.bmp");
	cin.get();

	//-----------------------------------------------------------

	Chargement("image01.bmp");
	Coordonnee carree;

	carree.ligne = centre.ligne-center  ;
	carree.colonne = centre.colonne - center;
	//DessineCarre(carree,diametre,3,rouge);

	Coordonnee carree2;
	carree2.ligne = centre.ligne - diametre*1.3;
	carree2.colonne = centre.colonne - diametre*1.3;
	float diametre_carree2 = diametre *2.60 ;
	//DessineCarre(carree2,diametre_carree2,3,rouge);
	Recadre(carree2, diametre * 2.60,diametre * 2.60);
	//Detoure(150,50,75, blanc);

	//Detoure(119,88,27,24, blanc);
	Sauvegarde("resultat2.bmp");

	//-----------------------------------------------------------

	Chargement("image01.bmp");

	Negatif();

	Sauvegarde("resultat3_negatif.bmp");

	SeuilleNoirBlanc(50);

	Sauvegarde("resultat3_negatif_seuille.bmp");


	Recadre(carree2, diametre * 2.50,diametre * 2.50);

	Sauvegarde("resultat3_neg_seuille_recadre.bmp");


	Coordonnee point[9];
	int i=0;

	// ecrire les coordonn�es de chaque impact dans un tableau de coordonn�es .
	// sachant que la structure de 'coordonn�es' est { ligne ; colonne } , nous pourrons acceder a chaque attribut
	// du tableau de coordonn�es precedement cr�er grace a 'Tab_coord[variable_compteur]' .
	/*


	*/


	do
	{

		point[i] = RechercheZone(10,10,noir);
		Colorie(point[i],10,10,bleu);
		Coordonnee carree3;
		DessineCarre(point[i],12,3,rouge);
		cout<<endl;
		cout<<"Voici les coordonnees des points : " ;
		cout<<endl ;
		cout <<  "point numero : " << i << " -----  ligne : " << point[i].ligne << " et colonne " << point[i].colonne << "." << endl;

		point[i].ligne = point[i].ligne+5; // car nous avons trac� un carre de 10 pixels
		point[i].colonne = point[i].colonne+5;

		cout<<endl;
		cout << " Et son centre a pour coordonnees : ligne -> " << point[i].ligne << " et pour colonne -> " << point[i].colonne << "." <<endl;
		DessineCroix(point[i],5,1,vert);
		i = i + 1 ;



	}while(point[i].ligne != -1 && point[i].colonne != -1 );

	Sauvegarde("resultat3_final.bmp");

	//-----------------------------------------------------------

	/*Tourne180();
	int j = 0;
	do
	{

		point[j] = RechercheZone(10,10,noir);
		//Colorie(point[i],10,10,bleu);
		//Coordonnee carree3;
		//DessineCarre(point[i],12,3,rouge);
		cout<<endl;
		cout<<"Voici les coordonnees des points : " ;
		cout<<endl ;
		cout <<  "point numero : " << j << " -----  ligne : " << point[j].ligne << " et colonne " << point[j].colonne << "." << endl;

		point[j].ligne = point[j].ligne+5; // car nous avons trac� un carre de 10 pixels
		point[j].colonne = point[j].colonne+5;

		cout<<endl;
		cout << " Et son centre a pour coordonnees : ligne -> " << point[j].ligne << " et pour colonne -> " << point[j].colonne << "." <<endl;
		DessineCroix(point[j],5,1,vert);
		j = j + 1 ;



	}while(point[j].ligne != -1 && point[j].colonne != -1 );

	Sauvegarde("resultat4.bmp");
	*/
	//-----------------------------------------------------------

 int k = 0;
	Chargement("image01.bmp");
	Recadre(carree2, diametre * 2.60,diametre * 2.60);
	/*do
	{
		point[k].ligne = point[k].ligne+5; // car nous avons trac� un carre de 10 pixels
		point[k].colonne = point[k].colonne+5;
		DessineCroix(point[k],5,1,vert);
		j = j + 1 ;

	}while(point[k].ligne != -1 && point[k].colonne != -1 );
	 */
	 Sauvegarde("resultat5.bmp");


}

Cible::Cible()
{


}


