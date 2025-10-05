//AUTHOR: Jack Fontenot
//Assignment Title: Program 2
//Assignment Description: Maxima Set
//Due Date: 9/7/2025
//Date Created: 9/7/2025
//Date Last Modified: 9/7/2025

#include "maxima.h"
#include <iostream>
using namespace std;
Set maximaSet(Set s){
    if(s.Size() <= 1){
        return s;
    }

    Set L;
    Set G;

    if(s.Size() == 2){
        L.push(s.at(1));
        G.push(s.at(0));
    }else{
        L = s.low(s.median());
        G = s.high(s.median());
    }
    Set m1;
    m1 = maximaSet(L);
    Set m2;
    m2 = maximaSet(G);
    point q;
    q.x = m2.at(0).x;
    q.y = m2.at(0).y;

    for(int i = m1.Size() - 1; i >= 0 && m1.Size() > 0; --i){
        if(m1.at(i).x <= q.x && m1.at(i).y < q.y){
            m1.pop(m1.at(i));
        }
    }

    return mergeSet(m1, m2);
}

Set mergeSet(Set a, Set b){
    Set res;

    for(int i = 0; i < a.Size(); ++i){
        res.push(a.at(i));
    }

    for(int i = 0; i < b.Size(); ++i){
        res.push(b.at(i));
    }

    return res;
}
