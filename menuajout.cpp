#include "menuajout.h"

menuAjout::menuAjout(QMainWindow *parent) : QMainWindow{parent}, d_vue{this}
{
    d_vue.creeInterfaceSaisie();

    connect(&d_vue, &vue::Ajouter, this, &menuAjout::onClick_valider);
    connect(&d_vue, &vue::Quitter, this, &menuAjout::close);

}

void menuAjout::onClick_valider()
{
    //d_id = d_vue.getId();
    d_poids = d_vue.getPoids();
    d_pred = d_vue.getPred();
    d_suc = d_vue.getSuc();

    emit envoieAjout();

    close();
}

int  menuAjout::getPoids() const
{
    return d_poids;
}

vector<int> menuAjout::getPred() const
{
    return d_pred;
}

vector<int> menuAjout::getSuc() const
{
    return d_suc;
}
