#ifndef SAA_H_INCLUDED
#define SAA_H_INCLUDED
#include "Stochastique.h"

class SAA : public Stochastique
{
    public:
        SAA(Probleme *);
        virtual ~SAA();
        void generationEchantillon(int nbEchantillon);
        vector<int> executer(vector<int> solutionInitial);

    protected:
    private:
        vector<vector<Scenario>> echantillon;
        vector<int> solutionMoyenne;
        vector<int> solutionMinimale;
        int valeurFctObjMinimale;
};


#endif // SAA_H_INCLUDED
