//AUTHOR: Jack Fontenot
//Assignment Title: Program 2
//Assignment Description: Maxima Set
//Due Date: 9/7/2025
//Date Created: 9/7/2025
//Date Last Modified: 9/7/2025

#include "graphics.h"

using namespace std;

void display(Set s, Set m){
    char c[200][200];
    int y1;
    int x1;

    for(int i = 0; i < 200; ++i){
        for(int j = 0; j < 200; ++j){
            c[i][j] = '.';
        }
    }

    for(int i = 0; i < s.Size(); ++i){
        y1 = 200 - s.at(i).y;
        x1 = s.at(i).x;
        c[y1][x1] = 'o';
    }

    for(int i = 0; i < m.Size(); ++i){
        y1 = 200 - m.at(i).y;
        x1 = m.at(i).x;
        c[y1][x1] = '*';
    }

    cout << "Visualization: " << endl;
    for(int i = 0; i < 200; ++i){
        for(int j = 0; j < 200; ++j){
            cout << c[i][j];
        }
        cout << endl;
    }
}
