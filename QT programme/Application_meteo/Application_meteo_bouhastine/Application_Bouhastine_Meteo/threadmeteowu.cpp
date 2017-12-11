#include "threadmeteowu.h"

// Création des variables globales
string ville;
string pays;
ConditionsActuelles CA;
ConditionsAVenir CF[4];

ThreadMeteoWU::ThreadMeteoWU(QObject *parent) :
    QThread(parent)
{


}

void ThreadMeteoWU::run()
{
    MeteoWU meteo;
    meteo.rechercherMeteo(ville, pays);
    CA = meteo.Actuellement();
    for(int i=0 ; i<4 ; i++)
    CF[i] = meteo.Previsions(i);
}
