#include "vue.h"

vue::vue(QMainWindow* fenetre) : d_fenetre{fenetre}
{}

void vue::creeInterface(widgetGraph& wg)
{
    d_fenetre->setWindowState(Qt::WindowMaximized);
    d_fenetre->setWindowTitle("Graphe");
    d_fenetre->setMinimumSize(600, 600);

    auto central = new QWidget;
    auto mainLayout = new QVBoxLayout;
    central->setLayout(mainLayout);
    d_fenetre->setCentralWidget(central);

    setupMenu();

    mainLayout->addWidget(new QLabel("Votre graphe :"), 0, Qt::AlignLeft);

    // POUR AJOUTER LE GRAPH DANS LA VUE
    wgLayout = new QVBoxLayout();
    mainLayout->addLayout(wgLayout);

    d_wg = &wg;
    wgLayout->addWidget(d_wg);
    d_wg->show();
    //d_wg->close(); //pour fermer le graph
}

void vue::creeInterfaceSaisie()
{
    d_fenetre->setWindowTitle("Ajouter Noeud");

    auto central = new QWidget;
    auto mainLayout = new QVBoxLayout;
    central->setLayout(mainLayout);
    d_fenetre->setCentralWidget(central);

    menuAjout();
}

void vue::creeInterfaceSaisieFSAPS()
{
    d_fenetre->setWindowTitle("Saisir graph FS/APS");

    auto central = new QWidget;
    auto mainLayout = new QVBoxLayout;
    central->setLayout(mainLayout);
    d_fenetre->setCentralWidget(central);

    fenetreSaisieFSAPS();
}

void vue::creeInterfaceSaisieMatrice()
{
    d_fenetre->setWindowTitle("Saisir graph Matrice");

    auto central = new QWidget;
    auto mainLayout = new QVBoxLayout;
    central->setLayout(mainLayout);
    d_fenetre->setCentralWidget(central);

    fenetreSaisieMatrice();
}

void vue::creeInterfaceTarjan()
{
    d_fenetre->setWindowTitle("Composantes fortement connexes");

    auto central = new QWidget;
    auto mainLayout = new QVBoxLayout;
    central->setLayout(mainLayout);
    d_fenetre->setCentralWidget(central);

    fenetreTarjan();
}

void vue::creeInterfaceSupprimer()
{
    d_fenetre->setWindowTitle("Supprimer Noeud");

    auto central = new QWidget;
    auto mainLayout = new QVBoxLayout;
    central->setLayout(mainLayout);
    d_fenetre->setCentralWidget(central);

    fenetreMenuSupprimer();
}

void vue::creeInterfacePruferDecode()
{
    d_fenetre->setWindowTitle("Saisie pour Prufer (decode)");

    auto central = new QWidget;
    auto mainLayout = new QVBoxLayout;
    central->setLayout(mainLayout);
    d_fenetre->setCentralWidget(central);

    fenetrePruferDecode();
}

void vue::creeInterfaceDijkstra()
{
    d_fenetre->setWindowTitle("Saisie pour Dijkstra");

    auto central = new QWidget;
    auto mainLayout = new QVBoxLayout;
    central->setLayout(mainLayout);
    d_fenetre->setCentralWidget(central);

    fenetreDijkstra();
}
void vue::creeInterfaceOrdonnancement()
{
    d_fenetre->setWindowTitle("Saisie des taches");

    auto central = new QWidget;
    auto mainLayout = new QVBoxLayout;
    central->setLayout(mainLayout);
    d_fenetre->setCentralWidget(central);

    fenetreOrdonnancement();
}

void vue::setupMenu()
{
    setupMenuFichier();
    setupMenuAlgo();
    setupMenuInfo();
}

void vue::setupMenuFichier()
{
    auto menuGraph = d_fenetre->menuBar()->addMenu("&Fichier");

    auto actionCharger = new QAction{"Charger"};
    actionCharger->setToolTip("Charger graph");
    menuGraph->addAction(actionCharger);
    connect(actionCharger, &QAction::triggered, this, &vue::onCharger);

    auto sousMenuSaisie = menuGraph->addMenu("Saisie");

    auto actionSaisieFSAPS = new QAction{"Via FS/APS"};
    actionSaisieFSAPS->setToolTip("FS/APS");
    sousMenuSaisie->addAction(actionSaisieFSAPS);
    connect(actionSaisieFSAPS, &QAction::triggered, this, &vue::onSaisieFSAPS);

    auto actionSaisieMatrice = new QAction{"Via Matrice"};
    actionSaisieMatrice->setToolTip("Matrice");
    sousMenuSaisie->addAction(actionSaisieMatrice);
    connect(actionSaisieMatrice, &QAction::triggered, this, &vue::onSaisieMatrice);

    menuGraph->addSeparator();

    auto actionAjout = new QAction{"Ajout Noeud"};
    actionAjout->setToolTip("Ajout Noeud");
    menuGraph->addAction(actionAjout);
    connect(actionAjout, &QAction::triggered, this, &vue::onAjout);

    /*auto actionSupprimer = new QAction{"Supprimer Noeud"};
    actionSupprimer->setToolTip("Supprimer Noeud");
    menuGraph->addAction(actionSupprimer);
    connect(actionSupprimer, &QAction::triggered, this, &vue::onSuppression);*/

    menuGraph->addSeparator();

    auto actionQuitter = new QAction{"Quitter"};
    actionQuitter->setToolTip("Quitter application");
    menuGraph->addAction(actionQuitter);
    connect(actionQuitter, &QAction::triggered, this, &vue::onQuitter);
}

void vue::setupMenuAlgo()
{
    auto menuAlgo = d_fenetre->menuBar()->addMenu("&Algorithmes");

    auto actionDistance = new QAction{"Distance"};
    actionDistance->setToolTip("Distance algorithme");
    menuAlgo->addAction(actionDistance);
    connect(actionDistance, &QAction::triggered, this, &vue::onDistance);

    auto actionRang = new QAction{"Rang"};
    actionRang->setToolTip("Rang algorithme");
    menuAlgo->addAction(actionRang);
    connect(actionRang, &QAction::triggered, this, &vue::onRang);

    auto actionTarjan = new QAction{"Tarjan"};
    actionTarjan->setToolTip("Tarjan algorithme");
    menuAlgo->addAction(actionTarjan);
    connect(actionTarjan, &QAction::triggered, this, &vue::onTarjan);

    auto actionOrdonnancement = new QAction{"Ordonnancement"};
    actionOrdonnancement->setToolTip("Ordonnancement algorithme");
    menuAlgo->addAction(actionOrdonnancement);
    connect(actionOrdonnancement, &QAction::triggered, this, &vue::onOrdonnancement);

    auto actionDijkstra = new QAction{"Dijkstra"};
    actionDijkstra->setToolTip("Dijkstra algorithme");
    menuAlgo->addAction(actionDijkstra);
    connect(actionDijkstra, &QAction::triggered, this, &vue::onDijkstra);

    auto actionDantzig = new QAction{"Dantzig"};
    actionDantzig->setToolTip("Dantzig algorithme");
    menuAlgo->addAction(actionDantzig);
    connect(actionDantzig, &QAction::triggered, this, &vue::onDantzig);

    auto actionKruskal = new QAction{"Kruskal"};
    actionKruskal->setToolTip("Kruskal algorithme");
    menuAlgo->addAction(actionKruskal);
    connect(actionKruskal, &QAction::triggered, this, &vue::onKruskal);

    auto SousMenuPrufer = menuAlgo->addMenu("Prufer");

    auto actionPruferEncode = new QAction{"Prufer_encode"};
    actionPruferEncode->setToolTip("Prufer encode");
    SousMenuPrufer->addAction(actionPruferEncode);
    connect(actionPruferEncode, &QAction::triggered, this, &vue::onPruferEncode);

    auto actionPruferDecode = new QAction{"Prufer_decode"};
    actionPruferDecode->setToolTip("Prufer decode");
    SousMenuPrufer->addAction(actionPruferDecode);
    connect(actionPruferDecode, &QAction::triggered, this, &vue::onPruferDecode);
}
void vue::setupMenuInfo()
{
    auto menuInfo = d_fenetre->menuBar()->addMenu("&Info");

    auto infoDistance = new QAction{"Distance"};
    infoDistance->setToolTip("Distance algorithme");
    menuInfo->addAction(infoDistance);
    connect(infoDistance, &QAction::triggered, this, &vue::oninfoDistance);

    auto infoRang = new QAction{"Rang"};
    infoRang->setToolTip("Distance algorithme");
    menuInfo->addAction(infoRang);
    connect(infoRang, &QAction::triggered, this, &vue::oninfoRang);

    auto infoTarjan = new QAction{"Tarjan"};
    infoTarjan->setToolTip("Distance algorithme");
    menuInfo->addAction(infoTarjan);
    connect(infoTarjan, &QAction::triggered, this, &vue::oninfoTarjan);

    auto infoOrdonnancement = new QAction{"Ordonnancement"};
    infoOrdonnancement->setToolTip("Distance algorithme");
    menuInfo->addAction(infoOrdonnancement);
    connect(infoOrdonnancement, &QAction::triggered, this, &vue::oninfoOrdonnancement);

    auto infoDijkstra = new QAction{"Dijkstra"};
    infoDijkstra->setToolTip("Distance algorithme");
    menuInfo->addAction(infoDijkstra);
    connect(infoDijkstra, &QAction::triggered, this, &vue::oninfoDijkstra);

    auto infoDantzig = new QAction{"Dantzig"};
    infoDantzig->setToolTip("Distance algorithme");
    menuInfo->addAction(infoDantzig);
    connect(infoDantzig, &QAction::triggered, this, &vue::oninfoDantzig);

    auto infoKruskal = new QAction{"Kruskal"};
    infoKruskal->setToolTip("Distance algorithme");
    menuInfo->addAction(infoKruskal);
    connect(infoKruskal, &QAction::triggered, this, &vue::oninfoKruskal);

    auto SousMenuPrufer = menuInfo->addMenu("Prufer");

    auto infoPruferEncode = new QAction{"Prufer Encode"};
    infoPruferEncode->setToolTip("Distance algorithme");
    SousMenuPrufer->addAction(infoPruferEncode);
    connect(infoPruferEncode, &QAction::triggered, this, &vue::oninfoPrufer_encode);

    auto infoPruferDecode = new QAction{"Prufer Decode"};
    infoDistance->setToolTip("Distance algorithme");
    SousMenuPrufer->addAction(infoPruferDecode);
    connect(infoPruferDecode, &QAction::triggered, this, &vue::oninfoPrufer_decode);
}
void vue::menuAjout()
{
    auto layoutBas = new QHBoxLayout{};

    auto boutonValider = new QPushButton("Valider");
    layoutBas->addWidget(boutonValider);
    connect(boutonValider, &QPushButton::clicked, this, &vue::onAjouter);

    auto boutonQuitter = new QPushButton{"Quitter", nullptr};
    connect(boutonQuitter, &QPushButton::clicked, this, &vue::Quitter);
    layoutBas->addWidget(boutonQuitter);

    auto layoutInfo = new QVBoxLayout{};

    auto layoutSucc = new QHBoxLayout{};
    auto pannelSucc = new QLabel{"Successeur du noeud"};
    layoutSucc->addWidget(pannelSucc,1);

    d_suc = new QLineEdit{};
    layoutSucc->addWidget(d_suc);

    auto layoutPrec = new QHBoxLayout{};
    auto pannelPrec = new QLabel{"Predecesseur du noeud"};
    layoutPrec->addWidget(pannelPrec,1);

    d_prec = new QLineEdit{};
    layoutPrec->addWidget(d_prec);

    auto layoutPoids = new QHBoxLayout{};
    auto labelPoids = new QLabel{"Poids du noeud"};
    layoutPoids->addWidget(labelPoids,1);

    d_poids = new QLineEdit{};
    layoutPoids->addWidget(d_poids);

    layoutInfo->addLayout(layoutSucc);
    layoutInfo->addLayout(layoutPrec);
    layoutInfo->addLayout(layoutPoids);

    auto mainLayout = new QVBoxLayout;
    mainLayout->addLayout(layoutInfo);
    mainLayout->addLayout(layoutBas);

    auto central = new QWidget;
    central->setLayout(mainLayout);
    d_fenetre->setCentralWidget(central);
}

void vue::fenetreSaisieMatrice()
{
    auto layoutBas = new QHBoxLayout{};

    auto boutonValider = new QPushButton("Valider");
    layoutBas->addWidget(boutonValider);
    connect(boutonValider, &QPushButton::clicked, this, &vue::onSaisieMatriceValider);

    auto boutonQuitter = new QPushButton{"Quitter", nullptr};
    connect(boutonQuitter, &QPushButton::clicked, this, &vue::Quitter);
    layoutBas->addWidget(boutonQuitter);

    auto layoutInfo = new QVBoxLayout{};

    auto layoutN= new QHBoxLayout{};
    auto labelN = new QLabel{"Nombre de noeud : "};
    layoutN->addWidget(labelN,1);
    d_n = new QLineEdit{};
    layoutN->addWidget(d_n);

    layoutInfo->addLayout(layoutN);

    auto layoutM = new QHBoxLayout{};
    auto labelM = new QLabel{"Nombre d'arc : "};
    layoutM->addWidget(labelM,1);
    d_m = new QLineEdit{};
    layoutM->addWidget(d_m);

    layoutInfo->addLayout(layoutM);

    auto layoutMatrice= new QHBoxLayout{};
    auto labelMatrice = new QLabel{"Matrice : "};
    layoutMatrice->addWidget(labelMatrice,1);
    d_matriceSaisie = new QTextEdit{};
    layoutMatrice->addWidget(d_matriceSaisie);

    layoutInfo->addLayout(layoutMatrice);

    auto layoutCoutBox= new QHBoxLayout{};
    auto labelCoutBox = new QLabel{"Cout ? "};
    layoutCoutBox->addWidget(labelCoutBox,1);
    d_coutBox = new QCheckBox{};
    layoutCoutBox->addWidget(d_coutBox);

    layoutInfo->addLayout(layoutCoutBox,1);

    auto layoutCout= new QHBoxLayout{};
    auto labelCout = new QLabel{"Cout : "};
    layoutCout->addWidget(labelCout,1);
    d_coutSaisie = new QTextEdit{};
    layoutCout->addWidget(d_coutSaisie);

    layoutInfo->addLayout(layoutCout,1);

    auto layoutOriente= new QHBoxLayout{};
    auto labelOriente = new QLabel{"Oriente ? "};
    layoutOriente->addWidget(labelOriente,1);
    d_checkOriente = new QCheckBox{};
    layoutOriente->addWidget(d_checkOriente);

    layoutInfo->addLayout(layoutOriente,1);

    auto mainLayout = new QVBoxLayout;
    mainLayout->addLayout(layoutInfo);
    mainLayout->addLayout(layoutBas);

    auto central = new QWidget;
    central->setLayout(mainLayout);
    d_fenetre->setCentralWidget(central);
}

void vue::fenetreSaisieFSAPS()
{
    auto mainLayout = new QVBoxLayout;

    auto layoutInfo = new QVBoxLayout{};

    auto layoutFS = new QHBoxLayout{};
    auto labelFS = new QLabel{"FS : "};
    layoutFS->addWidget(labelFS,1);
    d_FSSaisie = new QLineEdit{};
    layoutFS->addWidget(d_FSSaisie);

    layoutInfo->addLayout(layoutFS,1);

    auto layoutAPS = new QHBoxLayout{};
    auto labelAPS = new QLabel{"APS : "};
    layoutAPS->addWidget(labelAPS,1);
    d_APSSaisie = new QLineEdit{};
    layoutAPS->addWidget(d_APSSaisie);

    layoutInfo->addLayout(layoutAPS,1);

    auto layoutCoutBox= new QHBoxLayout{};
    auto labelCoutBox = new QLabel{"Cout ? "};
    layoutCoutBox->addWidget(labelCoutBox,1);
    d_coutBox = new QCheckBox{};
    layoutCoutBox->addWidget(d_coutBox);

    layoutInfo->addLayout(layoutCoutBox,1);

    auto layoutCout= new QHBoxLayout{};
    auto labelCout = new QLabel{"Cout : "};
    layoutCout->addWidget(labelCout,1);
    d_coutSaisie = new QTextEdit{};
    layoutCout->addWidget(d_coutSaisie);

    layoutInfo->addLayout(layoutCout,1);

    auto layoutOriente= new QHBoxLayout{};
    auto labelOriente = new QLabel{"Oriente ? "};
    layoutOriente->addWidget(labelOriente,1);
    d_checkOriente = new QCheckBox{};
    layoutOriente->addWidget(d_checkOriente);

    layoutInfo->addLayout(layoutOriente,1);

    auto layoutBas = new QHBoxLayout{};

    auto boutonValider = new QPushButton("Valider");
    layoutBas->addWidget(boutonValider);
    connect(boutonValider, &QPushButton::clicked, this, &vue::onSaisieFSAPSValider);

    auto boutonQuitter = new QPushButton{"Quitter", nullptr};
    connect(boutonQuitter, &QPushButton::clicked, this, &vue::Quitter);
    layoutBas->addWidget(boutonQuitter);

    mainLayout->addLayout(layoutInfo);
    mainLayout->addLayout(layoutBas);

    auto central = new QWidget;
    central->setLayout(mainLayout);
    d_fenetre->setCentralWidget(central);
}

void vue::fenetrePruferDecode()
{
    auto layoutBas = new QHBoxLayout{};

    auto boutonValider = new QPushButton{"Valider"};
    layoutBas->addWidget(boutonValider);
    connect(boutonValider, &QPushButton::clicked, this, &vue::onValide_PruferDecode);

    auto boutonQuitter = new QPushButton{"Quitter"};
    layoutBas->addWidget(boutonQuitter);
    connect(boutonQuitter, &QPushButton::clicked, this, &vue::onQuitte_PruferDecode);

    auto layoutInfo = new QVBoxLayout{};

    auto layoutP = new QHBoxLayout{};
    auto pannelP = new QLabel{"Saisie d'un tableau de Prufer"};
    layoutP->addWidget(pannelP);
    d_p = new QLineEdit{};
    layoutP->addWidget(d_p);

    layoutInfo->addLayout(layoutP);

    auto mainLayout = new QVBoxLayout;
    mainLayout->addLayout(layoutInfo);
    mainLayout->addLayout(layoutBas);

    auto central = new QWidget;
    central->setLayout(mainLayout);
    d_fenetre->setCentralWidget(central);
}
void vue::fenetreDijkstra()
{
    auto layoutBas = new QHBoxLayout{};

    auto boutonValider = new QPushButton{"Valider", nullptr};
    layoutBas->addWidget(boutonValider);
    connect(boutonValider, &QPushButton::clicked, this, &vue::onValide_Dijkstra);

    auto boutonQuitter = new QPushButton{"Quitter", nullptr};
    layoutBas->addWidget(boutonQuitter);
    connect(boutonQuitter, &QPushButton::clicked, this, &vue::onQuitte_Dijkstra);

    auto layoutInfo = new QVBoxLayout{};

    auto layoutS = new QHBoxLayout{};
    auto pannelS = new QLabel{"Saisie du sommet de depart", nullptr};
    layoutS->addWidget(pannelS);
    d_sommet_depart = new QLineEdit{};
    layoutS->addWidget(d_sommet_depart);

    layoutInfo->addLayout(layoutS);

    auto mainLayout = new QVBoxLayout;
    mainLayout->addLayout(layoutInfo);
    mainLayout->addLayout(layoutBas);

    auto central = new QWidget;
    central->setLayout(mainLayout);
    d_fenetre->setCentralWidget(central);
}
void vue::fenetreOrdonnancement()
{
    auto layoutBas = new QHBoxLayout{};

    auto boutonValider = new QPushButton{"Valider", nullptr};
    layoutBas->addWidget(boutonValider);
    connect(boutonValider, &QPushButton::clicked, this, &vue::onValide_Ordonnancement);

    auto boutonQuitter = new QPushButton{"Quitter", nullptr};
    layoutBas->addWidget(boutonQuitter);
    connect(boutonQuitter, &QPushButton::clicked, this, &vue::onQuitte_Ordonnancement);

    auto layoutInfo = new QVBoxLayout{};

    auto layoutTache = new QHBoxLayout{};
    auto pannelTache = new QLabel{"Saisie des taches sous la forme : NOM_TACHE>DUREE>PREDECESSEURS_1-PREDECESSEURS_1-... OU '0', ... ", nullptr};
    layoutTache->addWidget(pannelTache);
    d_taches = new QTextEdit{};
    layoutTache->addWidget(d_taches);

    layoutInfo->addLayout(layoutTache);

    auto mainLayout = new QVBoxLayout;
    mainLayout->addLayout(layoutInfo);
    mainLayout->addLayout(layoutBas);

    auto central = new QWidget;
    central->setLayout(mainLayout);
    d_fenetre->setCentralWidget(central);
}

void vue::fenetreMenuSupprimer()
{
    auto mainLayout = new QVBoxLayout;

    auto layoutBas = new QHBoxLayout{};

    auto boutonValider = new QPushButton{"Valider"};
    layoutBas->addWidget(boutonValider);
    connect(boutonValider, &QPushButton::clicked, this, &vue::onAjouter);

    auto boutonQuitter = new QPushButton{"Quitter"};
    layoutBas->addWidget(boutonQuitter);
    connect(boutonQuitter, &QPushButton::clicked, this, &vue::Quitter);

    //auto layoutInfo = new QVBoxLayout{};

    auto layoutId = new QHBoxLayout{};
    auto labelId = new QLabel("Identifiant du noeud");
    layoutId->addWidget(labelId,1);

    d_idSuppr = new QLineEdit{};
    layoutId->addWidget(d_idSuppr);

    mainLayout->addLayout(layoutId);
    mainLayout->addLayout(layoutBas);
    //mainLayout->addLayout(layoutInfo);

    auto central = new QWidget;
    central->setLayout(mainLayout);
    d_fenetre->setCentralWidget(central);
}

void vue::fenetreTarjan()
{
    auto layoutBas = new QHBoxLayout{};
    auto boutonQuitter = new QPushButton{"Quitter", nullptr};
    layoutBas->addWidget(boutonQuitter);
    connect(boutonQuitter, &QPushButton::clicked, this, &vue::onQuitte_Ordonnancement);


    auto mainLayout = new QVBoxLayout;
    mainLayout->addLayout(layoutBas);

    auto central = new QWidget;
    central->setLayout(mainLayout);
    d_fenetre->setCentralWidget(central);
}

void vue::onQuitter()
{
    emit Quitter();
}
void vue::onCharger()
{
    emit Charger();
}

void vue::onSaisieFSAPS()
{
    emit SaisieFSAPS();
}

void vue::onSaisieMatrice()
{
    emit SaisieMatrice();
}

void vue::onAjout()
{
    emit Ajout();
}

void vue::onSuppression()
{
    emit Suppression();
}

void vue::onDistance()
{
    emit AlgorithmeSelectionneDistance();
}

void vue::onRang()
{
    emit AlgorithmeSelectionneRang();
}

void vue::onTarjan()
{
    emit AlgorithmeSelectionneTarjan();
}

void vue::onOrdonnancement()
{
    emit AlgorithmeSelectionneOrdonnancement();
}

void vue::onDijkstra()
{
    emit AlgorithmeSelectionneDijkstra();
}

void vue::onDantzig()
{
    emit AlgorithmeSelectionneDantzig();
}

void vue::onKruskal()
{
    emit AlgorithmeSelectionneKruskal();
}

void vue::onPruferEncode()
{
    emit AlgorithmeSelectionnePruferEncode();
}

void vue::onPruferDecode()
{
    emit AlgorithmeSelectionnePruferDecode();
}

void vue::oninfoDistance()
{
    emit InfoDistance();
}

void vue::oninfoRang()
{
    emit InfoRang();
}

void vue::oninfoTarjan()
{
    emit InfoTarjan();
}

void vue::oninfoOrdonnancement()
{
    emit InfoOrdonnancement();
}

void vue::onSaisieFSAPSValider()
{
    emit saisieFSAPSValider();
}

void vue::onSaisieMatriceValider()
{
    emit saisieMatriceValider();
}

void vue::oninfoDijkstra()
{
    emit InfoDijkstra();
}

void vue::oninfoDantzig()
{
    emit InfoDantzig();
}

void vue::oninfoKruskal()
{
    emit InfoKruskal();
}

void vue::oninfoPrufer_encode()
{
    emit InfoPrufer_encode();
}

void vue::oninfoPrufer_decode()
{
    emit InfoPrufer_decode();
}

void vue::onAjouter()
{
    emit Ajouter();
}

void vue::onValide_PruferDecode()
{
    emit Valider_PruferDecode();
}

void vue::onQuitte_PruferDecode()
{
    emit Quitte_PruferDecode();
}
void vue::onValide_Dijkstra()
{
    emit Valider_Dijkstra();
}

void vue::onQuitte_Dijkstra()
{
    emit Quitter_Dijkstra();
}
void vue::onValide_Ordonnancement()
{
    emit Valider_Ordonnancement();
}

void vue::onQuitte_Ordonnancement()
{
    emit Quitter_Ordonnancement();
}

int vue::getPoids()
{
    return this->d_poids->text().toInt();
}

vector<int> vue::getSuc()
{
    QString s = this->d_suc->text();
    vector<int> suc;
    suc.push_back(0);
    QStringList list = s.split(',');
    for(unsigned i = 0 ; i < list.size() ; ++i)
        suc.push_back(list[i].toInt());
    return suc;
}

vector<int> vue::getPred()
{
    QString s = this->d_prec->text();
    vector<int> prec;
    prec.push_back(0);
    QStringList list = s.split(',');
    for(unsigned i = 0 ; i < list.size() ; ++i)
        prec.push_back(list[i].toInt());
    return prec;
}


vector<int> vue::getP()
{
    QString s = this->d_p->text();
    vector<int> p;
    QStringList list = s.split(',');
    for(unsigned i = 0 ; i < list.size() ; ++i)
        p.push_back(list[i].toInt());
    return p;
}
int vue::getSommet_depart()
{
    return this->d_sommet_depart->text().toInt();
}
vector<int> vue::getDureeTaches()
{
    QString s = this->d_taches->toPlainText();
    vector<int> duree;
    QStringList list = s.split(',');
    for(unsigned i = 0 ; i < list.size() ; ++i)
    {
        QStringList nom = list[i].split('>');
        duree.push_back(nom[1].toInt());
    }
    return duree;
}

vector<int> vue::getFpOrd()
{
    QString s = this->d_taches->toPlainText();
    vector<int> fp;
    QStringList list = s.split(',');
    for(unsigned i = 0 ; i < list.size() ; ++i)
    {
        QStringList nom = list[i].split('>');
        QStringList pred = nom[2].split('-');
        for(unsigned j = 0 ; j < pred.size() ; ++j)
        {
            if(pred[j].toInt() != '0')
                fp.push_back(pred[j].toInt());
        }
        fp.push_back(0);
    }
    fp[0] = fp.size()-1;
    return fp;
}

vector<vector<int>> vue::getCoutSaisie()
{
    QString s = this->d_coutSaisie->toPlainText();
    QStringList ligne = s.split(",");
    int n = getAPSSaisie()[0];
    int m = getFSSaisie()[0] - n;
    vector<vector<int>> nCout(n+1);
    int cpt = 0;
    nCout[0].resize(2);
    nCout[0][0] = n;
    nCout[0][1] = m;

    for(int i = 1; i <= n; ++i)
    {
           nCout[i].reserve(n+1);
           nCout[i].push_back(0);
           for(int j = 1; j <= n; ++j)
           {
               nCout[i].push_back(ligne[cpt].toInt());
               cpt++;
           }
    }

    return nCout;
}

vector<int> vue::getAPSSaisie()
{
    QString s = this->d_APSSaisie->text();
    vector<int> p;
    QStringList list = s.split(',');
    for(unsigned i = 0 ; i < list.size() ; ++i)
        p.push_back(list[i].toInt());
    return p;
}

vector<int> vue::getFSSaisie()
{
    QString s = this->d_FSSaisie->text();
    vector<int> p;
    QStringList list = s.split(',');
    for(unsigned i = 0 ; i < list.size() ; ++i)
        p.push_back(list[i].toInt());
    return p;
}

bool vue::getBoxSaisie()
{
    return d_coutBox->isChecked();
}

bool vue::getBoxOrienteSaisie()
{
     return d_checkOriente->isChecked();
}

int vue::getN()
{
    return d_n->text().toInt();
}

int vue::getM()
{
    return d_m->text().toInt();
}


vector<vector<int>> vue::getMatriceSaisie()
{
    QString s = this->d_matriceSaisie->toPlainText();
    QStringList ligne = s.split(",");
    int n = getN();
    int m = getM();
    vector<vector<int>> matrice(n+1);
    int cpt = 0;
    matrice[0].resize(2);
    matrice[0][0] = n;
    matrice[0][1] = m;

    for(int i = 1; i <= n; ++i)
    {
           matrice[i].reserve(n+1);
           matrice[i].push_back(0);
           for(int j = 1; j <= n; ++j)
           {
               matrice[i].push_back(ligne[cpt].toInt());
               cpt++;
           }
    }
    return matrice;
}

void vue::setWidgetGraph(widgetGraph* wg)
{
    d_wg = wg;
}
