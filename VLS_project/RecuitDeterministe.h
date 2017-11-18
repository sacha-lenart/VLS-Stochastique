#ifndef RECUITDETERMINISTE_H_INCLUDED
#define RECUITDETERMINISTE_H_INCLUDED
#include "Recuit.h"

class RecuitDeterministe : public Recuit
{
    public:
        RecuitDeterministe(Probleme *);
        virtual ~RecuitDeterministe();
        vector<int> executer(vector<int> solutionInitial);
    protected:
    private:
};

#endif // RECUITDETERMINISTE_H_INCLUDED
