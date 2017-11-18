#include "mainwindow.h"
#include "VLS.h"
#include "RecuitDeterministe.h"

#include <iostream>
#include <ctime>


using namespace std;


int main(int argc, char *argv[])
{
    // init rand
    srand(time(NULL));

    // start application
    QApplication app(argc, argv);

    // main window
    MainWindow main_wind;

    // display main window
    main_wind.show();

    // end application
    return app.exec();
}

/*
int main() {

    srand(time(NULL));

    VLS *myvls;
    myvls = new VLS("stations_velib_paris_10.json");
    int nb_station = 10;
    int nb_scenario = 20;
    myvls->retrieveData();
    for (int i=1; i<nb_scenario; i++) {
        myvls->generationScenario();
    }

    RecuitStochastique* rec_s;
    rec_s = new RecuitStochastique(NULL);
    rec_s->setmonProbleme(myvls);
    vector<int> solInit;
    for (int i = 0; i<nb_station; i++)
        solInit.push_back(0);

    vector<int> solFinale = rec_s->executer(solInit);
    for (int i = 0; i<nb_station; i++)
        cout << solFinale.at(i) << " ";

    cout << endl << "ok" << endl;
} */

/*
int main() {
    srand(time(NULL));

    VLS *myvls;
    myvls = new VLS("stations_velib_paris_3.json");
    int nb_station = 3;
    int nb_scenario = 200;
    myvls->retrieveData();
    for (int i=1; i<nb_scenario; i++) {
        myvls->generationScenario();
    }

    SAA* rec_saa;
    rec_saa = new SAA(NULL);
    rec_saa->setmonProbleme(myvls);
    vector<int> solInit;
    for (int i = 0; i<nb_station; i++)
        solInit.push_back(0);

    rec_saa->generationEchantillon(5);

    vector<int> solFinale = rec_saa->executer(solInit);
    for (unsigned int i = 0; i<solFinale.size(); i++)
        cout << solFinale.at(i) << " ";

    cout << endl << "ok" << endl;
}*/
