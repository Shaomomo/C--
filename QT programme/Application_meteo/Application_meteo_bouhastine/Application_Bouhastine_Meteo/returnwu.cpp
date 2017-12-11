#include "returnwu.h"

ReturnWU::ReturnWU()
{
    ville = "Paris";
    pays = "France";
    cle = "44102082f83bea7a";

}

string ReturnWU::creerRequeteWU()
{
   string requete;
   requete ="GET /api/"+cle+"/conditions/forecast/lang:FR/q/"+pays+"/"+ville+".xml HTTP/1.1\r\nHost:api.wunderground.com\r\nX-Target-URI: http://api.wunderground.com\r\nConnection:Keep-Alive\r\n\r\n";
    return requete;

}

void ReturnWU::modifierVille(string uneville)
{
    ville = uneville;
}

void ReturnWU::modifierPays(string unpays)
{
    pays = unpays;
}

string ReturnWU::afficherPays()
{
    return pays;
}

string ReturnWU::afficherVille()
{
    return ville;

}
