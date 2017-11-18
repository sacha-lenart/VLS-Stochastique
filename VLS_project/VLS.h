#ifndef VLS_H
#define VLS_H
#include "Station.h"
#include "Probleme.h"


class VLS : public Probleme
{
    public:
        VLS(string);
        VLS(vector<Station>, Algorithme * );
        virtual ~VLS();
        float calculerFctObj(vector<int> solutionInitial, int id_scen, int cout_pen);
        vector<Station> getStations(){return mesStations;}
        void setFileName(string f_name) {filename = f_name;}
        bool verfiContraintes(vector<int> mesx);
        void retrieveData();
        void generationScenario();
        float calculerFctObjSAA(vector<int> solutionInitial);

    protected:

    private:
        /* Argument data jsonfile*/
        vector<Station> mesStations;
        string filename;
};

#endif // VLS_H
