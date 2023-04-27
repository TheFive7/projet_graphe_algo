#ifndef SAISIEMATRICE_H
#define SAISIEMATRICE_H

#include <QMainWindow>
#include "vue.h"

class saisieMatrice : public QMainWindow
{
    Q_OBJECT
public:
    explicit saisieMatrice(QWidget *parent = nullptr);
    vector<vector<int>> getMatrice();
    vector<vector<int>> getCout();
    bool getCheck();
    int getN();
    int getM();
    bool getCheckOriente();
signals:
    void envoieSaisieMatrice();

private slots:
    void onClick_valider();
private:
    vue d_vue;
    vector<vector<int>> d_matrice;
    vector<vector<int>> d_cout;
    bool d_check;
    int d_n;
    int d_m;
    bool d_checkOriente;
};

#endif // SAISIEMATRICE_H
