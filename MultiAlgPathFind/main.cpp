//Author: Jack Fontenot
//Assignment Title: Program 5
//Assignment Description: multi algo path finder
//Due Date: 10/12/2025
//Date Created: 10/11/2025
//Date Last Modified: 10/11/2025

#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <ctime>

using namespace std;
struct edge;

struct point{
    int name;
    point* pred;
    vector<edge*> edges;
    int d;
    char stat = 'U';

    point(int name): name(name){}
};

struct edge{
    point* s;
    point* d;
    int w;

    edge(point* s, point* d, int w){
        this->s = s;
        this->d = d;
        this->w = w;
    }

    //gets the adjacent point to a
    point* getO(point* a){
        point* res = s;

        if(a == s){
            res = d;
        }

        return res;
    }

    //checks if edge is outgoing from a
    bool isOut(point* a){
        bool flag = true;

        if(a == d){
            flag = false;
        }

        return flag;
    }
};

//comparator for priority q
struct comp{
    bool operator()(const point* a, const point* b){
        return a->d > b->d;
    }
};

//directed graph Djikstra
void djikstraD(vector<vector<point*>>&, point*, int&, int&);

//undirected graph Djikstra
void djikstraU(vector<vector<point*>>&, point*, int&, int&);

//Bellman-Ford Algo
bool BF(vector<vector<point*>>&, point*, int&, int&, vector<edge*>&);

//DFS for DAG shortest paths
void DFS(vector<vector<point*>>&, point*, vector<point*>&);

//DAG shortest paths
void sDAG(vector<vector<point*>>&, point*, vector<point*>&, int&, int&);

//for checking if a vertex has already been created
bool contains(vector<int>&, int&);

//for checking if a point has been taken out of the q
bool contains(vector<point*>&, point*);

int main()
{
    int n, m;
    int a = 0;
    int aS = 0;
    int v1, v2, w;
    char type;
    int algo;
    int source;
    int normalizer;
    bool neg = false;
    vector<vector<point*>> g;
    vector<point*> ranks;
    vector<edge*> edgeH;
    vector<int> nums;
    point* p1 = nullptr;
    point* p2 = nullptr;
    edge* e = nullptr;
    bool bf = true;

    clock_t start = clock();
    clock_t stop;
    double time;

    cin >> n >> m;

    //fill the list with n vertices
    for(int i = 0; i < n ; ++i){
        vector<point*> filler;
        g.push_back(filler);
    }

    //m edges
    for(int i = 0; i < m; ++i){
        cin >> v1 >> v2 >> w;
        if(w < 0){
            neg = true;
        }

        if(i == 0){
            normalizer = v1;
        }

        v1 -= normalizer;
        v2 -= normalizer;

        //first input
        if(i == 0 && v1 != v2){
            nums.push_back(v1);
            nums.push_back(v2);

            p1 = new point(v1);
            p2 = new point(v2);

            e = new edge(p1, p2, w);
            //edge holder for BF
            edgeH.push_back(e);
            p1->edges.push_back(e);

            g.at(v1).push_back(p1);
            g.at(v1).push_back(p2);

            g.at(v2).push_back(p2);

            //input 2+
        }else if(v1 != v2){
            if(!contains(nums, v1)){
                p1 = new point(v1);
                g.at(v1).push_back(p1);
            }

            if(!contains(nums, v2)){
                p2 = new point(v2);
                g.at(v2).push_back(p2);
            }

            e = new edge(g.at(v1).front(), g.at(v2).front(), w);

            edgeH.push_back(e);
            g.at(v1).front()->edges.push_back(e);
            g.at(v2).front()->edges.push_back(e);

            g.at(v1).push_back(g.at(v2).front());
            g.at(v2).push_back(g.at(v1).front());
        }
    }

    cin >> source;
    source -= normalizer;

    cout << "Treat graph as (D)irected or (U)ndirected? [D/U]: ";
    cin >> type;
    cout << type << endl;

    cout << "Choose algorithm: ";
    cout << "(1) Dijkstra  (2) Bellman-Ford(3) DAG Shortest Paths: ";
    cin >> algo;
    cout << algo << endl;

    if(!(algo == 1 && neg)){
        cout << "Algorithm: ";
        if(algo == 1){
            cout << "Dijkstra";
        }else if(algo == 2){
            cout << "Bellman-Ford";
        }else if(algo == 3){
            cout << "DAG Shortest Paths";
        }
        cout << endl;

        cout << "Source: ";
        cout << source << endl;

        for(size_t i = 0; i < g.size(); ++i){
            if(g.at(i).front()->name == source){
                p1 = g.at(i).front();
            }
        }

        if(algo == 1){
            if(type == 'U'){
                //start = clock();
                djikstraU(g, p1, a, aS);
                stop = clock();
            }else{
                //start = clock();
                djikstraD(g, p1, a, aS);
                stop = clock();
            }
        }else if(algo == 2){
            //start = clock();
            bf = BF(g, p1, a, aS, edgeH);
            stop = clock();
            if(!bf){
                cout << "Negative-weight cycle detected. "
                     << "Shortest paths undefined." << endl;
            }
        }else if(algo == 3){
            //start = clock();
            sDAG(g, p1, ranks, a, aS);
            stop = clock();
        }

        time = (1000.0 * ((double)(stop - start)))/(CLOCKS_PER_SEC/1000.0);

        cout << "Vertex  Distance  Predecessor" << endl;
        for(size_t i = 0; i < g.size(); ++i){
            cout << setw(6) << g.at(i).front()->name;
            cout << setw(10) << g.at(i).front()->d;
            cout << setw(13) << g.at(i).front()->pred->name;
            cout << endl;
        }

        cout << "Runtime (ms): " << fixed << setprecision(3) << time << endl;
        cout << "Relaxations: attempts=" << a << ", successes=" << aS << endl;
    }else{
        cout << "Warning: negative edge weights present; ";
        cout << "Dijkstra’s algorithm is invalid on such graphs." << endl;
        cout << "Please choose Bellman-Ford (2)." << endl;
    }


    return 0;
}

//directed graph Djikstra
void djikstraD(vector<vector<point*>>& g, point* s, int& a, int& aS){
    priority_queue<point*, vector<point*>, comp> q;
    point* u = nullptr;
    edge* e = nullptr;
    point* v = nullptr;
    vector<point*> pop;

    for(size_t i = 0; i < g.size(); ++i){
        //set D[v] to infinity
        g.at(i).front()->d = 1000000;
    }

    //set source predecessor and D[s]
    s->d = 0;
    s->pred = new point(-1);

    for(size_t i = 0; i < g.size(); ++i){
        //set priority q
        q.push(g.at(i).front());
    }

    while(!q.empty()){
        u = q.top();
        q.pop();
        //add it to popped list
        pop.push_back(u);
        for(size_t i = 0; i < u->edges.size(); ++i){
            e = u->edges.at(i);
            //check if outgoing edge
            if(e->isOut(u)){
                v = e->getO(u);
                a++;
                if(!contains(pop, v)){
                    if(u->d + e->w < v->d){
                        v->d = u->d + e->w;
                        v->pred = u;
                        q.push(s);
                        q.pop();
                        aS++;
                    }
                }
            }
        }
    }

    a++;
}

//undirected graph Djikstra
void djikstraU(vector<vector<point*>>& g, point* s, int& a, int& aS){
    priority_queue<point*, vector<point*>, comp> q;
    point* u = nullptr;
    edge* e = nullptr;
    point* v = nullptr;
    vector<point*> pop;

    for(size_t i = 0; i < g.size(); ++i){
        //set D[v] to infinity
        g.at(i).front()->d = 1000000;
    }

    //set source predecessor and D[s]
    s->d = 0;
    s->pred = new point(-1);

    for(size_t i = 0; i < g.size(); ++i){
        //set priority q
        q.push(g.at(i).front());
    }

    while(!q.empty()){
        u = q.top();
        q.pop();
        //add it to popped list
        pop.push_back(u);
        for(size_t i = 0; i < u->edges.size(); ++i){
            e = u->edges.at(i);
            v = e->getO(u);
            a++;
            if(!contains(pop, v)){
                if(u->d + e->w < v->d){
                    v->d = u->d + e->w;
                    v->pred = u;

                    //for making sure the priority q reorders
                    q.push(s);
                    q.pop();

                    aS++;
                }
            }
        }
    }

    a++;
}

//Bellman-Ford Algo
bool BF(vector<vector<point*>>& g, point* s,int& a,int& aS,vector<edge*>& es){
    point* u = nullptr;
    point* v = nullptr;
    edge* e = nullptr;
    bool flag = true;

    for(size_t i = 0; i < g.size(); ++i){
        //set D[v] to infinity
        g.at(i).front()->d = 1000000;
    }

    //set source predecessor and D[s]
    s->d = 0;
    s->pred = new point(-1);

    for(size_t i = 1; i < g.size() - 1; ++i){
        for(size_t j = 0; j < es.size(); ++j){
            a++;
            e = es.at(j);
            u = e->s;
            v = e->d;
            if(u->d + e->w < v->d){
                v->d = u->d + e->w;
                v->pred = u;
                aS++;
            }
        }
    }

    //check for negative cycle
    for(size_t i = 0; i < es.size(); ++i){
        e = es.at(i);
        u = e->s;
        v = e->d;
        if(u->d + e->w < v->d){
            flag = false;
            a++;
            aS++;
            v->d = u->d + e->w;
            v->pred = u;
        }
    }

    return flag;
}

//check if a point has already been created
bool contains(vector<int>& nums, int& n){
    bool flag = false;

    for(size_t i = 0; i < nums.size(); ++i){
        if(nums.at(i) == n){
            flag = true;
        }
    }

    if(!flag){
        nums.push_back(n);
    }

    return flag;
}

//shortest path DAG algo
void sDAG(vector<vector<point*>>& g, point* s, vector<point*>& ranks,
          int& a, int& aS){
    point* v = nullptr;
    point* z = nullptr;
    edge* e = nullptr;
    DFS(g, s, ranks);
    int vSize = static_cast<int>(ranks.size());

    //set source predecessor
    s->pred = new point(-1);

    for(int i = vSize - 1; i >= 0; --i){
        //set D[v] to infinity
        v = ranks.at(i);
        v->d = 1000000;
    }

    //set source distance
    s->d = 0;

    for(int i = vSize - 1; i > 0; --i){
        v = ranks.at(i);
        for(size_t j = 0; j < v->edges.size(); ++j){
            e = v->edges.at(j);
            //check if its an outgoing edge
            if(e->isOut(v)){
                z = e->getO(v);
                a++;
                if(v->d + e->w < z->d){
                    z->d = v->d + e->w;
                    z->pred = v;
                    aS++;
                }
            }
        }
    }
    aS--;
}

//Depth first search for sDAG
void DFS(vector<vector<point*>>& g, point* s, vector<point*>& ranks){
    point* v = nullptr;
    edge* e = nullptr;
    s->stat = 'A';

    for(size_t i = 0; i < s->edges.size(); ++i){
        e = s->edges.at(i);
        if(e->isOut(s)){
            v = e->d;
            if(v->stat == 'U'){
                v->pred = s;
                DFS(g, v, ranks);
            }
        }
    }

    ranks.push_back(s);
    s->stat = 'C';
}

//for checking if a point has been taken out of the q
bool contains(vector<point*>& points, point* p){
    bool flag = false;

    for(size_t i = 0; i < points.size(); ++i){
        if(points.at(i) == p){
            flag = true;
        }
    }

    return flag;
}

