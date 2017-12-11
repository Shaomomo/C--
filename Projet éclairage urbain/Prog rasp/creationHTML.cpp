#include "creationHTML.h"

CREATIONHTML::CREATIONHTML()
{
}

int CREATIONHTML::CreateRueFile(){
// Etape 1 : Ouverture du fichier des informations globales de la rue
    string nomFichierTXT = "fichiersRaspberry/"+numeroRue+"/infoGlobalesRue.txt";
    ifstream fichierInfosRue(nomFichierTXT.c_str(), ios::in);
// Etape 2 : Vérification de l'état du fichier et traitement des données en fonction des ';'
    if(fichierInfosRue){
        string lectureFichier;
        string contenuFichier[34];
        int i=0;
        while(getline(fichierInfosRue, lectureFichier, ';')){
            contenuFichier[i]=lectureFichier;
            i++;
        }
// Etape 3 : On ouvre le fichier 'Rue.html' qui sera notre page de rue, généré en PARTIE par le C++
        string nomFichierHTML = "Rue.html";
        ofstream fichierRueHTML(nomFichierHTML.c_str(), ios::out); // On ouvre le fichier en ios::out pour écraser le fichier précident
// Etape 4 : Vérification de l'état du fichier et génération du code HTML primaire
if(fichierRueHTML){
    fichierRueHTML << "<!DOCTYPE html>" << endl; // Indique le type d'HTML utilisé
    fichierRueHTML << "<html>" << endl; // Balise HTML (Page HTML)
    fichierRueHTML << "<head>" << endl; // Balise HEAD (En tête)
    fichierRueHTML << "<title>Historique d'une rue</title>" << endl;
    fichierRueHTML << "<meta charset='UTF-8'>" << endl;
    fichierRueHTML << "<link rel='stylesheet' type='text/css' href='rue.css'>" << endl;
    fichierRueHTML << "</head>" << endl;
    fichierRueHTML << "<body>" << endl;
    fichierRueHTML << "<a href='index.html' id='button_index' class='button button-info'>Retour Index</a>";
    fichierRueHTML << "<div class='image' style='background: url(\"fichiersRaspberry/"+numeroRue+"/imageRue.PNG\")no-repeat; background-size: cover;'></div>";
    fichierRueHTML << "<div id='div_infosGlobale'>" << endl;
    fichierRueHTML << "<h3 style='padding: 15px; text-align:center;'>Détails sur la rue</h3>" << endl;
    /* Affichage des infos */
        fichierRueHTML << "<div class='titleSection'>Informations générales :</div>";
        fichierRueHTML << "<div class='contentSection'>" << endl;
        fichierRueHTML << "<strong>Rue <span class='content_NumRue'>"+contenuFichier[1]+"</span> :</strong> <span class='content_NomRue'>"+contenuFichier[3]+"</span><br>" << endl;
        fichierRueHTML << "<strong>Ville :</strong> <span class='content_NomVille'>"+contenuFichier[5]+"</span>" << endl;
        fichierRueHTML << "</div>" << endl;
        fichierRueHTML << "<div class='titleSection'>Etat :</div>";
        fichierRueHTML << "<div class='contentSection'>" << endl;
        fichierRueHTML << "<strong>Mode de fonctionnement :</strong> <span class='content_mode'>"+contenuFichier[7]+"</span><br>" << endl;
        fichierRueHTML << "</div>" << endl;
    /* Affichage des infos */
    fichierRueHTML << "</div>" << endl;
    fichierRueHTML << "<div id='div_afficheHistorique'>"+numeroRue+"</div>" << endl;
    fichierRueHTML << "<script type='text/javascript' src='anonymousFunction.js'></script>" << endl;
    fichierRueHTML << "</body>" << endl;
    fichierRueHTML << "</html>" << endl;

// Etape
    fichierRueHTML.close();
} else {
    cout << "Ouverture du fichier fichier HTML : ERREUR" << endl;
}
/* FICHIER HTML ECRITURE */
fichierInfosRue.close();
        return 1;
    } else {
        cout << "Ouverture du fichier historique.txt : ERREUR" << endl;
        return 0;
    }
}

bool CREATIONHTML::VerrifMessage(string message){
    string recupererDebutMessage;


    recupererDebutMessage = message.substr(0,18);
    if(recupererDebutMessage == "GET /?envoiValeur="){
        cout << message.length() << endl;
        numeroRue = message.substr(18, 5);
        if(numeroRue[numeroRue.length()-1]==' '){
            numeroRue = numeroRue.substr(0,numeroRue.length()-1);
        }
        return true;
    }
    return false;
}

string CREATIONHTML::CheckTheDate(){
    time_t rawtime;
      struct tm * timeinfo;
      char buffer[80];

      time (&rawtime);
      timeinfo = localtime(&rawtime);

      strftime(buffer,80,"%a,%d %b %Y %H:%M:%S GMT",timeinfo);
      std::string str(buffer);

    return str;
}



