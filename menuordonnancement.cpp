#include "menuordonnancement.h"

menuOrdonnancement::menuOrdonnancement(QMainWindow *parent) : QMainWindow{parent}, d_vue{this}
{
    d_vue.creeInterfaceOrdonnancement();

    connect(&d_vue, &vue::Valider_Ordonnancement, this, &menuOrdonnancement::onClick_valider);
    connect(&d_vue, &vue::Quitter_Ordonnancement, this, &menuOrdonnancement::close);
}

vector<int> menuOrdonnancement::getDuree() const
{
    return d_duree;
}

vector<int> menuOrdonnancement::getFp() const
{
    return d_fp;
}

vector<int> menuOrdonnancement::getApp() const
{
    return d_app;
}


void menuOrdonnancement::onClick_valider()
{
    d_duree = d_vue.getDureeTaches();
    d_fp = d_vue.getFpOrd();

    vector<int> new_app(d_duree.size()+1);

    //Construire APP a partir de FP
    new_app[0] = d_duree.size();
    new_app[1] = 1;
    int k = 2;
    int ind_crt = 2;
    for(int i = 1 ; i <= d_fp[0] ; ++i)
    {
        if(d_fp[i] == 0 && k < d_fp[0])
        {
            new_app[ind_crt] = k;
            ind_crt++;
        }
        k++;
    }

    d_app = new_app;

    emit valide();

    close();
}

