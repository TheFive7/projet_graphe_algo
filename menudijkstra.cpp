#include "menudijkstra.h"

menudijkstra::menudijkstra(QMainWindow *parent) : QMainWindow{parent}, d_vue{this}
{
    d_vue.creeInterfaceDijkstra();

    connect(&d_vue, &vue::Valider_Dijkstra, this, &menudijkstra::onClick_valider);
    connect(&d_vue, &vue::Quitter_Dijkstra, this, &menudijkstra::close);
}
int menudijkstra::getSommet()
{
    return d_sommet;
}
void menudijkstra::onClick_valider()
{
    d_sommet = d_vue.getSommet_depart();

    emit valide();

    close();
}

