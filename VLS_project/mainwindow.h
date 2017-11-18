#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QSlider>
#include <QQuickView>
#include <iostream>

#include "computationthread.h"
#include "model.h"
#include "VLS.h"
#include "RecuitDeterministe.h"
#include "RecuitStochastique.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT // autorise l'usage de slots personnalisés

    public:
        MainWindow();

    public slots:
        void chooseFile();
        void setRecDetSelected();
        void setRecStoSelected();
        void setSaaSelected();
        void setScenario(int nbScenario);
        void setEchantillon(int nbEchantillon);
        void startComputation();
        void enableParameters();
        void updateModel();

    private:

        void initSlidersDisabled();
        void disableParameters();
        void loadDataModel();
        void changeSolutionModel();
        QString getDescribtion(Station station, int sol);

        QHBoxLayout *main_layout;
        ComputationThread *cThread;

        // sélection du fichier
        QVBoxLayout *file_layout;
        QLabel *file_label;
        QPushButton *file_button;
        QGroupBox *file_box;

        // choix de l'algorithme
        QGroupBox *choose_grpbox;
        QRadioButton *choose_recuit_det;
        QRadioButton *choose_recuit_sto;
        QSlider *slider_recuit;
        QHBoxLayout *slider_recuit_layout;
        QRadioButton *choose_saa;
        QHBoxLayout *slider_saa_layout;
        QSlider *slider_saa;
        QVBoxLayout *choose_vbox;
        QLabel *label_recuit;
        QLabel *label_saa;

        // start
        QPushButton *start_button;
        QHBoxLayout *start_layout;

        // séparation de l'appli en deux parties
        QVBoxLayout *param_box;   // paramètrage
        QGroupBox *display_box; // affichage

        // map
        QVBoxLayout *map_layout;
        QQuickView *view;
        QLabel *cost_label;

        // modele
        VlsStationModel *model;

        // problème affiché
        VLS *myvls;
        int algo; // 0 : recuit déterministe, 1 : recuit stocha, 2 : SAA
};

#endif // MAINWINDOW_H
