#include "computationthread.h"
#include <iostream>

ComputationThread::ComputationThread()
{

}

void ComputationThread::changeNbScenario(int nbScenario)
{
    nb_scenario = nbScenario;
}

void ComputationThread::changeNbEchantillon(int nbEchantillon)
{
    nb_echantillon = nbEchantillon;
}

void ComputationThread::runningAlgo()
{
    start();
}

#include <time.h>

void ComputationThread::run()
{
    float temps;
    clock_t t1, t2;
    t1 = clock();
    solutionFinale = recuit->executer(solutionInitiale);
    t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    cout << "temps execution : " << temps << endl;

    emit computationEnded();
}
