#ifndef MENUSUPPRIMER_H
#define MENUSUPPRIMER_H

#include <QMainWindow>
#include "vue.h"

class menuSupprimer : public QMainWindow
{
    Q_OBJECT
public:
    explicit menuSupprimer(QWidget *parent = nullptr);

    int getId();
signals:
private:
    vue d_vue;
    int d_id;
};

#endif // MENUSUPPRIMER_H
