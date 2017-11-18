#include "Stochastique.h"

Stochastique::Stochastique() : Recuit()
{

}

Stochastique::Stochastique(Probleme * monProbleme) : Recuit(monProbleme)
{
    //ctor
}

Stochastique::~Stochastique()
{
    //dtor
}

vector<int> Stochastique::recuitStochastique(vector<int> solutionInitial){
    vector<int> solutions; // ensemble de solutions intermédiaires de taille nb_sol * nb_scenarios
    vector<int> solution_moyenne; // sauvegarde du dernier état

    int nb_sta = solutionInitial.size();
    int nb_scen = monProbleme->getScenarios().size();

    //cout << "Execution sur " << nb_sta << " stations et " << nb_scen << " scenarios !" << endl;


    vector<int> solInitialeIndiv; // solution toujours remplie de 0
    for (int i=0; i<nb_sta; i++) {
        solInitialeIndiv.push_back(0);
    }

    bool prem_iter = true;

    do {
        //cout << endl << "NOUVELLE ITERATION" << endl;
        // clear des dernières solutions (on a garder la solution moyenne)
        solutions.clear();

        vector<int> solFinaleIndiv;
        // calcule des recuits déterministes
        for (int i=0; i<nb_scen; i++) {
            //cout << "scen : " << i << endl;
            solFinaleIndiv.clear();
            if (prem_iter) {
                solFinaleIndiv = Recuit::recuit(solInitialeIndiv, i, 0);
            }
            else {
                // recuit avec un cout de pénalité non nul
                solFinaleIndiv = Recuit::recuit(solInitialeIndiv, i, (monProbleme->getvalFctObj())/10);
            }

            // on place la nouvelle solution dans le tableau de solutions
            //cout << "sol i : ";
            for (int j=0; j<nb_sta; j++) {
                solutions.push_back(solFinaleIndiv.at(j));
                //cout << solFinaleIndiv.at(j) << " ";
            }
            //cout << endl;
        }

        // calcule de la solution moyenne
        solution_moyenne.clear();
        //cout << "sol moyenne : " << endl;
        for (int i=0; i<nb_sta; i++) {
            int somme = 0;
            for (int j=0; j<nb_scen; j++ ) {
                somme += solutions.at(j*nb_sta + i);
            }
            float float_moy = ((float) somme)/nb_scen;
            int int_moy = float_moy;
            if ((float_moy-int_moy) > 0.5) {
                solution_moyenne.push_back((somme/nb_scen) + 1);
                //cout << (somme/nb_scen) + 1 << " ";
            }
            else {
                solution_moyenne.push_back(somme/nb_scen);
                //cout << somme/nb_scen << " ";
            }
        }
        //cout << endl;

        // enregistrement de la solution moyenne dans le problème
        monProbleme->setsolutions(solution_moyenne);

        prem_iter = false;

    } while (!touteSolutionsEgale(solutions, nb_sta, nb_scen));

    return solution_moyenne;
}


bool Stochastique::touteSolutionsEgale(vector<int> solutions, int nb_station, int nb_scenario)
{
    for(int i=0; i<nb_scenario; i++) {
        for (int j=0; j<nb_station; j++) {
            if(solutions[i*nb_station + j] != solutions[j]) {
                return false;
             }
        }
    }
    return true;
}
