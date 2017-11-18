#ifndef RECUIT_H
#define RECUIT_H
#include <time.h>
#include<math.h>
#include <cstdlib>
#include "Algorithme.h"
#include <iostream>


class Recuit : public Algorithme
{
    public:
        Recuit(Probleme *);
        Recuit(); //
        virtual ~Recuit();
        virtual vector<int> executer(vector<int> solutionInitial) = 0;
    protected:
        vector<int> recuit(vector<int> solutionInitial, int nb_scen, int pen);
        float temperature;
        int nbIterations;
        int palierTemperature;
        vector<int> voisinage(vector<int> solutionInitial);
};

#endif // RECUIT_H
