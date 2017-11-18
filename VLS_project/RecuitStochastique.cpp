
#include "RecuitStochastique.h"
#include "VLS.h"


RecuitStochastique::RecuitStochastique(Probleme * monProbleme) :Stochastique(monProbleme)
{

}


RecuitStochastique::RecuitStochastique():Stochastique()
{

}


RecuitStochastique::~RecuitStochastique()
{
    //dtor
}


vector<int> RecuitStochastique::executer(vector<int> solutionInitial)
{
    return recuitStochastique(solutionInitial);
}





