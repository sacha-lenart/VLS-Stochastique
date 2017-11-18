#ifndef STATION_H
#define STATION_H
#include <string>
#include "Localisation.h"

using namespace std;

class Station
{
    public:
        Station(string, int, int, int, int, int, Localisation);
        virtual ~Station();

        string getnom() { return nom; }
        void setnom(string val) { nom = val; }
        int getNbVelo() { return nbVelo; }
        void setNbVelo(int nbVelo) { this->nbVelo = nbVelo; }
        int getCapacite() { return capacite; }
        void setCapactie(int capacite) { this->capacite = capacite; }
        int getCoutVelo() { return coutVelo; }
        void setCoutVelo(int coutVelo) { this->coutVelo = coutVelo; }
        int getCoutDeficit() { return coutDeficit; }
        void setCoutDeficit(int coutDeficit) { this->coutDeficit = coutDeficit  ; }
        int getCoutSurplus() { return coutSurplus; }
        void setCoutSurplus(int coutSurplus) { this->coutSurplus = coutSurplus; }
        Localisation getLocalisation() {return localisation;}
        void setLocalisation(Localisation localisation) {this->localisation=localisation;}

    protected:

    private:
        string nom;
        int nbVelo;// nombre de velos pour la solution initiale
        int capacite;
        int coutVelo;
        int coutDeficit;
        int coutSurplus;
        Localisation localisation;
};

#endif // STATION_H
