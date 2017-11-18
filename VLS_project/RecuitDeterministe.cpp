#include "RecuitDeterministe.h"


RecuitDeterministe::RecuitDeterministe(Probleme * monProbleme) : Recuit(monProbleme)
{
    //ctor
}

RecuitDeterministe::~RecuitDeterministe()
{
    //dtor
}


vector<int> RecuitDeterministe::executer(vector<int> solutionInitial){
    return Recuit::recuit(solutionInitial, 0, 0);
}
