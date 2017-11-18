#ifndef STOCHASTIQUE_H_INCLUDED
#define STOCHASTIQUE_H_INCLUDED
#include "Recuit.h"

class Stochastique : public Recuit
{
    public:
        Stochastique(Probleme *);
        Stochastique();
        virtual ~Stochastique();
    protected:
        vector<int> recuitStochastique(vector<int> solutionInitial);
        bool touteSolutionsEgale(vector<int> solutions, int nb_station, int nb_scenario);
    private:
        virtual vector<int> executer(vector<int> solutionInitial)=0;
};


#endif // STOCHASTIQUE_H_INCLUDED
