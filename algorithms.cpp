#include "algorithms.h"

#include <QDebug>

bool Dantzig(vector<vector<int>>& c)
{
    //Initialisation
    int n = c[0][0];
    int k, i, j;
    double x;

    for(k = 1 ; k < n ; ++k)
    {
        for( i = 1 ; i <= k ; ++i)
        {
            for(j = 1 ; j <= k ; ++j)
            {
                if((x = c[i][j] + c[j][k+1]) < c[i][k+1])
                    c[i][k+1] = x;

                if((x = c[k+1][j] + c[j][i]) < c[k+1][i])
                    c[k+1][i] = x;
            }
            if(c[i][k+1] + c[k+1][i] < 0)
            {
                //cout<<"Presence d'un circuit absorbant passant par "<<i<<" et "<<k+1<<" ."<<endl;
                return false;
            }
        }
        for(i = 1 ; i <= k ; ++i)
            for( j = 1 ; j <= k ; ++j)
            {
                if( (x = c[i][k+1] + c[k+1][j]) < c[i][j])
                    c[i][j] = x;
            }
    }
    return true;
}

void demi_degre_interieur(const vector<int>& FS, const vector<int>& APS, vector<int> &DDI)
{
    DDI.resize(APS[0] + 1);
    DDI[0] = APS[0];
    for(int i = 1; i <= APS[0]; ++i)
    {
        DDI[i] = 0;
    }
    for(int i = 1; i < FS[0]; ++i)
    {
        if(FS[i] != 0)
            DDI[FS[i]]++;
    }
}

void descente_largeur(int r,const vector<int>& fs, const vector<int>& aps, vector<int>& dist)
{
    int nb_sommets = aps[0];
    int i = 0;
    int j = 1;
    int k = 0;
    int ifin;
    int s;
    int t;
    int it;
    //int* fil = new int[nb_sommets+1];
    vector<int> fil(nb_sommets+1);
    fil[0] = nb_sommets;
    dist.resize(nb_sommets+1);
    dist[0] = nb_sommets;
    fil[1] = r;

    for(int h = 1 ; h <= nb_sommets ; ++h)
    {
        dist[h] = -1;
    }
    dist[r] = 0;

    while(i<j) //Tq la file d'attente n'est pas vide
    {
        ++k;
        ifin = j;
        while(i<ifin) //On parcourt le bloc courant
        {
            ++i;
            s = fil[i];
            it = aps[s];
            t = fs[it];
            while(t>0) //On parcourt tous les successeurs de chaque sommet du bloc courant
            {
                if(dist[t] == -1) //Si le successeur du sommet courant n'est pas encore marqué
                {
                    ++j;
                    fil[j] = t; //On le place dans le bloc suivant en préparation et on lui affecte la distance courante
                    dist[t] = dist[fil[i]]+1;//dist[t] = k;//Variante : dist[t] = dist[fil[i]]+1;
                }
                t = fs[++it];
            }
        }
    }
}

void Dijkstra(const vector<int>& fs, const vector<int>& aps, const vector<vector<int>>& p, int s, vector<int> &d, vector<int> &pr)
{
        int ind;
        int i, j, k, v;
        int n = aps[0];
        int m = fs[0];
        pr.resize(n+1, 0);
        d.resize(n+1, 0);
        vector<int> inS(n+1);

        for(i = 1; i <= n; i++)
        {
            d[i] = p[s][i];
            inS[i] = 1;
            pr[i] = s;
        }

        d[s] = 0;
        inS[s] = 0;
        ind = n-1;
        while(ind > 0)
        {
            m = 100;
            for(i = 1; i <= n; i++)
            {
                if(inS[i] == 1)
                {
                    if(d[i] > 0 and d[i] < m)
                    {
                        m = d[i];
                        j = i;
                    }
                }
            }
            if(m == 100)
                    return;
            inS[j] = 0;
            --ind;
            k = aps[j];
            while(fs[k] != 0)
            {
                if(inS[fs[k]] == 1)
                {
                    v = d[j] + p[j][fs[k]];
                    if(d[fs[k]] == -1 or v < d[fs[k]])
                    {
                        d[fs[k]] = v;
                        pr[fs[k]] = j;
                    }
                }
                k++;
            }
        }
}

void empiler (int x, vector<int>& pilch)
{
    pilch[x] = pilch[0];
    pilch[0] = x;
}

void englobe_ordonnancement(const vector<int>& fs, const vector<int>& aps, const vector<int>& duree_taches, vector<int>& new_fs, vector<int>& new_aps)
{
    ///Initialisation :
    vector<int> file_pred;
    vector<int> adr_prem_pred;
    vector<int> file_pred_critique;
    vector<int> adr_prem_pred_critique;
    vector<int> longueur_critique;

    ///Tranformation de fs/pas --> fp/app :
    transforme_FS_APS_TO_FP_APP(fs, aps, file_pred, adr_prem_pred);

    Ordonnancement(file_pred, adr_prem_pred, duree_taches, file_pred_critique, adr_prem_pred_critique, longueur_critique);

    cout<<"Longueur critique : "<<endl;
    printVector(longueur_critique);
    cout<<endl;
    cout<<endl;

    ///Transformation de fp/app --> fs/aps :
    transforme_FP_APP_TO_FS_APS(file_pred_critique,adr_prem_pred_critique,new_fs,new_aps);

    cout<<"Nouveau FS & APS : "<<endl;
    printVector(new_fs);
    cout<<endl;
    printVector(new_aps);
}

void fortconnexe(const vector<int>& FS, const vector<int>& APS, vector<int>& cfc, vector<int>& pilch, vector<int>& pred, vector<int>& prem)
{
    int n = APS[0], p = 0;

   // qDebug() << "APS 0 : " << APS[0];
  //  qDebug() << "FS 0 : " << FS[0];

    cfc.clear();
    cfc.resize(n + 1);
    cfc[0] = n;

    pilch.clear();
    pilch.resize(n + 1);

    pred.clear();
    pred.resize(n + 1, 0);

    prem.clear();
    prem.reserve(n + 1);
    prem.push_back(0);

    vector<int> tarj;
    tarj.reserve(n + 1);
    vector<bool> entarj(n + 1, true);
    vector<int> num(n + 1, 0);
    vector<int> ro(n + 1, 0);

    int k = 0;

    pilch[0] = 0;

    for(int s = 1; s <= n; ++s)
    {
        if(num[s] == 0)
        {
            traversee(s, p, k, FS, APS, cfc, pilch, pred, prem, tarj, entarj, num, ro);
        }
    }

    prem[0] = k;
/*
    cout << "num:   "; printVector(num);
    cout << "ro:    "; printVector(ro);*/
}

void Kruskal(const Graph& g, Graph &t)
{
        //TRANSFORMATION DU GRAPH AVEC LA STRUCTURE VOULU
        typedef struct {
            int s;
            int t;
            double p;
        } arete;
        typedef struct {
            int n;
            int m;
            vector<arete> a;
        } graphe;

        arete ar;
        graphe graphReturn;
        vector<int> FS  = g.getFS();
        vector<int> APS = g.getAPS();
        //graphReturn.n = APS.size();
        graphReturn.n = APS[0];
        vector<vector<int>> cout = g.getCouts();
        int j = 1;
        int taille_a = 0;
        for(unsigned i = 1; i < APS.size(); i++)
        {
            while(FS[j] != 0)
            {
                int succ  = FS[j];
                int pred  = i;
                bool flag = true;
                int n = 0;
                while(flag && n < taille_a)
                {
                    if((succ == graphReturn.a[n].s && pred == graphReturn.a[n].t) || (succ == graphReturn.a[n].t && pred == graphReturn.a[n].s))
                    {
                         if(flag)
                         {
                             flag = false;
                         }
                    }
                    ++n;
                }
                if(flag)
                {
                    ar.s = succ;
                    ar.t = pred;
                    ar.p = cout[i][FS[j]];
                    graphReturn.a.push_back(ar);
                    ++taille_a;
                }
                j++;
            }
            j++;
        }
        graphReturn.m = graphReturn.a.size();

        //TRIE DU GRAPHE EN FONCTION DES COUTS ET DES ARETES
        arete tmp;
        for (int i = 0; i < graphReturn.m - 1; i++)
            for (int cpt = i + 1; cpt < graphReturn.m; cpt++)
                if ((graphReturn.a[cpt].p < graphReturn.a[i].p) || (graphReturn.a[cpt].p == graphReturn.a[i].p && graphReturn.a[cpt].s < graphReturn.a[i].t) || (graphReturn.a[cpt].p == graphReturn.a[i].p && graphReturn.a[cpt].t < graphReturn.a[i].t))
                {
                    tmp = graphReturn.a[cpt];
                    graphReturn.a[cpt] = graphReturn.a[i];
                    graphReturn.a[i] = tmp;
                }

        //INITIALISATION DES DONNEES
        int n = graphReturn.n;
        int *prem = new int[n + 1];
        int *pilch = new int[n + 1];
        int *cfc = new int[n + 1];
        int *NbElem = new int[n + 1];
        for(int i = 1; i <= n; i++)
        {
            prem[i] = i;
            pilch[i] = 0;
            cfc[i] = i;
            NbElem[i] = 1;
        }

        //KRUSKAL
        graphe GraphFinal;
        GraphFinal.a.resize(graphReturn.n-1);
        int x;
        int y;
        int i = 0; int cpt = 0;
        while(cpt < n-1)
        {
            arete ar = graphReturn.a[i];
            x = cfc[ar.s];
            y = cfc[ar.t];
            if(x != y)
            {
                GraphFinal.a[cpt++] = graphReturn.a[i];

                if(NbElem[i] < NbElem[cpt])
                {
                    int aux = i;
                    i = cpt;
                    cpt = aux;
                }
                int s = prem[cpt];
                cfc[s] = i;
                while(pilch[s] != 0)
                {
                    s = pilch[s];
                    cfc[s] = i;
                }
                pilch[s] = prem[i];
                prem[i] = prem[cpt];
                NbElem[i] += NbElem[cpt];
            }
            i++;
        }
        GraphFinal.n = graphReturn.n;
        GraphFinal.m = graphReturn.n - 1;

        vector<vector<int>> matriceCout(APS[0]+1);
        vector<vector<int>> matrice(APS[0]+1);
        for(unsigned i = 0; i < matrice.size(); i++)
        {
            matrice[i].resize(APS[0]+1);
            matriceCout[i].resize(APS[0]+1);
            for(unsigned j = 0; j < matrice[i].size(); j++)
            {
                matriceCout[i][j] = 0;
                matrice[i][j] = 0;
            }
        }

        for(unsigned i = 0 ; i < GraphFinal.a.size() ; ++i)
        {
            std::cout<<GraphFinal.a[i].s<<"-"<<GraphFinal.a[i].t<<"-"<<GraphFinal.a[i].p<<endl;
        }


/*
        for(unsigned i = 0; i < GraphFinal.a.size(); i++)
        {
            matriceCout[GraphFinal.a[i].s][GraphFinal.a[i].t] = GraphFinal.a[i].p;
            matrice[GraphFinal.a[i].s][GraphFinal.a[i].t] = 1;
        }

        for(unsigned i = 1 ; i < matrice.size() ; ++i)
        {
            printVector(matrice[i]);
        }
*/
        //t.setMatrice(matrice);
        //t.setCout(matriceCout);
}

void mat_distance(const vector<int>& FS, const vector<int>& APS, vector<vector<int>>& matriceDistance) {
    int n = APS[0];
    matriceDistance.resize(n + 1);
    matriceDistance[0].resize(2);

    for (int r = 1 ; r <= n ; r++) {
        descente_largeur(r,FS,APS,matriceDistance[r]);
    }
    matriceDistance[0][0] = n;
}

void Ordonnancement(const vector<int> file_pred, const vector<int> adr_prem_pred, const vector<int> duree_taches, vector<int>& file_pred_critique, vector<int>& adr_prem_pred_critique, vector<int>& longueur_critique)
{
    int n = adr_prem_pred[0];
    int m = file_pred[0];

    file_pred_critique.resize(m+1);
    adr_prem_pred_critique.resize(n+1);

    adr_prem_pred_critique[0] = n;

    longueur_critique.resize(n+1);
    longueur_critique[0] = n;

    int kc = 1; //Indice de la dernière place remplie dans fpc
    int t, lg; //la longueur lg de la tâche t
    longueur_critique[1] = 0;
    file_pred_critique[1] = 0; //Fin de la liste
    adr_prem_pred_critique[1] = 1;

    for(int s = 2 ; s <= n ; ++s)
    {
        //Calcul de lc[s] en fonction des prédecesseurs critiques de s
        longueur_critique[s] = 0;
        adr_prem_pred_critique[s] = kc+1; //Début de la liste des prédecesseurs critiques de s
        for(int k = adr_prem_pred[s] ; (t = file_pred[k]) != 0 ; ++k)
        {
            lg = longueur_critique[t] + duree_taches[t];
            if(lg >= longueur_critique[s])
            {
                if(lg > longueur_critique[s])
                {
                    longueur_critique[s] = lg; //Nouvelle lg candidate à être critique
                    kc = adr_prem_pred_critique[s] ;
                    file_pred_critique[kc] = t;
                }
                else //lg == lc[s]
                {
                    ++kc;
                    file_pred_critique[kc] = t;
                }
            }
        }
        ++kc;
        file_pred_critique[kc] = 0; //Fin de la liste des prédecesseurs critiques de s
    }
    file_pred_critique[0] = kc;
}

void printVector(const vector<int>& v)
{
    unsigned i = 0;
    cout << "[";
    for(i = 0; i < v.size() - 1; ++i)
    {
        cout << v[i] << ", ";
    }
    cout << v[i] << "]\n";
}

void Prufer_decode(const vector<int>& p, vector<vector<int>>& mat) {
    unsigned m = p[0];
    unsigned n = m + 2;
    vector<int> s(m + 3);

    mat.clear();
    mat.resize(n + 1);
    mat[0].resize(2);
    mat[0][0] = n;
    mat[0][1] = n + m;

    for(unsigned i = 1; i <= n; ++i) {
        mat[i].resize(n + 1, 0);
    }

    for(unsigned i = 1; i <= n; ++i) {
        s[i] = 0;
    }

    for(unsigned i = 1; i <= m; ++i) {
        ++s[p[i]];
    }

    for(unsigned i = 1; i <= m; ++i) {
        unsigned k = 1;
        while(s[k] != 0) ++k;

        mat[p[i]][k] = 1;
        mat[k][p[i]] = 1;

        s[k] = -1;
        --s[p[i]];
    }

    int k = -1;
    for(unsigned i = 1; i <= n; ++i) {
        if(s[i] == 0) {
            if(k == -1) {
                k = i;
            } else {
                mat[i][k] = 1;
                mat[k][i] = 1;
            }
        }
    }
}

void Prufer_encode(vector<vector<int>> mat, vector<int>& p) {
    unsigned n = mat[0][0];
    p.clear();
    p.resize(n - 1);
    p[0] = n - 2;

    for(unsigned i = 1; i <= n; ++i) {
        mat[i][0] = 0;
        for(unsigned j = 1; j <= n; ++j) {
            mat[i][0] += mat[i][j];
        }
    }

    for(unsigned k = 1; k <= n-2; ++k) {
        int i = 1, j = 1;
        while (mat[i][0] != 1) {
            ++i;
        }

        while (mat[i][j] != 1) {
            ++j;
        }

        p[k] = j;
        mat[i][j] = 0;
        mat[j][i] = 0;
        mat[i][0] = 0;
        --mat[j][0];
    }
}

void rang(vector<int>& rang, const vector<int>& fs, const vector<int>& aps)
{
        int n = aps[0];
        int s,rangActuel,h,t;
        rang.resize(n+1);
        vector<int> pilch(n+1);
        vector<int> prem(n+1);
        rang[0] = n;
        vector<int> ddi;
        demi_degre_interieur(fs, aps, ddi);

        //Initialisation à -1
        pilch[0] = 0;
        for(s = 1; s <= n; s++)
        {
            rang[s] = -1; // n : nombre de sommets de G represente l'infini
            if (ddi[s] == 0)
                empiler(s,pilch);
        }

        rangActuel = -1;
        s = pilch[0];
        prem[0] = s;

        while (pilch[0] > 0)
        {
            rangActuel++;
            pilch[0] = 0;
            while (s > 0)
            {
                rang[s] = rangActuel;
                h = aps[s];
                t = fs[h];
                while (t > 0)
                    {
                    ddi[t]--;
                    if (ddi[t] == 0)
                        empiler(t,pilch);
                    h++;
                    t=fs[h];
                }
                s = pilch[s];
            }
            s = pilch[0];
            prem[rangActuel+1] = s;
        }
}

void rangToString(const vector<int>& FS, const vector<int>& APS)
{
    // ON VA PAS SE MENTIR MAIS C'EST PAAAAS VRAIMENT UN TO_STRING QUOI

    vector<int> rangT;
    rang(rangT, FS, APS);

    cout<<"Rang : "<<endl;
    cout<<"APS : ";
    for(unsigned i = 0 ; i < APS.size(); i++)
        cout<<APS[i]<<", ";
    cout << endl;
    cout<<"FS : ";
    for(unsigned i = 0 ; i < FS.size(); i++)
        cout<<FS[i]<<", ";
    cout << endl;
    cout << "RangT : ";
    for(unsigned i = 0 ; i < rangT.size(); i++)
         cout<<rangT[i]<<", ";
    cout << endl;
}

void Tarjan(const vector<int>& FS, const vector<int>& APS)
{
    vector<int> cfc, pilch, pred, prem;
    fortconnexe(FS, APS, cfc, pilch, pred, prem);

    /*cout << "cfc:   "; printVector(cfc);
    cout << "pilch: "; printVector(pilch);
    cout << "pred:  "; printVector(pred);
    cout << "prem:  "; printVector(prem);

    cout << "FS:    "; printVector(FS);
    cout << "APS:   "; printVector(APS);
*/
}

void traversee(int s, int& p, int& k, const vector<int>& FS, const vector<int>& APS, vector<int>& cfc, vector<int>& pilch, vector<int>& pred, vector<int>& prem, vector<int>& tarj, vector<bool>& entarj, vector<int>& num, vector<int>& ro)
{
    ++p;
    num[s] = p;
    ro[s] = p;

    tarj.push_back(s);

    int i = APS[s];
    int t = FS[i];
    while(t != 0)
    {
        if(num[t] == 0)
        {
            pred[t] = i;
            traversee(t, p, k, FS, APS, cfc, pilch, pred, prem, tarj, entarj, num, ro);
        }

        if(entarj[t]){
            if(ro[t] < ro[s]) ro[s] = ro[t];
            else if(num[t] < ro[s] and entarj[t]) ro[s] = num[t];
        }

        ++i;
        t = FS[i];
    }

    if(ro[s] == num[s])
    {
        ++k;

        int u = 0;
        do
        {
            u = tarj.back();
            tarj.pop_back();
            entarj[u] = false;
            empiler(u, pilch);
            cfc[u] = k;
        } while(u != s);

        prem.push_back(pilch[0]);
        pilch[0] = 0;
    }
}

void transforme_FP_APP_TO_FS_APS(const vector<int>& fp, const vector<int>& app, vector<int>& fs, vector<int>& aps)
{
    int n = app[0];

    aps.clear();
    fs.clear();

    aps.reserve(n+1);
    aps.push_back(n);

    fs.reserve(fp[0]+1);
    fs.push_back(fp[0]);

    for(int i = 1; i <= n; ++i)
    {
        for(int j = 1; j <= fp[0]; ++j)
        {
            if(fp[j] == i)
            {
                unsigned k = 1;
                while(k < app.size() and app[k] <= j)
                {
                    ++k;
                }
                fs.push_back(k-1);
            }
        }
        fs.push_back(0);
    }

    aps.push_back(1);
    for(unsigned i = 1; i < fs.size()-1; ++i)
    {
        if(fs[i] == 0) aps.push_back(i+1);
    }
}

void transforme_FS_APS_TO_FP_APP(const vector<int>& fs, const vector<int>& aps, vector<int>& fp, vector<int>& app)
{
    int n = aps[0] ;
    app.push_back(n);
    fp.push_back(fs[0]);
    for(int i = 1 ; i <= n ; ++i)
    {
        app.push_back(fp.size());
        for(int j = 1 ; j <= fs[0] ; ++j)
        {
            if(fs[j] == i)
            {
                int k = 1;
                while(aps[k] <= j)
                {
                    k++;
                }
                fp.push_back(k-1);
            }
        }
        fp.push_back(0);
    }
}

int partition(vector<int>& t, int g, int d)
{
    //Sert pour le tri du tableau
    int m = g;
    for(int i = g+1 ; i <= d ; ++i)
    {
        if(t[i] < t[g])
        {
            ++m;
            std::swap(t[i],t[m]);
        }
    }
    std::swap(t[g],t[m]);
    return m;
}

void TrierTableau_QuickSort(vector<int>& tab, int g, int d)
{
    if(g<d)
    {
        int m = partition(tab,g,d);
        TrierTableau_QuickSort(tab,g,m-1);
        TrierTableau_QuickSort(tab,m+1,d);
    }
}

void versGrapheReduit(const vector<int>& cfc, const vector<int>& prem,const vector<int>& fs,const vector<int>& aps, vector<vector<int>>& mat)
{
    //On initialise correctement la matrice representant le futur graphe reduit
    mat.resize(prem[0]+1);
    mat[0].resize(2);
    mat[0][0] = prem[0];
    for(int i = 1; i <= prem[0] ; ++i)
            mat[i].resize(prem[0]+1,0);

    //On commence par l'ordre croissant des composantes
    bool est_deja_dans_composant = false;
    for(int composant = 1; composant <= prem[0] ; ++composant)
    {
        //On commence par chercher l'ensemble des sommets qui sont dans le composant courant
        for(int i = 1 ; i <= cfc[0] ; ++i)
        {
            //Si le sommet courant est dans la composante, on regarde tous ses successeurs
            if(cfc[i] == composant)
            {
                vector<int> est_deja; //Tableau qui nous renseigne sur le fait qu'une composante a deja ete trouvee (on ne la met pas deux fois)
                bool est_vide = true;
                est_deja.reserve(prem[0]); //Au maximum...
                //On commence a chercher les successeurs...
                int j = aps[i];
                while(fs[j] != 0) //Parcourt des successeurs
                {
                    //Le composant du successeurs
                    int comp_suiv = cfc[fs[j]];
                    if(!est_vide) //Si est_deja n'est pas vide
                    {
                        //On regarde si la composante trouvee est deja presente
                        for(unsigned k = 0 ; k < est_deja.size() ; ++k)
                        {
                            //Si elle est deja ou que le successeur est en fait dans la meme composante
                            if(comp_suiv == est_deja[k] || comp_suiv == composant)
                                est_deja_dans_composant = true;
                        }
                    }
                    //Si la comoosante n'est pas encore dans est_deja
                    if(!est_deja_dans_composant)
                    {
                        if(composant != comp_suiv)//Dans le cas ou c'est vide, il faut verifier cette condition avant de l'ajouter
                        {
                            est_deja.push_back(comp_suiv);
                            est_vide = false;
                        }
                    }
                    //On regarde le successeur suivant
                    ++j;
                    est_deja_dans_composant = false;
                }
                //Si le tableau est_deja contient plus d'un élément
                if(est_deja.size() > 1)
                {
                    TrierTableau_QuickSort(est_deja, 0, est_deja.size());
                }
                //Si est_deja n'est pas vide (dans le cas ou aucun des sommets de la composante
                //n'a de successeur autre que des sommets appartenant a cette composante)
                if(!est_vide)
                {
                    unsigned cpt = 0;
                    unsigned k = 1;
                    //On met les composantes trouvees dans la matrice en tant que successeur de la composante courante
                    while(cpt < est_deja.size() && k < mat[composant].size())
                    {
                        if(est_deja[cpt] == (int)k)
                        {
                            mat[composant][k] = 1;
                            ++cpt;
                        }
                        ++k;
                    }
                }
                //On enleve tous les elements du tableau
                est_deja.clear();
            } // fin du if
        }//fin du for i
    } //fin des composantes

    //A ce stade l'integralite de la matrice est remplie sauf la cellule contenant le nombre d'arcs et de sommets.
    //On parcourt la matrice definitive pour determiner le nombre d'arcs pour en deduire mat[0][1]
    int nb_arcs = 0;
    for(unsigned i = 1 ; i < mat.size() ; ++i)
        for(unsigned j = 1 ; j < mat[i].size() ; ++j)
            if(mat[i][j] == 1)
                nb_arcs++;

    mat[0][1] = nb_arcs;
} //fin de la fonction

//Fonction du prof -- Faux pour le moment
void Graph_reduit(const vector<int>& prem,const vector<int>& pilch,const vector<int>& cfc,const vector<int>& fs, const vector<int>& aps,vector<int>&fsr, vector<int>& apsr)
{
     int s, kr = 1, nb_comp = prem[0];
     vector<bool> deja_mis(nb_comp+1);
     fsr.resize(fs[0]+1);
     apsr.resize(nb_comp+1);
     apsr[0] = kr;
     for(int i = 1 ; i < nb_comp ; i++)
     {
         apsr[i]= kr;
         for(int j = 1; j <= nb_comp ; j++)
         {
            deja_mis[j]=false;
         }
         deja_mis[i] = true;
         s = prem[0];
         while(s!=0)
         {
             for(int t = aps[s] ; fs[t] != 0 ; t++)
             {
                 if(deja_mis[cfc[fs[t]]] == false)
                 {
                     fsr[kr] = cfc[fs[t]];
                     kr++;
                     deja_mis[cfc[fs[t]]] = true;
                 }
             }
            s = pilch[s];
         }
         fsr[kr] = 0;
         kr++;
     }
     fsr[0] = kr-1;
     deja_mis.clear();
}

void base_Greduit(const vector<int>& fsR, const vector<int>& apsR, vector<int>& baseR_GrapheR)
{
    int nb_sommets = apsR[0];
    baseR_GrapheR.resize(nb_sommets+1);
    vector<int> ddir(nb_sommets+1);
    for(int i = 0 ; i <= nb_sommets ; ++i)
        ddir[i] = 0;

    for(int kr = 1 ; kr <= fsR[kr] ; kr++)
        ddir[fsR[kr]]++;


    int nb = 0;
    for(int c = 1 ; c <= nb_sommets ; c++)
        if (ddir[c] == 0)
            baseR_GrapheR[++nb] = c;

    baseR_GrapheR[0] = nb;
}

void edition_bases(const vector<int>& prem, const vector<int>& pilch, const vector<int>& baseR, vector<int>& baseInitiale)
{
    int nb = baseR[0];                  // Nombre de CFC de l’unique base du graphe réduit
    baseInitiale.resize(nb+1);            // pile qui mémorise les sommets des bases du graphe initial
    baseInitiale[0] = nb;
    int p = 1;
    int som = prem[baseR[1]];           // premier sommet de la première CFC
    while(p >= 1)
    {
        if((p<= nb) && (som != 0))
        {
             baseInitiale[p] = som;
             p++;
             if(p <= nb)
                 som = prem[baseR[p]];
             //else printVector(Base);    // Affiche le contenu du tableau Base contenant les sommets d’une base du graphe initial
        }
        else
        {
             p--;
             som = pilch[baseInitiale[p]];
        }
    }
}
string toStringVector(const vector<int>& tab)
{
    string s = "[ ";
    for(unsigned i = 0 ; i < tab.size() ; ++i)
    {
        s += std::to_string(tab[i]) + ", ";
    }
    s += "]";
    return s;
}









