#ifndef APPLICATION_H
#define APPLICATION_H

#include "graph.h"
#include "algorithms.h"

class application
{
public:
    application();

    void menuPrincipal();

    void load();
    void FSandAPS();
    void matrice();
    void fichier();
    void algorithmes();

    bool verifieDistance();
    bool verifieRang();
    bool verifieTarjan();
    bool verifieOrdonnancement();
    bool verifieDijkstra(int sommet_depart);
    bool verifieDantzig();
    bool verifieKruskal();
    bool verifiePruferEncode();
    bool verifiePruferDecode(const vector<int>& p);

    bool                englobe_Dantzig         ();
    void                englobe_Dijkstra        (int sommet_depart,vector<int>& d, vector<int>& pr);
    vector<vector<int>> englobe_Distance        ();
    void                englobe_Kruskal         ();
    void                englobe_Ordonnancement  (const vector<int>& duree_taches, const vector<int>& fp, const vector<int>& app, vector<int>& longueur_critique);
    void                englobe_Prufer_decode   (const vector<int>& p);
    vector<int>         englobe_Prufer_encode   ();
    vector<int>         englobe_Rang            ();
    void                englobe_Tarjan          (vector<int>& cfc, vector<int>& pilch, vector<int>& pred, vector<int>& prem, vector<int>& base, vector<int>& baseInitiale);
    bool                verifieFS_APS_NonVide   ();
    bool                verifieMatrice_NonVide  ();
    bool                verifieCout_NonVide     ();
private:
    Graph d_graphe;
    void    transformeVersMatrice   ();
    void    transformeVersFS_APS    ();
};

#endif // APPLICATION_H
