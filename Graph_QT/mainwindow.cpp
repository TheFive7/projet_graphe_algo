#include "mainwindow.h"
#include<iostream>
#include<QMessageBox>

MainWindow::MainWindow(QMainWindow* parent) : QMainWindow{parent}, d_wg{new widgetGraph(1500, 1000)}, d_wgClone{new widgetGraph(1500,1000)}, d_vue{this}, menuPruferD{new menuPruferDecode}, menuDijkstra{new menudijkstra}, menuOrd{new menuOrdonnancement}, menuS{new menuAjout}, menuSuppr{new menuSupprimer}, menuFSAPS{new class saisieFSAPS}, menuMatrice{new class saisieMatrice}
{
    d_vue.creeInterface(d_wg);

    connect(&d_vue, &vue::Quitter, this, &MainWindow::close);
    connect(&d_vue, &vue::Charger, this, &MainWindow::charge);
    connect(&d_vue, &vue::SaisieFSAPS, this, &MainWindow::saisieFSAPS);
    connect(&d_vue, &vue::SaisieMatrice, this, &MainWindow::saisieMatrice);
    connect(&d_vue, &vue::Ajout, this, &MainWindow::ajoute);
    connect(&d_vue, &vue::Suppression, this, &MainWindow::supprime);

    connect(&d_vue, &vue::AlgorithmeSelectionneDistance, this, &MainWindow::onClick_Distance);
    connect(&d_vue, &vue::AlgorithmeSelectionneRang, this, &MainWindow::onClick_Rang);
    connect(&d_vue, &vue::AlgorithmeSelectionneTarjan, this, &MainWindow::onClick_Tarjan);
    connect(&d_vue, &vue::AlgorithmeSelectionneOrdonnancement, this, &MainWindow::onClick_Ordonnancement);
    connect(&d_vue, &vue::AlgorithmeSelectionneDijkstra, this, &MainWindow::onClick_Dijkstra);
    connect(&d_vue, &vue::AlgorithmeSelectionneDantzig, this, &MainWindow::onClick_Dantzig);
    connect(&d_vue, &vue::AlgorithmeSelectionneKruskal, this, &MainWindow::onClick_Kruskal);
    connect(&d_vue, &vue::AlgorithmeSelectionnePruferEncode, this, &MainWindow::onClick_Prufer_encode);
    connect(&d_vue, &vue::AlgorithmeSelectionnePruferDecode, this, &MainWindow::onClick_Prufer_decode);

    connect(menuPruferD, &menuPruferDecode::valide, this, &MainWindow::onValiderPruferDecode);
    connect(menuDijkstra, &menudijkstra::valide, this, &MainWindow::onValiderDijkstra);
    connect(menuOrd, &menuOrdonnancement::valide, this, &MainWindow::onValiderOrdonnancement);
    connect(menuS, &menuAjout::envoieAjout, this, &MainWindow::onValiderAjout);
    connect(menuFSAPS, &saisieFSAPS::envoieSaisieFSAPS, this, &MainWindow::onValideSaisieFSAPS);
    connect(menuMatrice, &saisieMatrice::envoieSaisieMatrice, this, &MainWindow::onValideSaisieMatrice);



    connect(&d_vue, &vue::InfoDistance, this, &MainWindow::onClickDistance_INFO);
    connect(&d_vue, &vue::InfoRang, this, &MainWindow::onClickRang_INFO);
    connect(&d_vue, &vue::InfoTarjan, this, &MainWindow::onClickTarjan_INFO);
    connect(&d_vue, &vue::InfoOrdonnancement, this, &MainWindow::onClickOrdonnancement_INFO);
    connect(&d_vue, &vue::InfoDijkstra, this, &MainWindow::onClickDijkstra_INFO);
    connect(&d_vue, &vue::InfoDantzig, this, &MainWindow::onClickDantzig_INFO);
    connect(&d_vue, &vue::InfoKruskal, this, &MainWindow::onClickKruskal_INFO);
    connect(&d_vue, &vue::InfoPrufer_encode, this, &MainWindow::onClickPrufer_encode_INFO);
    connect(&d_vue, &vue::InfoPrufer_decode, this, &MainWindow::onClickPrufer_decode_INFO);

}

bool MainWindow::verifieDistance()
{
    //Il faut que fs et aps soit initialisé ou la matrice ET que le graphe soit oriente.
    if(d_wg.getOriente())
    {
        if(d_wg.getUsingFSandAPS())
        {
            if(d_wg.verifieFS_APS_NonVide())
                return true;
            else
            {
                auto info = new QMessageBox{QMessageBox::Warning,"ERREUR DISTANCE: ","FS et APS vide !",QMessageBox::Ok};
                info->exec();
                return false;
            }
        }
        else if(d_wg.verifieMatrice_NonVide())
        {
            return true;
        }
        else
        {
            auto info = new QMessageBox{QMessageBox::Warning,"ERREUR DISTANCE: ","Matrice vide !",QMessageBox::Ok};
            info->exec();
            return false;
        }
    }
    else
    {
        auto info = new QMessageBox{QMessageBox::Warning,"ERREUR DISTANCE: ","Graphe non oriente !",QMessageBox::Ok};
        info->exec();
        return false;
    }
}

bool MainWindow::verifieRang()
{
    //Il faut que fs et aps soit initialisé ou la matrice ET que le graphe soit oriente.
    if(d_wg.getOriente())
    {
        if(d_wg.getUsingFSandAPS())
        {
            if(d_wg.verifieFS_APS_NonVide())
                return true;
            else
            {
                auto info = new QMessageBox{QMessageBox::Warning,"ERREUR RANG: ","FS et APS vide !",QMessageBox::Ok};
                info->exec();
                return false;
            }
        }
        else if(d_wg.verifieMatrice_NonVide())
        {
            return true;
        }
        else
        {
            auto info = new QMessageBox{QMessageBox::Warning,"ERREUR RANG: ","Matrice vide !",QMessageBox::Ok};
            info->exec();
            return false;
        }
    }
    else
    {
        auto info = new QMessageBox{QMessageBox::Warning,"ERREUR RANG: ","Graphe non oriente !",QMessageBox::Ok};
        info->exec();
        return false;
    }
}
bool MainWindow::verifieTarjan()
{
    //Il faut que fs et aps soit initialisé ou la matrice.
    if(d_wg.getOriente())
    {
        if(d_wg.getUsingFSandAPS())
        {
            if(d_wg.verifieFS_APS_NonVide())
                return true;
            else
            {
                auto info = new QMessageBox{QMessageBox::Warning,"ERREUR TARJAN: ","FS et APS vide !",QMessageBox::Ok};
                info->exec();
                return false;
            }
        }
        else if(d_wg.verifieMatrice_NonVide())
        {
            return true;
        }
        else
        {
            auto info = new QMessageBox{QMessageBox::Warning,"ERREUR TARJAN: ","Matrice vide !",QMessageBox::Ok};
            info->exec();
            return false;
        }
    }
    else
    {
        auto info = new QMessageBox{QMessageBox::Warning,"ERREUR TARJAN: ","Graphe non oriente !",QMessageBox::Ok};
        info->exec();
        return false;
    }
}
bool MainWindow::verifieOrdonnancement()
{
    return true; //Dans tous les cas, c'est deja verifie..
}

bool MainWindow::verifieDijkstra(int sommet_depart)
{
    //Il faut que le graphe soit oriente.
    //Il faut que fs et aps soit initialisé ou la matrice.
    //Il faut que le cout soit correct, qu'il ne contienne pas de cout < 0
    if(d_wg.getOriente())
    {
        if(d_wg.getUsingFSandAPS())
        {
            if(d_wg.verifieFS_APS_NonVide())
            {
                if(sommet_depart <= 0 || sommet_depart > d_wg.getAps()[0])
                {
                    string str = std::to_string(d_wg.getAps()[0]);
                    QString s = "Le sommet saisi n'est pas valide ! Veuillez saisir un sommet compris entre 1 et ";
                    s += s.fromStdString(str);
                    auto info = new QMessageBox{QMessageBox::Warning,"ERREUR DIJKSTRA: ",s,QMessageBox::Ok};
                    info->exec();
                    return false; //Le sommet saisi n'est pas valide !
                }
                else
                {
                    if(d_wg.verifieCout_NonVide())
                    {
                        vector<vector<int>> couts = d_wg.getCouts();
                        if(couts[0][0] != d_wg.getAps()[0] || couts[0][1] != (d_wg.getFs()[0] - d_wg.getAps()[0]))
                        {
                            auto info = new QMessageBox{QMessageBox::Warning,"ERREUR DIJKSTRA: ","Les elements presents dans le cout en ligne 0 ne correspondent pas avec le fs et aps",QMessageBox::Ok};
                            info->exec();
                            return false;//Les elements presents dans le cout ne correspondent pas avec le fs et aps
                        }
                        else
                        {
                            for(unsigned i = 1 ; i < couts.size() ; ++i)
                            {
                                for(unsigned j = 1 ; j < couts[i].size() ; ++j)
                                {
                                    if(couts[i][j] < -1)
                                    {
                                        string str = std::to_string(i);
                                        string str2 = std::to_string(j);
                                        QString s = "L'element present dans le cout en ligne ";
                                        s += s.fromStdString(str);
                                        s += " et en colonne ";
                                        s += s.fromStdString(str2);
                                        s += " est negatif ! Veuillez modifier cette valeur en positive pour utiliser Dijkstra.";
                                        auto info = new QMessageBox{QMessageBox::Warning,"ERREUR DIJKSTRA: ",s,QMessageBox::Ok};
                                        info->exec();
                                        return false;//Cout negatif interdit !
                                    }
                                }
                            }
                            return true;
                        }
                    }
                    else
                    {
                        auto info = new QMessageBox{QMessageBox::Warning,"ERREUR DIJKSTRA: ","Le cout est vide !",QMessageBox::Ok};
                        info->exec();
                        return false; //Cout vide
                    }
                }
            }
            else
            {
                auto info = new QMessageBox{QMessageBox::Warning,"ERREUR DIJKSTRA: ","FS et APS vide !",QMessageBox::Ok};
                info->exec();
                return false; //Graphe Vide - Fs & Aps
            }
        //Matrice
        }
        else
        {
            if(d_wg.verifieMatrice_NonVide())
            {
                int n = d_wg.getMatrice()[0][0];
                int m = d_wg.getMatrice()[0][1];
                if(sommet_depart <= 0 || sommet_depart > n)
                {
                    string str = std::to_string(n);
                    QString s = "Le sommet saisi n'est pas valide ! Veuillez saisir un sommet compris entre 1 et ";
                    s += s.fromStdString(str);
                    auto info = new QMessageBox{QMessageBox::Warning,"ERREUR DIJKSTRA: ",s,QMessageBox::Ok};
                    info->exec();
                    return false; //Le sommet saisi n'est pas valide !
                }
                else
                {
                    if(d_wg.verifieCout_NonVide())
                    {
                        vector<vector<int>> couts = d_wg.getCouts();
                        if(couts[0][0] != n || couts[0][1] != m)
                        {
                            auto info = new QMessageBox{QMessageBox::Warning,"ERREUR DIJKSTRA: ","Les elements presents dans le cout en ligne 0 ne correspondent pas avec la matrice",QMessageBox::Ok};
                            info->exec();
                            return false;//Les elements presents dans le cout ne correspondent pas avec la matrice
                        }
                        else
                        {
                            for(unsigned i = 1 ; i < couts.size() ; ++i)
                            {
                                for(unsigned j = 1 ; j < couts[i].size() ; ++j)
                                {
                                    if(couts[i][j] < 0)
                                    {
                                        string str = std::to_string(i);
                                        string str2 = std::to_string(j);
                                        QString s = "L'element present dans le cout en ligne ";
                                        s += s.fromStdString(str);
                                        s += " et en colonne ";
                                        s += s.fromStdString(str2);
                                        s += " est negatif ! Veuillez modifier cette valeur en positive pour utiliser Dijkstra.";
                                        auto info = new QMessageBox{QMessageBox::Warning,"ERREUR DIJKSTRA: ",s,QMessageBox::Ok};
                                        info->exec();
                                        return false;//Cout negatif interdit !
                                    }
                                }
                            }
                            return true;
                        }
                    }
                    else
                    {
                        auto info = new QMessageBox{QMessageBox::Warning,"ERREUR DIJKSTRA: ","Le cout est vide !",QMessageBox::Ok};
                        info->exec();
                        return false; //Cout vide
                    }
                }
            }
            else
            {
                auto info = new QMessageBox{QMessageBox::Warning,"ERREUR DIJKSTRA: ","Matrice vide !",QMessageBox::Ok};
                info->exec();
                return false; //Graphe Vide - Matrice
            }
        }
    }
    else
    {
        auto info = new QMessageBox{QMessageBox::Warning,"ERREUR DIJKSTRA: ","Graphe non oriente !",QMessageBox::Ok};
        info->exec();
        return false;
    }
}
bool MainWindow::verifieDantzig()
{
    //Il faut que le graphe soit oriente.
    //Il faut que le cout soit bien initialisé ou la matrice.
    if(d_wg.getOriente())
    {
        if(d_wg.getUsingFSandAPS())
        {
            if(d_wg.verifieFS_APS_NonVide())
            {
                if(d_wg.verifieCout_NonVide())
                {
                    vector<vector<int>> couts = d_wg.getCouts();
                    if(couts[0][0] != d_wg.getAps()[0] || couts[0][1] != (d_wg.getFs()[0] - d_wg.getAps()[0]))
                    {
                        auto info = new QMessageBox{QMessageBox::Warning,"ERREUR DANTZIG: ","Les elements presents dans le cout en ligne 0 ne correspondent pas avec le fs et aps",QMessageBox::Ok};
                        info->exec();
                        return false;//Les elements presents dans le cout ne correspondent pas avec le fs et aps
                    }
                    return true;
                }
                else
                {
                    auto info = new QMessageBox{QMessageBox::Warning,"ERREUR DANTZIG: ","Cout vide !",QMessageBox::Ok};
                    info->exec();
                    return false; //Cout vide
                }
            }
            else
            {
                auto info = new QMessageBox{QMessageBox::Warning,"ERREUR DANTZIG: ","FS et APS vide !",QMessageBox::Ok};
                info->exec();
                return false; //Graphe Vide - Fs & Aps
            }
        }
        else
        {
           if(d_wg.verifieMatrice_NonVide())
           {
               int n = d_wg.getMatrice()[0][0];
               int m = d_wg.getMatrice()[0][1];
               vector<vector<int>> couts = d_wg.getCouts();
               if(couts[0][0] != n || couts[0][1] != m)
               {
                   auto info = new QMessageBox{QMessageBox::Warning,"ERREUR DANTZIG: ","Les elements presents dans le cout en ligne 0 ne correspondent pas avec la matrice",QMessageBox::Ok};
                   info->exec();
                   return false;//Les elements presents dans le cout ne correspondent pas avec la matrice
               }
               return true;
           }
           else
           {
               auto info = new QMessageBox{QMessageBox::Warning,"ERREUR DANTZIG: ","Matrice vide !",QMessageBox::Ok};
               info->exec();
               return false; //Graphe Vide - Matrice
           }
        }
    }
    else
    {
        auto info = new QMessageBox{QMessageBox::Warning,"ERREUR DANTZIG: ","Graphe non oriente !",QMessageBox::Ok};
        info->exec();
        return false;
    }
    return false;
}

bool MainWindow::verifieKruskal()
{
    //Il faut que fs et aps soit initialisé ou la matrice ET que le graphe soit non oriente.
    if(!d_wg.getOriente())
    {
        if(d_wg.getUsingFSandAPS())
        {
            if(d_wg.verifieFS_APS_NonVide())
            {
                return true;
            }
            else
            {
                auto info = new QMessageBox{QMessageBox::Warning,"ERREUR KRUSKAL: ","FS et APS vide !",QMessageBox::Ok};
                info->exec();
                return false;
            }
        }
        else if(d_wg.verifieMatrice_NonVide())
        {
            return true;
        }
        else
        {
            auto info = new QMessageBox{QMessageBox::Warning,"ERREUR KRUSKAL: ","Matrice vide !",QMessageBox::Ok};
            info->exec();
            return false;
        }
    }
    else
    {
        auto info = new QMessageBox{QMessageBox::Warning,"ERREUR KRUSKAL: ","Graphe oriente !",QMessageBox::Ok};
        info->exec();
        return false;
    }
}

bool MainWindow::verifiePruferEncode()
{
    //Il faut que fs et aps soit initialisé ou la matrice ET que le graphe soit non oriente.
    if(!d_wg.getOriente())
    {
        if(d_wg.getUsingFSandAPS())
        {
            if(d_wg.verifieFS_APS_NonVide())
                return true;
            else
            {
                auto info = new QMessageBox{QMessageBox::Warning,"ERREUR PRUFER_ENCODE: ","FS et APS vide !",QMessageBox::Ok};
                info->exec();
                return false;
            }
        }
        else if(d_wg.verifieMatrice_NonVide())
        {
            return true;
        }
        else
        {
            auto info = new QMessageBox{QMessageBox::Warning,"ERREUR PRUFER_ENCODE: ","Matrice vide !",QMessageBox::Ok};
            info->exec();
            return false;
        }
    }
    else
    {
        auto info = new QMessageBox{QMessageBox::Warning,"ERREUR PRUFER_ENCODE: ","Graphe oriente !",QMessageBox::Ok};
        info->exec();
        return false;
    }
}

bool MainWindow::verifiePruferDecode(const vector<int>& p)
{
    unsigned m = p[0];
    if(m != p.size()-1)
    {
        auto info = new QMessageBox{QMessageBox::Warning,"ERREUR PRUFER_DECODE: ","P n'est pas correctement saisi : p[0] contient le nombre total d'elements du tableau",QMessageBox::Ok};
        info->exec();
        return false;
    }
    else
    {
        int nb_max_sommets = m+2;
        for(unsigned i = 1 ; i <= m ; ++i)
        {
            if(p[i] <= 0 || p[i] > nb_max_sommets)
            {
                QString s = "P n'est pas correctement saisi : p[";
                s += s.fromStdString(std::to_string(i));
                s += "] est soit negatif soit superieur a ";
                s += s.fromStdString(std::to_string(p[0]+2));
                auto info = new QMessageBox{QMessageBox::Warning,"ERREUR PRUFER_DECODE: ",s,QMessageBox::Ok};
                info->exec();
                return false;
            }
        }
        return true;
    }
}

void MainWindow::charge()
{
    QString filters =   "Fichiers de Graph (*.graph);;"
                        "Tous les fichiers (*)";

    QString fileName = QFileDialog::getOpenFileName(this, windowTitle(), QDir::currentPath(), filters);

    if(fileName.isEmpty())
    {
        //Afficher message d'erreur
    }
    else if(!fileName.endsWith(".graph"))
    {
        //Afficher message d'erreur
    }
    else
    {
        std::ifstream ifs(fileName.toStdString());

        if(!ifs)
        {
            //Afficher message d'erreur
        }
        else
        {
            d_wg.loadFrom(ifs);
        }
    }
}

void MainWindow::saisieMatrice()
{
    menuMatrice->show();
}

void MainWindow::saisieFSAPS()
{
    menuFSAPS->show();
}

void MainWindow::ajoute()
{
    //Ajoute un noeud
    menuS->show();
}

void MainWindow::supprime()
{
    //Supprime un noeud
    menuSuppr->show();
}

void MainWindow::onClick_Distance()
{
    vector<vector<int>> mat_dist;
    if(verifieDistance())
    {
         mat_dist = d_wg.englobe_Distance();
         QString s = "";
         for(unsigned i = 0 ; i < mat_dist.size() ; ++i)
         {
             s += s.fromStdString(toStringVector(mat_dist[i])) + "\n";
         }
         auto info = new QMessageBox{QMessageBox::Information,"Resultat de l'algorithme des distances : ",s,QMessageBox::Ok};
         info->exec();
    }
}

void MainWindow::onClick_Rang()
{
    vector<int> rang;
    if(verifieRang())
    {
        rang = d_wg.englobe_Rang();
        QString s = "";
        s += s.fromStdString(toStringVector(rang));
        auto info = new QMessageBox{QMessageBox::Information,"Resultat du rang : ",s,QMessageBox::Ok};
        info->exec();
    }
}

void MainWindow::onClick_Tarjan()
{
    if(verifieTarjan())
    {
        vector<int> cfc, prem, pred, pilch, baseR, baseI;

        d_wg.englobe_Tarjan(cfc,pilch,pred,prem,baseR,baseI);
        QString s = "";
        s += "cfc : ";
        s += s.fromStdString(toStringVector(cfc));
        s += "\n";
        s += "prem : ";
        s += s.fromStdString(toStringVector(prem));
        s += "\n";
        s += "pilch : ";
        s += s.fromStdString(toStringVector(pilch));
        s += "\n";
        s += "pred : ";
        s += s.fromStdString(toStringVector(pred));
        s += "\n";
        s += "base reduite du graphe reduit : ";
        s += s.fromStdString(toStringVector(baseR));
        s += "\n";
        s += "base initiale du graphe : ";
        s += s.fromStdString(toStringVector(baseI));
        s += "\n";
        auto info = new QMessageBox{QMessageBox::Information,"Resultat de Tarjan : ",s,QMessageBox::Ok};
        info->exec();
    }
}

void MainWindow::onClick_Ordonnancement()
{
    menuOrd->show();
}

void MainWindow::onClick_Dijkstra()
{
    menuDijkstra->show();
}

void MainWindow::onClick_Dantzig()
{
    if(verifieDantzig())
    {
        if(d_wg.englobe_Dantzig())
        {
            QString s = "";
            s += "cout : ";
            for(unsigned i = 0 ; i < d_wg.getCouts().size() ; ++i)
            {
                s += s.fromStdString(toStringVector(d_wg.getCouts()[i]));
                s += "\n";
            }
            auto info = new QMessageBox{QMessageBox::Information,"Resultat Dantzig :",s,QMessageBox::Ok};
            info->exec();
        }
        else
        {
            auto info = new QMessageBox{QMessageBox::Warning,"Erreur Dantzig :","Presence d'un circuit absorbant : ",QMessageBox::Ok};
            info->exec();
        }
    }
}

void MainWindow::onClick_Kruskal()
{
    if(verifieKruskal())
    {
        d_wg.englobe_Kruskal();
    }
}

void MainWindow::onClick_Prufer_encode()
{
    if(verifiePruferEncode())
    {
        vector<int> p = d_wg.englobe_Prufer_encode();
        QString s;
        auto info = new QMessageBox{QMessageBox::Information,"Resultat du codage de Prufer : ",s.fromStdString(toStringVector(p)),QMessageBox::Ok};
        info->exec();
    }
}

void MainWindow::onClick_Prufer_decode()
{
    menuPruferD->show();
}

void MainWindow::onClickDistance_INFO()
{
    QString texte = "Cet algorithme a pour but de determiner l'ensemble des distances separant chaque sommet du graphe de l'ensemble des autres.\n"
                    "Il sert notamment des les problèmes de réseaux ou de trajet lorsq'un arc ne possède pas de poids.\n"
                    "Son resultat est donne sous la forme d'une matrice appelee matrice des distances.\n"
                    "La complexite de cet algorithme est en O( .. )";
    auto info = new QMessageBox{QMessageBox::Information,"Information : Algorithme des distances",texte,QMessageBox::Close};
    info->exec();
}

void MainWindow::onClickRang_INFO()
{
    QString texte = "Cet algorithme a pour but de determiner le rang de chaque sommet du graphe.\n"
                    "Le rang d'un sommet est la longueur d'une plus long chemin arrivant à lui.\n"
                    "On suppose que si le graphe admet un circuit alors les sommets concernes auront un rang egal a -1.\n"
                    "Il sert dans le domaine mathematique afin de determiner par exemple la dimension d'un graphe.\n"
                    "Son resultat est donne sous la forme d'un tableau contenant le rang de chaque sommet.\n"
                    "La complexite de cet algorithme est en O( .. )";
    auto info = new QMessageBox{QMessageBox::Information,"Information : Algorithme du rang",texte,QMessageBox::Close};
    info->exec();
}

void MainWindow::onClickTarjan_INFO()
{
    QString texte = "Cet algorithme a pour but de determiner le graphe reduit du graphe courant.\n"
                    "Le graphe reduit est sans circuit et ses sommets correspondent aux composantes fortement connexes du graphe.\n"
                    "Il est utilise pour simplifier des graphes complexes par exemple.\n"
                    "Son resultat est donne sous la forme d'un nouveau graphe (le graphe reduit).\n"
                    "De plus, les bases des deux graphes seront aussi indiquees.\n"
                    "Pour rappel, la base d'un graphe est l'ensemble des sommets necessaires pour qu'a partir de ce dernier, on puisse atteindre n'importe quel sommet.\n"
                    "La complexite de cet algorithme est en O( n )";
    auto info = new QMessageBox{QMessageBox::Information,"Information : Algorithme de Tarjan",texte,QMessageBox::Close};
    info->exec();
}

void MainWindow::onClickOrdonnancement_INFO()
{
    QString texte = "Cet algorithme a pour but de determiner l'ensemble des dates au plus tot et date au plus tard afin d'en deduire un (des) chemin(s) critique(s).\n"
                    "Un chemin critique est un chemin du graphe composes de sommets dont les durees de realisation ne peuvent etre retardees.\n"
                    "Il est notamment utilise dans les gestion de planification de taches afin d'etablir le meilleur planning possible.\n"
                    "Son resultat est donne sous la forme d'un nouveau graphe compose des sommets critiques et du(des) chemin(s) critique(s).\n"
                    "La complexite de cet algorithme est en O( .. )";
    auto info = new QMessageBox{QMessageBox::Information,"Information : L'ordonnancement",texte,QMessageBox::Close};
    info->exec();
}

void MainWindow::onClickDijkstra_INFO()
{
    QString texte = "Cet algorithme a pour but de determiner le(s) chemin(s) le(s) plus court(s) d'un graphe a partir d'un sommet de depart donne.\n"
                    "Il est utilise, comme la distance, pour determiner le plus court chemin entre deux points (villes, réseau, ...) mais en tenant compte des poids des arcs.\n"
                    "Pour lancer cet algorithme, il faut avoir saisi un cout dont les valeurs non determinees valent -1. De plus, le graphe doit etre oriente.\n"
                    "Son resultat est donne sous la forme de deux tableaux representant respectivement le poids minimal du chemin (d) et le chemin (pr).\n"
                    "La complexite de cet algorithme est en O( a + n x log(n) )";
    auto info = new QMessageBox{QMessageBox::Information,"Information : Algorithme de Dijkstra",texte,QMessageBox::Close};
    info->exec();
}

void MainWindow::onClickDantzig_INFO()
{
    QString texte = "Cet algorithme a pour but de determiner la matrice de cout la plus optimale possible en tenant compte des raccourcis proposes par le graphe compte tenu de ses poids.\n"
                    "Pour lancer cet algorithme, il faut avoir un graphe non oriente ainsi qu'une matrice des couts implementees de 0 si il n'y a pas d'arc ou si le poids vaut 0.\n"
                    "Son resultat est donne sous la forme d'une matrice appellee matrice des couts.\n"
                    "Il est utilise, comme la distance, pour determiner le plus court chemin entre deux points (villes, réseau, ...) mais en tenant compte des poids des arcs.\n"
                    "La complexite de cet algorithme est en O( N/V )";
    auto info = new QMessageBox{QMessageBox::Information,"Information : Algorithme de Dantzig",texte,QMessageBox::Close};
    info->exec();
}

void MainWindow::onClickKruskal_INFO()
{
    QString texte = "Cet algorithme a pour but de determiner un arbre recouvrant minimal d'un graphe non oriente.\n"
                    "Il est par exemple utilise pour simplifier des cablages.\n"
                    "Afin de lancer cet algorithme, le graphe doit etre non oriente. De plus, une matrice des couts doit etre implementees.\n"
                    "Son resultat est donne sous la forme d'un nouveau graphe.\n"
                    "La complexite de cet algorithme est en O( A log(A) )";
    auto info = new QMessageBox{QMessageBox::Information,"Information : Algorithme de Kruskal",texte,QMessageBox::Close};
    info->exec();
}

void MainWindow::onClickPrufer_encode_INFO()
{
    QString texte = "Cet algorithme a pour but de coder un graphe donne sous la forme d'un tableau de Prufer.\n"
                    "Il peut etre utile pour representer n'importe quel probleme sous forme d'un tableau d'entier unique.\n"
                    "Afin de lancer cet algorithme, le graphe saisi doit etre non oriente et tous les sommets ne doivent pas etre predeceeseurs et successeurs."
                    "Son resultat est donne sous la forme d'un tableau d'entier.\n"
                    "La complexite de cet algorithme est en O( .. )";
    auto info = new QMessageBox{QMessageBox::Information,"Information : Algorithme de Prufer [encodage]",texte,QMessageBox::Close};
    info->exec();
}

void MainWindow::onClickPrufer_decode_INFO()
{
    QString texte = "Cet algorithme a pour but de decoder un tableau de Prufer en graphe.\n"
                    "Son resultat est donne sous la forme d'un graphe.\n"
                    "La complexite de cet algorithme est en O( .. ).";
    auto info = new QMessageBox{QMessageBox::Information,"Information : Algorithme de Prufer [decodage]",texte,QMessageBox::Close};
    info->exec();
}

void MainWindow::onValiderAjout()
{
    vector<int> Pred;
    vector<int> Suc;

    vector<int> menuPred = menuS->getPred();
    vector<int> menuSuc = menuS->getSuc();

    int k1 = 1;
    int k2 = 1;


    int nbNoeud = d_wg.getAps()[0] + 2;

    for(int i = 0; i < nbNoeud; i++)
    {
        if(menuPred[k1] == i)
        {
            Pred.push_back(1);
            k1++;
        }
        else
            Pred.push_back(0);
        if(menuSuc[k2] == i)
        {
             Suc.push_back(1);
             k2++;
        }
        else
            Suc.push_back(0);
    }

    Noeud n{d_wg.getAps()[0] + 1};
    d_wg.ajouterNoeud(n, Pred, Suc);
}

void MainWindow::onValiderPruferDecode()
{
    if(verifiePruferDecode(menuPruferD->getP()))
    {
        d_wg.englobe_Prufer_decode(menuPruferD->getP());
    }
}

void MainWindow::onValiderDijkstra()
{
    vector<int> d, pr;
    if(verifieDijkstra(menuDijkstra->getSommet()))
    {
        d_wg.englobe_Dijkstra(menuDijkstra->getSommet(),d,pr);
        QString s = "";
        s += "distance : ";
        s += s.fromStdString(toStringVector(d));
        s += "\n";
        s += "pr : ";
        s += s.fromStdString(toStringVector(pr));
        auto info = new QMessageBox{QMessageBox::Information,"Resultat de Dijkstra",s,QMessageBox::Ok};
        info->exec();
    }
}

void MainWindow::onValiderOrdonnancement()
{
    if(verifieOrdonnancement())
    {
        vector<int> long_critique;
        d_wg.englobe_Ordonnancement(menuOrd->getDuree(),menuOrd->getFp(),menuOrd->getApp(),long_critique);
        QString s = "";
        auto info = new QMessageBox{QMessageBox::Information,"Resultat de l'ordonnancement : Longueur Critique",s.fromStdString(toStringVector(long_critique)),QMessageBox::Ok};
        info->exec();
    }
}

void MainWindow::onValideSaisieFSAPS()
{
    //A faire quand on pourra charger des graphes
    vector<int> FS = menuFSAPS->getFS();
    vector<int> APS = menuFSAPS->getAPS();
    Graph g{FS, APS, menuFSAPS->getCheckOriente()};
    if(menuFSAPS->getCheck())
    {
        vector<vector<int>> cout = menuFSAPS->getCout();
        g.setCout(cout);
    }
    cout<<g.getEst_oriente();
    d_wg.loadGraph(g);
}

void MainWindow::onValideSaisieMatrice()
{
    vector<vector<int>> matrice = menuMatrice->getMatrice();
    Graph g{matrice, menuMatrice->getCheckOriente()};
    if(menuMatrice->getCheck())
    {
        vector<vector<int>> cout = menuMatrice->getCout();
        g.setCout(cout);
    }
    cout<<g.getEst_oriente();
    d_wg.loadGraph(g);
}

