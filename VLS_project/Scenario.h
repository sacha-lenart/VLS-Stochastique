#ifndef SCENARIO_H
#define SCENARIO_H
#include <vector>
#include <iostream>

using namespace std;

class Scenario
{
    public:
        Scenario(vector<int>);
        //Scenario(vector<int, allocator<int> >);
        virtual ~Scenario();

        vector<int> getDonnees() const { return donnees; }
        void Setdonnees(vector<int> val) { donnees = val; }
        vector<int> GetSolutionScenario() {return this->solution_scenario;}
        void SetSolutionScenario(vector<int> newsol){this->solution_scenario = newsol; }

    protected:

    private:
        vector<int> donnees;
        vector<int> solution_scenario;
};

#endif // SCENARIO_H
