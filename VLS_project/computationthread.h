#ifndef COMPUTATIONTHREAD_H
#define COMPUTATIONTHREAD_H

#include <QThread>
#include "Recuit.h"
#include "RecuitDeterministe.h"
#include "RecuitStochastique.h"
#include "SAA.h"

class ComputationThread : public QThread
{
    Q_OBJECT

    public:
        ComputationThread();
        void changeNbScenario(int nbScenario);
        int getNbScenario() {return nb_scenario;}
        void changeNbEchantillon(int nbEchantillon);
        int getNbEchantillon() {return nb_echantillon;}
        void runningAlgo();
        void setRecuit(Recuit *r) {recuit = r;}
        void setSolutionInitiale(vector<int> sol_init) {solutionInitiale.clear(); solutionInitiale = sol_init;}
        void setSolutionFinale(vector<int> sol_finale) {solutionFinale.clear(); solutionFinale = sol_finale;}
        vector<int> getSolutionFinale() {return solutionFinale;}
        void run();

    public slots:

    signals:
        void computationEnded();

    private:
        int nb_scenario;
        int nb_echantillon;
        vector<int> solutionInitiale;
        vector<int> solutionFinale;
        Recuit *recuit;
};

#endif // COMPUTATIONTHREAD_H
