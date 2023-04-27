#ifndef MENUAJOUT_H
#define MENUAJOUT_H

#include "vue.h"

class menuAjout : public QMainWindow
{
    Q_OBJECT
public:
    explicit menuAjout(QMainWindow *parent = nullptr);

    int getPoids() const;
    vector<int> getSuc() const;
    vector<int> getPred() const;

signals:
    void envoieAjout();

private slots:
    void onClick_valider();

private:
    vue d_vue;
    int d_poids;
    vector<int> d_suc;
    vector<int> d_pred;
};

#endif // MENUAJOUT_H
