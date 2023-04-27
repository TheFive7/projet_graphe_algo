#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "graph.h"

#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

bool Dantzig                    (vector<vector<int>>& c);
void demi_degre_interieur       (const vector<int>& FS, const vector<int>& APS, vector<int>& DDI);
void descente_largeur           (int r, const vector<int>& fs, const vector<int>& aps, vector<int>& dist);
void Dijkstra                   (const vector<int>& fs, const vector<int>& aps, const vector<vector<int>>& p, int s, vector<int> &d, vector<int> &pr);
void empiler                    (int x, vector<int>& pilch);
void englobe_ordonnancement     (const vector<int>& fs, const vector<int>& aps, const vector<int>& duree_taches, vector<int>& new_fs, vector<int>& new_aps);
void fortconnexe                (const vector<int>& FS, const vector<int>& APS, vector<int>& cfc, vector<int>& pilch, vector<int>& pred, vector<int>& prem);
void Kruskal                    (const Graph& g, Graph &t);
void mat_distance               (const vector<int>& FS, const vector<int>& APS, vector<vector<int>>& matriceDistance);
void Ordonnancement             (const vector<int> file_pred, const vector<int> adr_prem_pred, const vector<int> duree_taches, vector<int>& file_pred_critique, vector<int>& adr_prem_pred_critique, vector<int>& longueur_critique);
void printVector                (const vector<int>& vector);
void Prufer_decode              (const vector<int>& p, vector<vector<int>>& mat);
void Prufer_encode              (vector<vector<int>> mat, vector<int>& p);
void rang                       (vector<int>& rang, const vector<int>& FS, const vector<int>& APS);
void rangToString               (const vector<int>& FS, const vector<int>& APS);
void Tarjan                     (const vector<int>& FS, const vector<int>& APS);
void transforme_FP_APP_TO_FS_APS(const vector<int>& fp, const vector<int>& app, vector<int>& fs, vector<int>& aps);
void transforme_FS_APS_TO_FP_APP(const vector<int>& fs, const vector<int>& aps, vector<int>& fp, vector<int>& app);
void traversee                  (int s, int& p, int& k, const vector<int>& FS, const vector<int>& APS, vector<int>& cfc, vector<int>& pilch, vector<int>& pred, vector<int>& prem, vector<int>& tarj, vector<bool>& entarj, vector<int>& num, vector<int>& ro);
int  partition                  (vector<int>& t, int g, int d);
void TrierTableau_QuickSort     (vector<int>& tab, int g, int d);
void versGrapheReduit           (const vector<int>& cfc, const vector<int>& prem, const vector<int>& fs, const vector<int>& aps, vector<vector<int>>& mat);
void Graph_reduit               (const vector<int>& prem,const vector<int>& pilch,const vector<int>& cfc,const vector<int>& fs, const vector<int>& aps,vector<int>&fsr, vector<int>& apsr);
void base_Greduit               (const vector<int>& fsR, const vector<int>& apsR, vector<int>& baseR_GrapheR);
void edition_bases              (const vector<int>& prem, const vector<int>& pilch, const vector<int>& baseR, vector<int>& baseInitiale);
string toStringVector             (const vector<int>& tab);

#endif // ALGORITHMS_H
