#include "widgetgraph.h"
#include "cmath"

widgetGraph::widgetGraph(QWidget *parent) : QGraphicsView(parent), sceneSizeW{900}, sceneSizeH{900} {
    setup();
}

widgetGraph::widgetGraph(unsigned sceneSize, QWidget *parent) : QGraphicsView(parent), sceneSizeW{sceneSize}, sceneSizeH{sceneSize} {
    setup();
}

widgetGraph::widgetGraph(unsigned sceneSizeW, unsigned sceneSizeH, QWidget *parent) : QGraphicsView(parent), sceneSizeW{sceneSizeW}, sceneSizeH{sceneSizeH} {
    setup();
}

void widgetGraph::setup() {
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(1), qreal(1));

    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-(int)sceneSizeW, -(int)sceneSizeH / 2, sceneSizeW * 2, sceneSizeH);
    setScene(scene);

    d_g = Graph();
    loadGraph(d_g);
    ajouterNoeud(Noeud(2), {0, 1, 0}, {0, 0, 0});
    ajouterNoeud(Noeud(3), {0, 1, 0, 0}, {0, 0, 1, 0});
    ajouterNoeud(Noeud(4), {0, 0, 1, 1, 0}, {0, 0, 1, 0, 0});
}

void widgetGraph::itemMoved() {
    if (!timerId) {
        timerId = startTimer(1000 / 25);
    }
}

void widgetGraph::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Up:
        moveGraph(0, -20);
        break;
    case Qt::Key_Down:
        moveGraph(0, 20);
        break;
    case Qt::Key_Left:
        moveGraph(-20, 0);
        break;
    case Qt::Key_Right:
        moveGraph(20, 0);
        break;
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    case Qt::Key_Space:
    case Qt::Key_Enter:
        centerGraph();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}

void widgetGraph::moveGraph(qreal dx, qreal dy) {
    for (auto node : nodes) {
        node->moveBy(dx, dy);
    }
}

void widgetGraph::timerEvent(QTimerEvent *event) {
    Q_UNUSED(event);

    for (widgetNode *node : qAsConst(nodes)) {
        node->calculateForces();
    }

    bool itemsMoved = false;
    for (widgetNode *node : qAsConst(nodes)) {
        if (node->advancePosition()) {
            itemsMoved = true;
        }
    }

    if (!itemsMoved) {
        killTimer(timerId);
        timerId = 0;
    }
}

void widgetGraph::wheelEvent(QWheelEvent *event) {
    scaleView(pow(2., event->angleDelta().y() / 240.0));
}

void widgetGraph::drawBackground(QPainter *painter, const QRectF &rect) {
    Q_UNUSED(rect);

    QRectF sceneRect = this->sceneRect();

    // Remplissage
    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::white);
    painter->fillRect(rect.intersected(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);

    // Texte
    QRectF textRect(sceneRect.left() + 4, sceneRect.top() + 4, sceneRect.width() - 4, sceneRect.height() - 4);
    QString message("Présentation graphique du graphe");

    QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(14);
    painter->setFont(font);
    painter->setPen(Qt::white);
    painter->drawText(textRect.translated(2, 2), message);
    painter->setPen(Qt::black);
    painter->drawText(textRect, message);
}

void widgetGraph::scaleView(qreal scaleFactor) {
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100) {
        return;
    }

    scale(scaleFactor, scaleFactor);
}

void widgetGraph::zoomIn() {
    scaleView(1.2);
}

void widgetGraph::zoomOut() {
    scaleView(1 / 1.2);
}

vector<int> widgetGraph::getFs() const {
    return d_g.getFS();
}

vector<int> widgetGraph::getAps() const {
    return d_g.getAPS();
}

vector<vector<int>> widgetGraph::getCouts() const {
    return d_g.getCouts();
}

vector<vector<int>> widgetGraph::getMatrice() const {
    return d_g.getMatAdj();
}

bool widgetGraph::getUsingFSandAPS() const {
    return d_g.isUsingFsAndAps();
}

bool widgetGraph::getOriente() const {
    return d_g.getEst_oriente();
}

Graph widgetGraph::getGraph() const {
    return d_g;
}

bool widgetGraph::englobe_Dantzig() {
    vector<vector<int>> c = d_g.getCouts();
    if(Dantzig(c)) {
        d_g.setCout(c);
        return true;
    } else {
        return false;
    }
}

void widgetGraph::englobe_Dijkstra(int sommet_depart, vector<int>& d, vector<int>& pr) {
    cout<<"DIJK";
    if(!d_g.isUsingFsAndAps()) {
        transformeVersFS_APS();
    }

    Dijkstra(d_g.getFS(),d_g.getAPS(),d_g.getCouts(),sommet_depart,d,pr);
}

vector<vector<int>> widgetGraph::englobe_Distance() {
    vector<vector<int>> matriceDistance;
    if(!d_g.isUsingFsAndAps()) {
        transformeVersFS_APS();
    }
    mat_distance(d_g.getFS(),d_g.getAPS(),matriceDistance);
    return matriceDistance;
}

void widgetGraph::englobe_Kruskal() {
    Graph t;
    if(!d_g.isUsingFsAndAps()) {
        transformeVersFS_APS();
    }
    Kruskal(d_g,t);

    for(int i = 1 ; i < t.getMatAdj().size() ; ++i) {
        printVector(t.getMatAdj()[i]);
    }

    //loadGraph(t);
}

void widgetGraph::englobe_Ordonnancement(const vector<int>& duree_taches, const vector<int>& fp, const vector<int>& app, vector<int>& longueur_critique) {
    vector<int> new_fs, new_aps;
    vector<int> file_pred_critique;
    vector<int> adr_prem_pred_critique;

    Ordonnancement(fp, app, duree_taches, file_pred_critique, adr_prem_pred_critique, longueur_critique);

    transforme_FP_APP_TO_FS_APS(file_pred_critique,adr_prem_pred_critique,new_fs,new_aps);

    loadGraph(Graph{new_fs,new_aps});
}

void widgetGraph::englobe_Prufer_decode(const vector<int>& p) {
    vector<vector<int>> mat;
    Prufer_decode(p, mat);

    loadGraph(Graph{mat,false});
}

vector<int> widgetGraph::englobe_Prufer_encode() {
    vector<int> p;
    if(d_g.isUsingFsAndAps()) {
        transformeVersMatrice();
    }
    vector<vector<int>> mat = d_g.getMatAdj();
    Prufer_encode(mat, p);
    return p;
}

vector<int> widgetGraph::englobe_Rang() {
    vector<int> rg;
    if(!d_g.isUsingFsAndAps()) {
        transformeVersFS_APS();
    }
    rang(rg,d_g.getFS(),d_g.getAPS());
    return rg;
}

void widgetGraph::englobe_Tarjan(vector<int>& cfc, vector<int>& pilch, vector<int>& pred, vector<int>& prem, vector<int>& base, vector<int>& baseInitiale) {
    if(!d_g.isUsingFsAndAps()) {
        transformeVersFS_APS();
    }
    fortconnexe(d_g.getFS(),d_g.getAPS(),cfc,pilch,pred,prem);

    //traitement du resultat
    vector<vector<int>> mat;
    versGrapheReduit(cfc,prem,d_g.getFS(),d_g.getAPS(),mat);

    //On va utiliser g pour shortcut
    Graph g = Graph{mat};

    //determination de la base du graphe reduit :
    vector<int> fs, aps;

    // d_g.matAdj_to_FS_APS(fs,aps);
    g.matAdj_to_FS_APS(fs,aps);

    base_Greduit(fs,aps,base);

    //determination de la base du graphe initial :
    edition_bases(prem,pilch,base,baseInitiale);
}

bool widgetGraph::verifieFS_APS_NonVide() {
    if(d_g.getFS().empty() || d_g.getAPS().empty()) {
        return false;
    }
    return true;
}

bool widgetGraph::verifieMatrice_NonVide() {
    vector<vector<int>> mat = d_g.getMatAdj();
    if(mat.empty()) {
        return false;
    } else if(mat[0].size() != 2) {
        return false;
    } else {
        unsigned size = mat[1].size();
        for(unsigned i = 2 ; i < mat.size() ; ++i) {
            if(mat[i].size() != size) {
                return false;
            }
        }
        return true;
    }
}

bool widgetGraph::verifieCout_NonVide() {

    if(d_g.getCouts().empty()) {
        return false;
    } else {
         vector<vector<int>> cout = d_g.getCouts();
        if(cout[0].size() != 2) {
            return false;
        } else {
            unsigned size = cout[1].size();
            for(unsigned i = 2 ; i < cout.size() ; ++i) {
                if(cout[i].size() != size) {
                    return false;
                }
            }
            return true;
        }
    }
}

void widgetGraph::ajouterNoeud(const Noeud& noeud, const vector<int>& pred, const vector<int>& succ) {
    auto node = new widgetNode(this, noeud);
    nodes << node;
    scene->addItem(node);
    centerNode(node);

    for(unsigned i = 0; i < nodes.size(); ++i) {
        if(pred[i+1]) {
            auto edge = new widgetEdge(nodes[i], node);
            nodes[i]->addEdge(edge);
            scene->addItem(edge);
        }
        if(succ[i+1]) {
            auto edge = new widgetEdge(node, nodes[i]);
            nodes[i]->addEdge(edge);
            scene->addItem(edge);
        }
    }
    d_g.ajouterNoeud(noeud, pred, succ);
}

void widgetGraph::loadFrom(std::istream& ist) {
    d_g.loadFrom(ist);
    loadGraph(d_g);
}

void widgetGraph::transformeVersMatrice() {
    vector<vector<int>> matrice ;
    d_g.FS_APS_to_MatAdj(matrice);

    for(unsigned i = 1 ; i < matrice.size() ; ++i) {
        printVector(matrice[i]);
    }

    d_g = Graph(matrice, d_g.getSommets(), d_g.getEst_oriente(), d_g.getA_Des_Poids());
}

void widgetGraph::transformeVersFS_APS() {
    vector<int> fs, aps;
    d_g.matAdj_to_FS_APS(fs,aps);

    d_g = Graph(fs, aps, d_g.getSommets(), d_g.getEst_oriente(), d_g.getA_Des_Poids());
}

void widgetGraph::loadGraph(const Graph& g) {
    d_g = g;
    scene->clear();
    nodes.resize(0);

    for(unsigned i = 1; i < d_g.getSommets().size(); ++i) {
        auto node = new widgetNode(this, *d_g.getSommets()[i]);

        nodes << node;
        scene->addItem(node);
    }

    centerGraph();

    if(d_g.isUsingFsAndAps()) {
        for(unsigned i = 1; i < d_g.getAPS().size(); ++i) {
            unsigned j = d_g.getFS()[d_g.getAPS()[i]];
            unsigned k = d_g.getAPS()[i];
            while(j != 0) {
                int iBis = i-1, jBis = j-1;
                auto edge = new widgetEdge(nodes[iBis], nodes[jBis]);
                nodes[iBis]->addEdge(edge);
                scene->addItem(edge);
                ++k;
                j = d_g.getFS()[k];
            }
        }
    } else {
        for(unsigned i = 1; i < d_g.getMatAdj().size(); ++i) {
            for(unsigned j = 1; j < d_g.getMatAdj()[i].size(); ++j) {
                if(d_g.getMatAdj()[i][j] != 0) {
                    int iBis = i-1, jBis = j-1;
                    auto edge = new widgetEdge(nodes[iBis], nodes[jBis]);
                    nodes[iBis]->addEdge(edge);
                    scene->addItem(edge);
                }
            }
        }
    }
}

void widgetGraph::centerGraph() {
    for(auto node : nodes) {
        centerNode(node);
    }
}

void widgetGraph::centerNode(widgetNode* node) {
    if(nodes[0] == node) {
        node->setPos(0, 0);
    } else {
        auto i = nodes.indexOf(node);
        auto p = nodes[i-1]->pos();
        nodes[i]->setPos(p.x() + 50, std::pow(-1, nodes[i-1]->getNoeud()->getId()) * 50 + p.y());
    }
}

void widgetGraph::saveIn(std::ostream& ost) {
    d_g.saveIn(ost);
}



















