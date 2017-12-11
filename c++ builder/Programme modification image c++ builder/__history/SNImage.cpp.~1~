#include"SNImage.h"
SNImage::SNImage()
{   sign=0;largeur=0;hauteur=0;tailleFile=0;offset=0;tailleImage=0;
	tailleTete=0;format=0;resoLarg=0;resoHaut=0;dimensionMax=0;
}
SNImage::~SNImage()
{   //libération de la mémoire
	if(dimensionMax)
	{	for(int i=0;i<dimensionMax;i++)
			delete []image[i];
		delete []image;
	}
}
void SNImage::Chargement(string nomFichier)
{	ifstream entree;
	long i,j;char k; long h;
	unsigned long dimensionMaxPrecedente=dimensionMax;
	entree.open(nomFichier.c_str(),fstream::binary);
	//lecture entête image:
	entree.read((char*)&sign,2*sizeof(char));//signature (BM)=424D
	entree.read((char*)&tailleFile,sizeof(long));
	entree.read((char*)&zero,sizeof(long));
	entree.read((char*)&offset,sizeof(long));
	entree.read((char*)&tailleTete,sizeof(long));
	entree.read((char*)&largeur,sizeof(long));
	entree.read((char*)&hauteur,sizeof(long));
	entree.read((char*)&format,sizeof(long));
	entree.read((char*)&zero,sizeof(long));
	entree.read((char*)&tailleImage,sizeof(long));
	entree.read((char*)&resoLarg,sizeof(long));
	entree.read((char*)&resoHaut,sizeof(long));
	entree.read((char*)&zero,sizeof(long));
	entree.read((char*)&zero,sizeof(long));
	//calcul de k
	k=(4-(largeur*3)%4)%4;
	//remplissage tableau 2 dimensions
	i=hauteur-1;j=0;//i indice des lignes
	if(sign!=0x4D42) cout<<"Vous devez choisir un bitmap .bmp";
	else   if(format!=0x180001) cout<<"Vous devez choisir un bitmap 24 bits";
	else
	{   //libération éventuelle de la mémoire occupée par l'ancienne image
		if(dimensionMaxPrecedente)
		{	for(h=0;h<dimensionMaxPrecedente;h++)
				delete []image[h];
			delete []image;
		}
		if(hauteur>largeur) dimensionMax=hauteur;
		else dimensionMax=largeur;
		//réservation de la mémoire
		image=new Pixel*[dimensionMax];//i
		for(h=0;h<dimensionMax;h++)
			image[h]=new Pixel[dimensionMax];//j
		while(!entree.eof())
		{	entree.read((char*)&image[i][j].bleu,sizeof(char));
			entree.read((char*)&image[i][j].vert,sizeof(char));
			entree.read((char*)&image[i][j].rouge,sizeof(char));
			j++;
			if(j==largeur)
			{  	entree.seekg(k,ios_base::cur);
				j=0;i--;
			}
		}
	}
	entree.close();
}
void SNImage::Sauvegarde(string nomFichier)
{   ofstream sortie; int i,j; char k,z=0,n;
	sortie.open(nomFichier.c_str(),fstream::binary);
	k=(4-(largeur*3)%4)%4;
	sortie.write((char*)&sign,2*sizeof(char));
	sortie.write((char*)&tailleFile,sizeof(long));
	sortie.write((char*)&zero,sizeof(long));
	sortie.write((char*)&offset,sizeof(long));
	sortie.write((char*)&tailleTete,sizeof(long));
	sortie.write((char*)&largeur,sizeof(long));
	sortie.write((char*)&hauteur,sizeof(long));
	sortie.write((char*)&format,sizeof(long));
	sortie.write((char*)&zero,sizeof(long));
	sortie.write((char*)&tailleImage,sizeof(long));
	sortie.write((char*)&resoLarg,sizeof(long));
	sortie.write((char*)&resoHaut,sizeof(long));
	sortie.write((char*)&zero,sizeof(long));
	sortie.write((char*)&zero,sizeof(long));
	for(i=hauteur-1;i>=0;i--)
	{	for(j=0;j<largeur;j++)
		{   sortie.write((char*)&image[i][j].bleu,sizeof(char));
			sortie.write((char*)&image[i][j].vert,sizeof(char));
			sortie.write((char*)&image[i][j].rouge,sizeof(char));
		}
		//pixels de remplissage
		for(n=0;n<k;n++)
			sortie.write((char*)&z,sizeof(char));
	}
	 sortie.close();
}
void SNImage::Tourne90Droite()
{	int i,j;
	Pixel **temp;
	temp=new Pixel*[dimensionMax];//la hauteur de temp est la largeur de image
	for(i=0;i<dimensionMax;i++)
		temp[i]=new Pixel[dimensionMax];
	unsigned long htemp;
	for(i=0;i<hauteur;i++)
	{	for(j=0;j<largeur;j++)
		{	temp[j][(hauteur-1)-i]=image[i][j];
		}
	}
	htemp=hauteur;hauteur=largeur;largeur=htemp;
	for(i=0;i<hauteur;i++)
	{	for(j=0;j<largeur;j++)
		{	image[i][j]=temp[i][j];
		}
	}
	for(i=0;i<dimensionMax;i++)
		delete []temp[i];
	delete []temp;
}
void SNImage::Tourne180()
{   Tourne90Droite();
	Tourne90Droite();
}
void SNImage::Tourne90Gauche()
{   Tourne90Droite();
	Tourne180();
}
void SNImage::Negatif()
{	int i,j;
	for(i=0;i<hauteur;i++)
	{	for(j=0;j<largeur;j++)
		{	image[i][j].bleu=~(image[i][j].bleu);
			image[i][j].vert=~(image[i][j].vert);
			image[i][j].rouge=~(image[i][j].rouge);
		}
	}
}
void SNImage::RetourneHorizontal()
{	int i,j;
	Pixel temp;
	for(i=0;i<hauteur;i++)
	{	for(j=0;j<largeur/2;j++)
		{	temp=image[i][(largeur-1)-j];image[i][(largeur-1)-j]=image[i][j];image[i][j]=temp;
		}
	}
}
void SNImage::RetourneVertical()
{	int i,j;
	Pixel temp;
	for(i=0;i<hauteur/2;i++)
	{	for(j=0;j<largeur;j++)
		{	temp=image[(hauteur-1)-i][j];image[(hauteur-1)-i][j]=image[i][j];image[i][j]=temp;
		}
	}
}
void SNImage::NiveauGris()
{	int i,j;
	unsigned char rouge,vert,bleu,gris;
	for(i=0;i<hauteur;i++)
	{	for(j=0;j<largeur;j++)
		{	bleu=image[i][j].bleu;
			vert=image[i][j].vert;
			rouge=image[i][j].rouge;
			image[i][j].bleu=(bleu+vert+rouge)/3;
			image[i][j].vert=(bleu+vert+rouge)/3;
			image[i][j].rouge=(bleu+vert+rouge)/3;
		}
	}
}
void SNImage::Eclaircit(int niveau)
{	int i,j;
	for(i=0;i<hauteur;i++)
	{	for(j=0;j<largeur;j++)
		{	if((int)(image[i][j].bleu)+niveau<256) image[i][j].bleu=image[i][j].bleu+niveau; else image[i][j].bleu=255;
			if((int)(image[i][j].vert)+niveau<256) image[i][j].vert=image[i][j].vert+niveau; else image[i][j].vert=255;
			if((int)(image[i][j].rouge)+niveau<256) image[i][j].rouge=image[i][j].rouge+niveau; else image[i][j].rouge=255;
		}
	}
}
void SNImage::Assombrit(int niveau)
{	int i,j;
	for(i=0;i<hauteur;i++)
	{	for(j=0;j<largeur;j++)
		{	if((int)(image[i][j].bleu)-niveau>=0) image[i][j].bleu=image[i][j].bleu-niveau; else image[i][j].bleu=0;
			if((int)(image[i][j].vert)-niveau>=0) image[i][j].vert=image[i][j].vert-niveau; else image[i][j].vert=0;
			if((int)(image[i][j].rouge)-niveau>=0) image[i][j].rouge=image[i][j].rouge-niveau; else image[i][j].rouge=0;
		}
	}
}
void SNImage::SeuilleNoirBlanc(int niveau)
{	int i,j;
	NiveauGris();
	for(i=0;i<hauteur;i++)
	{	for(j=0;j<largeur;j++)
		{	if(image[i][j].bleu<niveau)
			{	image[i][j].bleu=0; image[i][j].vert=0; image[i][j].rouge=0;
			}
			else
			{	image[i][j].bleu=255; image[i][j].vert=255; image[i][j].rouge=255;
			}
		}
	}
}
void SNImage::Colorie(Coordonnee coord,int l,int h,Pixel couleur)
{   if((coord.ligne+h<=hauteur)&&(coord.colonne+l<=largeur))
	for(int i=coord.ligne;i<coord.ligne+h;i++)
	{	for(int j=coord.colonne;j<coord.colonne+l;j++)
		{	if(i>=0 && i<hauteur && j>=0 && j<largeur)
			{	image[i][j].bleu=couleur.bleu;
				image[i][j].vert=couleur.vert;
				image[i][j].rouge=couleur.rouge;
			}
		}
	}

}
void SNImage::Detoure(int largeurGauche,int largeurDroite,int largeurHaut,int largeurBas,Pixel couleur)
{   Coordonnee coor;
	coor.ligne=0;coor.colonne=0;
	Colorie(coor,largeurGauche,hauteur,couleur);
	Colorie(coor,largeur,largeurHaut,couleur);
	coor.ligne=0;coor.colonne=largeur-largeurDroite;
	Colorie(coor,largeurDroite,hauteur,couleur);
	coor.ligne=hauteur-largeurBas;coor.colonne=0;
	Colorie(coor,largeur,largeurBas,couleur);

}
void SNImage::Recadre(Coordonnee coord,int l,int h)
{   if((coord.ligne+h<=hauteur)&&(coord.colonne+l<=largeur))
	{   for(int i=0;i<h;i++)
		{	for(int j=0;j<l;j++)
			{	image[i][j]=image[i+coord.ligne][j+coord.colonne];
			}
		}
		largeur=l;hauteur=h;
		int k=(4-(largeur*3)%4)%4;
		tailleImage=(largeur+k)*(hauteur)*3;
		tailleFile=tailleImage+offset;
	}
}
Coordonnee SNImage::RechercheZone(int l,int h,Pixel couleur)
{   Coordonnee coord={-1,-1};
	int i,j,m,n;
	bool zoneTrouve;
	for(int i=0;i<hauteur;i++)
	{	for(int j=0;j<largeur;j++)
		{   if(image[i][j].bleu==couleur.bleu && image[i][j].vert==couleur.vert && image[i][j].rouge==couleur.rouge)
			{   zoneTrouve=true;
				for(int m=0;m<h;m++)
				{   for(int n=0;n<l;n++)
					{	if(image[i+m][j+n].bleu!=couleur.bleu || image[i+m][j+n].vert!=couleur.vert || image[i+m][j+n].rouge!=couleur.rouge)
							zoneTrouve=false;
					}
				}
				if(zoneTrouve)
				{   coord.ligne=i;
					coord.colonne=j;
					i=hauteur;
					j=largeur;
				}
			}
		}
	}
	return coord;
}

void SNImage::DessineCroix(Coordonnee coord,int taille,int epaisseur,Pixel couleur)
{       Coordonnee debut;
		debut.ligne=coord.ligne-taille/2;debut.colonne=coord.colonne-epaisseur/2;
		if(debut.ligne<0) debut.ligne=0;
		if(debut.colonne<0) debut.colonne=0;
		Colorie(debut,epaisseur,taille,couleur);
		debut.ligne=coord.ligne-epaisseur/2;debut.colonne=coord.colonne-taille/2;
		if(debut.ligne<0) debut.ligne=0;
		if(debut.colonne<0) debut.colonne=0;
		Colorie(debut,taille,epaisseur,couleur);
}
void SNImage::DessineCarre(Coordonnee coord,int taille,int epaisseur,Pixel couleur)
{       Coordonnee debut=coord;
		debut.ligne-=epaisseur/2;
		debut.colonne-=epaisseur/2;
		Colorie(debut,epaisseur,taille,couleur);//f ou e
		Colorie(debut,taille,epaisseur,couleur);//a
		debut.colonne+=taille;
		Colorie(debut,epaisseur,taille,couleur);//b ou c
		debut=coord;
		debut.ligne-=epaisseur/2;
		debut.colonne-=epaisseur/2;
		debut.ligne+=taille;
		Colorie(debut,taille+epaisseur,epaisseur,couleur);//g ou d
}
void SNImage::Dessine11Segments(Coordonnee coord,int taille,int epaisseur,Pixel couleur,string message)
{       int ligneDepart=coord.ligne;
		for(int i=0;i<message.length();i++)
		{       coord.ligne=ligneDepart;
				switch (message.c_str()[i])
				{       case '0':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'i');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'j');

								break;
						case '1':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'i');
								break;
						case '2':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case '3':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case '4':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case '5':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case '6':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case '7':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'i');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'j');
								break;
						case '8':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case '9':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'A':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'a':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'j');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								break;
						case 'B':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'i');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'k');
								break;
						case 'b':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'C':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								break;
						case 'c':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'D':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'h');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'k');
								break;
						case 'd':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'E':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'e':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'j');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								break;
						case 'F':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'f':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'i');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'j');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								break;
						case 'G':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'k');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								break;
						case 'g':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'i');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'h');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'j');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								break;
						case 'H':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'h':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'I':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'l');
								break;
						case 'i':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								break;
						case 'J':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								break;
						case 'j':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'i');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'j');
								break;
						case 'K':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'i');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'k');
								break;
						case 'k':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'k');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'L':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								break;
						case 'l':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'i');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'j');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								break;

						case 'M':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'i');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'h');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								break;
						case 'm':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'N':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'k');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'h');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								break;
						case 'n':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'j');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'k');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								break;
						case 'O':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								break;
						case 'o':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'P':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'p':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'i');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'j');
								break;
						case 'Q':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'k');
								break;
						case 'q':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'h');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'k');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'R':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'k');
								break;
						case 'r':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'S':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 's':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'k');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'T':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'l');
								break;
						case 't':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'i');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'j');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'U':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								break;
						case 'u':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								break;
						case 'V':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'j');
								break;
						case 'v':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'j');
								break;
						case 'W':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'j');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'k');
								break;
						case 'w':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'j');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'k');
								break;
						case 'X':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'h');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'i');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'j');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'k');
								break;
						case 'x':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'j');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'k');
								break;
						case 'Y':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'h');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'i');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'j');
								break;
						case 'y':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'i');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'j');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'h');
								break;
						case 'Z':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'i');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'j');
								break;
						case 'z':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'j');
								break;
						case '-':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
				}
				coord.colonne+=2*(taille/2);
				coord.ligne=ligneDepart;
		}
}
void SNImage::Dessine7Segments(Coordonnee coord,int taille,int epaisseur,Pixel couleur,string message)
{       int ligneDepart=coord.ligne;
		for(int i=0;i<message.length();i++)
		{       coord.ligne=ligneDepart;
				switch (message.c_str()[i])
				{       case '0':
						case 'D':
						case 'O':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'b');
                                ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
                                ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								break;
						case '1':
						case 'I':
						case 'l':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								break;
						case '2':
						case 'Z':
						case 'z':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
                                ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
                                break;
						case '3':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case '4':
						case 'Y':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case '5':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
                        case '6':
                                ChangeCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
                                ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
                                ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
                                break;
                        case '7':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'a');
                                ChangeCouleurSegment(coord,taille,epaisseur,couleur,'b');
                                ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								break;
						case '8':
						case 'B':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case '9':
						case 'g':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
												ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'A':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'b':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'C':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								break;
						case 'c':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'd':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'E':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'e':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'F':
						case 'f':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'G':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								break;
						case 'H':
						case 'h':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'i':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								break;
						case 'J':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
						case 'j':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								break;
						case 'k':
						case 'K':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'L':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								break;
						case 'M':
						case 'm':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								break;
						case 'N':
						case 'n':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;

						case 'o':
						case 'a':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'P':
						case 'p':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'Q':
						case 'q':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'R':
						case 'r':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'S':
						case 's':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'T':
						case 't':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'U':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								break;
						case 'u':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								break;
						case 'V':
						case 'W':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								break;
						case 'v':
						case 'w':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'e');
								break;
						case 'x':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								break;
						case 'X':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'a');
								break;
						case 'y':
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangeCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
				}
				coord.colonne+=2*(taille/2);
				coord.ligne=ligneDepart;
		}
}

void SNImage::ChangeCouleurSegment(Coordonnee coord,int taille,int epaisseur,Pixel couleur,char segment)//segment='a' 'b' 'c' 'd' 'e' 'f'
{       Coordonnee debut,fin;
		switch (segment)
		{       case 'a':
						debut=coord; debut.ligne-=epaisseur/2; debut.colonne-=epaisseur/2; Colorie(debut,taille/2+epaisseur,epaisseur,couleur); break;
				case 'b':
						debut=coord; debut.ligne-=epaisseur/2; debut.colonne-=epaisseur/2; debut.colonne+=taille/2; Colorie(debut,epaisseur,taille/2+epaisseur,couleur); break;
				case 'f':
						debut=coord; debut.ligne-=epaisseur/2; debut.colonne-=epaisseur/2; Colorie(debut,epaisseur,taille/2+epaisseur,couleur); break;
				case 'g':
						debut=coord; debut.ligne-=epaisseur/2; debut.colonne-=epaisseur/2; debut.ligne+=taille/2; Colorie(debut,taille/2+epaisseur,epaisseur,couleur); break;
				case 'c':
						debut=coord; debut.ligne-=epaisseur/2-taille/2; debut.colonne-=epaisseur/2; debut.colonne+=taille/2; Colorie(debut,epaisseur,taille/2+epaisseur,couleur); break;
				case 'e':
						debut=coord; debut.ligne-=epaisseur/2-taille/2; debut.colonne-=epaisseur/2; Colorie(debut,epaisseur,taille/2+epaisseur,couleur); break;
				case 'd':
						debut=coord; debut.ligne-=epaisseur/2-taille/2; debut.colonne-=epaisseur/2; debut.ligne+=taille/2; Colorie(debut,taille/2+epaisseur,epaisseur,couleur); break;
				case 'h':
						debut=coord;
						fin=debut; fin.ligne+=taille/2-1;fin.colonne+=taille/4-1;
						TraceDiagonale(debut,fin,epaisseur,couleur);
						break;
				case 'i':
						debut=coord;
						debut.colonne+=taille/2;
						fin=debut; fin.ligne+=taille/2-1;fin.colonne-=taille/4-1;
						TraceDiagonale(debut,fin,epaisseur,couleur);
						break;
				case 'j':
						debut=coord; debut.colonne+=taille/4;debut.ligne+=taille/2;
						fin=coord; fin.ligne+=taille-1; fin.colonne-=1;
						TraceDiagonale(debut,fin,epaisseur,couleur);
						break;
				case 'k':
						debut=coord; debut.ligne+=taille/2; debut.colonne+=taille/4;
						fin=debut; fin.ligne+=taille/2-1;fin.colonne+=taille/4-1;
						TraceDiagonale(debut,fin,epaisseur,couleur);
						break;
				case 'l':
						debut=coord; debut.ligne-=epaisseur/2; debut.colonne-=epaisseur/2; debut.colonne+=taille/4; Colorie(debut,epaisseur,taille+epaisseur,couleur); break;
		}
}
void SNImage::TraceDiagonaleUnPixel(Coordonnee debut,Coordonnee fin, Pixel couleur)
{   Pixel r={0,0,255},b={255,0,0},v={0,255,0},bl={255,255,255},n={0,0,0};
	int h=abs(debut.ligne-fin.ligne);
	int l=abs(debut.colonne-fin.colonne);
	int ajoutArrondi=0;
	if(h!=0 && l!=0)
	{	int kj=1,ki=1,manque;
		if(l>=h) {kj=l/h;manque=l-kj*h;if(manque){ajoutArrondi=l/manque; if(((float)l/manque-(int)(l/manque))>=0.5) ajoutArrondi++;}}
		else {ki=h/l;manque=h-ki*l;if(manque){ajoutArrondi=h/manque; if(((float)h/manque-(int)(h/manque))>=0.5) ajoutArrondi++;}}
		if(debut.ligne>fin.ligne)
		{   Coordonnee temp=fin;
			fin=debut;
			debut=temp;
		}
		int j=debut.colonne,i=debut.ligne;
		if(debut.colonne<fin.colonne)
		{   if(ki==1)
			for(i=debut.ligne;i<debut.ligne+h;i++)
			{   for(int k=0;k<kj;k++)
					if(i>=0 && i<hauteur && j>=0 && j<largeur)
					{	image[i][j++]=couleur;
						if(manque)if(!(j%(ajoutArrondi)))image[i][j++]=couleur;
					}
			}
			else
			for(int j=debut.colonne;j<debut.colonne+l;j++)
			{	for(int k=0;k<ki;k++)
					if(i>=0 && i<hauteur && j>=0 && j<largeur)
					{	image[i++][j]=couleur;
						if(manque)if(!(i%(ajoutArrondi)))image[i++][j]=couleur;
					}
			}
		}
		else
		{   if(ki==1)
			for(i=debut.ligne;i<debut.ligne+h;i++)
			{	for(int k=0;k<kj;k++)
					if(i>=0 && i<hauteur && j>=0 && j<largeur)
					{	if(manque)
						{	if(i%(ajoutArrondi))image[i][j--]=couleur;
							else image[i][j]=couleur;
						}
					}
			}
			else
			for(int j=debut.colonne;j>=debut.colonne-l;j--)
			{	for(int k=0;k<ki;k++)
					if(i>=0 && i<hauteur && j>=0 && j<largeur)
					{	image[i++][j]=couleur;
						if(manque)if(!(i%(ajoutArrondi)))image[i++][j]=couleur;
					}
			}
		}
	}
}
void SNImage::TraceDiagonale(Coordonnee debut,Coordonnee fin, int epaisseur, Pixel couleur)
{	Coordonnee CDebut=debut,CFin=fin;
	CDebut.ligne-epaisseur/2;
	CFin.ligne-epaisseur/2;
	for(int k=0;k<epaisseur;k++)
	{	TraceDiagonaleUnPixel(CDebut,CFin,couleur);
		Coordonnee cd=CDebut; cd.colonne++;
		Coordonnee cf=CFin; cf.colonne++;
		TraceDiagonaleUnPixel(cd,cf,couleur);
		CDebut.ligne++;
		CFin.ligne++;
	}
}
void SNImage::TraceCercleUnPixel(Coordonnee centre, int rayon, Pixel couleur)
{   for(int angle=0; angle<3600; angle++)
	{	int i=rayon*sin(angle*M_PI/1800)+centre.ligne;
		int j=rayon*cos(angle*M_PI/1800)+centre.colonne;
		if(i>=0 && i<hauteur && j>=0 && j<largeur) image[i][j]=couleur;
	}
}
void SNImage::TraceCercle(Coordonnee centre, int rayon, int epaisseur, Pixel couleur)
{   int Rmax=rayon+epaisseur/2;
	for(int k=0;k<epaisseur;k++)
	{	TraceCercleUnPixel(centre, Rmax--, couleur);
	}
}
