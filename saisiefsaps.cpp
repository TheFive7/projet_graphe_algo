#include "saisiefsaps.h"

saisieFSAPS::saisieFSAPS(QWidget *parent) : QMainWindow{parent}, d_vue{this}
{
    d_vue.creeInterfaceSaisieFSAPS();

    connect(&d_vue, &vue::saisieFSAPSValider, this, &saisieFSAPS::onClick_valider);
    connect(&d_vue, &vue::Quitter, this, &saisieFSAPS::close);
}

void saisieFSAPS::onClick_valider()
{
    d_FS = d_vue.getFSSaisie();
    d_APS = d_vue.getAPSSaisie();
    d_checkOriente = d_vue.getBoxOrienteSaisie();
    d_Check = d_vue.getBoxSaisie();
    if(d_Check)
        d_cout = d_vue.getCoutSaisie();

    emit envoieSaisieFSAPS();

    close();
}

vector<int> saisieFSAPS::getFS()
{
    return d_FS;
}

vector<int> saisieFSAPS::getAPS()
{
    return d_APS;
}

vector<vector<int>> saisieFSAPS::getCout()
{
    return d_cout;
}

bool saisieFSAPS::getCheck()
{
    return d_Check;
}

bool saisieFSAPS::getCheckOriente()
{
    return d_checkOriente;
}
