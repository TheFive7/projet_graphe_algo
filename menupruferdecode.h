#ifndef MENUPRUFERDECODE_H
#define MENUPRUFERDECODE_H

#include "vue.h"

class menuPruferDecode : public QMainWindow
{
    Q_OBJECT
public:
    explicit menuPruferDecode(QMainWindow *parent = nullptr);

    vector<int> getP();

signals :
    void valide();

private slots :
    void onClick_valider();
private:
    vue d_vue;
    vector<int> d_p;
};

#endif // MENUPRUFERDECODE_H
