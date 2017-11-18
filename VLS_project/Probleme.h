#pragma once

#ifndef PROBLEME_H
#pragma once
#define PROBLEME_H
#include <vector>
#include "Scenario.h"

using namespace std;

class Algorithme;

class Probleme
{
    public:
        Probleme(Algorithme *);
        Probleme();
        virtual ~Probleme();

        vector<int> getsolutions() { return solutions; }
        vector<Scenario> getScenarios(){ return mesScenarios;}
        vector<Scenario>& getScenariosRef(){ return mesScenarios;} //
        void setsolutions(vector<int> val) { solutions = val; }
        int getvalFctObj() { return valFctObj; }
        void setvalFctObj(int val) { valFctObj = val; }
        virtual float calculerFctObj(vector<int> solutionInitial, int id_scen, int cout_pen)=0; // Fonction qui permet de calculer la valeur de la fonction objectif mais avec une solution différente
        virtual bool verfiContraintes(vector<int> solution) = 0;
        void setScenarios(vector<Scenario> mesScenarios){this->mesScenarios=mesScenarios;}
        void setAlgo(Algorithme *);
        virtual void generationScenario() = 0;
        virtual float calculerFctObjSAA(vector<int> solutionInitial)=0;

        //virtual int valFonctionObjectif() = 0;

    protected:
        vector<Scenario> mesScenarios;
        vector<int> solutions;
        double valFctObj;

    private:
        Algorithme *algo;

};

#endif // PROBLEME_H
