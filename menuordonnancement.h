#ifndef MENUORDONNANCEMENT_H
#define MENUORDONNANCEMENT_H

#include "vue.h"
#include <QLabel>
#include <QMainWindow>

class menuOrdonnancement : public QMainWindow
{
    Q_OBJECT
public:
    explicit menuOrdonnancement(QMainWindow *parent = nullptr);

    vector<int> getDuree() const;
    vector<int> getFp() const;
    vector<int> getApp() const;
signals :
    void valide();
private slots :
    void onClick_valider();
private:
    vue d_vue;
    vector<int> d_duree;
    vector<int> d_fp;
    vector<int> d_app;
};


#endif // MENUORDONNANCEMENT_H
