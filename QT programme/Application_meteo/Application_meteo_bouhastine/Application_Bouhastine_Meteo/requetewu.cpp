#include "requetewu.h"

RequeteWU::RequeteWU()
{
    ville = "Paris";
    pays = "France";
    cle = "44102082f83bea7a";

}

string RequeteWU::creerRequeteWU()
{
   string requete;
   requete ="GET /api/"+cle+"/conditions/forecast/lang:FR/q/"+pays+"/"+ville+".xml HTTP/1.1\r\nHost:api.wunderground.com\r\nX-Target-URI: http://api.wunderground.com\r\nConnection:Keep-Alive\r\n\r\n";
    return requete;

}

void RequeteWU::modifierVille(string uneville)
{
    ville = uneville;
}

void RequeteWU::modifierPays(string unpays)
{
    pays = unpays;
}

string RequeteWU::afficherPays()
{
    return pays;
}

string RequeteWU::afficherVille()
{
    return ville;

}
