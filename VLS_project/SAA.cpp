#include "SAA.h"
#include "VLS.h"


SAA::SAA(Probleme * monProbleme) : Stochastique(monProbleme)
{

}

SAA::~SAA()
{
    //dtor
}

void SAA::generationEchantillon(int nbEchantillon){
    vector<Scenario> echan;
    echantillon.clear();
    for(int i=0;i<nbEchantillon;i++){
        this->echantillon.push_back(echan);
    }

    for(int i=0;i<nbEchantillon;i++){
        for(unsigned int j=0;j<monProbleme->getScenarios().size()/nbEchantillon;j++){
            this->echantillon[i].push_back(monProbleme->getScenarios()[i*(monProbleme->getScenarios().size()/nbEchantillon)+j]);
        }
    }
}

vector<int> SAA::executer(vector<int> solutionInitial){

    vector<vector<int>> solution;

    for(unsigned int i=0;i<echantillon.size();i++){
        monProbleme->setScenarios(echantillon[i]);
        solution.push_back(recuitStochastique(solutionInitial));
    }

    /*for(unsigned int i=0;i<solution.size();i++){
        for(unsigned int j=0;j<solution[i].size();j++){
            cout<<solution[i][j]<<" ";
        }
        cout<<endl;
    }*/


    for(unsigned int j=0;j<solution[0].size();j++){
        solutionMoyenne.push_back(0);
    }


    for(unsigned int i=0;i<solution.size();i++){
        for(unsigned int j=0;j<solution[i].size();j++){
            solutionMoyenne[j]+=solution[i][j];
        }
    }
    for(unsigned int i=0;i<solutionMoyenne.size();i++){

        float float_moy = ((float) solutionMoyenne[i])/solution.size();
        int int_moy = float_moy;
        if ((float_moy-int_moy) > 0.5) {
            solutionMoyenne[i]=solutionMoyenne[i]/solution.size()+1;
        }
        else {
            solutionMoyenne[i]=solutionMoyenne[i]/solution.size();
        }
    }


    //Nb de scenario que l'on va ajouter pour le scenario de reference
    for(int i=0;i<1000;i++){
        monProbleme->generationScenario();
    }

    solutionMinimale=solution[0];
    valeurFctObjMinimale=monProbleme->calculerFctObjSAA(solutionMinimale);
    for(int i=1;i<solution.size();i++){
        if(monProbleme->calculerFctObjSAA(solution[i])<valeurFctObjMinimale){
            solutionMinimale=solution[i];
            valeurFctObjMinimale=monProbleme->calculerFctObjSAA(solution[i]);
        }
    }

    return solutionMinimale;
}
