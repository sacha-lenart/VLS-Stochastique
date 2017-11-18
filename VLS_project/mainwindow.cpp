#include "mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>

// link des données pour le fichier qml
#include <qqmlengine.h>
#include <qqmlcontext.h>
#include <qqml.h>
#include <QtQuick/qquickitem.h>

MainWindow::MainWindow() : QMainWindow()
{

    //***************** paramètres *****************

    // fichier
    file_layout = new QVBoxLayout();
    file_button = new QPushButton("Sélectionner un fichier");
    file_button->setMaximumWidth(170);
    file_label = new QLabel("aucun fichier");
    file_layout->addWidget(file_button);
    file_layout->addWidget(file_label);
    file_box = new QGroupBox("Choix du fichier");
    file_box->setLayout(file_layout);
    param_box = new QVBoxLayout();
    param_box->addWidget(file_box);

    // choix algorithme
    // sliders
    slider_recuit = new QSlider(Qt::Horizontal);
    slider_recuit->setDisabled(true);
    int init_nb_scen = 2;
    int init_nb_echant = 2;
    slider_recuit->setRange(init_nb_scen, 10);
    slider_recuit->setTickPosition(QSlider::TicksBelow);
    slider_recuit->setTickInterval(init_nb_scen);
    label_recuit = new QLabel(QString::number(init_nb_scen));
    slider_recuit_layout = new QHBoxLayout();
    slider_recuit_layout->addWidget(slider_recuit);
    slider_recuit_layout->addWidget(label_recuit);
    slider_saa = new QSlider(Qt::Horizontal);
    slider_saa->setRange(init_nb_echant, 10);
    slider_saa->setTickPosition(QSlider::TicksBelow);
    slider_saa->setTickInterval(2);
    label_saa = new QLabel(QString::number(init_nb_echant));
    slider_saa_layout = new QHBoxLayout();
    slider_saa_layout->addWidget(slider_saa);
    slider_saa_layout->addWidget(label_saa);
    initSlidersDisabled();
    // group box
    choose_recuit_det = new QRadioButton("Recuit déterministe");
    choose_recuit_det->setChecked(true);
    choose_recuit_sto = new QRadioButton("Recuit stochastique");
    choose_saa = new QRadioButton("SAA");
    choose_vbox = new QVBoxLayout();
    choose_vbox->addWidget(choose_recuit_det);
    choose_vbox->addWidget(choose_recuit_sto);
    choose_vbox->addLayout(slider_recuit_layout);
    choose_vbox->addWidget(choose_saa);
    choose_vbox->addLayout(slider_saa_layout);
    choose_grpbox = new QGroupBox("Choix de l'algorithme");
    choose_grpbox->setLayout(choose_vbox);
    param_box->addWidget(choose_grpbox);

    // start button
    start_button = new QPushButton("Start");
    start_button->setMaximumWidth(80);
    start_layout = new QHBoxLayout();
    start_layout->setAlignment(Qt::AlignRight);
    start_layout->addWidget(start_button);
    param_box->addLayout(start_layout);


    //***************** affichage ******************

    model = new VlsStationModel();

    //display_box = new QGroupBox();
    view = new QQuickView();
    QQmlContext *ctxt = view->rootContext();
    ctxt->setContextProperty("stationModel", model);
    view->setSource(QUrl(QStringLiteral("qrc:///places_map.qml")));
    view->show();

    QWidget *container = QWidget::createWindowContainer(view);
    container->setMinimumHeight(500);
    container->setMinimumWidth(500);
    container->setFocusPolicy(Qt::TabFocus);

    map_layout = new QVBoxLayout();
    cost_label = new QLabel("Coût de la solution : -");
    map_layout->addWidget(container);
    map_layout->addWidget(cost_label);

    //***************** main ***********************

    // ajout au main_layout
    main_layout = new QHBoxLayout();
    main_layout->addItem(param_box);
   // main_layout->addWidget(display_box);
    main_layout->addLayout(map_layout);

    // ajouter main_layout à la QMainWindow
    QWidget *main_widget = new QWidget();
    // on place main_layout dans un widget
    // car on ne peut pas ajouter directement main_layout
    main_widget->setLayout(main_layout);
    // ajout du widget dans la fenêtre
    this->setCentralWidget(main_widget);

    cThread = new ComputationThread();
    cThread->changeNbEchantillon(init_nb_echant);
    cThread->changeNbScenario(init_nb_scen);

    //***************** slots **********************

    connect(file_button, SIGNAL(clicked()), this, SLOT(chooseFile()));
    connect(slider_recuit, SIGNAL(valueChanged(int)), this, SLOT(setScenario(int)));
    connect(slider_saa, SIGNAL(valueChanged(int)), this, SLOT(setEchantillon(int)));
    connect(choose_recuit_det, SIGNAL(clicked()), this, SLOT(setRecDetSelected()));
    connect(choose_recuit_sto, SIGNAL(clicked()), this, SLOT(setRecStoSelected()));
    connect(choose_saa, SIGNAL(clicked()), this, SLOT(setSaaSelected()));
    connect(start_button, SIGNAL(clicked()), this, SLOT(startComputation()));
    connect(cThread, SIGNAL(computationEnded()), this, SLOT(enableParameters()));
    connect(cThread, SIGNAL(computationEnded()), this, SLOT(updateModel()));

    //***************** init problem ****************
    algo = 0; // de base : recuit déterministe
    myvls = new VLS("no_file");
}


void MainWindow::initSlidersDisabled()
{
    label_recuit->setDisabled(true);
    slider_recuit->setDisabled(true);
    label_saa->setDisabled(true);
    slider_saa->setDisabled(true);
}


void MainWindow::chooseFile()
{
    QString file_name;
    file_name = QFileDialog::getOpenFileName(this, "Choix du fichier", QString(), "JSON (*.json)");

    if(file_name == "") {
        file_name = "aucun fichier";

        // affichage du nom du fichier
        file_label->setText(file_name);
    }

    // retour a l'utilisateur
    QMessageBox::information(this, "Fichier", "Vous avez choisi :\n" + file_name);

    // si nom de fichier rentré on charge le fichier
    if (file_name != "aucun fichier") {
        // affichage du nom du fichier
        QFileInfo file_info(file_name);
        QString file_name_short = file_info.fileName();
        file_label->setText(file_name_short);

        // modification du nom de fichier du vls
        myvls->setFileName(file_name.toStdString());

        // chargement des données dans le vls
        myvls->retrieveData();

        // modification des données dans le model pour la vue qml
        loadDataModel();
    }
}

QString MainWindow::getDescribtion(Station station, int sol)
{
    QString describtion;
    describtion =  " " + QString::fromStdString(station.getnom()) + "\n";
    describtion += "k : " + QString::number(station.getCapacite()) + ", ";
    describtion += "c : " + QString::number(station.getCoutVelo()) + ", ";
    describtion += "v : " + QString::number(station.getCoutDeficit()) + ", ";
    describtion += "w : " + QString::number(station.getCoutSurplus()) + "\n ";
    describtion += "meilleur solution : ";
    if (sol == -1) describtion += "-";
    else describtion += QString::number(sol);
    return describtion;
}

void MainWindow::loadDataModel()
{
    QList<VlsStation> new_stations;
    QString tmp_describtion;
    // récupération des données à afficher sur la map
    for(int i=0; i<myvls->getStations().size(); i++)
    {
        tmp_describtion = getDescribtion(myvls->getStations().at(i), -1);
        VlsStation tmp_station(myvls->getStations().at(i).getLocalisation().GetcoordY(),
                               myvls->getStations().at(i).getLocalisation().GetcoordX(),
                               tmp_describtion);
        new_stations << tmp_station;
    }
    int to_delete = model->getVlsStations().size(); // nombre d'éléments à supprimer
    for(int i=0; i<to_delete; i++) {
        model->operationToRemoveItemAtRow(0);
    }
    model->setNewStations(new_stations);
    cost_label->setText("Coût de la solution : -");
}

void MainWindow::changeSolutionModel()
{

}

void MainWindow::setRecDetSelected()
{
    algo = 0;
    initSlidersDisabled();
}

void MainWindow::setRecStoSelected()
{
    algo = 1;

    label_recuit->setEnabled(true);
    slider_recuit->setEnabled(true);
    label_saa->setDisabled(true);
    slider_saa->setDisabled(true);
}

void MainWindow::setSaaSelected()
{
    algo = 2;

    label_recuit->setDisabled(true);
    slider_recuit->setDisabled(true);
    label_saa->setEnabled(true);
    slider_saa->setEnabled(true);
}

void MainWindow::setScenario(int nbScenario)
{
    cThread->changeNbScenario(nbScenario);
    label_recuit->setText(QString::number(nbScenario));
    if (nbScenario == 1) algo = 0;
    else algo = 1;
}

void MainWindow::setEchantillon(int nbEchantillon)
{
    cThread->changeNbEchantillon(nbEchantillon);
    label_saa->setText(QString::number(nbEchantillon));
}

void MainWindow::startComputation()
{
    if (file_label->text() != "aucun fichier") {
        Recuit *rec;
        SAA *saa;
        myvls->retrieveData(); // permet de reset les scénarios
        if (algo == 0) {
            rec = new RecuitDeterministe(NULL);
            rec->setmonProbleme(myvls);
        }
        else if (algo == 1) {
            rec = new RecuitStochastique(NULL);
            rec->setmonProbleme(myvls);
            for(int i=1; i<cThread->getNbScenario(); i++) {
                myvls->generationScenario();
            }
        }
        else if (algo == 2) {
            saa = new SAA(NULL);
            saa->setmonProbleme(myvls);
            int nb_scen_tot = cThread->getNbEchantillon()*10;
            for(int i=1; i<nb_scen_tot; i++) {
                myvls->generationScenario();
            }
            saa->generationEchantillon(cThread->getNbEchantillon());
        }
        vector<int> solutionInitial;
        for(int i=0; i<myvls->getStations().size(); i++) {
            solutionInitial.push_back(0);
        }

        if ((algo == 0) || (algo == 1)) cThread->setRecuit(rec);
        else if (algo == 2) cThread->setRecuit(saa);

        cThread->setSolutionFinale(solutionInitial);
        cThread->setSolutionInitiale(solutionInitial);

        // griser les paramètres
        disableParameters();
        // lancer l'algo dans le thread
        cThread->runningAlgo();
    }
    else {
        QMessageBox::warning(this, "Erreur",
          "Sélectionnez un fichier pour en extraire les données");
    }
}

void MainWindow::enableParameters()
{
    file_box->setEnabled(true);
    choose_grpbox->setEnabled(true);
    start_button->setEnabled(true);
}

void MainWindow::disableParameters()
{
    file_box->setDisabled(true);
    choose_grpbox->setDisabled(true);
    start_button->setDisabled(true);
}

void MainWindow::updateModel()
{
    QString tmp_describtion;
    QList<VlsStation> new_stations;
    for(int i=0; i<myvls->getStations().size(); i++)
    {
        tmp_describtion = getDescribtion(myvls->getStations().at(i), cThread->getSolutionFinale().at(i));
        VlsStation tmp_station(myvls->getStations().at(i).getLocalisation().GetcoordY(),
                               myvls->getStations().at(i).getLocalisation().GetcoordX(),
                               tmp_describtion);
        new_stations << tmp_station;
    }
    model->setNewStations(new_stations);
    cost_label->setText("Coût de la solution : " + QString::number(myvls->calculerFctObj(cThread->getSolutionFinale(), 0, 0)));
}
