#ifndef MENUDIJKSTRA_H
#define MENUDIJKSTRA_H

#include "vue.h"
#include <QLabel>
#include <QMainWindow>

class menudijkstra : public QMainWindow
{
    Q_OBJECT
public:
    explicit menudijkstra(QMainWindow *parent = nullptr);

    int getSommet();
signals :
    void valide();
private slots :
    void onClick_valider();
private:
    vue d_vue;
    int d_sommet;
};


#endif // MENUDIJKSTRA_H
