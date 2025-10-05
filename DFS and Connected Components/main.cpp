//Author: Jack Fontenot
//Assignment Title: Program 4
//Assignment Description: Biconnected Components
//Due Date: 10/5/2025
//Date Created: 9/27/25
//Date Last Modified: 10/5/2025

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct edge;

struct point{
    int name;
    char stat;
    point* parent;
    bool isB;
    bool isA;

    vector<edge*> edges;

    point(): name(-1), stat('U'), parent(nullptr), isB(0), isA(0){}
    point(int n): name(n), stat('U'), parent(nullptr), isB(0), isA(0){}

    size_t size(){
        return edges.size();
    }

};

struct edge{
    point* a;
    point* b;
    char eStat;

    edge(point* a, point* b){
        if(a->name > b->name){
            this->a = b;
            this->b = a;
        }else{
            this->a = a;
            this->b = b;
        }
        this->a->isA = true;
        this->b->isB = true;
        eStat = '\n';
    }

    edge(){
        a = new point();
        b = new point();
        eStat = '\n';
    }

    void setS(char c){
        eStat = c;
    }

    char getS(){
        return eStat;
    }

    point* getO(point* u){
        point* res;

        if(u == a){
            res = b;
        }else{
            res = a;
        }

        return res;
    }
};

//used to check if an input point has already been created
bool contains(vector<int>, int);

//used to check if a biconnected component has been added already
bool contains(vector<vector<edge*>>&, edge*);

//recursive DFS
void DFS(vector<vector<point*>>&, point*, stack<edge*>&,
         vector<edge*>&, vector<point*>&);

//find biconnected components
vector<vector<edge*>> linkComponents(vector<vector<point*>>&,
                                     stack<edge*>, vector<edge*>&,
                                     vector<point*>&);
//returns the edge of 2 points if they are incidental on the same edge
edge* edgeOf(point*, point*);

//checks if a point is an articulation point
bool isAP(point*);

int main()
{
    vector<vector<point*>> g;
    vector<vector<edge*>> F;
    vector<int> nums;
    stack<edge*> sE;
    vector<edge*> backE;
    vector<point*> ranks;
    int n;
    int m;
    int in1, in2;

    cin >> n;
    cin >> m;

    for(int i = 0; i < n; ++i){
        vector<point*> filler;
        g.push_back(filler);
    }

    for(int i = 0; i < m; ++i){

        cin >> in1;
        cin >> in2;

        if(i == 0 && in1 != in2){
            point* p1 = new point(in1);
            point* p2 = new point(in2);

            g.at(in1).push_back(p1);
            g.at(in1).push_back(p2);
            g.at(in2).push_back(p2);
            g.at(in2).push_back(p1);

            nums.push_back(in1);
            nums.push_back(in2);

            edge* e = new edge(p1, p2);
            p1->edges.push_back(e);
            p2->edges.push_back(e);
        }else if(in1 != in2){
            if(!(contains(nums, in1))){
                point* p1 = new point(in1);
                g.at(in1).push_back(p1);

                nums.push_back(in1);
            }

            if(!(contains(nums, in2))){
                point* p2 = new point(in2);
                g.at(in2).push_back(p2);

                nums.push_back(in2);
            }

            g.at(in1).push_back(g.at(in2).front());
            g.at(in2).push_back(g.at(in1).front());

            edge* e = new edge(g.at(in1).front(), g.at(in2).front());
            g.at(in1).front()->edges.push_back(e);
            g.at(in2).front()->edges.push_back(e);
        }


    }

    DFS(g,g.at(0).front(), sE, backE, ranks);

    F = linkComponents(g, sE, backE, ranks);

    cout << "Biconnected components: " << endl;
    for(size_t i = 0; i < F.size(); ++i){
        cout << "Component " << i+1 << ": ";
        for(size_t j = 0; j < F.at(i).size(); ++j){
            cout << "(" << F.at(i).at(j)->a->name << ", " <<
            F.at(i).at(j)->b->name << ") ";
        }
        cout << endl;
    }

    cout << endl;
    cout << "Articulation Points: " << endl;
    for(size_t i = ranks.size()-1; i >= 0 && i < ranks.size(); --i){
        if(isAP(ranks.at(i))){
            cout << ranks.at(i)->name << endl;
        }
    }

    return 0;
}


//recursive DFS
void DFS(vector<vector<point*>>& g, point* u, stack<edge*>& sE,
         vector<edge*>& backE, vector<point*>& ranks){
    u->stat = 'A';

    for(size_t i = 0; i < u->size(); ++i){
        point* v = u->edges.at(i)->getO(u);
        if(v->stat == 'U'){
            u->edges.at(i)->setS('t');
            v->parent = u;
            DFS(g, v, sE, backE, ranks);
            sE.push(u->edges.at(i));
        }else if(u->edges.at(i)->eStat != 't'){
            if(v->stat == 'A'){
                u->edges.at(i)->setS('b');
                backE.push_back(u->edges.at(i));
            }else{
                u->edges.at(i)->setS('c');
            }
        }
    }

    ranks.push_back(u);

    u->stat = 'C';
}

//find biconnected components
vector<vector<edge*>> linkComponents(vector<vector<point*>>& g,stack<edge*>sE,
                                     vector<edge*>& backE,
                                     vector<point*>& ranks){
    vector<vector<edge*>> F;
    vector<vector<edge*>> res;
    stack<edge*> s = sE;
    point* v = nullptr;
    point* u = nullptr;

    for(size_t i = s.size(); i > 0; --i){
        edge* f = s.top();
        f->eStat = 'u';

        vector<edge*> temp;
        temp.push_back(f);

        F.push_back(temp);

        s.pop();
    }

    for(size_t i = 0; i < ranks.size(); ++i){
        v = ranks.at(ranks.size()-i-1);

        for(size_t j = 0; j < backE.size(); ++j){
            edge* e = backE.at(j);
            if(e->a == v){
                vector<edge*> temp;
                temp.push_back(e);
                F.push_back(temp);

                u = e->b;

                while(u != v && u->parent != nullptr){
                    edge* f = edgeOf(u, u->parent);
                    if(f != nullptr){
                        F.back().push_back(f);
                        if(f->eStat == 'u'){
                            f->eStat = 'l';
                            u = u->parent;
                        }else{
                            u = v;
                        }
                    }
                }
            }
        }
    }

    for(size_t i = F.size() - 1; i >= 0 && i < F.size(); --i){
        if(i == F.size() - 1){
            res.push_back(F.at(i));
        }else{
            if(!contains(res, F.at(i).front())){
                res.push_back(F.at(i));
            }
        }
    }

    return res;
}

//used to check if an input point has already been created
bool contains(vector<int> f, int x){
    bool flag = false;

    for(size_t i = 0; i < f.size(); ++i){
        if(f.at(i) == x){
            flag = true;
        }
    }

    return flag;
}

//returns the edge of 2 points if they are incidental on an edge
edge* edgeOf(point* u, point* v){
    edge* res = nullptr;

    for(size_t i = 0; i < u->edges.size(); ++i){
        if(u->edges.at(i)->a == v || u->edges.at(i)->b == v){
            res = u->edges.at(i);
        }
    }

    return res;
}

//used to check if a biconnected component has been added already
bool contains(vector<vector<edge*>>& f, edge* e){
    bool flag = false;

    for(size_t i = 0; i < f.size(); ++i){
        for(size_t j = 0; j < f.at(i).size(); ++j){
            if(f.at(i).at(j) == e){
                flag = true;
            }
        }
    }

    return flag;
}

//checks if a point is an articulation point
bool isAP(point* v){
    bool flag = true;

    if(!v->isA || !v->isB || v->edges.size() < 2){
        flag = false;
    }else{
        for(size_t i = 0; i < v->edges.size() - 1; ++i){
            point* o;
            o = v->edges.at(i)->getO(v);
            point* o1;
            o1 = v->edges.at(i+1)->getO(v);
            for(size_t j = 0; j < o->edges.size(); ++j){
                if(o->edges.at(j)->getO(o) == o1 && !(o->name > v->name)){
                    flag = false;
                }
            }
        }
    }

    return flag;
}
