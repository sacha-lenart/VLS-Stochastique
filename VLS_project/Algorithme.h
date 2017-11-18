#ifndef ALGORITHME_H
#define ALGORITHME_H
#include "Probleme.h"
#include <vector>

class Algorithme
{
    public:
        Algorithme();
        Algorithme(Probleme *);
        virtual ~Algorithme();

        Probleme * getmonProbleme() { return this->monProbleme; }
        void setmonProbleme(Probleme * val) { this->monProbleme = val; }
        virtual vector<int> executer(vector<int> solutionInitial) = 0;

    protected:
        Probleme *monProbleme;

    private:

};

#endif // ALGORITHME_H
