#ifndef WIDGETGRAPH_H
#define WIDGETGRAPH_H

#include "algorithms.h"
#include "graph.h"
#include "widgetedge.h"
#include "widgetnode.h"

#include <QGraphicsView>
#include <QKeyEvent>

class widgetGraph : public QGraphicsView
{
    Q_OBJECT

public:
    widgetGraph(QWidget *parent = nullptr);
    widgetGraph(unsigned sceneSize, QWidget *parent = nullptr);
    widgetGraph(unsigned sceneSizeW, unsigned sceneSizeH, QWidget *parent = nullptr);

    vector<int>         getFs() const;
    vector<int>         getAps() const;
    vector<vector<int>> getCouts() const;
    vector<vector<int>> getMatrice() const;
    bool                getUsingFSandAPS() const;
    bool                getOriente() const;
    Graph               getGraph() const;

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

    void ajouterNoeud   (const Noeud& noeud, const vector<int>& pred, const vector<int>& succ);
    void centerGraph    ();
    void itemMoved      ();
    void loadFrom       (std::istream& ist);
    void loadGraph      (const Graph& g);
    void saveIn         (std::ostream& ost);

public slots:
    void zoomIn();
    void zoomOut();

protected:
    void drawBackground (QPainter *painter, const QRectF &rect) override;
    void keyPressEvent  (QKeyEvent *event) override;
    void scaleView      (qreal scaleFactor);
    void timerEvent     (QTimerEvent *event) override;
#if QT_CONFIG(wheelevent)
    void wheelEvent     (QWheelEvent *event) override;
#endif

private:
    Graph               d_g;
    QList<widgetNode*>  nodes;
    QGraphicsScene*     scene;
    unsigned            sceneSizeW, sceneSizeH;
    int                 timerId = 0;

    void    centerNode              (widgetNode* node);
    void    moveGraph               (qreal dx, qreal dy);
    void    setup                   ();
    void    transformeVersMatrice   ();
    void    transformeVersFS_APS    ();
};

#endif // WIDGETGRAPH_H
