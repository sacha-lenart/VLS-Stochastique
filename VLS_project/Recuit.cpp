#include "Recuit.h"

Recuit::Recuit(Probleme * monProbleme) : Algorithme(monProbleme), temperature(15.0), nbIterations(600), palierTemperature(1)
{
    //ctor
}
Recuit::Recuit() : temperature(15.0), nbIterations(600), palierTemperature(1)
{

}

Recuit::~Recuit()
{
    //dtor
}


vector<int> Recuit::recuit(vector<int> solutionInitial, int nb_scen, int pen){
    float minValFctObj = Algorithme::monProbleme->calculerFctObj(solutionInitial, nb_scen, pen);
    vector<int> meilleurSolution=solutionInitial;
    int tmp_temperature = this->temperature;
    while(tmp_temperature > 0) {
        cout << tmp_temperature << endl;
        int i=0;
        while(i<this->nbIterations) {
            //cout << "   " << i << endl;
            vector<int> voisin = voisinage(solutionInitial);
            int valFctObjVoisin = Algorithme::monProbleme->calculerFctObj(voisin, nb_scen, pen);
            float deltaValFctObj = valFctObjVoisin - Algorithme::monProbleme->calculerFctObj(solutionInitial, nb_scen, pen);

            if (deltaValFctObj<0){
                solutionInitial=voisin;
                int ftcObjSolutionInitial = valFctObjVoisin;
                if(ftcObjSolutionInitial < minValFctObj){
                    minValFctObj= ftcObjSolutionInitial;
                    meilleurSolution=solutionInitial;
                }
            }
            else{
                float proba = rand()%(101)/100.0;
                //cout<<proba<<endl;
                //cout<<deltaValFctObj<<endl;
                //cout<<exp(-deltaValFctObj/this->temperature)<<endl;
                //cout << "|";
                if(proba<=exp(-deltaValFctObj/tmp_temperature)){
                    //cout << proba << " ";
                    solutionInitial=voisin;
                    //cout<<"Changement proba"<<endl;
                }
            }
            i++;
        }
        tmp_temperature = tmp_temperature - this->palierTemperature;
    }
    return meilleurSolution;
}

vector<int> Recuit::voisinage(vector<int> solutionInitial){


    vector<int> solution;
    do{
        solution = solutionInitial;
        int nbgen=rand()%3;
        int stationI,stationJ;

        int somme=0;
        for(int i=0;i<solution.size();i++){
            somme+=solution[i];
        }
        if(somme<=0){
            nbgen=1;
        }

        //Echanger un vélo d'une station i à j
        //Faire 2 aléatoire pour choisir la station i vers j

        if(nbgen==0){
            do{
                stationI=rand()%(solution.size());
            }while(solution[stationI]-1<0);
            do{
                stationJ=rand()%(solution.size()); //nbStation est le nombre de station total.
            }while(stationJ==stationI);
            //cout<<solution[stationI]<<" "<<solution[stationJ]<<endl;
            solution[stationI]-=1;
            solution[stationJ]+=1;
            //cout<<solution[stationI]<<" "<<solution[stationJ]<<endl;
        }
        //Ajouter un vélo a une station i
        //Faire un aleatoire pour choisir la station i
        else if(nbgen==1){
            stationI=rand()%(solution.size());
            solution[stationI]+=1;
        }
        //Enlever un velo a une station i
        //Faire un aleatoire pour choisir la station i
        else{
            do{
                stationI=rand()%(solution.size());
            }while(solution[stationI]-1<0);
            solution[stationI]-=1;
        }
    }
    while(!Algorithme::monProbleme->verfiContraintes(solution));

    /*for(int i=0;i<solution.size();i++){
        cout<<solutionInitial[i]<<" ";
    }*/
    //cout<<endl;
    return solution;
}
