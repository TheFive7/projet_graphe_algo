#include "saisiematrice.h"

saisieMatrice::saisieMatrice(QWidget *parent)
    : QMainWindow{parent}, d_vue{this}
{
    d_vue.creeInterfaceSaisieMatrice();

    connect(&d_vue, &vue::saisieMatriceValider, this, &saisieMatrice::onClick_valider);
    connect(&d_vue, &vue::Quitter, this, &saisieMatrice::close);
}

void saisieMatrice::onClick_valider()
{
    d_matrice = d_vue.getMatriceSaisie();
    d_check = d_vue.getBoxSaisie();
    d_checkOriente = d_vue.getBoxOrienteSaisie();
    d_n = d_vue.getN();
    d_m = d_vue.getM();

    if(d_check)
        d_cout = d_vue.getCoutSaisie();

    emit envoieSaisieMatrice();

    close();
}

vector<vector<int>> saisieMatrice::getMatrice()
{
    return d_matrice;
}

vector<vector<int>> saisieMatrice::getCout()
{
    return d_cout;
}

bool saisieMatrice::getCheck()
{
    return d_check;
}

bool saisieMatrice::getCheckOriente()
{
    return d_checkOriente;
}


int saisieMatrice::getN()
{
    return d_n;
}

int saisieMatrice::getM()
{
    return d_m;
}

