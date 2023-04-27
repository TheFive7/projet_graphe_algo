#include "menusupprimer.h"

menuSupprimer::menuSupprimer(QWidget *parent)
    : QMainWindow{parent}, d_vue{this}
{
    d_vue.creeInterfaceSupprimer();

    connect(&d_vue, &vue::Quitter, this, &menuSupprimer::close);
}

int menuSupprimer::getId()
{
    return d_id;
}
