#include "VLS.h"
#include <fstream>
#include <iostream>
#include <vector>
#include "json.hpp"


using namespace std;
using json = nlohmann::json;

VLS::VLS(string file_name)
{
    filename = file_name;
}

VLS::VLS(vector<Station> mesStations, Algorithme * algo) : Probleme(algo), mesStations(mesStations)
{

}

VLS::~VLS()
{
    //dtor
}



bool VLS::verfiContraintes(vector<int> solution){
    //Premiere contrainte a verifier : nombre de vélo de la station i est inférieur ou égale a la capacité de la station i

    vector<Station> mes_stations = mesStations;

    for(int i =0; i< mes_stations.size();i++){
        /*(1a)*/
        if(solution[i] > mes_stations.at(i).getCapacite())
        {
            //cout<<solution[i]<<" "<<mesStations.at(i).getCapacite()<<endl;
            //cout << "contrainte (1a) non respecté !"<<endl;
            return false;
        }
    }

   return true;

}


float VLS::calculerFctObj(vector<int> solutionInitial, int id_scen, int cout_pen) {

    int nb_station = mesStations.size();

    float somme1=0;//somme des coûts de l'attribution des vélos pour chaque station i
    float somme2=0;
    float somme3=0;

    for(int i=0;i<nb_station;i++){
        somme1+=mesStations[i].getCoutVelo()*solutionInitial[i];
    }

    // préparation des données
    vector<int> scenario = mesScenarios[id_scen].getDonnees();
    int size_stations = mesStations.size();
    vector<Station> mes_stations = mesStations;

    for(int i=0;i<nb_station;i++)
    {
        int nbVeloStationI=solutionInitial[i];
        int nbVeloPartiStationI=0;//nombre de vélos demandés
        //Compter le nombre de vélo qui sont parti de la station i
        for(int j=0;j<nb_station-1;j++){
            //On additionne la demande de i à j
            nbVeloPartiStationI += scenario.at(i*(nb_station-1)+j);
        }
        //Si le nombre de vélos est insufisant en rajoute du coût lié au déficit de vélos
        if(nbVeloStationI<nbVeloPartiStationI){
            somme2+=mes_stations.at(i).getCoutDeficit()*(nbVeloPartiStationI-nbVeloStationI);//Iijs- : nombre de velo qui manque pour faire i vers j sur le scenario s
        }
    }

    //A chaque fois + NbStation-1
    //A j=i +(NbStation-1)*2+1
    int val2 = size_stations-1;//Valeur pour recuperer la bonne case dans le tableau de donnees de Scenario
    for(int i=0;i<nb_station;i++){
        int nbVeloStationI=solutionInitial[i];
        int nbVeloArriveStationI=0;
        //Compter le nombre de vélo qui sont arrive a la station i
        for(int j=0;j<nb_station-1;j++){
            if(i==j && i!=0 && i!=nb_station-1){
                val2+=nb_station;
            }
            nbVeloArriveStationI+= scenario.at(val2);
            val2+=nb_station-1;
            if(val2>=(nb_station*(nb_station-1))){
                val2=val2-nb_station*(nb_station-1);
            }
        }
        if(mes_stations.at(i).getCapacite()-nbVeloStationI < nbVeloArriveStationI){
            somme3+=mes_stations.at(i).getCoutDeficit()*(nbVeloArriveStationI-(mes_stations.at(i).getCapacite()-nbVeloStationI));//Iijs- : nombre de velo qui manque pour faire i vers j sur le scenario s
        }
    }

    // calcule de la pénalité
    // calcule de l'écart à la moyenne pour chaque scénario
    int ecart = 0;
    if (cout_pen != 0) {
        for(int i=0; i<size_stations; i++) {
            // la derniere solution est stockée dans "solutions" de Probleme
            ecart += abs(solutionInitial.at(i) - solutions.at(i));
        }
    }

    // stockage de la solution moyenne
    if (id_scen == 0)
        valFctObj = somme1+somme2+somme3 + ecart*cout_pen;

    return somme1+somme2+somme3 + ecart*cout_pen;
}




float VLS::calculerFctObjSAA(vector<int> solutionInitial){

    float somme1=0;//somme des couts de l'attribution des v?los pour chaque station i
    float somme2=0;
    float somme3=0;

    // préparation des données
    //vector<Scenario> mes_scenarios = mesScenarios[id_scen].getDonnees();
    int size_stations = mesStations.size();
    vector<Station> mes_stations = mesStations;
    int nb_station = mes_stations.size();

    for(int i=0;i<nb_station;i++){
        somme1+=mes_stations.at(i).getCoutVelo()*solutionInitial[i];
    }


    float sommeScenario = 0;
    float ProbaScenario = 1.0/mesScenarios.size();//Chaque sc?nario ? la m?me probabilit?
    for(unsigned int s=0;s<mesScenarios.size();s++)//boucle des sc?narios
    {
        Scenario scenario = mesScenarios[s];
        for(int i=0;i<nb_station;i++)
        {
            int nbVeloStationI=solutionInitial[i];
            int nbVeloPartiStationI=0;//nombre de v?los demand?s
            /*Compter le nombre de v?lo qui sont parti de la station i*/
            for(int j=0;j<nb_station-1;j++){
                /*On additionne la demande de i ? j*/
                nbVeloPartiStationI+=scenario.getDonnees().at(i*(nb_station-1)+j);
            }
            /*Si le nombre de v?los est insufiddant en rajoute du co?t li? au d?ficit de v?los*/
            if(nbVeloStationI<nbVeloPartiStationI){
                somme2+=mes_stations.at(i).getCoutDeficit()*(nbVeloPartiStationI-nbVeloStationI);/*Iijs- : nombre de velo qui manque pour faire i vers j sur le scenario s*/
            }
        }
    //A chaque fois + NbStation-1
    //A j=i +(NbStation-1)*2+1
        int val2 = size_stations-1;//Valeur pour recuperer la bonne case dans le tableau de donnees de Scenario
        for(int i=0;i<nb_station;i++){
            int nbVeloStationI=solutionInitial[i];
            int nbVeloArriveStationI=0;
            /*Compter le nombre de v?lo qui sont arrive a la station i*/
            for(int j=0;j<nb_station-1;j++){
                if(i==j && i!=0 && i!=nb_station-1){
                    val2+=nb_station;
                }
                nbVeloArriveStationI+= scenario.getDonnees().at(val2);
                val2+=nb_station-1;
                if(val2>=(nb_station*(nb_station-1))){
                    val2=val2-nb_station*(nb_station-1);
                }
            }
            if(mes_stations.at(i).getCapacite()-nbVeloStationI<nbVeloArriveStationI){
                somme3+=mes_stations.at(i).getCoutDeficit()*(nbVeloArriveStationI-(mes_stations.at(i).getCapacite()-nbVeloStationI));/*Iijs- : nombre de velo qui manque pour faire i vers j sur le scenario s*/
            }
        }
        sommeScenario+=ProbaScenario*((double)(somme2+somme3));
    }
    return (float)somme1+sommeScenario;
}




int generateAlea(int gmin, int gmax)
 {
      return ( rand()%(gmax-gmin ) + gmin);
 }

double generateAleaDouble(double gmin, double gmax)
{
     return ( rand()/(double)RAND_MAX ) * (gmax-gmin) + gmin;
}

void VLS::generationScenario()
{
    vector<int> new_demandes;
    for(unsigned int i=0;i<mesStations.size();i++)
    {
        // calcule de la somme des demandes pour la station
        int somme = 0;
        for(unsigned int j=i*(mesStations.size()-1); j<(i+1)*(mesStations.size()-1); j++) {
            somme += mesScenarios.at(0).getDonnees().at(j);
        }

        // calcule des bornes -20% et +20%
        double mymin = (double)somme*0.8;
        double mymax = (double)somme*1.2;
        double somme_alea = (int)generateAleaDouble(mymin,mymax);

        // ajout de valeurs dans le scenario
        for (unsigned int i=0; i<mesStations.size()-1; i++)
            new_demandes.push_back(0);

        // incrémentation des valeurs
        while (somme_alea > 0) {
            // choix de la station
            int station_choisi = generateAlea(0, mesStations.size()-1);
            new_demandes[station_choisi + i*(mesStations.size()-1)] += 1;
            somme_alea -= 1;
        }
    }

    Scenario scen(new_demandes);
    mesScenarios.push_back(scen);
}


/**
* RetrieveData :
* réalise la récupération des données pour les stocker dans les différentes classes et initialiser la demande moyenne
*/
void VLS::retrieveData()
{
    //ifstream fichier(this->filename.c_str(), ios::in);  // on ouvre le fichier en lecture
    //En utilisant la librairie json
    ifstream fichier(this->filename.c_str());
    /*if (fichier) {
        cout << "Fichier chargé" << endl;
    }
    else cerr << "Impossible de charger le fichier selectionné" << endl;*/

    json myjson;
    fichier >> myjson;
    unsigned int nb_sta = myjson.size(); // si trois stations, myjson.size() retourne 3
    vector<int> demandes; //Les demandes du scénario moyen

    //On alloue le nombre de demandes_ij qui est : nb_station*(nb_station-1)
    demandes.assign(nb_sta*(nb_sta-1),0);

    //clear des stations précédentes
    mesStations.clear();
    // parcours des stations du fichier json
    for(unsigned int i=0; i<nb_sta; i++)
    {
        //creation des stations
        string name = myjson[i].at("name").get<std::string>();
        double lat = myjson[i].at("position").at("lat");
        double lng = myjson[i].at("position").at("lng");
        //la localisation de la station
        Localisation loc = Localisation(lng,lat);
        int capacite =  myjson[i].at("bike_stands");
        int nb_velos = 0; // dans le json : myjson[i].at("available_bikes")

        // couts fixes pour toutes les stations
        int coutvelo = 5;
        int coutdeficit = 50;
        int coutsurplus = 40;

        Station station(name,nb_velos,capacite,coutvelo,coutdeficit,coutsurplus,loc);
        mesStations.push_back(station);

        int velos_demandes = myjson[i].at("available_bike_stands");
        for(int j=0; j<velos_demandes; j++)
        {
            //tirage alatoire d'une station destination(autre que i) :
            int dest;
            do { dest = generateAlea(0, nb_sta);
            } while(dest==i); // si même station trouvée on retire au sort

            //La demande en vélo pour le trajet i à dest est augmentée de 1
            if (i < dest) demandes[i*(nb_sta-1)+dest-1] += 1;
            else demandes[i*(nb_sta-1)+dest]+=1;
        }
    }

    Scenario scen(demandes);
    mesScenarios.clear();
    mesScenarios.push_back(scen);

    // affichage des demandes
    /*for (int i=0; i<scen.getDonnees().size(); i++) {
        int depart = (i / (nb_sta-1));
        int arrivee = (i % (nb_sta-1));
        if (arrivee >= depart) arrivee += 1;
        cout << "De station" << depart << " a la station" << arrivee << " : " << mesScenarios.at(0).getDonnees().at(i) << endl;
    }*/
}



/*ostream& operator<<( ostream &flux, VLS const& vls )
{
    cout << vls.Getfilename() <<endl;
    cout <<vls.Getnbvelototal() <<endl;
    cout << "ok\n";
    cout << vls.getScenarios().size();
    //cout <<vls.getScenarios().at(0) <<endl;
    //cout <<  <<endl;
    return flux;
}*/
