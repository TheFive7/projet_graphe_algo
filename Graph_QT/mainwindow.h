#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "widgetgraph.h"
#include "vue.h"
#include "menuajout.h"
#include "menupruferdecode.h"

#include "menudijkstra.h"
#include "menuordonnancement.h"

#include "menusupprimer.h"
#include "saisiefsaps.h"
#include "saisiematrice.h"

#include <fstream>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QMainWindow* parent = nullptr);
private:
    widgetGraph d_wg;

    widgetGraph d_wgClone;

    vue d_vue;

    bool verifieDistance();
    bool verifieRang();
    bool verifieTarjan();
    bool verifieOrdonnancement();
    bool verifieDijkstra(int sommet_depart);
    bool verifieDantzig();
    bool verifieKruskal();
    bool verifiePruferEncode();
    bool verifiePruferDecode(const vector<int>& p);

    menuPruferDecode *menuPruferD;
    menudijkstra *menuDijkstra;
    menuOrdonnancement *menuOrd;
    menuAjout *menuS;
    menuSupprimer *menuSuppr;
    saisieFSAPS *menuFSAPS;
    saisieMatrice *menuMatrice;
private slots :

    void charge();
    void saisieMatrice();
    void saisieFSAPS();
    void ajoute();
    void supprime();
    void onClick_Distance();
    void onClick_Rang();
    void onClick_Tarjan();
    void onClick_Ordonnancement();
    void onClick_Dijkstra();
    void onClick_Dantzig();
    void onClick_Kruskal();
    void onClick_Prufer_encode();
    void onClick_Prufer_decode();

    void onClickDistance_INFO();
    void onClickRang_INFO();
    void onClickTarjan_INFO();
    void onClickOrdonnancement_INFO();
    void onClickDijkstra_INFO();
    void onClickDantzig_INFO();
    void onClickKruskal_INFO();
    void onClickPrufer_encode_INFO();
    void onClickPrufer_decode_INFO();

    void onValiderAjout();
    void onValiderPruferDecode();
    void onValiderDijkstra();
    void onValiderOrdonnancement();
    void onValideSaisieFSAPS();
    void onValideSaisieMatrice();
};

#endif // MAINWINDOW_H
