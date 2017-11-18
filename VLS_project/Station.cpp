#include "Station.h"

Station::Station(string nom, int nbVelo, int capacite, int coutVelo, int coutDeficit, int coutSurplus, Localisation localisation)
: nom(nom), nbVelo(nbVelo), capacite(capacite), coutVelo(coutVelo), coutDeficit(coutDeficit), coutSurplus(coutSurplus), localisation(localisation)
{
    //ctor
}

Station::~Station()
{
}
