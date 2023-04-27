#ifndef TEST_H
#define TEST_H

#include "algorithms.h"

#include <fstream>

using std::cerr;

const int COUT_INFINI = 500000;

/** FS_1 & APS_1 + cout_1
 *  Un noeud sans prédécesseurs (1)
 */
const vector<int> FS_1 {16, 2, 3, 0, 4, 7, 0, 4, 0, 5, 0, 6, 7, 0, 0, 6, 0};
const vector<int> APS_1 {7, 1, 4, 7, 9, 11, 14, 15};
const vector<vector<int>> cout_1 {
    {7, 9},
    {0, 0, 5, 2, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 6},
    {0, 0, 0, 0, 2, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 2, 2},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0},
};

/** FS_2 & APS_2
 *  Un noeud sans prédécesseurs (1)
 *  Une composante fortement connexe (6 - 7)
 */
const vector<int> FS_2 {17, 2, 3, 0, 4, 7, 0, 4, 0, 5, 0, 6, 7, 0, 7, 0, 6, 0};
const vector<int> APS_2 {7, 1, 4, 7, 9, 11, 14, 16};

/** FS_3 & APS_3 + matAdj_3
 * @todo définir ce qu'il y a de-dans
 */
const vector<int> FS_3 {22, 2, 3, 4, 0, 0, 6, 0, 7, 0, 1, 2, 6, 0, 3, 4, 7, 8, 0, 4, 0, 7, 0};
const vector<int> APS_3 {8, 1, 5, 6, 8, 10, 14, 19, 21};
const vector<vector<int>> matAdj_3 {
    {8, 14},
    {0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 1, 1, 1, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 1, 1},
    {0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0},
};

/** FS_4 & APS_4
 * 2 noeuds sans prédécesseurs (1 - 8)
 * 2 composantes fortement connexes (5 - 6 - 4 - 3 - 2) (10 - 9 - 8)
 *
 * @details Représente le graphe utilisé pour l'exemple de Tarjan dans le cours
 */
const vector<int> FS_4 {26, 2, 7, 0, 3, 5, 0, 4, 0, 6, 0, 4, 0, 2, 5, 7, 0, 0, 1, 9, 0, 10, 0, 3, 8, 9, 0};
const vector<int> APS_4 {10, 1, 4, 7, 9, 11, 13, 17, 18, 21, 23};

/** FS_5 & APS_5
 *  1 noeud sans predecesseur (1)
 *  1 -> 2 - > 3 < - 4 -> 5 / 1 -> 3
 *
*/
const vector<int> FS_5 {10, 2, 3, 0, 4, 0, 0, 3, 5, 0, 0};
const vector<int> APS_5 {5, 1, 4, 6, 7, 10};
const vector<int> duree_taches{5, 4, 5, 7, 2, 1};


/** FS_6 & APS_6 + COUTS_6
 *
 *
*/
const vector<int> FS_6 {13, 2, 4, 0, 4, 5, 0, 4, 0, 0, 1, 3, 4, 0};
const vector<int> APS_6 {5, 1, 4, 7, 9, 10};
const vector<vector<int>> COUTS_6 {
    {5, 8},
    {0, 0      ,  -2,  4      ,  COUT_INFINI, COUT_INFINI},
    {0, COUT_INFINI     ,  0      ,  COUT_INFINI,  4      , 3      },
    {0, COUT_INFINI,  COUT_INFINI,  0      ,  1      , COUT_INFINI},
    {0, COUT_INFINI,  COUT_INFINI,  COUT_INFINI,  0      , COUT_INFINI},
    {0, 0      ,  COUT_INFINI,  -1     ,  -1     , 0      },
};/*
const vector<vector<int>> COUTS_6 {
    {5, 8},
    {0,0,-2,4 ,0 ,0},
    {0,0,0 ,0 ,4 ,3},
    {0,0,0 ,0 ,1 ,0},
    {0,0,0 ,0 ,0 ,0},
    {0,0,0 ,-1,-1,0},
};
*/

/** FS_7 & APS_7 + COUTS_7
 *
 *
*/
const vector<int> FS_7 {6, 2, 3, 0, 3, 0, 0};
const vector<int> APS_7 {3, 1, 4, 6};
const vector<vector<int>> COUTS_7 {
    {3,6},
    {0,0,0,3},
    {0,COUT_INFINI,0,2},
    {0,COUT_INFINI,COUT_INFINI,0},
};

/* -------------------------------------------------- */

void test();

void testAjoutNoeud();
void testDantzig();
void testDijkstra();
void testDistance();
void testLoadGraph();
void testOrdonnancement();
void testPrufer();
void testRang();
void testTarjan();
void testTransforme_FP_APP_TO_FS_APS();

#endif // TEST_H
