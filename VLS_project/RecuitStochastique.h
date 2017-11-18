#ifndef RECUITSTOCHASTIQUE_H_INCLUDED
#define RECUITSTOCHASTIQUE_H_INCLUDED
#include "Stochastique.h"

class RecuitStochastique : public Stochastique
{
    public:
        RecuitStochastique();
        RecuitStochastique(Probleme *);
        virtual ~RecuitStochastique();
        vector<int> executer(vector<int> solutionInitial);
    protected:
    private:
};

#endif // RECUITSTOCHASTIQUE_H_INCLUDED
